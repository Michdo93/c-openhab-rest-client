"""
Generates the REST functions of c-openhab-rest-client from python-openhab-rest-client.

The Python library is the reference: every method of a REST class is translated
statement by statement (same endpoint, headers, query parameters, body, status
handling and messages). Python values become cJSON values handled by the runtime in
src/py_rt.c. Only a small, regular subset of Python is supported; anything else
raises an error so that nothing is translated silently wrong.

Naming: Items.getItems -> openhab_items_getItems, ThingTypes.getThingType ->
openhab_thing_types_getThingType. Required Python parameters stay positional; optional
ones are named arguments in C99 style (designated initializers behind a macro):

    cJSON* r = openhab_items_getItems(client, .tags = "Light", .fields = "name,state");

Usage: python3 py2c.py <path to python-openhab-rest-client/openhab> <repository root>
       python3 py2c.py --readme <path>   (method tables for README.md)
"""
import ast
import glob
import json
import os
import re
import sys

SKIP_FILES = ("Async", "__", "Client", "SSE")
C_KEYWORDS = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double",
              "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long",
              "register", "restrict", "return", "short", "signed", "sizeof", "static", "struct",
              "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "errno"}
NAME_TYPES = {"language": "str", "prefix": "str", "typeFilter": "str", "moduleTypeUID": "str",
              "channelTypeUID": "str", "itemType": "str", "tags": "str",
              "summary": "bool", "staticDataOnly": "bool"}


class Unsupported(Exception):
    pass


def snake(cls):
    """Items -> items, ThingTypes -> thing_types, UI -> ui, UUID -> uuid."""
    if cls.isupper():
        return cls.lower()
    return re.sub(r"(?<!^)(?=[A-Z])", "_", cls).lower()


def cstr(s):
    out = json.dumps(s, ensure_ascii=False)
    return out.replace("??", "?\\?")


def ptype(arg, default):
    """Python type of a parameter: str, bool, int, float, json."""
    if arg.annotation is not None:
        a = ast.unparse(arg.annotation)
        return {"str": "str", "bool": "bool", "int": "int", "float": "float",
                "dict": "json", "list": "json"}.get(a) or (_ for _ in ()).throw(
            Unsupported(f"annotation {a}"))
    if arg.arg in NAME_TYPES:
        return NAME_TYPES[arg.arg]
    if isinstance(default, ast.Constant):
        v = default.value
        if isinstance(v, bool):
            return "bool"
        if isinstance(v, str):
            return "str"
        if isinstance(v, int):
            return "int"
    return "json"


class Method:
    def __init__(self, cls, fn):
        self.cls, self.fn, self.name = cls, fn, fn.name
        a = fn.args
        args = a.args[1:]
        defaults = [None] * (len(args) - len(a.defaults)) + list(a.defaults)
        self.params = []   # (name, type, default node or None, required)
        for arg, d in zip(args, defaults):
            if arg.arg in C_KEYWORDS:
                raise Unsupported(f"{cls}.{fn.name}: parameter {arg.arg} is a C keyword")
            self.params.append((arg.arg, ptype(arg, d), d, d is None))
        self.private = fn.name.startswith("_")
        self.stream = False

    @property
    def cname(self):
        return f"openhab_{snake(self.cls)}_{self.name}"

    @property
    def impl(self):
        return f"{snake(self.cls)}_{self.name.lstrip('_')}_impl"

    @property
    def required(self):
        return [p for p in self.params if p[3]]

    @property
    def optional(self):
        return [p for p in self.params if not p[3]]


def always_returns(stmts):
    for s in stmts:
        if isinstance(s, (ast.Return, ast.Raise)):
            return True
        if isinstance(s, ast.If) and s.orelse and always_returns(s.body) and always_returns(s.orelse):
            return True
        if isinstance(s, ast.Try) and always_returns(s.body) and \
                all(always_returns(h.body) for h in s.handlers):
            return True
    return False


