/* Generated from python-openhab-rest-client by tools/py2c.py – do not edit. */
#ifndef OPENHAB_API_H
#define OPENHAB_API_H

#include "openhab_client.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ── Actions ─────────────────────────────────────────────────────────────── */

/**
 * Get all available actions for provided thing UID.
 *
 * :param thingUID: The UID of the thing for which actions are to be retrieved.
 * :param language: (Optional) Language setting for the Accept-Language headers.
 *
 * :return: A list of actions.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_actions_getActions_args;
OPENHAB_API cJSON* openhab_actions_getActions_(openhab_client_t* client, const char* thingUID, openhab_actions_getActions_args a);
#define openhab_actions_getActions(c, thingUID, ...) \
    openhab_actions_getActions_((c), (thingUID), (openhab_actions_getActions_args){ ._ = 0, __VA_ARGS__ })

/**
 * Executes a thing action.
 *
 * :param thingUID: The UID of the thing on which the action is to be executed.
 * :param actionUID: The UID of the action to be executed.
 * :param actionInputs: The inputs for the action as a dictionary.
 * :param language: (Optional) Language setting for the Accept-Language headers.
 *
 * :return: A response from the server.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_actions_executeAction_args;
OPENHAB_API cJSON* openhab_actions_executeAction_(openhab_client_t* client, const char* thingUID, const char* actionUID, const cJSON* actionInputs, openhab_actions_executeAction_args a);
#define openhab_actions_executeAction(c, thingUID, actionUID, actionInputs, ...) \
    openhab_actions_executeAction_((c), (thingUID), (actionUID), (actionInputs), (openhab_actions_executeAction_args){ ._ = 0, __VA_ARGS__ })

/* ── Addons ──────────────────────────────────────────────────────────────── */

/**
 * Retrieves a list of all available add-ons.
 *
 * :param serviceID: Optional service ID to filter the results.
 * :param language: Optional language preference for the response.
 *
 * :return: A dictionary containing the add-ons data.
 *
 * Optional (named) arguments: .serviceID, .language
 */
typedef struct {
    int _;
    const char* serviceID;  /* default: None */
    const char* language;  /* default: None */
} openhab_addons_getAddons_args;
OPENHAB_API cJSON* openhab_addons_getAddons_(openhab_client_t* client, openhab_addons_getAddons_args a);
#define openhab_addons_getAddons(c, ...) \
    openhab_addons_getAddons_((c), (openhab_addons_getAddons_args){ ._ = 0, __VA_ARGS__ })

/**
 * Retrieves details of a specific add-on by its ID.
 *
 * :param addonID: The unique identifier of the add-on.
 * :param serviceID: Optional service ID to filter the results.
 * :param language: Optional language preference for the response.
 *
 * :return: A dictionary containing details of the specified add-on.
 *
 * Optional (named) arguments: .serviceID, .language
 */
typedef struct {
    int _;
    const char* serviceID;  /* default: None */
    const char* language;  /* default: None */
} openhab_addons_getAddon_args;
OPENHAB_API cJSON* openhab_addons_getAddon_(openhab_client_t* client, const char* addonID, openhab_addons_getAddon_args a);
#define openhab_addons_getAddon(c, addonID, ...) \
    openhab_addons_getAddon_((c), (addonID), (openhab_addons_getAddon_args){ ._ = 0, __VA_ARGS__ })

/**
 * Retrieves the configuration of a specific add-on.
 *
 * :param addonID: The unique identifier of the add-on.
 * :param serviceID: Optional service ID to filter the results.
 *
 * :return: A dictionary containing the configuration of the specified add-on.
 *
 * Optional (named) arguments: .serviceID
 */
typedef struct {
    int _;
    const char* serviceID;  /* default: None */
} openhab_addons_getAddonConfig_args;
OPENHAB_API cJSON* openhab_addons_getAddonConfig_(openhab_client_t* client, const char* addonID, openhab_addons_getAddonConfig_args a);
#define openhab_addons_getAddonConfig(c, addonID, ...) \
    openhab_addons_getAddonConfig_((c), (addonID), (openhab_addons_getAddonConfig_args){ ._ = 0, __VA_ARGS__ })

/**
 * Updates the configuration of a specific add-on and returns the updated configuration.
 *
 * :param addonID: The unique identifier of the add-on.
 * :param configData: A dictionary containing the new configuration settings.
 * :param serviceID: Optional service ID to specify the target service.
 *
 * :return: A dictionary containing the updated configuration.
 *
 * Optional (named) arguments: .serviceID
 */
typedef struct {
    int _;
    const char* serviceID;  /* default: None */
} openhab_addons_updateAddonConfig_args;
OPENHAB_API cJSON* openhab_addons_updateAddonConfig_(openhab_client_t* client, const char* addonID, const cJSON* configData, openhab_addons_updateAddonConfig_args a);
#define openhab_addons_updateAddonConfig(c, addonID, configData, ...) \
    openhab_addons_updateAddonConfig_((c), (addonID), (configData), (openhab_addons_updateAddonConfig_args){ ._ = 0, __VA_ARGS__ })

/**
 * Installs an add-on by its ID.
 *
 * :param addonID: The unique identifier of the add-on.
 * :param serviceID: Optional service ID to specify the target service.
 *
 * :return: A dictionary containing the installation status.
 *
 * Optional (named) arguments: .serviceID
 */
typedef struct {
    int _;
    const char* serviceID;  /* default: None */
} openhab_addons_installAddon_args;
OPENHAB_API cJSON* openhab_addons_installAddon_(openhab_client_t* client, const char* addonID, openhab_addons_installAddon_args a);
#define openhab_addons_installAddon(c, addonID, ...) \
    openhab_addons_installAddon_((c), (addonID), (openhab_addons_installAddon_args){ ._ = 0, __VA_ARGS__ })

/**
 * Uninstalls an add-on by its ID.
 *
 * :param addonID: The unique identifier of the add-on.
 * :param serviceID: Optional service ID to specify the target service.
 *
 * :return: A dictionary containing the uninstallation status.
 *
 * Optional (named) arguments: .serviceID
 */
typedef struct {
    int _;
    const char* serviceID;  /* default: None */
} openhab_addons_uninstallAddon_args;
OPENHAB_API cJSON* openhab_addons_uninstallAddon_(openhab_client_t* client, const char* addonID, openhab_addons_uninstallAddon_args a);
#define openhab_addons_uninstallAddon(c, addonID, ...) \
    openhab_addons_uninstallAddon_((c), (addonID), (openhab_addons_uninstallAddon_args){ ._ = 0, __VA_ARGS__ })

/**
 * Retrieves a list of all available add-on services.
 *
 * :param language: Optional language preference for the response.
 *
 * :return: A dictionary containing the available add-on services.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_addons_getAddonServices_args;
OPENHAB_API cJSON* openhab_addons_getAddonServices_(openhab_client_t* client, openhab_addons_getAddonServices_args a);
#define openhab_addons_getAddonServices(c, ...) \
    openhab_addons_getAddonServices_((c), (openhab_addons_getAddonServices_args){ ._ = 0, __VA_ARGS__ })

/**
 * Retrieves a list of suggested add-ons for installation.
 *
 * :param language: Optional language preference for the response.
 *
 * :return: A dictionary containing suggested add-ons.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_addons_getAddonSuggestions_args;
OPENHAB_API cJSON* openhab_addons_getAddonSuggestions_(openhab_client_t* client, openhab_addons_getAddonSuggestions_args a);
#define openhab_addons_getAddonSuggestions(c, ...) \
    openhab_addons_getAddonSuggestions_((c), (openhab_addons_getAddonSuggestions_args){ ._ = 0, __VA_ARGS__ })

/**
 * Retrieves a list of all available add-on types.
 *
 * :param language: Optional language preference for the response.
 *
 * :return: A dictionary containing available add-on types.
 *
 * Optional (named) arguments: .serviceID, .language
 */
typedef struct {
    int _;
    const char* serviceID;  /* default: None */
    const char* language;  /* default: None */
} openhab_addons_getAddonTypes_args;
OPENHAB_API cJSON* openhab_addons_getAddonTypes_(openhab_client_t* client, openhab_addons_getAddonTypes_args a);
#define openhab_addons_getAddonTypes(c, ...) \
    openhab_addons_getAddonTypes_((c), (openhab_addons_getAddonTypes_args){ ._ = 0, __VA_ARGS__ })

/**
 * Installs an add-on from a given URL.
 *
 * :param url: The URL of the add-on to install.
 *
 * :return: A dictionary containing the installation status.
 */
OPENHAB_API cJSON* openhab_addons_installAddonFromUrl(openhab_client_t* client, const char* url);

/* ── Audio ───────────────────────────────────────────────────────────────── */

/**
 * Retrieves the default sink if defined, or the first available sink.
 *
 * :param language: (Optional) Language setting for the Accept-Language header.
 *
 * :return: A dictionary containing information about the default sink.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_audio_getDefaultSink_args;
OPENHAB_API cJSON* openhab_audio_getDefaultSink_(openhab_client_t* client, openhab_audio_getDefaultSink_args a);
#define openhab_audio_getDefaultSink(c, ...) \
    openhab_audio_getDefaultSink_((c), (openhab_audio_getDefaultSink_args){ ._ = 0, __VA_ARGS__ })

/**
 * Retrieves the default source if defined, or the first available source.
 *
 * :param language: (Optional) Language setting for the Accept-Language header.
 *
 * :return: A dictionary containing information about the default source.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_audio_getDefaultSource_args;
OPENHAB_API cJSON* openhab_audio_getDefaultSource_(openhab_client_t* client, openhab_audio_getDefaultSource_args a);
#define openhab_audio_getDefaultSource(c, ...) \
    openhab_audio_getDefaultSource_((c), (openhab_audio_getDefaultSource_args){ ._ = 0, __VA_ARGS__ })

/**
 * Retrieves a list of all available sinks.
 *
 * :param language: (Optional) Language setting for the Accept-Language header.
 *
 * :return: A list of available sinks.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_audio_getSinks_args;
OPENHAB_API cJSON* openhab_audio_getSinks_(openhab_client_t* client, openhab_audio_getSinks_args a);
#define openhab_audio_getSinks(c, ...) \
    openhab_audio_getSinks_((c), (openhab_audio_getSinks_args){ ._ = 0, __VA_ARGS__ })

/**
 * Retrieves a list of all available sources.
 *
 * :param language: (Optional) Language setting for the Accept-Language header.
 *
 * :return: A list of available sources.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_audio_getSources_args;
OPENHAB_API cJSON* openhab_audio_getSources_(openhab_client_t* client, openhab_audio_getSources_args a);
#define openhab_audio_getSources(c, ...) \
    openhab_audio_getSources_((c), (openhab_audio_getSources_args){ ._ = 0, __VA_ARGS__ })

/* ── Auth ────────────────────────────────────────────────────────────────── */

/**
 * Retrieve the API tokens associated with the authenticated user.
 *
 * :param language: (Optional) Language setting for the API request.
 *
 * :return: JSON response from the server.
 */
OPENHAB_API cJSON* openhab_auth_getAPITokens(openhab_client_t* client);

/**
 * Revoke a specific API token associated with the authenticated user.
 *
 * :param tokenName: Name of the API token to be revoked.
 * :param language: (Optional) Language setting for the API request.
 *
 * :return: JSON response from the server.
 */
OPENHAB_API cJSON* openhab_auth_revokeAPIToken(openhab_client_t* client, const char* tokenName);

/**
 * Terminate the session associated with a refresh token.
 *
 * :param refreshToken: The refresh token used to delete the session.
 * :param id: The user ID associated with the refresh token.
 *
 * :return: JSON response from the server.
 */
OPENHAB_API cJSON* openhab_auth_logout(openhab_client_t* client, const char* refreshToken, const char* sessionID);

/**
 * Retrieve the sessions associated with the authenticated user.
 *
 * :return: JSON response from the server.
 */
OPENHAB_API cJSON* openhab_auth_getSessions(openhab_client_t* client);

/**
 * Obtain access and refresh tokens.
 *
 * :param useCookie: (Optional) Whether to use cookies for the session.
 * :param grantType: (Optional) The type of grant being requested.
 * :param code: (Optional) Authorization code for authentication.
 * :param redirectUri: (Optional) Redirect URI for OAuth authentication.
 * :param clientID: (Optional) Client ID for authentication.
 * :param refreshToken: (Optional) Refresh token for token renewal.
 * :param codeVerifier: (Optional) Code verifier for PKCE authentication.
 *
 * :return: JSON response from the server.
 *
 * Optional (named) arguments: .useCookie, .grantType, .code, .redirectURI, .clientID, .refreshToken, .codeVerifier
 */
typedef struct {
    int _;
    openhab_flag useCookie;  /* default: False */
    const char* grantType;  /* default: None */
    const char* code;  /* default: None */
    const char* redirectURI;  /* default: None */
    const char* clientID;  /* default: None */
    const char* refreshToken;  /* default: None */
    const char* codeVerifier;  /* default: None */
} openhab_auth_getToken_args;
OPENHAB_API cJSON* openhab_auth_getToken_(openhab_client_t* client, openhab_auth_getToken_args a);
#define openhab_auth_getToken(c, ...) \
    openhab_auth_getToken_((c), (openhab_auth_getToken_args){ ._ = 0, __VA_ARGS__ })

