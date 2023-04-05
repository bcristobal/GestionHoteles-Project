#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../provincia/provincia.h"
#include "../hotel/hotel.h"
#include "../bd/base_datos.h"

void menuAdmin(Provincias *provincias, Hoteles* hoteles, sqlite3* db);
void loginAdmin (sqlite3* db);

void loginAdmin (sqlite3* db) {
	int validar;
	char usuario[20], clave[20];
	do {
		printf("=================\nLOGIN\n=================\n");
			printf("Usuario: ");
			fflush(stdout);
			scanf("%s", usuario);
			printf("Clave: ");
			fflush(stdout);
			scanf("%s", clave);
		validar = validadAdmin(usuario, clave, db);
	} while (validar != 0);
}

void mostrarHoteles(Provincias *provincias, int eleccion, Hoteles* hoteles) {
	printf("\n\n\n=================\nMOSTRAR HOTELES\n=================");
	int n;
	char nombreProvincia[20];
	strcpy(nombreProvincia, provincias->provincias[eleccion].name);
	printf("\nHoteles de la provincia de %s:\n", nombreProvincia);
	for (n = 0; n < hoteles->numHoteles; ++n) {
		if (strcmp(hoteles->hoteles[n].provincia->name, nombreProvincia) == 0){
			imprimirHotel(&hoteles->hoteles[n]);
		}
	}
}

void menuProvinciasHoteles(Provincias* provincias, Hoteles* hoteles, sqlite3* db) {
	char str[10];
	int opcion;
	printf("\n\n\n=================\nMOSTRAR HOTELES\n=================");
	printf("\nProvincias:\n");
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
		mostrarHoteles(provincias, opcion - 1, hoteles);
	} else if (opcion == n + 1) {
		printf("\n\n\n");
		menuAdmin(provincias, hoteles, db);
	} else {
		printf("Opcion incorrecta!!!\n");
		menuProvinciasHoteles(provincias, hoteles, db);
	}

}

Hotel menuAnadirHotel (Provincias* provincias) {
	Hotel hotel;
	int idProv = 0;
	printf("=================\nAÑADIR HOTEL\n=================\n");
	printf("Nombre: ");
	fflush(stdout);
	scanf("%s", hotel.name);
	do {
		printf("estrellas: ");
		fflush(stdout);
		scanf("%i", &hotel.estrellas);
	} while (hotel.estrellas < 1 || hotel.estrellas > 5);

	for (int i = 0; i < (*provincias).numProvincias; ++i) {
		printf("%i. %s\n", provincias->provincias[i].id, provincias->provincias[i].name);
	}
	do {
		printf("Opcion: ");
		fflush(stdout);
		scanf("%i", &idProv);
	} while (idProv < 0 || idProv > (*provincias).numProvincias - 1);
	hotel.provincia = &((*provincias).provincias[idProv]);

	return hotel;
}

void menuEliminarHotel (Provincias* provincias, Hoteles * hoteles, sqlite3* db) {
	char str[10];
	int opcion;
	printf("=================\nELIMINAR HOTEL\n=================\n");
	int n;
	for (n = 0; n < provincias->numProvincias; ++n) {
		printf("%d. ", provincias->provincias[n].id + 1);
		imprimirProvincia(&provincias->provincias[n]);
	}
	printf("%d. Atras\n", n + 1);
	printf("Opcion: ");
	fflush(stdout);
	fgets(str, 10, stdin);
	sscanf(str, "%d", &opcion);
	opcion--;
	if (provincias->provincias[opcion].id == opcion) {
		printf("opcion provincias check\n");
		printf("\n\n\n=================\nMOSTRAR HOTELES\n=================");
		int j;
		char nombreProvincia[20];
		strcpy(nombreProvincia, provincias->provincias[opcion].name);
		printf("\nHoteles de la provincia de %s:\n", nombreProvincia);
		for (j = 0; j < hoteles->numHoteles; ++j) {
			if (strcmp(hoteles->hoteles[j].provincia->name, nombreProvincia) == 0){
				printf("ID: %d Nombre: ", hoteles->hoteles[j].id);
				imprimirHotel(&hoteles->hoteles[j]);
			}
		}
		printf("Opcion: ");
		fflush(stdout);
		fgets(str, 10, stdin);
		sscanf(str, "%d", &opcion);
		for (int i = 0; i < hoteles->numHoteles; ++i) {
			if (opcion == hoteles->hoteles[i].id) {
				eliminarHotel(&hoteles->hoteles[i], db);
			}
		}

	} else if (opcion == n + 1) {
		printf("\n\n\n");
		menuAdmin(provincias, hoteles, db);
	} else {
		printf("Opcion incorrecta!!!\n");
		menuEliminarHotel(provincias, hoteles, db);
	}

}

