#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../provincia/provincia.h"
#include "../hotel/hotel.h"
#include "../bd/base_datos.h"

void menuAdmin(Provincias *provincias);

void mostrarHoteles(Provincias *provincias, int eleccion) {
	printf("\n\n\n=================\nMOSTRAR HOTELES\n=================");
	int n;
	printf("\nHoteles de la provincia de %s",
			provincias->provincias[eleccion].name);
	for (n = 0; n < provincias->provincias[eleccion].hoteles.numHoteles; ++n) {
		imprimirHotel(&provincias->provincias[eleccion].hoteles.hoteles[n]);
	}
}

void menuProvinciasHoteles(Provincias *provincias) {
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
	if (opcion > 0 && opcion <= n) {
		printf("opcion provincias check\n");
		mostrarHoteles(provincias, opcion - 1);
	} else if (opcion == n + 1) {
		printf("\n\n\n");
		menuAdmin(provincias);
	} else {
		printf("Opcion incorrecta!!!\n");
		menuProvinciasHoteles(provincias);
	}

}

void menuAdmin(Provincias *provincias) {
	char str[10];
	int opcion;
	printf("============\nMENU ADMIN\n============");
	printf("\n1. Mostrar hoteles existentes.\n2. Anadir hotel.");
	printf(
			"\n3. Eliminar hotel.\n4. Mostrar reservas realizadas por distintos usuarios.");
	printf("\n5. Salir.\nOpcion: ");
	fflush(stdout);
	fgets(str, 3, stdin);
	sscanf(str, "%d", &opcion);
	switch (opcion) {
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

int main(void) {
	//INICIALIZACION DE LA BD
	sqlite3 * db;
	int result = sqlite3_open("bd/hotel.sqlite", &db); // &db es la dir de un puntero, por tanto es un puntero a un puntero que apunta a sqlite3
	if (result != SQLITE_OK) {
		printf("Error opening database\n");
	}
	printf("Database opened\n");
	//------------------------------------------------------------------
	//CREACION DE PROVINCIAS CON BD

	Provincias *provincias = (Provincias *) malloc(sizeof(Provincias));
	provincias->numProvincias = contarProvincias(db);
	provincias->provincias = malloc(provincias->numProvincias * sizeof(Provincia));
	initProvincias(provincias, db);

	//------------------------------------------------------------------
	//CREACION DE HOTELES CON BD TODO: SE NECESITAN JUNTAR HOTELES CON PROVINCIAS PARA QUE VAYA EL MENU, Y HOTELES EN SI
	Hoteles * hoteles = (Hoteles *) malloc(sizeof(Hoteles));
	hoteles->hoteles = malloc(hoteles->numHoteles * sizeof(Hotel));
	hoteles->numHoteles = contarHoteles(db);
	printf("NUMERO DE HOTELES == %d\n", hoteles->numHoteles);
	initHoteles(hoteles, db);

	//------------------------------------------------------------------
	//ANADIR HOTELES A UNA PROVINCIA (para probar la funcionalidad) (sin bd)
	provincias->provincias[1].hoteles.hoteles = (Hotel*) malloc(3 * sizeof(Hotel));
	provincias->provincias[1].hoteles = *hoteles;
	provincias->provincias[1].hoteles.numHoteles = 3;

	//------------------------------------------------------------------
	//INICIAR MENU
	menuAdmin(provincias);

	//------------------------------------------------------------------
	//CERRAR LA BD
	result = sqlite3_close(db);
		if (result != SQLITE_OK) {
			printf("\nError closing database\n");
			printf("%s\n", sqlite3_errmsg(db));
			return result;
		}
	printf("\nDatabase closed\n");
	//------------------------------------------------------------------

	//LIBERACION DE MEMORIA
	free(provincias);
	free(provincias->provincias);
//	free(hoteles);
//	free(hoteles->hoteles);
//	free(hotel1);
//	free(hotel2);
//	free(hotel3);
	free(provincias->provincias[1].hoteles.hoteles);

	//------------------------------------------------------------------

	return 0;
}