class Translator:
    def __init__(self, method, methods):
        self.m, self.methods = method, methods
        self.where = f"{method.cls}.{method.name}"
        self.params = {p[0] for p in method.params}
        self.trys = []          # label numbers of the enclosing try blocks
        self.counter = 0
        self.errname = None     # name of the exception variable in an except block

    def fail(self, what):
        raise Unsupported(f"{self.where}: {what}")

    # expressions: (C code, kind) – kind "obj" = cJSON*, "bool" = int, "stream" = openhab_sse_t*
    def cond(self, n):
        code, kind = self.expr(n)
        return code if kind == "bool" else f"py_truthy({code})"

    def obj(self, n):
        code, kind = self.expr(n)
        if kind == "bool":
            return f"py_bool(X, {code})"
        if kind == "stream":
            self.fail("stream used as value")
        return code

    def expr(self, n):
        m = getattr(self, "e_" + type(n).__name__, None)
        if not m:
            self.fail(f"expression {ast.unparse(n)}")
        return m(n)

    def e_Constant(self, n):
        v = n.value
        if v is None:
            return "py_none(X)", "obj"
        if v is True or v is False:
            return f"py_bool(X, {int(v)})", "obj"
        if isinstance(v, str):
            return f"py_s(X, {cstr(v)})", "obj"
        if isinstance(v, (int, float)):
            return f"py_num(X, {v!r})", "obj"
        self.fail(f"constant {v!r}")

    def e_Name(self, n):
        if n.id == self.errname:
            self.fail("exception object used as value")
        return f"v_{n.id}", "obj"

    def e_JoinedStr(self, n):
        parts = []
        for v in n.values:
            if isinstance(v, ast.Constant):
                parts.append(f"py_s(X, {cstr(v.value)})")
            elif isinstance(v, ast.FormattedValue):
                if v.format_spec is not None or v.conversion != -1:
                    self.fail("format spec")
                parts.append(self.strarg(v.value))
        return f"py_cat(X, {len(parts)}, {', '.join(parts)})", "obj"

    def strarg(self, n):
        """str(x) inside an f-string – handles str(err)."""
        if isinstance(n, ast.Name) and n.id == self.errname:
            return "py_exc_str(X)"
        if isinstance(n, ast.Call) and isinstance(n.func, ast.Name) and n.func.id == "str" \
                and isinstance(n.args[0], ast.Name) and n.args[0].id == self.errname:
            return "py_exc_str(X)"
        return self.obj(n)

    def e_Dict(self, n):
        parts = []
        for k, v in zip(n.keys, n.values):
            if not (isinstance(k, ast.Constant) and isinstance(k.value, (str, int))):
                self.fail(f"dict key {ast.unparse(k) if k else '**'}")
            parts += [cstr(str(k.value)), self.obj(v)]
        return f"py_dict(X, {len(n.keys)}{''.join(', ' + p for p in parts)})", "obj"

    def e_List(self, n):
        items = [self.obj(e) for e in n.elts]
        return f"py_list(X, {len(items)}{''.join(', ' + i for i in items)})", "obj"

    e_Tuple = e_List

    def e_Subscript(self, n):
        if isinstance(n.slice, ast.Slice):
            self.fail("slice")
        return f"py_get(X, {self.obj(n.value)}, {self.obj(n.slice)})", "obj"

    def e_Attribute(self, n):
        src = ast.unparse(n)
        if self.errname and src == f"{self.errname}.response.status_code":
            return "py_exc_status(X)", "obj"
        self.fail(f"attribute {src}")

    def e_BoolOp(self, n):
        fn = "py_and" if isinstance(n.op, ast.And) else "py_or"
        vals = [self.obj(v) for v in n.values]
        out = vals[-1]
        for v in reversed(vals[:-1]):
            out = f"{fn}({v}, {out})"
        return out, "obj"

    def e_UnaryOp(self, n):
        if isinstance(n.op, ast.Not):
            return f"!{self.cond(n.operand)}", "bool"
        if isinstance(n.op, ast.USub) and isinstance(n.operand, ast.Constant):
            return f"py_num(X, -{n.operand.value!r})", "obj"
        self.fail(ast.unparse(n))

    def e_IfExp(self, n):
        return f"({self.cond(n.test)} ? {self.obj(n.body)} : {self.obj(n.orelse)})", "obj"

    def e_Compare(self, n):
        if len(n.ops) != 1:
            self.fail(ast.unparse(n))
        op, L, R = n.ops[0], n.left, n.comparators[0]
        none_r = isinstance(R, ast.Constant) and R.value is None
        if isinstance(op, (ast.Is, ast.IsNot)):
            if not none_r:
                self.fail("'is' with something else than None")
            code = f"py_isnone({self.obj(L)})"
            return (code if isinstance(op, ast.Is) else f"!{code}"), "bool"
        lc, rc = self.obj(L), self.obj(R)
        if isinstance(op, ast.Eq):
            return f"py_eq({lc}, {rc})", "bool"
        if isinstance(op, ast.NotEq):
            return f"!py_eq({lc}, {rc})", "bool"
        if isinstance(op, ast.In):
            return f"py_contains({rc}, {lc})", "bool"
        if isinstance(op, ast.NotIn):
            return f"!py_contains({rc}, {lc})", "bool"
        sym = {ast.Lt: "<", ast.Gt: ">", ast.LtE: "<=", ast.GtE: ">="}[type(op)]
        return f"(py_cmp({lc}, {rc}) {sym} 0)", "bool"

    def e_DictComp(self, n):
        gen = n.generators[0]
        if (len(n.generators) == 1 and ast.unparse(gen.iter).endswith(".items()")
                and len(gen.ifs) == 1 and ast.unparse(n.key) == ast.unparse(gen.target.elts[0])
                and ast.unparse(n.value) == ast.unparse(gen.target.elts[1])
                and ast.unparse(gen.ifs[0]) == f"{gen.target.elts[1].id} is not None"):
            return f"py_without_none(X, {self.obj(gen.iter.func.value)})", "obj"
        self.fail(f"dict comprehension {ast.unparse(n)}")

    @staticmethod
    def kwargs(n):
        return {k.arg: k.value for k in n.keywords}

    def call_args(self, names, n):
        vals = [None] * len(names)
        for i, a in enumerate(n.args):
            vals[i] = a
        for k in n.keywords:
            if k.arg not in names:
                self.fail(f"keyword {k.arg}")
            vals[names.index(k.arg)] = k.value
        return vals

    def default_value(self, node):
        if node is None:
            return "py_none(X)"
        return self.obj(node)

    def e_Call(self, n):
        f = n.func
        src = ast.unparse(f)
        kw = self.kwargs(n)
        if src.startswith("self.client.") or src == "client.executeSSE":
            verb = f.attr
            path = n.args[0] if n.args else kw.pop("endpoint", None) or kw.pop("url")
            h = self.obj(kw["headers"]) if "headers" in kw else "NULL"
            prm = self.obj(kw["params"]) if "params" in kw else "NULL"
            data = self.obj(kw["data"]) if "data" in kw else "NULL"
            if verb in ("get", "post", "put", "delete"):
                return f'py_http(X, "{verb}", {self.obj(path)}, {h}, {data}, {prm})', "obj"
            if verb == "executeSSE":
                return f"py_sse(X, {self.obj(path)}, {h}, {prm})", "stream"
            self.fail(f"client.{verb}")
        if isinstance(f, ast.Attribute) and isinstance(f.value, ast.Name) and f.value.id == "self":
            target = self.methods.get(f.attr)
            if target is None:
                self.fail(f"unknown method self.{f.attr}")
            vals = self.call_args([p[0] for p in target.params], n)
            args = ["X"]
            for (pname, t, d, req), v in zip(target.params, vals):
                if v is None:
                    if req:
                        self.fail(f"missing argument {pname}")
                    args.append(self.default_value(d))
                else:
                    args.append(self.obj(v))
            return f"{target.impl}({', '.join(args)})", "stream" if target.stream else "obj"
        if isinstance(f, ast.Name):
            name = f.id
            if name == "str":
                return self.strarg(n.args[0]) if (isinstance(n.args[0], ast.Name)
                                                  and n.args[0].id == self.errname) \
                    else f"py_str(X, {self.obj(n.args[0])})", "obj"
            if name == "isinstance":
                t = ast.unparse(n.args[1])
                fn = {"StatusResponse": "py_isstatus", "dict": "py_isdict", "list": "py_islist",
                      "(list, tuple)": "py_islist", "str": "py_isstr", "bool": "py_isbool"}.get(t)
                if not fn:
                    self.fail(f"isinstance {t}")
                return f"{fn}({self.obj(n.args[0])})", "bool"
            if name == "quote":
                safe = kw.get("safe")
                s = safe.value if isinstance(safe, ast.Constant) else "/"
                return f"py_quote(X, {self.obj(n.args[0])}, {cstr(s)})", "obj"
            if name == "urlencode":
                return f"py_urlencode(X, {self.obj(n.args[0])})", "obj"
            if name == "dict":
                return f"py_copy(X, {self.obj(n.args[0])})", "obj"
            if name == "len":
                return f"py_num(X, py_len({self.obj(n.args[0])}))", "obj"
            if name == "_openStream":
                names = ["client", "topics", "path", "headers", "errors"]
                vals = self.call_args(names, n)
                a = [self.obj(v) if v is not None else "NULL" for v in vals[1:]]
                return f"py_open_stream(X, {', '.join(a)})", "stream"
            self.fail(f"call {name}")
        if isinstance(f, ast.Attribute):
            a = f.attr
            vsrc = ast.unparse(f.value)
            if vsrc == "json" and a == "dumps":
                return f"py_dumps(X, {self.obj(n.args[0])})", "obj"
            if vsrc == "urllib.parse" and a == "quote":
                safe = kw.get("safe")
                s = safe.value if isinstance(safe, ast.Constant) else "/"
                return f"py_quote(X, {self.obj(n.args[0])}, {cstr(s)})", "obj"
            obj = self.obj(f.value)
            args = [self.obj(x) for x in n.args]
            if a == "get":
                return f"py_getor(X, {obj}, {args[0]}, {args[1] if len(args) > 1 else 'NULL'})", "obj"
            if a == "lower":
                return f"py_lower(X, {obj})", "obj"
            if a == "strip" and not args:
                return f"py_strip(X, {obj})", "obj"
            if a == "rstrip":
                return f"py_rstrip(X, {obj}, {args[0]})", "obj"
            if a == "split":
                return f"py_split(X, {obj}, {args[0]})", "obj"
            if a == "join":
                return f"py_join(X, {obj}, {args[0]})", "obj"
        self.fail(f"call {ast.unparse(n)}")

    # ------------------------------------------------------------------ statements
    def check(self, p):
        """Exception check after a statement."""
        if self.trys:
            return [f"{p}if (X->exc) goto exc_{self.trys[-1]};"]
        return [f"{p}if (X->exc) return NULL;"]

    def block(self, stmts, ind):
        out = []
        for s in stmts:
            out += self.stmt(s, ind)
            if always_returns([s]):
                break
        return out

    def ret(self, value, p):
        if value is None:
            return [f"{p}return NULL;"] if self.m.stream else [f"{p}return py_none(X);"]
        code, kind = self.expr(value)
        if kind == "bool":
            code, kind = f"py_bool(X, {code})", "obj"
        if self.m.stream and kind != "stream":
            code, kind = f"py_as_stream(X, {code})", "stream"
        if not self.m.stream and kind == "stream":
            self.fail("stream returned from a normal method")
        t = "openhab_sse_t*" if kind == "stream" else "cJSON*"
        return [f"{p}{{", f"{p}    {t} r_ = {code};"] + self.check(p + "    ") + \
               [f"{p}    return r_;", f"{p}}}"]

    def stmt(self, s, ind):
        p = "    " * ind
        if isinstance(s, ast.Expr) and isinstance(s.value, ast.Constant):
            return []
        if isinstance(s, ast.Expr) and isinstance(s.value, ast.Call):
            return [f"{p}(void){self.obj(s.value)};"] + self.check(p)
        if isinstance(s, ast.Return):
            return self.ret(s.value, p)
        if isinstance(s, ast.Assign):
            if len(s.targets) != 1:
                self.fail("multiple assignment")
            t = s.targets[0]
            if isinstance(t, ast.Name):
                if t.id in self.params:
                    pass
                return [f"{p}v_{t.id} = {self.obj(s.value)};"] + self.check(p)
            if isinstance(t, ast.Subscript):
                return [f"{p}py_set(X, {self.obj(t.value)}, {self.obj(t.slice)}, "
                        f"{self.obj(s.value)});"] + self.check(p)
            self.fail(f"assignment to {ast.unparse(t)}")
        if isinstance(s, ast.If):
            out = [f"{p}if ({self.cond(s.test)}) {{"] + self.block(s.body, ind + 1)
            orelse = s.orelse
            while len(orelse) == 1 and isinstance(orelse[0], ast.If):
                e = orelse[0]
                out += [f"{p}}} else if ({self.cond(e.test)}) {{"] + self.block(e.body, ind + 1)
                orelse = e.orelse
            if orelse:
                out += [f"{p}}} else {{"] + self.block(orelse, ind + 1)
            return out + [p + "}"]
        if isinstance(s, ast.Try):
            if s.orelse or s.finalbody:
                self.fail("try/else/finally")
            self.counter += 1
            k = self.counter
            self.trys.append(k)
            out = [f"{p}/* try */"] + self.block(s.body, ind)
            self.trys.pop()
            if not always_returns(s.body):
                out.append(f"{p}goto end_{k};")
            http = req = None
            for h in s.handlers:
                t = ast.unparse(h.type)
                if t.endswith("HTTPError"):
                    http = h
                elif t.endswith("RequestException"):
                    req = h
                else:
                    self.fail(f"except {t}")
            out.append(f"exc_{k}:")
            for h, test in ((http, "X->exc == 1"), (req, "X->exc != 0")):
                if h is None:
                    continue
                old = self.errname
                self.errname = h.name
                body = self.block(h.body, ind + 1)
                self.errname = old
                out += [f"{p}if ({test}) {{", f"{p}    py_clear_exc(X);"] + body
                if not always_returns(h.body):
                    out.append(f"{p}    goto end_{k};")
                out.append(f"{p}}}")
            out += self.check(p) if self.trys else [f"{p}return NULL;"]
            out.append(f"end_{k}:;")
            return out
        if isinstance(s, ast.Pass):
            return []
        self.fail(f"statement {type(s).__name__}: {ast.unparse(s)[:80]}")


