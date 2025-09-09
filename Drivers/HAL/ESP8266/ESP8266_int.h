/*
 * ESP8266_int.h
 *
 *  Created on: Sep 8, 2025
 *      Author: pc
 */

#ifndef HAL_ESP8266_ESP8266_INT_H_
#define HAL_ESP8266_ESP8266_INT_H_


void HESP8266_vInit(void);
void HESP8266_vConnectAccessPoint(char* A_s8SSID, char* A_s8Password);
void HESP8266_vOpenServerTCPConnection(char* IP, char *SocketNo);
void HESP8266_vSendHttpRequest(char* URL);


#endif /* HAL_ESP8266_ESP8266_INT_H_ */