/* ── ChannelTypes ────────────────────────────────────────────────────────── */

/**
 * Retrieves all available channel types.
 *
 * :param language: Optional headers 'Accept-Language' to specify the preferred language.
 * :param prefixes: Optional query parameter to filter channel types by prefix.
 *
 * :return: A list of channel types.
 *
 * Optional (named) arguments: .prefixes, .language
 */
typedef struct {
    int _;
    const char* prefixes;  /* default: None */
    const char* language;  /* default: None */
} openhab_channel_types_getChannelTypes_args;
OPENHAB_API cJSON* openhab_channel_types_getChannelTypes_(openhab_client_t* client, openhab_channel_types_getChannelTypes_args a);
#define openhab_channel_types_getChannelTypes(c, ...) \
    openhab_channel_types_getChannelTypes_((c), (openhab_channel_types_getChannelTypes_args){ ._ = 0, __VA_ARGS__ })

/**
 * Retrieves the item types the given trigger channel type UID can be linked to.
 *
 * :param channelTypeUID: The unique UID of the channel type.
 * :param language: Optional headers 'Accept-Language' to specify the preferred language.
 *
 * :return: Details of the specific channel type.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_channel_types_getChannelType_args;
OPENHAB_API cJSON* openhab_channel_types_getChannelType_(openhab_client_t* client, const char* channelTypeUID, openhab_channel_types_getChannelType_args a);
#define openhab_channel_types_getChannelType(c, channelTypeUID, ...) \
    openhab_channel_types_getChannelType_((c), (channelTypeUID), (openhab_channel_types_getChannelType_args){ ._ = 0, __VA_ARGS__ })

/**
 * Retrieves the item types that can be linked to the specified trigger channel type.
 *
 * :param channelTypeUID: The unique UID of the channel type.
 *
 * :return: A list of item types.
 */
OPENHAB_API cJSON* openhab_channel_types_getLinkableItemTypes(openhab_client_t* client, const char* channelTypeUID);

/* ── ConfigDescriptions ──────────────────────────────────────────────────── */

/**
 * Retrieves all available config descriptions.
 *
 * :param language: Optional headers 'Accept-Language' to specify the preferred language.
 * :param scheme: Optional query parameter to filter results by a specific scheme.
 *
 * :return: A list of configuration descriptions.
 *
 * Optional (named) arguments: .scheme, .language
 */
typedef struct {
    int _;
    const char* scheme;  /* default: None */
    const char* language;  /* default: None */
} openhab_config_descriptions_getConfigDescriptions_args;
OPENHAB_API cJSON* openhab_config_descriptions_getConfigDescriptions_(openhab_client_t* client, openhab_config_descriptions_getConfigDescriptions_args a);
#define openhab_config_descriptions_getConfigDescriptions(c, ...) \
    openhab_config_descriptions_getConfigDescriptions_((c), (openhab_config_descriptions_getConfigDescriptions_args){ ._ = 0, __VA_ARGS__ })

/**
 * Retrieves a config description by URI.
 *
 * :param uri: The URI of the requested configuration description.
 * :param language: Optional headers 'Accept-Language' to specify the preferred language.
 *
 * :return: Details of the specific configuration description.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_config_descriptions_getConfigDescription_args;
OPENHAB_API cJSON* openhab_config_descriptions_getConfigDescription_(openhab_client_t* client, const char* uri, openhab_config_descriptions_getConfigDescription_args a);
#define openhab_config_descriptions_getConfigDescription(c, uri, ...) \
    openhab_config_descriptions_getConfigDescription_((c), (uri), (openhab_config_descriptions_getConfigDescription_args){ ._ = 0, __VA_ARGS__ })

/* ── Discovery ───────────────────────────────────────────────────────────── */

/**
 * Gets all bindings that support discovery.
 *
 * :return: Eine Liste der Bindings als Strings.
 */
OPENHAB_API cJSON* openhab_discovery_getDiscoveryBindings(openhab_client_t* client);

/**
 * Gets information about the discovery services for a binding.
 *
 * :param bindingId: The ID of the binding to get discovery information for.
 * :param language: Optional language parameter for the response (Accept-Language header).
 *
 * :return: Information about the discovery service for the specified binding.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_discovery_getBindingInfo_args;
OPENHAB_API cJSON* openhab_discovery_getBindingInfo_(openhab_client_t* client, const char* bindingID, openhab_discovery_getBindingInfo_args a);
#define openhab_discovery_getBindingInfo(c, bindingID, ...) \
    openhab_discovery_getBindingInfo_((c), (bindingID), (openhab_discovery_getBindingInfo_args){ ._ = 0, __VA_ARGS__ })

/**
 * Starts asynchronous discovery process for a binding and returns the timeout in seconds of the discovery operation.
 *
 * :param bindingID: The ID of the binding for which the discovery is to be started.
 * :param input: An input parameter to start the discovery.
 *
 * :return: Timeout duration of the discovery operation in seconds.
 *
 * Optional (named) arguments: .input
 */
typedef struct {
    int _;
    const char* input;  /* default: None */
} openhab_discovery_startBindingScan_args;
OPENHAB_API cJSON* openhab_discovery_startBindingScan_(openhab_client_t* client, const char* bindingID, openhab_discovery_startBindingScan_args a);
#define openhab_discovery_startBindingScan(c, bindingID, ...) \
    openhab_discovery_startBindingScan_((c), (bindingID), (openhab_discovery_startBindingScan_args){ ._ = 0, __VA_ARGS__ })

/* ── Events ──────────────────────────────────────────────────────────────── */

/**
 * Get all available events, optionally filtered by topic.
 *
 * :param topics: A comma-separated list of topics to filter the events by
 *                (e.g. "openhab/items/ * /statechanged,openhab/things/ * /statuschanged").
 *                The wildcard * also matches slashes.
 *
 * :return: A SSE stream of events (requests.Response) or {"error": ...}.
 *
 * Optional (named) arguments: .topics
 */
typedef struct {
    int _;
    const char* topics;  /* default: None */
} openhab_events_getEvents_args;
OPENHAB_API openhab_sse_t* openhab_events_getEvents_(openhab_client_t* client, openhab_events_getEvents_args a);
#define openhab_events_getEvents(c, ...) \
    openhab_events_getEvents_((c), (openhab_events_getEvents_args){ ._ = 0, __VA_ARGS__ })

/**
 * Initiates a new item state tracker connection.
 *
 * The first event of the stream carries the connection ID, which is needed for
 * updateSSEConnectionItems().
 *
 * :return: A SSE stream (requests.Response) or {"error": ...}.
 */
OPENHAB_API openhab_sse_t* openhab_events_initiateStateTracker(openhab_client_t* client);

/**
 * Changes the list of items a SSE connection will receive state updates for.
 *
 * :param connectionID: The ID of the existing connection.
 * :param items: A list of item names to subscribe to for state updates.
 *
 * :return: A success message when the update is completed.
 */
OPENHAB_API cJSON* openhab_events_updateSSEConnectionItems(openhab_client_t* client, const char* connectionID, const cJSON* items);

/* ── ItemEvents ──────────────────────────────────────────────────────────── */

/**
 * Get all item-related events.
 *
 * :return: A SSE stream of item events.
 */
OPENHAB_API openhab_sse_t* openhab_item_events_ItemEvent(openhab_client_t* client);

/**
 * Get events for added items.
 *
 * :param itemName: The name of the item (default is "*").
 *
 * :return: A SSE stream of added item events.
 *
 * Optional (named) arguments: .itemName
 */
typedef struct {
    int _;
    const char* itemName;  /* default: '*' */
} openhab_item_events_ItemAddedEvent_args;
OPENHAB_API openhab_sse_t* openhab_item_events_ItemAddedEvent_(openhab_client_t* client, openhab_item_events_ItemAddedEvent_args a);
#define openhab_item_events_ItemAddedEvent(c, ...) \
    openhab_item_events_ItemAddedEvent_((c), (openhab_item_events_ItemAddedEvent_args){ ._ = 0, __VA_ARGS__ })

/**
 * Get events for removed items.
 *
 * :param itemName: The name of the item (default is "*").
 *
 * :return: A SSE stream of removed item events.
 *
 * Optional (named) arguments: .itemName
 */
typedef struct {
    int _;
    const char* itemName;  /* default: '*' */
} openhab_item_events_ItemRemovedEvent_args;
OPENHAB_API openhab_sse_t* openhab_item_events_ItemRemovedEvent_(openhab_client_t* client, openhab_item_events_ItemRemovedEvent_args a);
#define openhab_item_events_ItemRemovedEvent(c, ...) \
    openhab_item_events_ItemRemovedEvent_((c), (openhab_item_events_ItemRemovedEvent_args){ ._ = 0, __VA_ARGS__ })

/**
 * Get events for updated items.
 *
 * :param itemName: The name of the item (default is "*").
 *
 * :return: A SSE stream of updated item events.
 *
 * Optional (named) arguments: .itemName
 */
typedef struct {
    int _;
    const char* itemName;  /* default: '*' */
} openhab_item_events_ItemUpdatedEvent_args;
OPENHAB_API openhab_sse_t* openhab_item_events_ItemUpdatedEvent_(openhab_client_t* client, openhab_item_events_ItemUpdatedEvent_args a);
#define openhab_item_events_ItemUpdatedEvent(c, ...) \
    openhab_item_events_ItemUpdatedEvent_((c), (openhab_item_events_ItemUpdatedEvent_args){ ._ = 0, __VA_ARGS__ })

/**
 * Get events for item commands.
 *
 * :param itemName: The name of the item (default is "*").
 *
 * :return: A SSE stream of item command events.
 *
 * Optional (named) arguments: .itemName
 */
typedef struct {
    int _;
    const char* itemName;  /* default: '*' */
} openhab_item_events_ItemCommandEvent_args;
OPENHAB_API openhab_sse_t* openhab_item_events_ItemCommandEvent_(openhab_client_t* client, openhab_item_events_ItemCommandEvent_args a);
#define openhab_item_events_ItemCommandEvent(c, ...) \
    openhab_item_events_ItemCommandEvent_((c), (openhab_item_events_ItemCommandEvent_args){ ._ = 0, __VA_ARGS__ })

/**
 * Get events for item state updates.
 *
 * :param itemName: The name of the item (default is "*").
 *
 * :return: A SSE stream of item state events.
 *
 * Optional (named) arguments: .itemName
 */
typedef struct {
    int _;
    const char* itemName;  /* default: '*' */
} openhab_item_events_ItemStateEvent_args;
OPENHAB_API openhab_sse_t* openhab_item_events_ItemStateEvent_(openhab_client_t* client, openhab_item_events_ItemStateEvent_args a);
#define openhab_item_events_ItemStateEvent(c, ...) \
    openhab_item_events_ItemStateEvent_((c), (openhab_item_events_ItemStateEvent_args){ ._ = 0, __VA_ARGS__ })

/**
 * Get events for predicted item state changes.
 *
 * :param itemName: The name of the item (default is "*").
 *
 * :return: A SSE stream of item state predicted events.
 *
 * Optional (named) arguments: .itemName
 */
typedef struct {
    int _;
    const char* itemName;  /* default: '*' */
} openhab_item_events_ItemStatePredictedEvent_args;
OPENHAB_API openhab_sse_t* openhab_item_events_ItemStatePredictedEvent_(openhab_client_t* client, openhab_item_events_ItemStatePredictedEvent_args a);
#define openhab_item_events_ItemStatePredictedEvent(c, ...) \
    openhab_item_events_ItemStatePredictedEvent_((c), (openhab_item_events_ItemStatePredictedEvent_args){ ._ = 0, __VA_ARGS__ })

/**
 * Get events for item state changes.
 *
 * Note: with the default "*", state changes of group items are included as
 * well, because their topic openhab/items/<group>/<member>/statechanged also
 * matches the pattern.
 *
 * :param itemName: The name of the item (default is "*").
 *
 * :return: A SSE stream of item state changed events.
 *
 * Optional (named) arguments: .itemName
 */
typedef struct {
    int _;
    const char* itemName;  /* default: '*' */
} openhab_item_events_ItemStateChangedEvent_args;
OPENHAB_API openhab_sse_t* openhab_item_events_ItemStateChangedEvent_(openhab_client_t* client, openhab_item_events_ItemStateChangedEvent_args a);
#define openhab_item_events_ItemStateChangedEvent(c, ...) \
    openhab_item_events_ItemStateChangedEvent_((c), (openhab_item_events_ItemStateChangedEvent_args){ ._ = 0, __VA_ARGS__ })

/**
 * Get events for state changes of group items.
 *
 * :param itemName: The name of the group item (default is "*").
 * :param memberName: The name of the group member that caused the change (default is "*").
 *
 * :return: A SSE stream of group item state changed events.
 *
 * Optional (named) arguments: .itemName, .memberName
 */
