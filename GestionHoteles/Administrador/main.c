#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "provincia.h"
#include "hotel.h"

void mostrarHoteles(Provincias * provincias, int eleccion){
	printf("\n\n\n=================\nMOSTRAR HOTELES\n=================");
	int n;
	printf("\nHoteles de la provincia de %s", provincias->provincias[eleccion].name);
	for (n = 0; n < provincias->provincias[eleccion].hoteles.numHoteles; ++n) {
		imprimirHotel(&provincias->provincias[eleccion].hoteles.hoteles[n]);
	}
}

void menuProvinciasHoteles(Provincias * provincias){
	char str[10];
	int opcion;
	printf("\n\n\n=================\nMOSTRAR HOTELES\n=================");
	printf("\nProvincias:\n");
	//Ejemplo Hardcodeado
	int n;
	for (n = 0; n < provincias->numProvincias; ++n) {
		printf("%d. ", n + 1);
		imprimirProvincia(&provincias->provincias[n]);
	}
	printf("%d. Atras\n", n + 1);
	printf("Opcion: ");
	fflush(stdout);
	fgets(str, 10, stdin);
	sscanf(str, "%d", &opcion);
	if (opcion > 0 && opcion <= (provincias->numProvincias)) {
		printf("opcion provincias check\n");
		mostrarHoteles(provincias, opcion - 1);
	} else if (opcion == 4){
		printf("\n\n\n");
		menuAdmin(provincias);
	} else {
		printf("Opcion incorrecta!!!\n");
		menuProvinciasHoteles(provincias);
	}

}

void menuAdmin(Provincias* provincias){
	char str[10];
	int opcion;
	printf("============\nMENU ADMIN\n============");
	printf("\n1. Mostrar hoteles existentes.\n2. Anadir hotel.");
	printf("\n3. Eliminar hotel.\n4. Mostrar reservas realizadas por distintos usuarios.");
	printf("\n5. Salir.\nOpcion: ");
	fflush(stdout);
	fgets(str, 3, stdin);
	sscanf(str, "%d", &opcion);
	switch(opcion){
	case 1: //MOSTRAR HOTELES
		menuProvinciasHoteles(provincias);
		break;
	case 2: //ANADIR HOTEL
		printf("Prueba");
		break;
	case 3: //ELIMINAR HOTEL
		printf("Prueba");
		break;
	case 4: //MOSTRAR RESERVAS
		printf("Prueba");
		break;
	case 5: //SALIR
		printf("\nGracias por utilizar nuestros sevicios!");
		break;
	default: //ELSE
		printf("\nOpcion incorrecta!!!\n");
		menuAdmin(provincias);
		break;
	}
}


int main(void){
	//CREACION DE PROVINCIAS (sin BD)
	char provincia[20] = "Alava"; //PROVINCIA 1
	Provincia* provincia1 = (Provincia *) malloc(sizeof(Provincia));
	strcpy(provincia1->name, provincia);
	provincia1->id = 0;
	strcpy(provincia, "Albacete"); //PROVINCIA 2
	Provincia* provincia2 = (Provincia *) malloc(sizeof(Provincia));
	strcpy(provincia2->name, provincia);
	provincia2->id = 1;
	strcpy(provincia, "Alicante"); //PROVINCIA 2
	Provincia* provincia3 = (Provincia *) malloc(sizeof(Provincia));
	strcpy(provincia3->name, provincia);
	provincia3->id = 2;
	Provincias* provincias = (Provincias *) malloc(sizeof(Provincias)); //ARRAY DE PROVINCIAS
	provincias->provincias = malloc(3 * sizeof(Provincia));
	provincias->provincias[0] = *provincia1;
	provincias->provincias[1] = *provincia2;
	provincias->provincias[2] = *provincia3;
	provincias->numProvincias = 3;

	//------------------------------------------------------------------
	//CREACION DE HOTELES (sin bd)
	char hotel[20] = "Hotel Lakua"; //HOTEL 1
	int estrellas = 4;
	Hotel* hotel1 = (Hotel *) malloc(sizeof(Hotel));
	hotel1->estrellas = estrellas;
	strcpy(hotel1->name, hotel);
	strcpy(hotel, "NH Canciller Ayala"); //HOTEL 2
	Hotel* hotel2 = (Hotel *) malloc(sizeof(Hotel));
	hotel2->estrellas = estrellas;
	strcpy(hotel2->name, hotel);
	strcpy(hotel, "Hotel Hito"); //HOTEL 3
	estrellas = 1;
	Hotel* hotel3 = (Hotel *) malloc(sizeof(Hotel));
	strcpy(hotel3->name, hotel);
	hotel3->estrellas = estrellas;
	Hoteles * hoteles = (Hoteles *) malloc(sizeof(Hoteles));
	hoteles->hoteles = (Hotel *) malloc(3 * sizeof(Hotel));
	hoteles->hoteles[0] = *hotel1;
	hoteles->hoteles[1] = *hotel2;
	hoteles->hoteles[2] = *hotel3;

	//------------------------------------------------------------------
	//ANADIR HOTELES A UNA PROVINCIA (para probar la funcionalidad) (sin bd)
	provincias->provincias[1].hoteles.hoteles = (Hotel *) malloc(3 * sizeof(Hotel));
	provincias->provincias[1].hoteles = *hoteles;
	provincias->provincias[1].hoteles.numHoteles = 3;

	//------------------------------------------------------------------
	//INICIAR MENU
	menuAdmin(provincias);

	//------------------------------------------------------------------
	//LIBERACION DE MEMORIA
	free(provincias);
	free(provincias->provincias);
	free(provincia1);
	free(provincia2);
	free(provincia3);
	free(hoteles);
	free(hoteles->hoteles);
	free(hotel1);
	free(hotel2);
	free(hotel3);
	free(provincias->provincias[1].hoteles.hoteles);

	//------------------------------------------------------------------

	return 0;
}

