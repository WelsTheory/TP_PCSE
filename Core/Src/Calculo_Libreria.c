/*
 * Calculo_Libreria.c
 *
 *  Created on: Apr 21, 2021
 *      Author: wels
 */
#include "Calculo_Libreria.h"

DataX_T X;
Calculos_t Cal;

uint32_t N_muestras = 0;

int32_t Calculo_Init(void)
{
	mpu60X0Read();
	Ax1 = mpu60X0GetAccelX_mss();
	Ay1 = mpu60X0GetAccelY_mss();
	Az1 = mpu60X0GetAccelZ_mss();
	if(Func_Calculo_6G() >= G6)
	{
		Cal.result = 0.0;
		Cal.result_vmp = 0.0;
		return -1;
	}
	if(Func_Calculo_2G() > G2)
	{
		Cal.result_vmp = 0.0;
		return -2;
	}
	X.n[N_muestras] = Func_Calculo_6G();
	N_muestras++;
	if(N_muestras >= Muestras)
	{
		if(Func_Integral() >= 1.5)
		{
			N_muestras = 0;
			Cal.result_vmp = 0.0;
			Cal.result = 0.0;
			Cal.integral_result = 0.0;
			return -3;
		}
		else
		{
			N_muestras = 0;
			return 1;
		}
	}
	return 1;
}

float Func_Calculo_6G(void)
{
	pow_x = pow(Ax1,2);
	pow_y = pow(Ay1,2);
	pow_z = pow(Az1,2);
	accel_tot = pow_x + pow_y + pow_z;
	Cal.result = sqrt(accel_tot);
	return Cal.result;
}

float Func_Calculo_2G(void)
{
	vmp_dato = pow_x + pow_z;
	Cal.result_vmp = sqrt(vmp_dato);
	return Cal.result_vmp;
}

float Func_Integral(void)
{
	for(N_muestras = 0; N_muestras < 94;N_muestras++)
	{
		if(N_muestras == 0)integral += X.n[0];
		integral += 2*X.n[N_muestras];
	}
	integral = coef*integral;
	return Cal.integral_result;
}