typedef struct {
    int _;
    const char* itemName;  /* default: '*' */
    const char* memberName;  /* default: '*' */
} openhab_item_events_GroupItemStateChangedEvent_args;
OPENHAB_API openhab_sse_t* openhab_item_events_GroupItemStateChangedEvent_(openhab_client_t* client, openhab_item_events_GroupItemStateChangedEvent_args a);
#define openhab_item_events_GroupItemStateChangedEvent(c, ...) \
    openhab_item_events_GroupItemStateChangedEvent_((c), (openhab_item_events_GroupItemStateChangedEvent_args){ ._ = 0, __VA_ARGS__ })

/* ── ThingEvents ─────────────────────────────────────────────────────────── */

/**
 * Get events for added things.
 *
 * :param thingUID: The UID of the thing (default is "*").
 *
 * :return: A SSE stream of added thing events.
 *
 * Optional (named) arguments: .thingUID
 */
typedef struct {
    int _;
    const char* thingUID;  /* default: '*' */
} openhab_thing_events_ThingAddedEvent_args;
OPENHAB_API openhab_sse_t* openhab_thing_events_ThingAddedEvent_(openhab_client_t* client, openhab_thing_events_ThingAddedEvent_args a);
#define openhab_thing_events_ThingAddedEvent(c, ...) \
    openhab_thing_events_ThingAddedEvent_((c), (openhab_thing_events_ThingAddedEvent_args){ ._ = 0, __VA_ARGS__ })

/**
 * Get events for removed things.
 *
 * :param thingUID: The UID of the thing (default is "*").
 *
 * :return: A SSE stream of removed thing events.
 *
 * Optional (named) arguments: .thingUID
 */
typedef struct {
    int _;
    const char* thingUID;  /* default: '*' */
} openhab_thing_events_ThingRemovedEvent_args;
OPENHAB_API openhab_sse_t* openhab_thing_events_ThingRemovedEvent_(openhab_client_t* client, openhab_thing_events_ThingRemovedEvent_args a);
#define openhab_thing_events_ThingRemovedEvent(c, ...) \
    openhab_thing_events_ThingRemovedEvent_((c), (openhab_thing_events_ThingRemovedEvent_args){ ._ = 0, __VA_ARGS__ })

/**
 * Get events for updated things.
 *
 * :param thingUID: The UID of the thing (default is "*").
 *
 * :return: A SSE stream of updated thing events.
 *
 * Optional (named) arguments: .thingUID
 */
typedef struct {
    int _;
    const char* thingUID;  /* default: '*' */
} openhab_thing_events_ThingUpdatedEvent_args;
OPENHAB_API openhab_sse_t* openhab_thing_events_ThingUpdatedEvent_(openhab_client_t* client, openhab_thing_events_ThingUpdatedEvent_args a);
#define openhab_thing_events_ThingUpdatedEvent(c, ...) \
    openhab_thing_events_ThingUpdatedEvent_((c), (openhab_thing_events_ThingUpdatedEvent_args){ ._ = 0, __VA_ARGS__ })

/**
 * Get events for thing status information.
 *
 * :param thingUID: The UID of the thing (default is "*").
 *
 * :return: A SSE stream of thing status information events.
 *
 * Optional (named) arguments: .thingUID
 */
typedef struct {
    int _;
    const char* thingUID;  /* default: '*' */
} openhab_thing_events_ThingStatusInfoEvent_args;
OPENHAB_API openhab_sse_t* openhab_thing_events_ThingStatusInfoEvent_(openhab_client_t* client, openhab_thing_events_ThingStatusInfoEvent_args a);
#define openhab_thing_events_ThingStatusInfoEvent(c, ...) \
    openhab_thing_events_ThingStatusInfoEvent_((c), (openhab_thing_events_ThingStatusInfoEvent_args){ ._ = 0, __VA_ARGS__ })

/**
 * Get events for thing status information changes.
 *
 * :param thingUID: The UID of the thing (default is "*").
 *
 * :return: A SSE stream of thing status information changed events.
 *
 * Optional (named) arguments: .thingUID
 */
typedef struct {
    int _;
    const char* thingUID;  /* default: '*' */
} openhab_thing_events_ThingStatusInfoChangedEvent_args;
OPENHAB_API openhab_sse_t* openhab_thing_events_ThingStatusInfoChangedEvent_(openhab_client_t* client, openhab_thing_events_ThingStatusInfoChangedEvent_args a);
#define openhab_thing_events_ThingStatusInfoChangedEvent(c, ...) \
    openhab_thing_events_ThingStatusInfoChangedEvent_((c), (openhab_thing_events_ThingStatusInfoChangedEvent_args){ ._ = 0, __VA_ARGS__ })

/* ── InboxEvents ─────────────────────────────────────────────────────────── */

/**
 * Get events for added things in the inbox.
 *
 * :param thingUID: The UID of the thing (default is "*").
 *
 * :return: A SSE stream of added inbox events.
 *
 * Optional (named) arguments: .thingUID
 */
typedef struct {
    int _;
    const char* thingUID;  /* default: '*' */
} openhab_inbox_events_InboxAddedEvent_args;
OPENHAB_API openhab_sse_t* openhab_inbox_events_InboxAddedEvent_(openhab_client_t* client, openhab_inbox_events_InboxAddedEvent_args a);
#define openhab_inbox_events_InboxAddedEvent(c, ...) \
    openhab_inbox_events_InboxAddedEvent_((c), (openhab_inbox_events_InboxAddedEvent_args){ ._ = 0, __VA_ARGS__ })

/**
 * Get events for removed things in the inbox.
 *
 * :param thingUID: The UID of the thing (default is "*").
 *
 * :return: A SSE stream of removed inbox events.
 *
 * Optional (named) arguments: .thingUID
 */
typedef struct {
    int _;
    const char* thingUID;  /* default: '*' */
} openhab_inbox_events_InboxRemovedEvent_args;
OPENHAB_API openhab_sse_t* openhab_inbox_events_InboxRemovedEvent_(openhab_client_t* client, openhab_inbox_events_InboxRemovedEvent_args a);
#define openhab_inbox_events_InboxRemovedEvent(c, ...) \
    openhab_inbox_events_InboxRemovedEvent_((c), (openhab_inbox_events_InboxRemovedEvent_args){ ._ = 0, __VA_ARGS__ })

/**
 * Get events for updated things in the inbox.
 *
 * :param thingUID: The UID of the thing (default is "*").
 *
 * :return: A SSE stream of updated inbox events.
 *
 * Optional (named) arguments: .thingUID
 */
typedef struct {
    int _;
    const char* thingUID;  /* default: '*' */
} openhab_inbox_events_InboxUpdatedEvent_args;
OPENHAB_API openhab_sse_t* openhab_inbox_events_InboxUpdatedEvent_(openhab_client_t* client, openhab_inbox_events_InboxUpdatedEvent_args a);
#define openhab_inbox_events_InboxUpdatedEvent(c, ...) \
    openhab_inbox_events_InboxUpdatedEvent_((c), (openhab_inbox_events_InboxUpdatedEvent_args){ ._ = 0, __VA_ARGS__ })

/* ── LinkEvents ──────────────────────────────────────────────────────────── */

/**
 * Get events for added item-channel links.
 *
 * :param itemName: The name of the item (default is "*").
 * :param channelUID: The UID of the channel (default is "*").
 *
 * :return: A SSE stream of added item-channel link events.
 *
 * Optional (named) arguments: .itemName, .channelUID
 */
typedef struct {
    int _;
    const char* itemName;  /* default: '*' */
    const char* channelUID;  /* default: '*' */
} openhab_link_events_ItemChannelLinkAddedEvent_args;
OPENHAB_API openhab_sse_t* openhab_link_events_ItemChannelLinkAddedEvent_(openhab_client_t* client, openhab_link_events_ItemChannelLinkAddedEvent_args a);
#define openhab_link_events_ItemChannelLinkAddedEvent(c, ...) \
    openhab_link_events_ItemChannelLinkAddedEvent_((c), (openhab_link_events_ItemChannelLinkAddedEvent_args){ ._ = 0, __VA_ARGS__ })

/**
 * Get events for removed item-channel links.
 *
 * :param itemName: The name of the item (default is "*").
 * :param channelUID: The UID of the channel (default is "*").
 *
 * :return: A SSE stream of removed item-channel link events.
 *
 * Optional (named) arguments: .itemName, .channelUID
 */
typedef struct {
    int _;
    const char* itemName;  /* default: '*' */
    const char* channelUID;  /* default: '*' */
} openhab_link_events_ItemChannelLinkRemovedEvent_args;
OPENHAB_API openhab_sse_t* openhab_link_events_ItemChannelLinkRemovedEvent_(openhab_client_t* client, openhab_link_events_ItemChannelLinkRemovedEvent_args a);
#define openhab_link_events_ItemChannelLinkRemovedEvent(c, ...) \
    openhab_link_events_ItemChannelLinkRemovedEvent_((c), (openhab_link_events_ItemChannelLinkRemovedEvent_args){ ._ = 0, __VA_ARGS__ })

/* ── ChannelEvents ───────────────────────────────────────────────────────── */

/**
 * Get events for changes in channel descriptions.
 *
 * :param channelUID: The UID of the channel (default is "*").
 *
 * :return: A SSE stream of channel description changed events.
 *
 * Optional (named) arguments: .channelUID
 */
typedef struct {
    int _;
    const char* channelUID;  /* default: '*' */
} openhab_channel_events_ChannelDescriptionChangedEvent_args;
OPENHAB_API openhab_sse_t* openhab_channel_events_ChannelDescriptionChangedEvent_(openhab_client_t* client, openhab_channel_events_ChannelDescriptionChangedEvent_args a);
#define openhab_channel_events_ChannelDescriptionChangedEvent(c, ...) \
    openhab_channel_events_ChannelDescriptionChangedEvent_((c), (openhab_channel_events_ChannelDescriptionChangedEvent_args){ ._ = 0, __VA_ARGS__ })

/**
 * Get events for triggered channels.
 *
 * :param channelUID: The UID of the channel (default is "*").
 *
 * :return: A SSE stream of channel triggered events.
 *
 * Optional (named) arguments: .channelUID
 */
typedef struct {
    int _;
    const char* channelUID;  /* default: '*' */
} openhab_channel_events_ChannelTriggeredEvent_args;
OPENHAB_API openhab_sse_t* openhab_channel_events_ChannelTriggeredEvent_(openhab_client_t* client, openhab_channel_events_ChannelTriggeredEvent_args a);
#define openhab_channel_events_ChannelTriggeredEvent(c, ...) \
    openhab_channel_events_ChannelTriggeredEvent_((c), (openhab_channel_events_ChannelTriggeredEvent_args){ ._ = 0, __VA_ARGS__ })

/* ── Iconsets ────────────────────────────────────────────────────────────── */

/**
 * Gets all icon sets.
 *
 * :param language: Optional language preference for the response (e.g. 'en', 'de').
 *
 * :return: A list of icon sets with details such as ID, label, description and supported formats.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_iconsets_getIconsets_args;
OPENHAB_API cJSON* openhab_iconsets_getIconsets_(openhab_client_t* client, openhab_iconsets_getIconsets_args a);
#define openhab_iconsets_getIconsets(c, ...) \
    openhab_iconsets_getIconsets_((c), (openhab_iconsets_getIconsets_args){ ._ = 0, __VA_ARGS__ })

/* ── Inbox ───────────────────────────────────────────────────────────────── */

/**
 * Get all discovered things.
 *
 * :param includeIgnored: Whether ignored entries should also be included (default: True).
 *
 * :return: A list of discovered things with details such as UID, flag, label, and properties.
 *
 * Optional (named) arguments: .includeIgnored
 */
typedef struct {
    int _;
    openhab_flag includeIgnored;  /* default: True */
} openhab_inbox_getDiscoveredThings_args;
OPENHAB_API cJSON* openhab_inbox_getDiscoveredThings_(openhab_client_t* client, openhab_inbox_getDiscoveredThings_args a);
#define openhab_inbox_getDiscoveredThings(c, ...) \
    openhab_inbox_getDiscoveredThings_((c), (openhab_inbox_getDiscoveredThings_args){ ._ = 0, __VA_ARGS__ })

/**
 * Removes the discovery result from the inbox.
 *
 * :param thingUID: The UID of the discovered thing to be removed.
 *
 * :return: The API response to the delete request.
 */
OPENHAB_API cJSON* openhab_inbox_removeDiscoveryResult(openhab_client_t* client, const char* thingUID);

/**
 * Approves the discovery result by adding the thing to the registry.
 *
 * :param thingUID: The UID of the discovered thing.
 * :param thingLabel: The new name of the thing.
 * :param newThingID: Optional: The new thing ID.
 * :param language: Optional: Language preference for the response.
 *
 * :return: The API response to the approval request.
 *
 * Optional (named) arguments: .newThingID, .language
 */