def returns_stream(fn, methods):
    for n in ast.walk(fn):
        if isinstance(n, ast.Return) and isinstance(n.value, ast.Call):
            src = ast.unparse(n.value.func)
            if src in ("_openStream", "self.client.executeSSE", "client.executeSSE"):
                return True
            if src.startswith("self.") and src[5:] in methods and methods[src[5:]].stream:
                return True
    return False


def doc_lines(fn):
    doc = ast.get_docstring(fn) or ""
    lines = []
    for l in doc.splitlines():
        l = l.rstrip().replace("*/", "* /").replace("/*", "/ *")
        lines.append(l)
    while lines and not lines[-1]:
        lines.pop()
    return lines


C_TYPES = {"str": "const char*", "bool": "int", "int": "int", "float": "double",
           "json": "const cJSON*"}
OPT_TYPES = {"str": "const char*", "bool": "openhab_flag", "int": "int", "float": "double",
             "json": "const cJSON*"}


def arg_conversion(name, t, required, default_code):
    """C code that turns a C argument into a cJSON value of the pool."""
    src = name if required else f"a.{name}"
    if t == "str":
        conv = f"py_s(X, {src})"
        return conv if required else f"({src} ? py_s(X, {src}) : {default_code})"
    if t == "bool":
        if required:
            return f"py_bool(X, {src})"
        return f"py_arg_flag(X, {src}, {default_code})"
    if t in ("int", "float"):
        return f"py_num(X, {src})" if required else f"({src} ? py_num(X, {src}) : {default_code})"
    return f"py_arg_json(X, {src})" if required else f"({src} ? py_arg_json(X, {src}) : {default_code})"


