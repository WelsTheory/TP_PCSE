

#ifndef INC_ESP8226_H
#define INC_ESP8226_H

uint32_t ESP_Init (char *SSID, char *PASSWD);
void ESP_Send_Data (char *APIkey, int Field_num, uint16_t value);
void ESP_Send_Multi (char *APIkey, int numberoffileds, uint16_t value[]);

#define SSID_Wifi		"Wels28"
#define PASS_Wifi		"w@2801(-)2206@j"
#define API_ThingSpeak 	"K77JWY4UUUZPGWSO"

#endif /* INC_ESPDATALOGGER_H_ */
