/*
 *
 *  GattLib - GATT Library
 *
 *  Copyright (C) 2016-2017  Olivier Martin <olivier@labapart.org>
 *
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "gattlib.h"

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

struct ble_multisensors{
	float temperature;
	float humidity;
	float pressure;
} ;

static struct ble_multisensors device = {0};


int main(int argc, char *argv[]) {

	uint8_t buffer[100];
	int i, ret;
	size_t len;
	gatt_connection_t* connection;
	unsigned char device_config[] = {0x0A, 0x08, 0x03, 0x06, 0x03, 0x06, 0x00, 0x02, 0x0A, 0x00, 0x01, 0x00, 0x00, 0x00, 0x05};
	unsigned char device_request[] = {0x01 };
	int value;

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

//////////////////////////////////////////////////////////////////////////////////////////////////

			value = buffer[5] + (buffer[6] << 8) + (buffer[7] << 16) + (buffer[8] << 24) ;
			device.pressure = (float)(value)/100;

			value = buffer[12] + (buffer[13] << 8) + (buffer[14] << 16) + (buffer[15] << 24) ;
			device.humidity = (float)(value)/1000;

            value = buffer[19] + (buffer[20] << 8) + (buffer[21] << 16) + (buffer[22] << 24) ;
            device.temperature = (float)(value)/100;

            printf("Temperature: %.2f \n", device.temperature);
            printf("Humidity: %.2f \n", device.humidity);
            printf("Pressure: %.2f \n", device.pressure);

//////////////////////////////////////////////////////////////////////////////////////////////////

		{
			FILE *f = fopen("/home/och/demo/ble_multisensor.txt", "w");
			if (f == NULL) {
				printf("Error opening file!\n");
				exit(-1);
			}

			/* print some text */
			fprintf(f, "temperature:%.2f\r\nhumidity:%.2f\r\npressure:%.2f\r\n",
					device.temperature, device.humidity, device.pressure);
			fclose(f);
		}

		{
			FILE *f = fopen("/home/och/demo/ble_multisensor.raw", "w");

			if (f == NULL) {
				printf("Error opening file!\n");
				exit(-1);
			}
			for (i = 0; i < len; i++) {
				fprintf(f, "%02x ", buffer[i]);
			}
			fprintf(f, "\n");
			fclose(f);
		}

		}

EXIT:
	gattlib_disconnect(connection);
	return ret;

}
