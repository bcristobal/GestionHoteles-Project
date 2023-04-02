
#include "base_datos.h"

int validadAdmin(char* usuario, char* clave, sqlite3 *db) {
	char c[30];

	sqlite3_stmt *stmt;
	char sql[] = "SELECT CLAVE FROM ADMINISTRADOR WHERE USUARIO = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	printf("SQL query prepared (SELECT)\n");

	result = sqlite3_bind_text(stmt, 1, usuario, strlen(usuario), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_step(stmt) ;
	if (result == SQLITE_ROW) {
		strcpy(c, (char *) sqlite3_column_text(stmt, 1));
	}

	result = sqlite3_finalize(stmt);
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (SELECT)\n");
			printf("%s\n", sqlite3_errmsg(db));
			return result;
		}
		printf("Prepared statement finalized (SELECT)\n");

	return strcmp(c, clave);
}
