
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
	int contador = 0;
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

		do {
			result = sqlite3_step(stmt) ;
			if (result == SQLITE_ROW) {
				contador++;

			}
		} while (result == SQLITE_ROW);

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
	(*provincias).numProvincias = contarProvincias(db);
	Provincia *prov;
	for (int i = 0; i < (*provincias).numProvincias; ++i) {
		prov = malloc(sizeof(Provincia));
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			(*prov).id = sqlite3_column_int(stmt, 0);
			strcpy((*prov).name, (char *) sqlite3_column_text(stmt, 1));
		}
		provincias[i] = prov;
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
