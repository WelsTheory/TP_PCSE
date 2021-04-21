/*
 * MEF_Libreria.h
 *
 *  Created on: Apr 21, 2021
 *      Author: wels
 */

#ifndef INC_MEF_LIBRERIA_H_
#define INC_MEF_LIBRERIA_H_

// Estructura MEFEstado
typedef enum{
	LECTURA_DATOS,
	ENVIO_DATOS,
	REINCIO_DATOS
}MEFEstado_t;

#define Dato_Fijo 200

MEFEstado_t estadoActual;

void MEF_Init(void);
void MEF_Update(void);

#endif /* INC_MEF_LIBRERIA_H_ */