typedef struct {
    int _;
    const char* newThingID;  /* default: None */
    const char* language;  /* default: None */
} openhab_inbox_approveDiscoveryResult_args;
OPENHAB_API cJSON* openhab_inbox_approveDiscoveryResult_(openhab_client_t* client, const char* thingUID, const char* thingLabel, openhab_inbox_approveDiscoveryResult_args a);
#define openhab_inbox_approveDiscoveryResult(c, thingUID, thingLabel, ...) \
    openhab_inbox_approveDiscoveryResult_((c), (thingUID), (thingLabel), (openhab_inbox_approveDiscoveryResult_args){ ._ = 0, __VA_ARGS__ })

/**
 * Flags a discovery result as ignored for further processing.
 *
 * :param thingUID: The UID of the discovered thing.
 *
 * :return: The API response to the ignore request.
 */
OPENHAB_API cJSON* openhab_inbox_ignoreDiscoveryResult(openhab_client_t* client, const char* thingUID);

/**
 * Removes the ignore flag from a discovery result.
 *
 * :param thingUID: The UID of the discovered thing.
 *
 * :return: The API response to the unignore request.
 */
OPENHAB_API cJSON* openhab_inbox_unignoreDiscoveryResult(openhab_client_t* client, const char* thingUID);

/* ── Items ───────────────────────────────────────────────────────────────── */

/**
 * Get all available items.
 *
 * :param type: Optional; Item type filter.
 * :param tags: Optional; Item tag filter.
 * :param metadata: Optional; Metadata selector (default: .*).
 * :param recursive: Optional; Whether to fetch group members recursively (default: False).
 * :param fields: Optional; Limit to specific fields (comma-separated).
 * :param staticDataOnly: Optional; Only returns cached data (default: False).
 * :param language: Optional; Language filter for headers "Accept-Language".
 * :param parents: Optional; Include the parent groups of each item (openHAB 4.1+).
 *
 * :return: A list containing the item data as returned by the API.
 *
 * Optional (named) arguments: .type, .tags, .metadata, .recursive, .fields, .staticDataOnly, .language, .parents
 */
typedef struct {
    int _;
    const char* type;  /* default: None */
    const char* tags;  /* default: None */
    const char* metadata;  /* default: '.*' */
    openhab_flag recursive;  /* default: False */
    const char* fields;  /* default: None */
    openhab_flag staticDataOnly;  /* default: False */
    const char* language;  /* default: None */
    openhab_flag parents;  /* default: None */
} openhab_items_getItems_args;
OPENHAB_API cJSON* openhab_items_getItems_(openhab_client_t* client, openhab_items_getItems_args a);
#define openhab_items_getItems(c, ...) \
    openhab_items_getItems_((c), (openhab_items_getItems_args){ ._ = 0, __VA_ARGS__ })

/**
 * Adds a list of items to the registry or updates the existing items.
 *
 * :param items: A list of item data (Dictionary).
 *
 * :return: A response object or confirmation that the items were successfully added or updated.
 */
OPENHAB_API cJSON* openhab_items_addOrUpdateItems(openhab_client_t* client, const cJSON* items);

/**
 * Gets a single item.
 *
 * :param itemName: The name of the item.
 * :param metadata: Optional; Metadata selector (default: .*).
 * :param recursive: Optional; Whether to fetch group members recursively (default: True).
 * :param language: Optional; Language filter for headers "Accept-Language".
 *
 * :return: A dictionary containing the requested item data.
 *
 * Optional (named) arguments: .metadata, .recursive, .language, .parents
 */
typedef struct {
    int _;
    const char* metadata;  /* default: '.*' */
    openhab_flag recursive;  /* default: True */
    const char* language;  /* default: None */
    openhab_flag parents;  /* default: None */
} openhab_items_getItem_args;
OPENHAB_API cJSON* openhab_items_getItem_(openhab_client_t* client, const char* itemName, openhab_items_getItem_args a);
#define openhab_items_getItem(c, itemName, ...) \
    openhab_items_getItem_((c), (itemName), (openhab_items_getItem_args){ ._ = 0, __VA_ARGS__ })

/**
 * Adds a new item to the registry or updates the existing item.
 *
 * :param itemName: The name of the item.
 * :param itemData: The data of the item (Dictionary).
 * :param language: Optional; Language filter for headers "Accept-Language".
 *
 * :return: A response object or confirmation that the item was successfully added or updated.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_items_addOrUpdateItem_args;
OPENHAB_API cJSON* openhab_items_addOrUpdateItem_(openhab_client_t* client, const char* itemName, const cJSON* itemData, openhab_items_addOrUpdateItem_args a);
#define openhab_items_addOrUpdateItem(c, itemName, itemData, ...) \
    openhab_items_addOrUpdateItem_((c), (itemName), (itemData), (openhab_items_addOrUpdateItem_args){ ._ = 0, __VA_ARGS__ })

/**
 * Sends a command to an item.
 *
 * :param itemName: The name of the item.
 * :param command: The command to be sent (e.g., ON, OFF).
 * :param source: Optional; Source of the command, shown in the event (openHAB 4.1+).
 *
 * :return: A response object or confirmation that the command was successfully sent.
 *
 * Optional (named) arguments: .source
 */
typedef struct {
    int _;
    const char* source;  /* default: None */
} openhab_items_sendCommand_args;
OPENHAB_API cJSON* openhab_items_sendCommand_(openhab_client_t* client, const char* itemName, const char* command, openhab_items_sendCommand_args a);
#define openhab_items_sendCommand(c, itemName, command, ...) \
    openhab_items_sendCommand_((c), (itemName), (command), (openhab_items_sendCommand_args){ ._ = 0, __VA_ARGS__ })

/**
 * Updates the state of an item.
 *
 * :param itemName: The name of the item.
 * :param state: The state to be signaled for the item.
 *
 * :return: A response object or confirmation that the state was successfully updated.
 *
 * Optional (named) arguments: .source
 */
typedef struct {
    int _;
    const char* source;  /* default: None */
} openhab_items_postUpdate_args;
OPENHAB_API cJSON* openhab_items_postUpdate_(openhab_client_t* client, const char* itemName, const char* state, openhab_items_postUpdate_args a);
#define openhab_items_postUpdate(c, itemName, state, ...) \
    openhab_items_postUpdate_((c), (itemName), (state), (openhab_items_postUpdate_args){ ._ = 0, __VA_ARGS__ })

/**
 * Removes an item from the registry.
 *
 * :param itemName: The name of the item.
 *
 * :return: A response object or confirmation that the item was successfully deleted.
 */
OPENHAB_API cJSON* openhab_items_deleteItem(openhab_client_t* client, const char* itemName);

/**
 * Adds a new member to a group item.
 *
 * :param itemName: The name of the group item.
 * :param memberItemName: The name of the member item.
 *
 * :return: A response object or confirmation that the group member was successfully added.
 */
OPENHAB_API cJSON* openhab_items_addGroupMember(openhab_client_t* client, const char* itemName, const char* memberItemName);

/**
 * Removes an existing member from a group item.
 *
 * :param itemName: The name of the group item.
 * :param memberItemName: The name of the member item.
 *
 * :return: A response object or confirmation that the group member was successfully removed.
 */
OPENHAB_API cJSON* openhab_items_removeGroupMember(openhab_client_t* client, const char* itemName, const char* memberItemName);

/**
 * Adds metadata to an item.
 *
 * :param itemName: The name of the item.
 * :param namespace: The namespace of the metadata.
 * :param metadata: A dictionary containing the metadata.
 *
 * :return: A response object or confirmation that the metadata was successfully added.
 */
OPENHAB_API cJSON* openhab_items_addMetadata(openhab_client_t* client, const char* itemName, const char* namespace_, const cJSON* metadata);

/**
 * Removes metadata from an item.
 *
 * :param itemName: The name of the item.
 * :param namespace: The namespace of the metadata.
 *
 * :return: A response object or confirmation that the metadata was successfully removed.
 */
OPENHAB_API cJSON* openhab_items_removeMetadata(openhab_client_t* client, const char* itemName, const char* namespace_);

/**
 * Gets the namespaces of an item.
 *
 * :param itemName: The name of the item.
 * :param language: Optional; Language filter for headers "Accept-Language".
 *
 * :return: A list of namespaces associated with the item.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_items_getMetadataNamespaces_args;
OPENHAB_API cJSON* openhab_items_getMetadataNamespaces_(openhab_client_t* client, const char* itemName, openhab_items_getMetadataNamespaces_args a);
#define openhab_items_getMetadataNamespaces(c, itemName, ...) \
    openhab_items_getMetadataNamespaces_((c), (itemName), (openhab_items_getMetadataNamespaces_args){ ._ = 0, __VA_ARGS__ })

/**
 * Gets the item that defines the requested semantics of an item.
 *
 * :param itemName: The name of the item.
 * :param semanticClass: The requested semantic class.
 * :param language: Optional; Language filter for headers "Accept-Language".
 *
 * :return: A dictionary containing the semantic item data.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_items_getSemanticItem_args;
OPENHAB_API cJSON* openhab_items_getSemanticItem_(openhab_client_t* client, const char* itemName, const char* semanticClass, openhab_items_getSemanticItem_args a);
#define openhab_items_getSemanticItem(c, itemName, semanticClass, ...) \
    openhab_items_getSemanticItem_((c), (itemName), (semanticClass), (openhab_items_getSemanticItem_args){ ._ = 0, __VA_ARGS__ })

/**
 * Gets the state of an item.
 *
 * :param itemName: The name of the item.
 *
 * :return: A dictionary containing the current state of the item.
 */
OPENHAB_API cJSON* openhab_items_getItemState(openhab_client_t* client, const char* itemName);

/**
 * Updates the state of an item.
 *
 * :param itemName: The name of the item.
 * :param state: The new state of the item.
 * :param language: Optional; Language filter for headers "Accept-Language".
 *
 * :return: A response object or confirmation that the state was successfully updated.
 *
 * Optional (named) arguments: .language, .source
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
    const char* source;  /* default: None */
} openhab_items_updateItemState_args;
OPENHAB_API cJSON* openhab_items_updateItemState_(openhab_client_t* client, const char* itemName, const char* state, openhab_items_updateItemState_args a);
#define openhab_items_updateItemState(c, itemName, state, ...) \
    openhab_items_updateItemState_((c), (itemName), (state), (openhab_items_updateItemState_args){ ._ = 0, __VA_ARGS__ })

/**
 * Adds a tag to an item.
 *
 * :param itemName: The name of the item.
 * :param tag: The tag to be added.
 *
 * :return: A response object or confirmation that the tag was successfully added.
 */
OPENHAB_API cJSON* openhab_items_addTag(openhab_client_t* client, const char* itemName, const char* tag);

/**
 * Removes a tag from an item.
 *
 * :param itemName: The name of the item.
 * :param tag: The tag to be removed.
 *
 * :return: A response object or confirmation that the tag was successfully removed.
 */
OPENHAB_API cJSON* openhab_items_removeTag(openhab_client_t* client, const char* itemName, const char* tag);

/**
 * Remove unused/orphaned metadata.
 *
 * :return: A response object or confirmation that orphaned metadata was successfully purged.
 */
OPENHAB_API cJSON* openhab_items_purgeOrphanedMetadata(openhab_client_t* client);

/* ── Links ───────────────────────────────────────────────────────────────── */

/**
 * Gets all available links.
 *
 * :param channelUID: Optional; Filters by the Channel UID.
 * :param itemName: Optional; Filters by the Item Name.
 *
 * :return: A list of links containing details such as ItemName, ChannelUID, and configuration.
 *
 * Optional (named) arguments: .channelUID, .itemName
 */
typedef struct {
    int _;
    const char* channelUID;  /* default: None */
    const char* itemName;  /* default: None */
} openhab_links_getLinks_args;
OPENHAB_API cJSON* openhab_links_getLinks_(openhab_client_t* client, openhab_links_getLinks_args a);
#define openhab_links_getLinks(c, ...) \
    openhab_links_getLinks_((c), (openhab_links_getLinks_args){ ._ = 0, __VA_ARGS__ })

/**
 * Retrieves an individual link.
 *
 * :param itemName: The name of the item.
 * :param channelUID: The UID of the channel.
 *
 * :return: The link with details of the item, channel UID, and configuration.
 */
OPENHAB_API cJSON* openhab_links_getLink(openhab_client_t* client, const char* itemName, const char* channelUID);

/**
 * Links an item to a channel.
 *
 * :param itemName: The name of the item.
 * :param channelUID: The UID of the channel.
 * :param configuration: The configuration for the link.
 *
 * :return: The API response when the link is successfully created.
 */
OPENHAB_API cJSON* openhab_links_linkItemToChannel(openhab_client_t* client, const char* itemName, const char* channelUID, const cJSON* configuration);

/**
 * Unlinks an item from a channel.
 *
 * :param itemName: The name of the item.
 * :param channelUID: The UID of the channel.
 *
 * :return: The API response when the link is successfully removed.
 */
OPENHAB_API cJSON* openhab_links_unlinkItemFromChannel(openhab_client_t* client, const char* itemName, const char* channelUID);

