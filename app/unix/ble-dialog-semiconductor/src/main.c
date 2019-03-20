/**
 * @file atcommands.c
 * @brief This is the source file.
 * $Id: $
 **/


//****************************** DEPENDENCIES ********************************//
//============================================================================//


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/socket.h>
//#include <bluetooth/bluetooth.h>
//#include <bluetooth/rfcomm.h>
//#include <bluetooth/hci.h>
//#include <bluetooth/hci_lib.h>
#include <assert.h>
#include "debug.h"

//#include <glib.h>
//#include <iostream>
#include "gattlib.h"
#include "main.h"

//******************************** DEFINES ***********************************//
//============================================================================//

//******************************** TYPEDEFS **********************************//
//============================================================================//

//********************************* ENUMS ************************************//
//============================================================================//

//***************************  PRIVATE VARIABLES *****************************//
//============================================================================//

//***************************  PUBLIC VARIABLES ******************************//
//============================================================================//

//***************************  PRIVATE FUNCTIONS *****************************//
//============================================================================//

//***************************  PUBLIC FUNCTIONS ******************************//
//============================================================================//


typedef enum { READ, WRITE} operation_t;
operation_t g_operation;

#define DIALOG_MULTISENSOR "80:EA:CA:70:A3:2B"
#define DIALOG_UUID_2408   "2ea78970-7d44-44bb-b097-26183f402408"
#define DIALOG_UUID_2409   "2ea78970-7d44-44bb-b097-26183f402409"
#define DIALOG_UUID_240A   "2ea78970-7d44-44bb-b097-26183f40240A"
#define DIALOG_UUID_2410   "2ea78970-7d44-44bb-b097-26183f402410"

static uuid_t g_uuid;
long int value_data;

static void usage(char *argv[]) {
	printf("%s <device_address> <read|write> <uuid> [<hex-value-to-write>]\n", argv[0]);
}


/**
 * @brief App Initialization
 **/
int main(int argc, char *argv[]) {

	uint8_t buffer[100];
	int i, ret;
	size_t len;
	gatt_connection_t* connection;
	unsigned char device_config[] = {0x0A, 0x08, 0x03, 0x06, 0x03, 0x06, 0x00, 0x02, 0x0A, 0x00, 0x01, 0x00, 0x00, 0x00, 0x05};
	unsigned char device_request[] = {0x01 };

	fprintf(stderr, "1. Initilializing communication with : %s \n", DIALOG_MULTISENSOR);

	connection = gattlib_connect(NULL, DIALOG_MULTISENSOR, BDADDR_LE_PUBLIC, BT_SEC_SDP, 0, 0);
	if (connection == NULL) {
		fprintf(stderr, "Fail to connect to the bluetooth device.\n");
		return 1;
	} else {
	    fprintf(stderr, "Connected to %s \n", DIALOG_MULTISENSOR);
	}

/////////////////////////////////////

	fprintf(stderr, "2. Reading : Device Features\n");

	g_operation = READ;

	if (g_operation == READ) {

		if (gattlib_string_to_uuid(DIALOG_UUID_2408, strlen(DIALOG_UUID_2408) + 1, &g_uuid) < 0) {
			usage(argv);
			return 1;
		}

		len = sizeof(buffer);
		ret = gattlib_read_char_by_uuid(connection, &g_uuid, buffer, &len);
		//ret = gattlib_write_char_by_handle(connection, 0x42, buffer, &len);
		if (ret == -1) {
			char uuid_str[MAX_LEN_UUID_STR + 1];

			gattlib_uuid_to_string(&g_uuid, uuid_str, sizeof(uuid_str));

			fprintf(stderr, "Could not find GATT Characteristic with UUID %s\n", uuid_str);
			goto EXIT;
		}

		printf("Read UUID completed: ");
		for (i = 0; i < len; i++) {
			printf("%02x ", buffer[i]);
		}
		printf("\n");
	}

/////////////////////////////////////

	fprintf(stderr, "3. Writting: Control Point: Configuration\n");

	g_operation = WRITE;

	if (g_operation == WRITE) {

		if (gattlib_string_to_uuid(DIALOG_UUID_2409, strlen(DIALOG_UUID_2409) + 1, &g_uuid) < 0) {
					usage(argv);
					return 1;
		}

		ret = gattlib_write_char_by_uuid(connection, &g_uuid, device_config, sizeof(device_config));
		if (ret == -1) {
			char uuid_str[MAX_LEN_UUID_STR + 1];

			gattlib_uuid_to_string(&g_uuid, uuid_str, sizeof(uuid_str));

			fprintf(stderr, "Could not find GATT Characteristic with UUID %s\n", uuid_str);
			goto EXIT;
		}
	}

	/////////////////////////////////////
	   fprintf(stderr, "4. Writting: Control Point: Request\n");

	   g_operation = WRITE;

		if (g_operation == WRITE) {

			if (gattlib_string_to_uuid(DIALOG_UUID_2409, strlen(DIALOG_UUID_2409) + 1, &g_uuid) < 0) {
						usage(argv);
						return 1;
			}

			ret = gattlib_write_char_by_uuid(connection, &g_uuid, device_request, sizeof(device_request));
			if (ret == -1) {
				char uuid_str[MAX_LEN_UUID_STR + 1];

				gattlib_uuid_to_string(&g_uuid, uuid_str, sizeof(uuid_str));

				fprintf(stderr, "Could not find GATT Characteristic with UUID %s\n", uuid_str);
				goto EXIT;
			}
		}

/////////////////////////////////////
//		fprintf(stderr, "5. Reading: Control Command Reply\n");
//
//		g_operation = READ;
//
//				if (g_operation == READ) {
//
//					if (gattlib_string_to_uuid(DIALOG_UUID_240A, strlen(DIALOG_UUID_240A) + 1, &g_uuid) < 0) {
//						usage(argv);
//						return 1;
//					}
//
//					len = sizeof(buffer);
//					ret = gattlib_read_char_by_uuid(connection, &g_uuid, buffer, &len);
//
//					if (ret == -1) {
//						char uuid_str[MAX_LEN_UUID_STR + 1];
//
//						gattlib_uuid_to_string(&g_uuid, uuid_str, sizeof(uuid_str));
//
//						fprintf(stderr, "Could not find GATT Characteristic with UUID %s\n", uuid_str);
//						goto EXIT;
//					}
//
//					printf("Read UUID completed: ");
//					for (i = 0; i < len; i++) {
//						printf("%02x ", buffer[i]);
//					}
//					printf("\n");
//				}

/////////////////////////////////////
		printf("6. Reading: Sensors Report\n");

		g_operation = READ;

		if (g_operation == READ) {

			if (gattlib_string_to_uuid(DIALOG_UUID_2410, strlen(DIALOG_UUID_2410) + 1, &g_uuid) < 0) {
				usage(argv);
				return 1;
			}

			len = sizeof(buffer);
			ret = gattlib_read_char_by_uuid(connection, &g_uuid, buffer, &len);

			if (ret == -1) {
				char uuid_str[MAX_LEN_UUID_STR + 1];

				gattlib_uuid_to_string(&g_uuid, uuid_str, sizeof(uuid_str));

				fprintf(stderr, "Could not find GATT Characteristic with UUID %s\n", uuid_str);
				goto EXIT;
			}

			printf("Read UUID completed: ");
			for (i = 0; i < len; i++) {
				printf("%02x ", buffer[i]);
			}
			printf("\n");
		}

EXIT:
	gattlib_disconnect(connection);
	return ret;

}
