/*
 * ficheros.c
 *
 *  Created on: Apr 3, 2023
 *      Author: unaialonso
 */

#include "ficheros.h"
#include <stdlib.h>
#include <stdio.h>

void guardarReserva(char cod_Reserva[], char fa_ini[], char fa_fin[], char id_hotel[], int num_Personas, char importe[]) {
       // Abrir el fichero de reservas en modo "append" para agregar la nueva reserva al final del fichero
       FILE *fichero;
       fichero = fopen("reservas.txt", "a");

       // Escribir los datos de la reserva en el formato indicado, separados por barras verticales (|)
       fprintf(fichero, "%s|%s|%s|%s|%d|%s\n", cod_Reserva, fa_ini, fa_fin, id_hotel, num_Personas, importe);

       // Cerrar el fichero de reservas
       fclose(fichero);
   }

void guardarHotel(int id, char nom[20], int numEst, int idProv) {
    FILE *fichero;

    fichero = fopen("hoteles.txt", "a");
    if (fichero == NULL) {
        printf("Error al abrir el fichero.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(fichero, "%d %s %d %d\n", id, nom, numEst, idProv);

    fclose(fichero);
}