def method_code(m, methods):
    tr = Translator(m, methods)
    fn = m.fn
    assigned = {t.id for n in ast.walk(fn) if isinstance(n, ast.Assign)
                for t in n.targets if isinstance(t, ast.Name)}
    params = [p[0] for p in m.params]
    locals_ = sorted(assigned - set(params))
    rtype = "openhab_sse_t*" if m.stream else "cJSON*"
    sig = ["py_ctx* X"] + [f"cJSON* v_{n}" for n in params]
    out = [f"static {rtype} {m.impl}({', '.join(sig)}) {{"]
    for v in locals_:
        out.append(f"    cJSON* v_{v} = NULL;")
    body = tr.block(fn.body, 1)
    out += body
    if not always_returns(fn.body):
        out.append("    return NULL;" if m.stream else "    return py_none(X);")
    out.append("}")
    used = "\n".join(out)
    # silence unused-variable warnings for locals/params that the body never reads
    pre = []
    for v in locals_ + params:
        if used.count(f"v_{v}") <= 1 + (0 if v in params else 0):
            pre.append(f"    (void)v_{v};")
    if pre:
        out = out[:1] + pre + out[1:]
    if not m.private:
        out += [""] + public_code(m)
    return out


def public_code(m):
    out = []
    ret = "openhab_sse_t*" if m.stream else "cJSON*"
    req = [f"{C_TYPES[t]} {n}" for n, t, d, r in m.required]
    if m.optional:
        sig = ["openhab_client_t* client"] + req + [f"{m.cname}_args a"]
        fname = m.cname + "_"
    else:
        sig = ["openhab_client_t* client"] + req
        fname = m.cname
    out.append(f"{ret} {fname}({', '.join(sig)}) {{")
    out.append("    py_ctx X_;")
    out.append("    py_ctx* X = &X_;")
    out.append("    py_init(X, client);")
    tr = Translator(m, {})
    args = ["X"]
    for n, t, d, r in m.params:
        dflt = None if r else ("py_none(X)" if d is None else tr.obj(d))
        args.append(arg_conversion(n, t, r, dflt))
    if m.optional:
        out.append("    (void)a._;")
    call = f"{m.impl}({', '.join(args)})"
    if m.stream:
        out.append(f"    openhab_sse_t* s = {call};")
        out.append("    return py_finish_stream(X, s, NULL);")
    else:
        out.append(f"    cJSON* r = {call};")
        out.append("    return py_finish(X, r);")
    out.append("}")
    return out


