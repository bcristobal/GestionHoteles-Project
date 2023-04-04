/*
 * ficheros.h
 *
 *  Created on: Apr 3, 2023
 *      Author: unaialonso
 */

#ifndef FICHEROS_FICHEROS_H_
#define FICHEROS_FICHEROS_H_

#include "../hotel/hotel.h"

void guardarReserva(char cod_Reserva[], char fa_ini[], char fa_fin[], char id_hotel[], int num_Personas, char importe[]);

void guardarHotel(int id, char nom[20], int numEst, int idProv);

#endif /* FICHEROS_FICHEROS_H_ */
