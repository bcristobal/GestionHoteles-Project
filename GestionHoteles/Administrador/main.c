#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../provincia/provincia.h"
#include "../hotel/hotel.h"
#include "../bd/base_datos.h"

char BD[20];
char version_app[20];

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

void mostrarHoteles(Provincias *provincias, int eleccion, Hoteles* hoteles, sqlite3 * bd) {
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
	char str[10];
	int opcion;
	printf("99. Menu principal\nOpcion: ");
	fflush(stdout);
	fgets(str, 10, stdin);
	sscanf(str, "%d", &opcion);
	if(opcion == 99){
		printf("\n\n\n");
		menuAdmin(provincias, hoteles, bd);
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
		mostrarHoteles(provincias, opcion - 1, hoteles, db);
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
		printf("=================\nMOSTRAR HOTELES\n=================");
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
		menuAdmin(provincias, hoteles, db);
	}
	else {
		printf("Opcion incorrecta!\n");
		menuEliminarHotel(provincias, hoteles, db);
	}

}

void menuAdmin(Provincias *provincias, Hoteles* hoteles, sqlite3* db) {
	char str[10];
	int opcion;
	printf("============\nMENU ADMIN\n============\n");
	printf("v:%s", version_app);
	printf("\n1. Mostrar hoteles existentes.\n2. Anadir hotel.");
	printf("\n3. Eliminar hotel.\n4. Mostrar reservas realizadas por distintos usuarios.");
	printf("\n5. Salir.\nOpcion: ");

	while(opcion < 6 || opcion > 0){
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
			printf("Proximamente disponible...\n");
			opcion = 5;
		} else if (opcion == 5){ //SALIR
			exit(EXIT_FAILURE);
		}
	}

}

void cargarPropiedades(){
    FILE *fp;
    char line[50];
    char key[20];
    char value[30];

    fp = fopen("properties/configuration.properties", "r");
    if (fp == NULL) {
        printf("Error al abrir el archivo de configuracion\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, 50, fp) != NULL) {
        if (line[0] == '#' || line[0] == '\n') {
            continue;
        }
        sscanf(line, "%[^=]=%[^\n]", key, value);
        if (strcmp(key, "bd") == 0) {
            strcpy(BD, value);
        } else if (strcmp(key, "version") == 0) {
            strcpy(version_app, value);
        }
    }
    fclose(fp);
}

int main(void) {
	cargarPropiedades();
	//INICIALIZACION DE LA BD
	sqlite3 * db;
	int result = sqlite3_open(BD, &db);
	if (result != SQLITE_OK) {
		logMensaje("Error opening database");
	}
	logMensaje("Error opening database");
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
		logMensaje(strcat("\nError closing database", sqlite3_errmsg(db)));
		return result;
	}
	logMensaje("\nDatabase closed");
	//------------------------------------------------------------------

	//LIBERACION DE MEMORIA
	free(provincias->provincias);
	free(provincias);
	free(hoteles->hoteles);
	free(hoteles);

	//------------------------------------------------------------------

	return 0;
}