def header_code(m):
    out = ["/**"]
    out += [" * " + l if l else " *" for l in doc_lines(m.fn)]
    if m.optional:
        names = ", ".join(f".{n}" for n, *_ in m.optional)
        out += [" *", f" * Optional (named) arguments: {names}"]
    out.append(" */")
    ret = "openhab_sse_t*" if m.stream else "cJSON*"
    req = [f"{C_TYPES[t]} {n}" for n, t, d, r in m.required]
    if m.optional:
        out.append("typedef struct {")
        out.append("    int _;")
        for n, t, d, r in m.optional:
            dflt = "None" if d is None else ast.unparse(d)
            out.append(f"    {OPT_TYPES[t]} {n};  /* default: {dflt} */")
        out.append(f"}} {m.cname}_args;")
        sig = ["openhab_client_t* client"] + req + [f"{m.cname}_args a"]
        out.append(f"OPENHAB_API {ret} {m.cname}_({', '.join(sig)});")
        macro_args = ", ".join(["c"] + [n for n, *_ in m.required])
        call_args = ", ".join(["(c)"] + [f"({n})" for n, *_ in m.required])
        out.append(f"#define {m.cname}({macro_args}, ...) \\")
        out.append(f"    {m.cname}_({call_args}, ({m.cname}_args){{ ._ = 0, __VA_ARGS__ }})")
    else:
        sig = ["openhab_client_t* client"] + req
        out.append(f"OPENHAB_API {ret} {m.cname}({', '.join(sig)});")
    return out


