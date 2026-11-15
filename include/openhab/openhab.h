/*
 * c-openhab-rest-client – one include for the whole library.
 *
 *   #include <openhab/openhab.h>
 *
 *   openhab_client_t* c = openhab_client_new("http://127.0.0.1:8080", .token = token);
 *   cJSON* r = openhab_items_sendCommand(c, "Wohnzimmer_Licht", "ON");
 *   if (openhab_is_error(r)) fprintf(stderr, "%s\n", openhab_error(r));
 *   cJSON_Delete(r);
 *   openhab_client_destroy(c);
 */
#ifndef OPENHAB_H
#define OPENHAB_H

#include "openhab_client.h"
#include "openhab_api.h"

#endif /* OPENHAB_H */
