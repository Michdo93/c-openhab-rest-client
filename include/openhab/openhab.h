#ifndef OPENHAB_H
#define OPENHAB_H

/**
 * openhab-rest-client — C Library
 * Single include for all openHAB REST API functions.
 *
 *   #include <openhab/openhab.h>
 *
 *   openhab_client_t* c = openhab_client_create("http://127.0.0.1:8080","openhab","habopen",NULL);
 *   char* items = openhab_items_get_all(c, NULL,NULL,NULL,0,NULL,0,NULL);
 *   printf("%s\n", items);
 *   free(items);
 *   openhab_client_destroy(c);
 */

#include "openhab_client.h"
#include "openhab_api.h"

#endif /* OPENHAB_H */