def load_classes(src):
    files = sorted(f for f in glob.glob(os.path.join(src, "*.py"))
                   if not os.path.basename(f).startswith(SKIP_FILES))
    result = []
    for f in files:
        tree = ast.parse(open(f, encoding="utf-8").read())
        for c in tree.body:
            if not isinstance(c, ast.ClassDef):
                continue
            fns = [fn for fn in c.body if isinstance(fn, ast.FunctionDef) and fn.name != "__init__"]
            methods = {fn.name: Method(c.name, fn) for fn in fns}
            for _ in range(3):
                for m in methods.values():
                    m.stream = returns_stream(m.fn, methods)
            result.append((os.path.basename(f), c, methods))
    return result


def generate(src, root):
    errors = []
    header = ["/* Generated from python-openhab-rest-client by tools/py2c.py – do not edit. */",
              "#ifndef OPENHAB_API_H", "#define OPENHAB_API_H", "",
              '#include "openhab_client.h"', "", "#ifdef __cplusplus", 'extern "C" {', "#endif", ""]
    files = {}
    for fname, c, methods in load_classes(src):
        try:
            code = []
            for m in methods.values():
                code += method_code(m, methods) + [""]
        except Unsupported as e:
            errors.append(str(e))
            continue
        cdoc = (ast.get_docstring(c) or "").strip()
        header += [f"/* ── {c.name} " + "─" * max(3, 70 - len(c.name)) + " */", ""]
        if cdoc:
            header += ["/* " + l + " */" for l in cdoc.splitlines() if l.strip()] + [""]
        for m in methods.values():
            if not m.private:
                header += header_code(m) + [""]
        # forward declarations, because methods call each other
        fwd = []
        for m in methods.values():
            rtype = "openhab_sse_t*" if m.stream else "cJSON*"
            sig = ["py_ctx* X"] + [f"cJSON* v_{p[0]}" for p in m.params]
            fwd.append(f"static {rtype} {m.impl}({', '.join(sig)});")
        files.setdefault(fname, []).append((c.name, fwd, code))
    header += ["#ifdef __cplusplus", "}", "#endif", "", "#endif /* OPENHAB_API_H */", ""]
    if errors:
        for e in errors:
            print("UNSUPPORTED:", e, file=sys.stderr)
        sys.exit(1)
    with open(os.path.join(root, "include", "openhab", "openhab_api.h"), "w", encoding="utf-8") as f:
        f.write("\n".join(header))
    gen = os.path.join(root, "src", "api")
    os.makedirs(gen, exist_ok=True)
    for old in glob.glob(os.path.join(gen, "*.c")):
        os.remove(old)
    names = []
    for fname, classes in files.items():
        base = fname[:-3]
        out = [f"/* Generated from {fname} of python-openhab-rest-client by tools/py2c.py – "
               "do not edit. */", '#include "../py_rt.h"', '#include "openhab/openhab_api.h"', "",
               "#if defined(__GNUC__)", '#pragma GCC diagnostic ignored "-Wunused-label"',
               '#pragma GCC diagnostic ignored "-Wunused-function"', "#endif", ""]
        for cname, fwd, code in classes:
            names.append(cname)
            out += fwd + [""] + code
        with open(os.path.join(gen, base + ".c"), "w", encoding="utf-8") as f:
            f.write("\n".join(out))
    print(f"{len(names)} classes: {', '.join(names)}", file=sys.stderr)


