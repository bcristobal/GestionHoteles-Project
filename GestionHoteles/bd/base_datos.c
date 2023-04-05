#include "base_datos.h"
#include <stdlib.h>


int validadAdmin(char* usuario, char* clave, sqlite3 *db) {
	char c[30];

	sqlite3_stmt *stmt;
	char sql[] = "SELECT CLAVE_ADMIN FROM ADMINISTRADOR WHERE USUARIO_ADMIN = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	else {
		printf("SQL query prepared (SELECT)\n");
	}

	result = sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	else {
		printf("Parameters binded\n");
	}

	result = sqlite3_step(stmt) ;
	if (result == SQLITE_ROW) {
		strcpy(c, (char *) sqlite3_column_text(stmt, 0));
		printf("se copia en c\n");
	}

	result = sqlite3_finalize(stmt);
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));
		}
		else {
			printf("Prepared statement finalized (SELECT)\n");
		}

	return strcmp(c, clave);
}

int contarProvincias(sqlite3 *db) {
	int contador;
	sqlite3_stmt *stmt;
		char sql[] = "SELECT COUNT(ID_PROV) FROM PROVINCIA";

		int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
		if (result != SQLITE_OK) {
			printf("Error preparing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));
		}
		else {
			printf("SQL query prepared (SELECT)\n");
		}

		result = sqlite3_step(stmt) ;
			if (result == SQLITE_ROW) {
				contador = sqlite3_column_int(stmt, 0);
				printf("se copia en c\n");
			}

		result = sqlite3_finalize(stmt);
			if (result != SQLITE_OK) {
				printf("Error finalizing statement (SELECT)\n");
				printf("%s\n", sqlite3_errmsg(db));
			}
			else {
				printf("Prepared statement finalized (SELECT)\n");
			}

		return contador;
}

int initProvincias (Provincias* provincias, sqlite3 *db) {
	sqlite3_stmt *stmt;
	char sql[] = "SELECT ID_PROV, NOM_PROV FROM PROVINCIA";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	else {
		printf("SQL query prepared (SELECT)\n");
	}
	//(*provincias).numProvincias = contarProvincias(db);
	//Provincia *prov;
	for (int i = 0; i < (*provincias).numProvincias; ++i) {
		//prov = malloc(sizeof(Provincia));
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			(*provincias).provincias[i].id = sqlite3_column_int(stmt, 0);
			strcpy((*provincias).provincias[i].name, (char *) sqlite3_column_text(stmt, 1));
		}
	}



	result = sqlite3_finalize(stmt);
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));
		}
		else {
			printf("Prepared statement finalized (SELECT)\n");
		}

	return result;

}

int contarHoteles(sqlite3 *db) {
	int contador;
	sqlite3_stmt *stmt;
		char sql[] = "SELECT COUNT(ID_HOTEL) FROM HOTEL";

		int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
		if (result != SQLITE_OK) {
			printf("\nError preparing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));
		}
		else {
			printf("SQL query prepared (SELECT)\n");
		}

		result = sqlite3_step(stmt) ;
			if (result == SQLITE_ROW) {
				contador = sqlite3_column_int(stmt, 0);
				printf("se copia en c\n");
			}

		result = sqlite3_finalize(stmt);
			if (result != SQLITE_OK) {
				printf("\nError finalizing statement (SELECT)\n");
				printf("%s\n", sqlite3_errmsg(db));
			}
			else {
				printf("Prepared statement finalized (SELECT)\n");
			}

		return contador;
}

int initHoteles (Hoteles * hoteles, sqlite3 *db, Provincias * provincias) {
	sqlite3_stmt *stmt;
	char sql[] = "SELECT h.ID_HOTEL, h.NOM_HOTEL, h.NUM_ESTTRELLAS, h.ID_PROV FROM HOTEL h";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	else {
		printf("SQL query prepared (SELECT)\n");
	}
	for (int i = 0; i < (*hoteles).numHoteles; ++i) {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			(*hoteles).hoteles[i].id = sqlite3_column_int(stmt, 0);
			strcpy((*hoteles).hoteles[i].name, (char *) sqlite3_column_text(stmt, 1));
			(*hoteles).hoteles[i].estrellas = sqlite3_column_int(stmt, 2);
			for (int n = 0; n < contarProvincias(db); ++n) {
				if (provincias->provincias[n].id == sqlite3_column_int(stmt, 3)) {
					(*hoteles).hoteles[i].provincia = provincias->provincias[n];
				}
			}

		}
	}



	result = sqlite3_finalize(stmt);
		if (result != SQLITE_OK) {
			printf("\nError finalizing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));
		}
		else {
			printf("Prepared statement finalized (SELECT)\n");
		}

	return result;

}
