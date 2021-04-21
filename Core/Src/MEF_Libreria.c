
#include "MEF_Libreria.h"
#include "sapi.h"
#include "Calculo_Libreria.h"

#define Mensaje_Bienvenida	"\r\nMedición de datos\r\n"
#define Mensaje_Error_ESP	"No se conectó correctamente!\r\n\r\n"
#define Mensaje_Wifi		"\r\nCONEXION CON EL WIFI"
#define Mensaje_IMU			"\r\nIMU MPU6050 inicializado correctamente."
#define Mensaje_Error_IMU	"IMU MPU6050 no inicializado, chequee las conexiones:"
#define Mensaje_Lectura		"LECTURA\r\n"
#define Mensaje_Alerta		"FALL\r\n"
#define Mensaje_Reinicio	"REINICIO\r\n"

extern I2C_HandleTypeDef hi2c1;
extern RTC_HandleTypeDef hrtc;
extern TIM_HandleTypeDef htim11;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern Calculos_t Cal;

char datos[20];
int8_t status;
uint16_t Buf[2] = {0,0};

void MEF_Init(void)
{
	HAL_UART_Transmit(&huart2, Mensaje_Bienvenida, 24, HAL_MAX_DELAY);
	if(ESP_Init(SSID_Wifi,PASS_Wifi)< LOW){
		HAL_UART_Transmit(&huart2,Mensaje_Error_ESP , 30, HAL_MAX_DELAY);
		while(1);
	}
	HAL_UART_Transmit(&huart2,Mensaje_Wifi, 23, HAL_MAX_DELAY);
	status = MPU6050_Init(MPU60X0_ADDRESS_0);
	if( status < LOW ){
		HAL_UART_Transmit(&huart2,Mensaje_Error_IMU , 60, HAL_MAX_DELAY);
		while(1);
	}
	HAL_UART_Transmit(&huart2,Mensaje_IMU, 42, HAL_MAX_DELAY);
	ESP_Send_Multi(API_ThingSpeak,2,Buf);
	estadoActual = LECTURA_DATOS;
	HAL_Delay(16000);
}

void MEF_Update(void)
{
	switch(estadoActual)
	{
	case LECTURA_DATOS:
		if(Calculo_Init() < LOW){
			estadoActual = ENVIO_DATOS;
		}
		else{
			sprintf(datos,"DATOS: %.2f\r\n", Cal.result);
			HAL_UART_Transmit(&huart2, datos, 20, HAL_MAX_DELAY);
			HAL_UART_Transmit(&huart2, Mensaje_Lectura, 11, HAL_MAX_DELAY);
		}
		HAL_Delay(8);
		break;
	case ENVIO_DATOS:
		Buf[0] = Dato_Fijo;
		Buf[1] = TRUE;
		ESP_Send_Multi(API_ThingSpeak,2,Buf);
		HAL_UART_Transmit(&huart2, Mensaje_Alerta, 6, HAL_MAX_DELAY);
		HAL_Delay(15000);
		estadoActual = REINCIO_DATOS;
		break;
	case REINCIO_DATOS:
		Buf[0] = LOW;
		Buf[1] = LOW;
		ESP_Send_Multi(API_ThingSpeak,2,Buf);
		HAL_UART_Transmit(&huart2, Mensaje_Reinicio, 12, HAL_MAX_DELAY);
		estadoActual = LECTURA_DATOS;
		HAL_Delay(15000);
		break;
	default:
		MEF_Init();
		break;
	}
}




