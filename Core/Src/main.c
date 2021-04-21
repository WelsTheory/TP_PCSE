
#include "sapi.h"

I2C_HandleTypeDef hi2c1;
RTC_HandleTypeDef hrtc;
TIM_HandleTypeDef htim11;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

//extern char time[10];

int main(void)
{
	boardInit();
	MEF_Init();
	while (1)
	{
		MEF_Update();
	}
}
