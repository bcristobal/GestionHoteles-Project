/*
 * reserva.h
 *
 *  Created on: Apr 5, 2023
 *      Author: unaialonso
 */

#ifndef RESERVA_RESERVA_H_
#define RESERVA_RESERVA_H_

typedef struct{

	int idRes;
	Fecha fechaIni;
	Fecha fechaFin;
	int idHab;
	int dni;
}Reserva;

void imprimirReserva(Reserva r);

#endif /* RESERVA_RESERVA_H_ */
