
#ifndef BASE_DATOS_H_
#define BASE_DATOS_H_

#include "sqlite3.h"
#include <stdio.h>
#include <string.h>
#include "../provincia/provincia.h"

int validadAdmin(char* usuario, char* clave, sqlite3 *db); // 0 es valido(el resto invalido)
int contarProvincias(sqlite3 *db);
int initProvincias (Provincias* provincias, sqlite3 *db);

#endif /* BASE_DATOS_H_ */