/**
 * Delete all links that refer to an item or thing.
 *
 * :param object: The name of the item or the UID of the thing.
 *
 * :return: The API response when all links are successfully deleted.
 */
OPENHAB_API cJSON* openhab_links_deleteAllLinks(openhab_client_t* client, const char* object);

/**
 * Get orphan links between items and broken/non-existent thing channels.
 *
 * :return: A list of orphan links.
 */
OPENHAB_API cJSON* openhab_links_getOrphanLinks(openhab_client_t* client);

/**
 * Remove unused/orphaned links.
 *
 * :return: The API response when the links are successfully removed.
 */
OPENHAB_API cJSON* openhab_links_purgeUnusedLinks(openhab_client_t* client);

/* ── Logging ─────────────────────────────────────────────────────────────── */

/**
 * Get all loggers.
 *
 * :return: A list of loggers with names and levels.
 */
OPENHAB_API cJSON* openhab_logging_getLoggers(openhab_client_t* client);

/**
 * Get a single logger.
 *
 * :param loggerName: The name of the logger.
 *
 * :return: The logger with the specified name and level.
 */
OPENHAB_API cJSON* openhab_logging_getLogger(openhab_client_t* client, const char* loggerName);

/**
 * Modify or add a logger.
 *
 * :param loggerName: The name of the logger.
 * :param level: The level of the logger.
 *
 * :return: The API response after modification or addition.
 */
OPENHAB_API cJSON* openhab_logging_modifyOrAddLogger(openhab_client_t* client, const char* loggerName, const char* level);

/**
 * Remove a single logger.
 *
 * :param loggerName: The name of the logger.
 *
 * :return: The API response after removing the logger.
 */
OPENHAB_API cJSON* openhab_logging_removeLogger(openhab_client_t* client, const char* loggerName);

/* ── ModuleTypes ─────────────────────────────────────────────────────────── */

/**
 * Get all available module types.
 *
 * :param tags: Optional filter for tags.
 * :param typeFilter: Optional filter for the type (action, condition, trigger).
 * :param language: (Optional) Language setting for the Accept-Language header.
 *
 * :return: A list of module types.
 *
 * Optional (named) arguments: .tags, .typeFilter, .language
 */
typedef struct {
    int _;
    const char* tags;  /* default: None */
    const char* typeFilter;  /* default: None */
    const char* language;  /* default: None */
} openhab_module_types_getModuleTypes_args;
OPENHAB_API cJSON* openhab_module_types_getModuleTypes_(openhab_client_t* client, openhab_module_types_getModuleTypes_args a);
#define openhab_module_types_getModuleTypes(c, ...) \
    openhab_module_types_getModuleTypes_((c), (openhab_module_types_getModuleTypes_args){ ._ = 0, __VA_ARGS__ })

/**
 * Gets a module type corresponding to the given UID.
 *
 * :param moduleTypeUID: The UID of the module type.
 * :param language: (Optional) Language setting for the Accept-Language header.
 *
 * :return: A dictionary with the module type information.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_module_types_getModuleType_args;
OPENHAB_API cJSON* openhab_module_types_getModuleType_(openhab_client_t* client, const char* moduleTypeUID, openhab_module_types_getModuleType_args a);
#define openhab_module_types_getModuleType(c, moduleTypeUID, ...) \
    openhab_module_types_getModuleType_((c), (moduleTypeUID), (openhab_module_types_getModuleType_args){ ._ = 0, __VA_ARGS__ })

/* ── Persistence ─────────────────────────────────────────────────────────── */

/**
 * Gets a list of persistence services.
 *
 * :return: A list of persistence services with IDs, labels, and types.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_persistence_getServices_args;
OPENHAB_API cJSON* openhab_persistence_getServices_(openhab_client_t* client, openhab_persistence_getServices_args a);
#define openhab_persistence_getServices(c, ...) \
    openhab_persistence_getServices_((c), (openhab_persistence_getServices_args){ ._ = 0, __VA_ARGS__ })

/**
 * Gets a persistence service configuration.
 *
 * :param serviceID: The ID of the persistence service.
 *
 * :return: The configuration of the service.
 */
OPENHAB_API cJSON* openhab_persistence_getServiceConfiguration(openhab_client_t* client, const char* serviceID);

/**
 * Sets a persistence service configuration.
 *
 * :param serviceID: The ID of the persistence service.
 * :param config: The configuration data.
 *
 * :return: The response from the API after modification.
 */
OPENHAB_API cJSON* openhab_persistence_setServiceConfiguration(openhab_client_t* client, const char* serviceID, const cJSON* config);

/**
 * Deletes a persistence service configuration.
 *
 * :param serviceID: The ID of the persistence service.
 *
 * :return: The response from the API after deleting the configuration.
 */
OPENHAB_API cJSON* openhab_persistence_deleteServiceConfiguration(openhab_client_t* client, const char* serviceID);

/**
 * Gets a list of items available via a specific persistence service.
 *
 * :param serviceID: Optional; The ID of the persistence service (default service if omitted).
 * :param itemName: Optional; Only return information for this item.
 *
 * :return: A list of items with their last and earliest timestamps.
 *
 * Optional (named) arguments: .serviceID, .itemName
 */
typedef struct {
    int _;
    const char* serviceID;  /* default: None */
    const char* itemName;  /* default: None */
} openhab_persistence_getItemsFromService_args;
OPENHAB_API cJSON* openhab_persistence_getItemsFromService_(openhab_client_t* client, openhab_persistence_getItemsFromService_args a);
#define openhab_persistence_getItemsFromService(c, ...) \
    openhab_persistence_getItemsFromService_((c), (openhab_persistence_getItemsFromService_args){ ._ = 0, __VA_ARGS__ })

/**
 * Gets item persistence data from the persistence service.
 *
 * :param itemName: The name of the item.
 * :param serviceID: Optional; The ID of the persistence service. If omitted, the default service is used.
 * :param startTime: Optional; Start time (ISO 8601, e.g. "2026-10-30T00:00:00.000Z"). Defaults to 1 day before `endTime`.
 * :param endTime: Optional; End time (ISO 8601). Defaults to the current time.
 * :param page: Optional; Page number, starting at 0. Paging is only active if `pageLength` is set as well.
 * :param pageLength: Optional; Number of data points per page. Without it, all data points are returned.
 * :param boundary: Optional; Also return the values just before and after the time range (default: False).
 * :param itemState: Optional; Add the current item state at the end of the series (default: False).
 * :param displayState: Optional; Add a formatted display state to every data point (openHAB 5.0+).
 * :param language: Optional; Value for the "Accept-Language" header.
 *
 * :return: The retrieved data points of the item.
 *
 * Optional (named) arguments: .serviceID, .startTime, .endTime, .page, .pageLength, .boundary, .itemState, .displayState, .language
 */
typedef struct {
    int _;
    const char* serviceID;  /* default: None */
    const char* startTime;  /* default: None */
    const char* endTime;  /* default: None */
    int page;  /* default: None */
    int pageLength;  /* default: None */
    openhab_flag boundary;  /* default: False */
    openhab_flag itemState;  /* default: False */
    openhab_flag displayState;  /* default: None */
    const char* language;  /* default: None */
} openhab_persistence_getItemPersistenceData_args;
OPENHAB_API cJSON* openhab_persistence_getItemPersistenceData_(openhab_client_t* client, const char* itemName, openhab_persistence_getItemPersistenceData_args a);
#define openhab_persistence_getItemPersistenceData(c, itemName, ...) \
    openhab_persistence_getItemPersistenceData_((c), (itemName), (openhab_persistence_getItemPersistenceData_args){ ._ = 0, __VA_ARGS__ })

/**
 * Stores item persistence data into the persistence service.
 *
 * :param serviceID: The ID of the persistence service.
 * :param itemName: The name of the item.
 * :param time: The time of the storage.
 * :param state: The state of the item to be stored.
 *
 * :return: The response from the API after storing the data.
 *
 * Optional (named) arguments: .serviceID
 */
typedef struct {
    int _;
    const char* serviceID;  /* default: None */
} openhab_persistence_storeItemData_args;
OPENHAB_API cJSON* openhab_persistence_storeItemData_(openhab_client_t* client, const char* itemName, const char* time, const char* state, openhab_persistence_storeItemData_args a);
#define openhab_persistence_storeItemData(c, itemName, time, state, ...) \
    openhab_persistence_storeItemData_((c), (itemName), (time), (state), (openhab_persistence_storeItemData_args){ ._ = 0, __VA_ARGS__ })

/**
 * Deletes item persistence data from a specific persistence service in a given time range.
 *
 * :param serviceID: The ID of the persistence service.
 * :param itemName: The name of the item.
 * :param startTime: The start time of the data to be deleted.
 * :param endTime: The end time of the data to be deleted.
 *
 * :return: The response from the API after deleting the data.
 */
OPENHAB_API cJSON* openhab_persistence_deleteItemData(openhab_client_t* client, const char* itemName, const char* startTime, const char* endTime, const char* serviceID);

/* ── ProfileTypes ────────────────────────────────────────────────────────── */

/**
 * Gets all available profile types.
 *
 * :param channelTypeUID: Optional filter for the channel type.
 * :param itemType: Optional filter for the item type.
 * :param language: (Optional) Language setting for the Accept-Language header.
 *
 * :return: A list of profile types.
 *
 * Optional (named) arguments: .channelTypeUID, .itemType, .language
 */
typedef struct {
    int _;
    const char* channelTypeUID;  /* default: None */
    const char* itemType;  /* default: None */
    const char* language;  /* default: None */
} openhab_profile_types_getProfileTypes_args;
OPENHAB_API cJSON* openhab_profile_types_getProfileTypes_(openhab_client_t* client, openhab_profile_types_getProfileTypes_args a);
#define openhab_profile_types_getProfileTypes(c, ...) \
    openhab_profile_types_getProfileTypes_((c), (openhab_profile_types_getProfileTypes_args){ ._ = 0, __VA_ARGS__ })

/* ── Rules ───────────────────────────────────────────────────────────────── */

/**
 * Get available rules, optionally filtered by tags and/or prefix.
 *
 * :param prefix: Optional prefix to filter the results.
 * :param tags: Optional tag array to filter the results.
 * :param summary: If true, only summary fields will be returned.
 * :param staticDataOnly: If true, only static data will be returned.
 *
 * :return: A list of rules (JSON objects).
 *
 * Optional (named) arguments: .prefix, .tags, .summary, .staticDataOnly
 */
typedef struct {
    int _;
    const char* prefix;  /* default: None */
    const char* tags;  /* default: None */
    openhab_flag summary;  /* default: False */
    openhab_flag staticDataOnly;  /* default: False */
} openhab_rules_getRules_args;
OPENHAB_API cJSON* openhab_rules_getRules_(openhab_client_t* client, openhab_rules_getRules_args a);
#define openhab_rules_getRules(c, ...) \
    openhab_rules_getRules_((c), (openhab_rules_getRules_args){ ._ = 0, __VA_ARGS__ })

/**
 * Creates a rule.
 *
 * :param ruleData: The rule data to be created (as a dictionary).
 *
 * :return: The created rule (JSON).
 */
OPENHAB_API cJSON* openhab_rules_createRule(openhab_client_t* client, const cJSON* ruleData);

/**
 * Gets the rule corresponding to the given UID.
 *
 * :param ruleUID: The UID of the rule to retrieve.
 *
 * :return: The rule object (JSON).
 */
OPENHAB_API cJSON* openhab_rules_getRule(openhab_client_t* client, const char* ruleUID);

/**
 * Updates an existing rule corresponding to the given UID.
 *
 * :param ruleUID: The UID of the rule to update.
 * :param ruleData: The new rule data (as a dictionary).
 *
 * :return: The updated rule (JSON).
 */
OPENHAB_API cJSON* openhab_rules_updateRule(openhab_client_t* client, const char* ruleUID, const cJSON* ruleData);

/**
 * Removes an existing rule corresponding to the given UID.
 *
 * :param ruleUID: The UID of the rule to delete.
 *
 * :return: The API response (status code).
 */
OPENHAB_API cJSON* openhab_rules_deleteRule(openhab_client_t* client, const char* ruleUID);

/**
 * Gets the rule's module corresponding to the given category and ID.
 *
 * :param ruleUID: The UID of the rule.
 * :param moduleCategory: The category of the module.
 * :param moduleID: The ID of the module.
 *
 * :return: The module (JSON).
 */
OPENHAB_API cJSON* openhab_rules_getModule(openhab_client_t* client, const char* ruleUID, const char* moduleCategory, const char* moduleID);

/**
 * Gets the module's configuration.
 *
 * :param ruleUID: The UID of the rule.
 * :param moduleCategory: The category of the module.
 * :param moduleID: The ID of the module.
 *
 * :return: The module configuration (JSON).
 */
OPENHAB_API cJSON* openhab_rules_getModuleConfig(openhab_client_t* client, const char* ruleUID, const char* moduleCategory, const char* moduleID);