void menuAdmin(Provincias *provincias, Hoteles* hoteles, sqlite3* db) {
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
	if(opcion == 1){ //MOSTRAR HOTELES
		menuProvinciasHoteles(provincias, hoteles, db);
	} else if(opcion == 2){ //ANADIR HOTEL
		Hotel hotel;
		hotel = menuAnadirHotel(provincias);
		imprimirHotel(&hotel);
		insertarHotel(&hotel, db);
	} else if(opcion == 3){ //ELIMINAR HOTEL
		menuEliminarHotel(provincias, hoteles, db);
	} else if(opcion == 4){ //MOSTRAR RESERVAS
		printf("Prueba");
	} else if(opcion == 5){ //SALIR
		printf("\nGracias por utilizar nuestros sevicios!");
	}else {
		printf("\nOpcion incorrecta!!!\n");
		menuAdmin(provincias, hoteles, db);
	}
}

int main(void) {
	//INICIALIZACION DE LA BD
	sqlite3 * db;
	int result = sqlite3_open("bd/hotel.sqlite", &db); // &db es la dir de un puntero, por tanto es un puntero a un puntero que apunta a sqlite3
	if (result != SQLITE_OK) {
		logMensaje("Error opening database\n");
	}
	logMensaje("Error opening database\n");
	//------------------------------------------------------------------
	//LOGIN
	loginAdmin(db);
	//------------------------------------------------------------------
	//CREACION DE PROVINCIAS CON BD

	Provincias *provincias = (Provincias *) malloc(sizeof(Provincias));
	provincias->numProvincias = contarProvincias(db);
	provincias->provincias = malloc(provincias->numProvincias * sizeof(Provincia));
	initProvincias(provincias, db);

	//------------------------------------------------------------------
	//CREACION DE HOTELES CON BD
	Hoteles * hoteles = (Hoteles *) malloc(sizeof(Hoteles));
	hoteles->hoteles = malloc(hoteles->numHoteles * sizeof(Hotel));
	hoteles->numHoteles = contarHoteles(db);
	initHoteles(hoteles, db, provincias);

	//------------------------------------------------------------------
	//INICIAR MENU
	menuAdmin(provincias, hoteles, db);

	//------------------------------------------------------------------
	//CERRAR LA BD
	result = sqlite3_close(db);
		if (result != SQLITE_OK) {
			logMensaje(strcat("\nError closing database\n", sqlite3_errmsg(db)));
			return result;
		}
		logMensaje("\nDatabase closed\n");
	//------------------------------------------------------------------

	//LIBERACION DE MEMORIA
//	for (int i = 0; i < hoteles->numHoteles; ++i) {
//		free(&hoteles->hoteles[i].provincia);
//	}
//	for (int i = 0; i < hoteles->numHoteles; ++i) {
//		free(&hoteles->hoteles[i]);
//	}
	free(provincias->provincias);
	free(provincias);
	free(hoteles->hoteles);
	free(hoteles);

	//------------------------------------------------------------------

	return 0;
}