def readme_tables(src):
    out = []
    for fname, c, methods in sorted(load_classes(src), key=lambda x: x[1].name.lower()):
        out += [f"### {c.name}", "", "| Function | Parameters | Named arguments | Returns |",
                "|---|---|---|---|"]
        for m in methods.values():
            if m.private:
                continue
            req = ", ".join(p[0] for p in m.required)
            opt = ", ".join("." + p[0] for p in m.optional)
            out.append(f"| `{m.cname}` | {req} | {opt} | "
                       f"{'`openhab_sse_t*`' if m.stream else '`cJSON*`'} |")
        out.append("")
    return "\n".join(out)


def main():
    if sys.argv[1] == "--dispatch":
        print(dispatch_code(sys.argv[2]))
        return
    if sys.argv[1] == "--readme":
        print(readme_tables(sys.argv[2]))
        return
    generate(sys.argv[1], sys.argv[2])


def dispatch_code(src):
    """test/dispatch.c: calls any function by class and method name with JSON arguments
    (positional list, a trailing object for named arguments) – for the differential test."""
    out = ["/* Generated by tools/py2c.py --dispatch – test helper. */",
           "#include <string.h>", "#include <openhab/openhab.h>", "",
           "static const cJSON* arg_(const cJSON* a, int i, const cJSON* kw, const char* name) {",
           "    int npos = cJSON_GetArraySize(a) - (kw ? 1 : 0);",
           "    if (i < npos) return cJSON_GetArrayItem(a, i);",
           "    return kw ? cJSON_GetObjectItemCaseSensitive(kw, name) : NULL;", "}",
           "static const char* s_(const cJSON* v) { return cJSON_IsString(v) ? v->valuestring : NULL; }",
           "static int b_(const cJSON* v) { return cJSON_IsTrue(v); }",
           "static openhab_flag f_(const cJSON* v) {",
           "    return cJSON_IsBool(v) ? (cJSON_IsTrue(v) ? OPENHAB_TRUE : OPENHAB_FALSE) : OPENHAB_UNSET;",
           "}",
           "static int i_(const cJSON* v) { return cJSON_IsNumber(v) ? v->valueint : 0; }",
           "static const cJSON* j_(const cJSON* v) { return cJSON_IsNull(v) ? NULL : v; }", "",
           "cJSON* dispatch(openhab_client_t* c, const char* cls, const char* m, const cJSON* args) {",
           "    const cJSON* kw = NULL;",
           "    int n = cJSON_GetArraySize(args);",
           "    const cJSON* last = cJSON_GetArrayItem(args, n - 1);",
           "    (void)n; (void)last;"]
    conv = {"str": "s_", "bool": "b_", "int": "i_", "float": "i_", "json": "j_"}
    optconv = {"str": "s_", "bool": "f_", "int": "i_", "float": "i_", "json": "j_"}
    for fname, c, methods in load_classes(src):
        for m in methods.values():
            if m.private or m.stream:
                continue
            out.append(f'    if (!strcmp(cls, "{c.name}") && !strcmp(m, "{m.name}")) {{')
            named = m.name in ("getItems", "getItem", "getItemPersistenceData")
            out.append(f"        kw = (cJSON_IsObject(last) && n > {len(m.required)} && "
                       f"{'1' if (m.optional and named) else '0'}) ? last : NULL;")
            req = []
            for i, (n_, t, d, r) in enumerate(m.params):
                if r:
                    req.append(f"{conv[t]}(arg_(args, {i}, kw, \"{n_}\"))")
            if m.optional:
                fields = []
                for i, (n_, t, d, r) in enumerate(m.params):
                    if not r:
                        fields.append(f".{n_} = {optconv[t]}(arg_(args, {i}, kw, \"{n_}\"))")
                out.append(f"        return {m.cname}_({', '.join(['c'] + req)}, "
                           f"({m.cname}_args){{ {', '.join(fields)} }});")
            else:
                out.append(f"        return {m.cname}({', '.join(['c'] + req)});")
            out.append("    }")
    out += ["    return NULL;", "}", ""]
    return "\n".join(out)


if __name__ == "__main__":
    main()