/**
 * Gets the module's configuration parameter.
 *
 * :param ruleUID: The UID of the rule.
 * :param moduleCategory: The category of the module.
 * :param moduleID: The ID of the module.
 * :param param: The name of the configuration parameter.
 *
 * :return: The configuration parameter value (JSON).
 */
OPENHAB_API cJSON* openhab_rules_getModuleConfigParam(openhab_client_t* client, const char* ruleUID, const char* moduleCategory, const char* moduleID, const char* param);

/**
 * Sets the module's configuration parameter value.
 *
 * :param ruleUID: The UID of the rule.
 * :param moduleCategory: The category of the module.
 * :param moduleID: The ID of the module.
 * :param param: The name of the configuration parameter.
 * :param value: The value to set for the configuration parameter.
 *
 * :return: The API response (status code).
 */
OPENHAB_API cJSON* openhab_rules_setModuleConfigParam(openhab_client_t* client, const char* ruleUID, const char* moduleCategory, const char* moduleID, const char* param, const char* value);

/**
 * Gets the rule actions.
 *
 * :param ruleUID: The UID of the rule.
 *
 * :return: A list of actions (JSON).
 */
OPENHAB_API cJSON* openhab_rules_getActions(openhab_client_t* client, const char* ruleUID);

/**
 * Gets the rule conditions.
 *
 * :param ruleUID: The UID of the rule.
 *
 * :return: A list of conditions (JSON).
 */
OPENHAB_API cJSON* openhab_rules_getConditions(openhab_client_t* client, const char* ruleUID);

/**
 * Gets the rule configuration values.
 *
 * :param ruleUID: The UID of the rule.
 *
 * :return: The configuration of the rule (JSON).
 */
OPENHAB_API cJSON* openhab_rules_getConfiguration(openhab_client_t* client, const char* ruleUID);

/**
 * Sets the rule configuration values.
 *
 * :param ruleUID: The UID of the rule.
 * :param configData: The new configuration data (as a dictionary).
 *
 * :return: The updated configuration (JSON).
 */
OPENHAB_API cJSON* openhab_rules_updateConfiguration(openhab_client_t* client, const char* ruleUID, const cJSON* configData);

/**
 * Sets the rule configuration values. Activates or deactivates the rule.
 *
 * :param ruleUID: The UID of the rule.
 * :param enable: If true, the rule will be activated. If false, the rule will be deactivated.
 *
 * :return: The API response (status code).
 */
OPENHAB_API cJSON* openhab_rules_setRuleState(openhab_client_t* client, const char* ruleUID, int enable);

/**
 */
OPENHAB_API cJSON* openhab_rules_enable(openhab_client_t* client, const char* ruleUID);

/**
 */
OPENHAB_API cJSON* openhab_rules_disable(openhab_client_t* client, const char* ruleUID);

/**
 * Executes the rule's actions immediately.
 *
 * :param ruleUID: The UID of the rule.
 * :param contextData: Optional context data for executing the rule.
 *
 * :return: The API response (status code).
 *
 * Optional (named) arguments: .contextData
 */
typedef struct {
    int _;
    const cJSON* contextData;  /* default: None */
} openhab_rules_runNow_args;
OPENHAB_API cJSON* openhab_rules_runNow_(openhab_client_t* client, const char* ruleUID, openhab_rules_runNow_args a);
#define openhab_rules_runNow(c, ruleUID, ...) \
    openhab_rules_runNow_((c), (ruleUID), (openhab_rules_runNow_args){ ._ = 0, __VA_ARGS__ })

/**
 * Gets the rule triggers.
 *
 * :param ruleUID: The UID of the rule.
 *
 * :return: A list of triggers (JSON).
 */
OPENHAB_API cJSON* openhab_rules_getTriggers(openhab_client_t* client, const char* ruleUID);

/**
 * Simulates the executions of rules filtered by tag 'Schedule' within the given times.
 *
 * :param fromTime: Simulates the executions of rules filtered by tag 'Schedule' within the given times.
 * :param untilTime: Simulates the executions of rules filtered by tag 'Schedule' within the given times.
 *
 * :return: The simulation results (JSON).
 */
OPENHAB_API cJSON* openhab_rules_simulateSchedule(openhab_client_t* client, const char* fromTime, const char* untilTime);

/* ── Services ────────────────────────────────────────────────────────────── */

/**
 * Get all configurable services.
 *
 * :param language: Optional language setting (as header).
 *
 * :return: A list of services (JSON).
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_services_getServices_args;
OPENHAB_API cJSON* openhab_services_getServices_(openhab_client_t* client, openhab_services_getServices_args a);
#define openhab_services_getServices(c, ...) \
    openhab_services_getServices_((c), (openhab_services_getServices_args){ ._ = 0, __VA_ARGS__ })

/**
 * Get configurable service for the given service ID.
 *
 * :param serviceID: The ID of the service to retrieve.
 * :param language: Optional language setting (as header).
 *
 * :return: The service object (JSON).
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_services_getService_args;
OPENHAB_API cJSON* openhab_services_getService_(openhab_client_t* client, const char* serviceID, openhab_services_getService_args a);
#define openhab_services_getService(c, serviceID, ...) \
    openhab_services_getService_((c), (serviceID), (openhab_services_getService_args){ ._ = 0, __VA_ARGS__ })

/**
 * Get service configuration for the given service ID.
 *
 * :param serviceID: The ID of the service.
 *
 * :return: The configuration of the service (JSON).
 */
OPENHAB_API cJSON* openhab_services_getServiceConfig(openhab_client_t* client, const char* serviceID);

/**
 * Updates a service configuration for the given service ID and returns the old configuration.
 *
 * :param serviceID: The ID of the service.
 * :param configData: The new configuration data (as a dictionary).
 *
 * :return: The old configuration of the service (JSON).
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_services_updateServiceConfig_args;
OPENHAB_API cJSON* openhab_services_updateServiceConfig_(openhab_client_t* client, const char* serviceID, const cJSON* configData, openhab_services_updateServiceConfig_args a);
#define openhab_services_updateServiceConfig(c, serviceID, configData, ...) \
    openhab_services_updateServiceConfig_((c), (serviceID), (configData), (openhab_services_updateServiceConfig_args){ ._ = 0, __VA_ARGS__ })

/**
 * Deletes a service configuration for the given service ID and returns the old configuration.
 *
 * :param serviceID: The ID of the service.
 *
 * :return: The old configuration of the service (JSON).
 */
OPENHAB_API cJSON* openhab_services_deleteServiceConfig(openhab_client_t* client, const char* serviceID);

/**
 * Get existing multiple context service configurations for the given factory PID.
 *
 * :param serviceID: The ID of the service.
 * :param language: Optional language setting (as header).
 *
 * :return: A list of contexts (JSON).
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_services_getServiceContexts_args;
OPENHAB_API cJSON* openhab_services_getServiceContexts_(openhab_client_t* client, const char* serviceID, openhab_services_getServiceContexts_args a);
#define openhab_services_getServiceContexts(c, serviceID, ...) \
    openhab_services_getServiceContexts_((c), (serviceID), (openhab_services_getServiceContexts_args){ ._ = 0, __VA_ARGS__ })

/* ── Sitemaps ────────────────────────────────────────────────────────────── */

/**
 * Get all available sitemaps.
 *
 * :return: A list of sitemaps (JSON).
 */
OPENHAB_API cJSON* openhab_sitemaps_getSitemaps(openhab_client_t* client);

/**
 * Get sitemap by name.
 *
 * :param sitemapName: The name of the sitemap to retrieve.
 * :param type: Optional query parameter for type.
 * :param jsonCallback: Optional query parameter for JSON callback.
 * :param includeHidden: Whether hidden widgets should be included.
 * :param language: Optional language setting (as header).
 *
 * :return: The sitemap object (JSON).
 *
 * Optional (named) arguments: .type, .jsonCallback, .includeHidden, .language
 */
typedef struct {
    int _;
    const char* type;  /* default: None */
    const char* jsonCallback;  /* default: None */
    openhab_flag includeHidden;  /* default: False */
    const char* language;  /* default: None */
} openhab_sitemaps_getSitemap_args;
OPENHAB_API cJSON* openhab_sitemaps_getSitemap_(openhab_client_t* client, const char* sitemapName, openhab_sitemaps_getSitemap_args a);
#define openhab_sitemaps_getSitemap(c, sitemapName, ...) \
    openhab_sitemaps_getSitemap_((c), (sitemapName), (openhab_sitemaps_getSitemap_args){ ._ = 0, __VA_ARGS__ })

/**
 * Polls the data for one page of a sitemap.
 *
 * :param sitemapName: The name of the sitemap.
 * :param pageID: The ID of the page.
 * :param subscriptionID: Optional query parameter for the subscription ID.
 * :param includeHidden: Whether hidden widgets should be included.
 * :param language: Optional language setting (as header).
 *
 * :return: The sitemap page (JSON).
 *
 * Optional (named) arguments: .subscriptionID, .includeHidden, .language
 */
typedef struct {
    int _;
    const char* subscriptionID;  /* default: None */
    openhab_flag includeHidden;  /* default: False */
    const char* language;  /* default: None */
} openhab_sitemaps_getSitemapPage_args;
OPENHAB_API cJSON* openhab_sitemaps_getSitemapPage_(openhab_client_t* client, const char* sitemapName, const char* pageID, openhab_sitemaps_getSitemapPage_args a);
#define openhab_sitemaps_getSitemapPage(c, sitemapName, pageID, ...) \
    openhab_sitemaps_getSitemapPage_((c), (sitemapName), (pageID), (openhab_sitemaps_getSitemapPage_args){ ._ = 0, __VA_ARGS__ })

/**
 * Polls the data for a whole sitemap. Not recommended due to potentially high traffic.
 *
 * :param sitemapName: The name of the sitemap.
 * :param subscriptionID: Optional query parameter for the subscription ID.
 * :param includeHidden: Whether hidden widgets should be included.
 * :param language: Optional language setting (as header).
 *
 * :return: The complete sitemap (JSON).
 *
 * Optional (named) arguments: .subscriptionID, .includeHidden, .language
 */
typedef struct {
    int _;
    const char* subscriptionID;  /* default: None */
    openhab_flag includeHidden;  /* default: False */
    const char* language;  /* default: None */
} openhab_sitemaps_getFullSitemap_args;
OPENHAB_API cJSON* openhab_sitemaps_getFullSitemap_(openhab_client_t* client, const char* sitemapName, openhab_sitemaps_getFullSitemap_args a);
#define openhab_sitemaps_getFullSitemap(c, sitemapName, ...) \
    openhab_sitemaps_getFullSitemap_((c), (sitemapName), (openhab_sitemaps_getFullSitemap_args){ ._ = 0, __VA_ARGS__ })

/**
 * Opens the event stream (SSE) of a sitemap subscription for one page.
 *
 * :param subscriptionID: The ID of the subscription (see subscribeToSitemapEvents()).
 * :param sitemapName: The name of the sitemap.
 * :param pageID: The ID of the page (the sitemap name for the home page).
 *
 * :return: A SSE stream (requests.Response, read it with iterSSEEvents()) or {"error": ...}.
 *
 * Optional (named) arguments: .sitemapName, .pageID
 */
typedef struct {
    int _;
    const char* sitemapName;  /* default: None */
    const char* pageID;  /* default: None */
} openhab_sitemaps_getSitemapEvents_args;
OPENHAB_API openhab_sse_t* openhab_sitemaps_getSitemapEvents_(openhab_client_t* client, const char* subscriptionID, openhab_sitemaps_getSitemapEvents_args a);
#define openhab_sitemaps_getSitemapEvents(c, subscriptionID, ...) \
    openhab_sitemaps_getSitemapEvents_((c), (subscriptionID), (openhab_sitemaps_getSitemapEvents_args){ ._ = 0, __VA_ARGS__ })

/**
 * Opens the event stream (SSE) of a sitemap subscription for the whole sitemap.
 * Not recommended due to potentially high traffic.
 *
 * :param subscriptionID: The ID of the subscription.
 * :param sitemapName: The name of the sitemap.
 *
 * :return: A SSE stream (requests.Response) or {"error": ...}.
 *
 * Optional (named) arguments: .sitemapName
 */
typedef struct {
    int _;
    const char* sitemapName;  /* default: None */
} openhab_sitemaps_getFullSitemapEvents_args;
OPENHAB_API openhab_sse_t* openhab_sitemaps_getFullSitemapEvents_(openhab_client_t* client, const char* subscriptionID, openhab_sitemaps_getFullSitemapEvents_args a);
#define openhab_sitemaps_getFullSitemapEvents(c, subscriptionID, ...) \
    openhab_sitemaps_getFullSitemapEvents_((c), (subscriptionID), (openhab_sitemaps_getFullSitemapEvents_args){ ._ = 0, __VA_ARGS__ })

/**
 * Creates a sitemap event subscription.
 *
 * :return: The response to the subscription request (JSON).
 */
OPENHAB_API cJSON* openhab_sitemaps_subscribeToSitemapEvents(openhab_client_t* client);

/* ── Systeminfo ──────────────────────────────────────────────────────────── */

/**
 * Gets information about the system.
 *
 * :return: A Dictionary with system informations.
 */
OPENHAB_API cJSON* openhab_systeminfo_getSystemInfo(openhab_client_t* client);

/**
 * Get all supported dimensions and their system units.
 *
 * :return: A Dictionary with UOM informations.
 */
OPENHAB_API cJSON* openhab_systeminfo_getUoMInfo(openhab_client_t* client);

/* ── Tags ────────────────────────────────────────────────────────────────── */

/**
 * Get all available semantic tags.
 *
 * :param language: Optional headers for language setting.
 *
 * :return: A list of semantic tags (JSON).
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_tags_getTags_args;
OPENHAB_API cJSON* openhab_tags_getTags_(openhab_client_t* client, openhab_tags_getTags_args a);
#define openhab_tags_getTags(c, ...) \
    openhab_tags_getTags_((c), (openhab_tags_getTags_args){ ._ = 0, __VA_ARGS__ })

/**
 * Creates a new semantic tag and adds it to the registry.
 *
 * :param tagData: The data object for the tag to be created.
 * :param language: Optional headers for language setting.
 *
 * :return: The response to the tag creation request (JSON).
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_tags_createTag_args;
OPENHAB_API cJSON* openhab_tags_createTag_(openhab_client_t* client, const cJSON* tagData, openhab_tags_createTag_args a);
#define openhab_tags_createTag(c, tagData, ...) \
    openhab_tags_createTag_((c), (tagData), (openhab_tags_createTag_args){ ._ = 0, __VA_ARGS__ })

/**
 * Gets a semantic tag and its sub-tags.
 *
 * :param tagID: The ID of the tag to retrieve.
 * :param language: Optional headers for language setting.
 *
 * :return: The tag object and its sub-tags (JSON).
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_tags_getTag_args;
OPENHAB_API cJSON* openhab_tags_getTag_(openhab_client_t* client, const char* tagID, openhab_tags_getTag_args a);
#define openhab_tags_getTag(c, tagID, ...) \
    openhab_tags_getTag_((c), (tagID), (openhab_tags_getTag_args){ ._ = 0, __VA_ARGS__ })

/**
 * Updates a semantic tag.
 *
 * :param tagID: The ID of the tag to be updated.
 * :param tagData: The new tag data.
 * :param language: Optional headers for language setting.
 *
 * :return: The response to the tag update request (JSON).
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_tags_updateTag_args;
OPENHAB_API cJSON* openhab_tags_updateTag_(openhab_client_t* client, const char* tagID, const cJSON* tagData, openhab_tags_updateTag_args a);
#define openhab_tags_updateTag(c, tagID, tagData, ...) \
    openhab_tags_updateTag_((c), (tagID), (tagData), (openhab_tags_updateTag_args){ ._ = 0, __VA_ARGS__ })

/**
 * Removes a semantic tag and its sub-tags from the registry.
 *
 * :param tagID: The ID of the tag to be removed.
 * :param language: Optional headers for language setting.
 *
 * :return: The response to the tag deletion request (JSON).
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_tags_deleteTag_args;
OPENHAB_API cJSON* openhab_tags_deleteTag_(openhab_client_t* client, const char* tagID, openhab_tags_deleteTag_args a);
#define openhab_tags_deleteTag(c, tagID, ...) \
    openhab_tags_deleteTag_((c), (tagID), (openhab_tags_deleteTag_args){ ._ = 0, __VA_ARGS__ })

/* ── Templates ───────────────────────────────────────────────────────────── */

/**
 * Get all available templates.
 *
 * :param language: (Optional) Language setting for the Accept-Language header.
 * :return: A list of templates.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_templates_getTemplates_args;
OPENHAB_API cJSON* openhab_templates_getTemplates_(openhab_client_t* client, openhab_templates_getTemplates_args a);
#define openhab_templates_getTemplates(c, ...) \
    openhab_templates_getTemplates_((c), (openhab_templates_getTemplates_args){ ._ = 0, __VA_ARGS__ })

/**
 * Gets a template corresponding to the given UID.
 *
 * :param templateUID: The UID of the template.
 * :param language: (Optional) Language setting for the Accept-Language header.
 *
 * :return: A dictionary with the details of the template.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_templates_getTemplate_args;
OPENHAB_API cJSON* openhab_templates_getTemplate_(openhab_client_t* client, const char* templateUID, openhab_templates_getTemplate_args a);
#define openhab_templates_getTemplate(c, templateUID, ...) \
    openhab_templates_getTemplate_((c), (templateUID), (openhab_templates_getTemplate_args){ ._ = 0, __VA_ARGS__ })

/* ── ThingTypes ──────────────────────────────────────────────────────────── */

/**
 * Gets all available thing types without config description, channels, and properties.
 *
 * :param bindingID: (Optional) Filter by binding ID.
 * :param language: (Optional) Language setting for the Accept-Language header.
 *
 * :return: A list of thing types.
 *
 * Optional (named) arguments: .bindingID, .language
 */
typedef struct {
    int _;
    const char* bindingID;  /* default: None */
    const char* language;  /* default: None */
} openhab_thing_types_getThingTypes_args;
OPENHAB_API cJSON* openhab_thing_types_getThingTypes_(openhab_client_t* client, openhab_thing_types_getThingTypes_args a);
#define openhab_thing_types_getThingTypes(c, ...) \
    openhab_thing_types_getThingTypes_((c), (openhab_thing_types_getThingTypes_args){ ._ = 0, __VA_ARGS__ })

/**
 * Gets a thing type by UID.
 *
 * :param thingTypeUID: The UID of the thing type.
 * :param language: (Optional) Language setting for the Accept-Language header.
 *
 * :return: A dictionary with the details of the thing type or an empty response with status 204.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_thing_types_getThingType_args;
OPENHAB_API cJSON* openhab_thing_types_getThingType_(openhab_client_t* client, const char* thingTypeUID, openhab_thing_types_getThingType_args a);
#define openhab_thing_types_getThingType(c, thingTypeUID, ...) \
    openhab_thing_types_getThingType_((c), (thingTypeUID), (openhab_thing_types_getThingType_args){ ._ = 0, __VA_ARGS__ })

/* ── Things ──────────────────────────────────────────────────────────────── */

/**
 * Get all available things.
 *
 * :param summary: If True, returns only the summary fields.
 * :param staticDataOnly: If True, returns a cacheable list.
 * :param language: The preferred language for the response.
 *
 * :return: JSON response with the things.
 *
 * Optional (named) arguments: .summary, .staticDataOnly, .language
 */
typedef struct {
    int _;
    openhab_flag summary;  /* default: False */
    openhab_flag staticDataOnly;  /* default: False */
    const char* language;  /* default: None */
} openhab_things_getThings_args;
OPENHAB_API cJSON* openhab_things_getThings_(openhab_client_t* client, openhab_things_getThings_args a);
#define openhab_things_getThings(c, ...) \
    openhab_things_getThings_((c), (openhab_things_getThings_args){ ._ = 0, __VA_ARGS__ })

/**
 * Creates a new thing and adds it to the registry.
 *
 * :param thingData: The JSON object containing the thing data.
 * :param language: The preferred language for the response.
 *
 * :return: The API response.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_things_createThing_args;
OPENHAB_API cJSON* openhab_things_createThing_(openhab_client_t* client, const cJSON* thingData, openhab_things_createThing_args a);
#define openhab_things_createThing(c, thingData, ...) \
    openhab_things_createThing_((c), (thingData), (openhab_things_createThing_args){ ._ = 0, __VA_ARGS__ })

/**
 * Gets a thing by UID.
 *
 * :param thingUID: The UID of the thing.
 * :param language: The preferred language for the response.
 *
 * :return: JSON response with the thing data.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_things_getThing_args;
OPENHAB_API cJSON* openhab_things_getThing_(openhab_client_t* client, const char* thingUID, openhab_things_getThing_args a);
#define openhab_things_getThing(c, thingUID, ...) \
    openhab_things_getThing_((c), (thingUID), (openhab_things_getThing_args){ ._ = 0, __VA_ARGS__ })

/**
 * Updates a thing.
 *
 * :param thingUID: The UID of the thing.
 * :param thingData: The JSON object containing the updated thing data.
 * :param language: The preferred language for the response.
 *
 * :return: The API response.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_things_updateThing_args;
OPENHAB_API cJSON* openhab_things_updateThing_(openhab_client_t* client, const char* thingUID, const cJSON* thingData, openhab_things_updateThing_args a);
#define openhab_things_updateThing(c, thingUID, thingData, ...) \
    openhab_things_updateThing_((c), (thingUID), (thingData), (openhab_things_updateThing_args){ ._ = 0, __VA_ARGS__ })

/**
 * Removes a thing from the registry. Set 'force' to __true__ if you want the thing to be removed immediately.
 *
 * :param thingUID: The UID of the thing.
 * :param force: If True, the thing will be immediately removed.
 * :param language: The preferred language for the response.
 *
 * :return: The API response.
 *
 * Optional (named) arguments: .force, .language
 */
typedef struct {
    int _;
    openhab_flag force;  /* default: False */
    const char* language;  /* default: None */
} openhab_things_deleteThing_args;
OPENHAB_API cJSON* openhab_things_deleteThing_(openhab_client_t* client, const char* thingUID, openhab_things_deleteThing_args a);
#define openhab_things_deleteThing(c, thingUID, ...) \
    openhab_things_deleteThing_((c), (thingUID), (openhab_things_deleteThing_args){ ._ = 0, __VA_ARGS__ })

/**
 * Updates a thing's configuration.
 *
 * :param thingUID: The UID of the thing.
 * :param configurationData: The configuration data of the thing.
 * :param language: The preferred language for the response.
 *
 * :return: The API response.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_things_updateThingConfiguration_args;
OPENHAB_API cJSON* openhab_things_updateThingConfiguration_(openhab_client_t* client, const char* thingUID, const cJSON* configurationData, openhab_things_updateThingConfiguration_args a);
#define openhab_things_updateThingConfiguration(c, thingUID, configurationData, ...) \
    openhab_things_updateThingConfiguration_((c), (thingUID), (configurationData), (openhab_things_updateThingConfiguration_args){ ._ = 0, __VA_ARGS__ })

/**
 * Gets the thing's configuration status.
 *
 * :param thingUID: The UID of the thing.
 * :param language: The preferred language for the response.
 *
 * :return: JSON response with the thing's configuration status.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_things_getThingConfigStatus_args;
OPENHAB_API cJSON* openhab_things_getThingConfigStatus_(openhab_client_t* client, const char* thingUID, openhab_things_getThingConfigStatus_args a);
#define openhab_things_getThingConfigStatus(c, thingUID, ...) \
    openhab_things_getThingConfigStatus_((c), (thingUID), (openhab_things_getThingConfigStatus_args){ ._ = 0, __VA_ARGS__ })

/**
 * Sets the thing's enabled status.
 *
 * :param thingUID: The UID of the thing.
 * :param enabled: If True, the thing will be enabled.
 * :param language: The preferred language for the response.
 *
 * :return: The API response.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_things_setThingStatus_args;
OPENHAB_API cJSON* openhab_things_setThingStatus_(openhab_client_t* client, const char* thingUID, int enabled, openhab_things_setThingStatus_args a);
#define openhab_things_setThingStatus(c, thingUID, enabled, ...) \
    openhab_things_setThingStatus_((c), (thingUID), (enabled), (openhab_things_setThingStatus_args){ ._ = 0, __VA_ARGS__ })

/**
 */
OPENHAB_API cJSON* openhab_things_enableThing(openhab_client_t* client, const char* thingUID);

/**
 */
OPENHAB_API cJSON* openhab_things_disableThing(openhab_client_t* client, const char* thingUID);

/**
 * Updates the firmware of a thing.
 *
 * :param thingUID: The UID of the thing.
 * :param firmwareVersion: The firmware version.
 * :param language: The preferred language for the response.
 *
 * :return: The API response.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_things_updateThingFirmware_args;
OPENHAB_API cJSON* openhab_things_updateThingFirmware_(openhab_client_t* client, const char* thingUID, const char* firmwareVersion, openhab_things_updateThingFirmware_args a);
#define openhab_things_updateThingFirmware(c, thingUID, firmwareVersion, ...) \
    openhab_things_updateThingFirmware_((c), (thingUID), (firmwareVersion), (openhab_things_updateThingFirmware_args){ ._ = 0, __VA_ARGS__ })

/**
 * Gets the thing's firmware status.
 *
 * :param thingUID: The UID of the thing.
 * :param language: The preferred language for the response.
 *
 * :return: JSON response with the firmware status.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_things_getThingFirmwareStatus_args;
OPENHAB_API cJSON* openhab_things_getThingFirmwareStatus_(openhab_client_t* client, const char* thingUID, openhab_things_getThingFirmwareStatus_args a);
#define openhab_things_getThingFirmwareStatus(c, thingUID, ...) \
    openhab_things_getThingFirmwareStatus_((c), (thingUID), (openhab_things_getThingFirmwareStatus_args){ ._ = 0, __VA_ARGS__ })

/**
 * Gets all available firmwares for the provided thing UID.
 *
 * :param thingUID: The UID of the thing.
 * :param language: The preferred language for the response.
 *
 * :return: A list of available firmwares.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_things_getThingFirmwares_args;
OPENHAB_API cJSON* openhab_things_getThingFirmwares_(openhab_client_t* client, const char* thingUID, openhab_things_getThingFirmwares_args a);
#define openhab_things_getThingFirmwares(c, thingUID, ...) \
    openhab_things_getThingFirmwares_((c), (thingUID), (openhab_things_getThingFirmwares_args){ ._ = 0, __VA_ARGS__ })

/**
 * Gets the thing's status.
 *
 * :param thingUID: The UID of the thing.
 * :param language: The preferred language for the response.
 *
 * :return: JSON response with the thing's status.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_things_getThingStatus_args;
OPENHAB_API cJSON* openhab_things_getThingStatus_(openhab_client_t* client, const char* thingUID, openhab_things_getThingStatus_args a);
#define openhab_things_getThingStatus(c, thingUID, ...) \
    openhab_things_getThingStatus_((c), (thingUID), (openhab_things_getThingStatus_args){ ._ = 0, __VA_ARGS__ })

/* ── Transformations ─────────────────────────────────────────────────────── */

/**
 * Get a list of all transformations.
 *
 * :return: A list of transformations (JSON).
 */
OPENHAB_API cJSON* openhab_transformations_getTransformations(openhab_client_t* client);

/**
 * Get a single transformation.
 *
 * :param transformationUID: The transformationUID of the transformation to retrieve.
 *
 * :return: The transformation (JSON).
 */
OPENHAB_API cJSON* openhab_transformations_getTransformation(openhab_client_t* client, const char* transformationUID);

/**
 * Update a single transformation.
 *
 * :param transformationUID: The transformationUID of the transformation to update.
 * :param transformationData: The new data for the transformation.
 *
 * :return: The response to the transformation update request (JSON).
 */
OPENHAB_API cJSON* openhab_transformations_updateTransformation(openhab_client_t* client, const char* transformationUID, const cJSON* transformationData);

/**
 * Delete a single transformation.
 *
 * :param transformationUID: The transformationUID of the transformation to delete.
 *
 * :return: The response to the transformation update request (JSON) or status/error message.
 */
OPENHAB_API cJSON* openhab_transformations_deleteTransformation(openhab_client_t* client, const char* transformationUID);

/**
 * Get all transformation services.
 *
 * :return: A list of transformation services (JSON).
 */
OPENHAB_API cJSON* openhab_transformations_getTransformationServices(openhab_client_t* client);

/* ── UI ──────────────────────────────────────────────────────────────────── */

/**
 * Get all registered UI components in the specified namespace.
 *
 * :param namespace: The namespace for which UI components should be retrieved.
 * :param summary: If True, only summary fields will be returned.
 *
 * :return: A list of UI components (JSON).
 *
 * Optional (named) arguments: .summary
 */
typedef struct {
    int _;
    openhab_flag summary;  /* default: False */
} openhab_ui_getUIComponents_args;
OPENHAB_API cJSON* openhab_ui_getUIComponents_(openhab_client_t* client, const char* namespace_, openhab_ui_getUIComponents_args a);
#define openhab_ui_getUIComponents(c, namespace_, ...) \
    openhab_ui_getUIComponents_((c), (namespace_), (openhab_ui_getUIComponents_args){ ._ = 0, __VA_ARGS__ })

/**
 * Add a UI component in the specified namespace.
 *
 * :param namespace: The namespace where the UI component should be added.
 * :param componentData: The data of the UI component (JSON) to be added.
 *
 * :return: The response to the request (JSON).
 */
OPENHAB_API cJSON* openhab_ui_addUIComponent(openhab_client_t* client, const char* namespace_, const cJSON* componentData);

/**
 * Get a specific UI component in the specified namespace.
 *
 * :param namespace: The namespace where the UI component is located.
 * :param componentUID: The UID of the UI component to retrieve.
 *
 * :return: The UI component (JSON).
 */
OPENHAB_API cJSON* openhab_ui_getUIComponent(openhab_client_t* client, const char* namespace_, const char* componentUID);

/**
 * Update a specific UI component in the specified namespace.
 *
 * :param namespace: The namespace where the UI component should be updated.
 * :param componentUID: The UID of the UI component to update.
 * :param componentData: The new data for the UI component (JSON).
 *
 * :return: The response to the request (JSON).
 */
OPENHAB_API cJSON* openhab_ui_updateUIComponent(openhab_client_t* client, const char* namespace_, const char* componentUID, const cJSON* componentData);

/**
 * Remove a specific UI component in the specified namespace.
 *
 * :param namespace: The namespace where the UI component should be removed.
 * :param componentUID: The UID of the UI component to delete.
 *
 * :return: The response to the request (JSON).
 */
OPENHAB_API cJSON* openhab_ui_deleteUIComponent(openhab_client_t* client, const char* namespace_, const char* componentUID);

/**
 * Get all registered UI tiles.
 *
 * :return: A list of UI tiles (JSON).
 */
OPENHAB_API cJSON* openhab_ui_getUITiles(openhab_client_t* client);

/* ── UUID ────────────────────────────────────────────────────────────────── */

/**
 * A unified unique id.
 *
 * :return: The UUID as String.
 */
OPENHAB_API cJSON* openhab_uuid_getUUID(openhab_client_t* client);

/* ── Voice ───────────────────────────────────────────────────────────────── */

/**
 * Gets the default voice.
 *
 * :return: A dictionary with the details of the default voice.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_voice_getDefaultVoice_args;
OPENHAB_API cJSON* openhab_voice_getDefaultVoice_(openhab_client_t* client, openhab_voice_getDefaultVoice_args a);
#define openhab_voice_getDefaultVoice(c, ...) \
    openhab_voice_getDefaultVoice_((c), (openhab_voice_getDefaultVoice_args){ ._ = 0, __VA_ARGS__ })

/**
 * Start dialog processing for a given audio source.
 *
 * :param sourceID: The ID of the audio source.
 * :param ksID: The ID of the keyword spotter (optional).
 * :param sttID: The ID of the speech-to-text system (optional).
 * :param ttsID: The ID of the text-to-speech system (optional).
 * :param voiceID: The ID of the voice (optional).
 * :param hliIDs: A comma-separated list of interpreter IDs (optional).
 * :param sinkID: The ID of the audio output (optional).
 * :param keyword: The keyword used to start the dialog (optional).
 * :param listeningItem: The name of the item to listen to (optional).
 * :param language: The language for the request (optional).
 *
 * :return: The response from the server.
 *
 * Optional (named) arguments: .ksID, .sttID, .ttsID, .voiceID, .hliIDs, .sinkID, .keyword, .listeningItem, .language
 */
typedef struct {
    int _;
    const char* ksID;  /* default: None */
    const char* sttID;  /* default: None */
    const char* ttsID;  /* default: None */
    const char* voiceID;  /* default: None */
    const char* hliIDs;  /* default: None */
    const char* sinkID;  /* default: None */
    const char* keyword;  /* default: None */
    const char* listeningItem;  /* default: None */
    const char* language;  /* default: None */
} openhab_voice_startDialog_args;
OPENHAB_API cJSON* openhab_voice_startDialog_(openhab_client_t* client, const char* sourceID, openhab_voice_startDialog_args a);
#define openhab_voice_startDialog(c, sourceID, ...) \
    openhab_voice_startDialog_((c), (sourceID), (openhab_voice_startDialog_args){ ._ = 0, __VA_ARGS__ })

/**
 * Stop dialog processing for a given audio source.
 *
 * :param sourceID: The ID of the audio source.
 * :return: The response from the server.
 */
OPENHAB_API cJSON* openhab_voice_stopDialog(openhab_client_t* client, const char* sourceID);

/**
 * Get the list of all interpreters.
 *
 * :param language: The language for the request (optional).
 *
 * :return: A list of interpreters if successful.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_voice_getInterpreters_args;
OPENHAB_API cJSON* openhab_voice_getInterpreters_(openhab_client_t* client, openhab_voice_getInterpreters_args a);
#define openhab_voice_getInterpreters(c, ...) \
    openhab_voice_getInterpreters_((c), (openhab_voice_getInterpreters_args){ ._ = 0, __VA_ARGS__ })

/**
 * Sends a text to the default human language interpreter.
 *
 * :param text: The text to be interpreted.
 * :param language: The language of the text.
 * :param IDs: A list of interpreter IDs (optional).
 *
 * :return: The response from the server.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_voice_interpretText_args;
OPENHAB_API cJSON* openhab_voice_interpretText_(openhab_client_t* client, const char* text, openhab_voice_interpretText_args a);
#define openhab_voice_interpretText(c, text, ...) \
    openhab_voice_interpretText_((c), (text), (openhab_voice_interpretText_args){ ._ = 0, __VA_ARGS__ })

/**
 * Gets a single interpreter.
 *
 * :param interpreterID: The ID of the interpreter.
 * :param language: The language for the request (optional).
 *
 * :return: The details of the interpreter.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_voice_getInterpreter_args;
OPENHAB_API cJSON* openhab_voice_getInterpreter_(openhab_client_t* client, const char* interpreterID, openhab_voice_getInterpreter_args a);
#define openhab_voice_getInterpreter(c, interpreterID, ...) \
    openhab_voice_getInterpreter_((c), (interpreterID), (openhab_voice_getInterpreter_args){ ._ = 0, __VA_ARGS__ })

/**
 * Sends a text to a given human language interpreter(s).
 *
 * :param text: The text to be interpreted.
 * :param language: The language of the text.
 * :param IDs: A list of interpreter IDs.
 *
 * :return: The response from the server.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_voice_interpretTextBatch_args;
OPENHAB_API cJSON* openhab_voice_interpretTextBatch_(openhab_client_t* client, const char* text, const cJSON* IDs, openhab_voice_interpretTextBatch_args a);
#define openhab_voice_interpretTextBatch(c, text, IDs, ...) \
    openhab_voice_interpretTextBatch_((c), (text), (IDs), (openhab_voice_interpretTextBatch_args){ ._ = 0, __VA_ARGS__ })

/**
 * Executes a simple dialog sequence without keyword spotting for a given audio source.
 *
 * :param sourceID: The ID of the audio source.
 * :param sttID: The ID of the speech-to-text system.
 * :param ttsID: The ID of the text-to-speech system.
 * :param voiceID: The ID of the voice.
 * :param hliIDs: A list of interpreter IDs (optional).
 * :param sinkID: The ID of the audio output (optional).
 * :param listeningItem: The name of the item to listen to (optional).
 * :param language: The language for the request (optional).
 *
 * :return: The response from the server.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_voice_listenAndAnswer_args;
OPENHAB_API cJSON* openhab_voice_listenAndAnswer_(openhab_client_t* client, const char* sourceID, const char* sttID, const char* ttsID, const char* voiceID, const cJSON* hliIDs, const char* sinkID, const char* listeningItem, openhab_voice_listenAndAnswer_args a);
#define openhab_voice_listenAndAnswer(c, sourceID, sttID, ttsID, voiceID, hliIDs, sinkID, listeningItem, ...) \
    openhab_voice_listenAndAnswer_((c), (sourceID), (sttID), (ttsID), (voiceID), (hliIDs), (sinkID), (listeningItem), (openhab_voice_listenAndAnswer_args){ ._ = 0, __VA_ARGS__ })

/**
 * Speaks a given text with a given voice through the given audio sink.
 *
 * :param text: The text to be spoken.
 * :param voiceID: The ID of the voice.
 * :param sinkID: The ID of the audio output.
 * :param volume: The volume level (default: 100).
 *
 * :return: The response from the server.
 *
 * Optional (named) arguments: .volume
 */
typedef struct {
    int _;
    const char* volume;  /* default: '100' */
} openhab_voice_sayText_args;
OPENHAB_API cJSON* openhab_voice_sayText_(openhab_client_t* client, const char* text, const char* voiceID, const char* sinkID, openhab_voice_sayText_args a);
#define openhab_voice_sayText(c, text, voiceID, sinkID, ...) \
    openhab_voice_sayText_((c), (text), (voiceID), (sinkID), (openhab_voice_sayText_args){ ._ = 0, __VA_ARGS__ })

/**
 * Get the list of all voices.
 *
 * :return: A list of voices if successful.
 *
 * Optional (named) arguments: .language
 */
typedef struct {
    int _;
    const char* language;  /* default: None */
} openhab_voice_getVoices_args;
OPENHAB_API cJSON* openhab_voice_getVoices_(openhab_client_t* client, openhab_voice_getVoices_args a);
#define openhab_voice_getVoices(c, ...) \
    openhab_voice_getVoices_((c), (openhab_voice_getVoices_args){ ._ = 0, __VA_ARGS__ })

#ifdef __cplusplus
}
#endif

#endif /* OPENHAB_API_H */
