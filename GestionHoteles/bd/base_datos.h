
#ifndef BASE_DATOS_H_
#define BASE_DATOS_H_

#include "sqlite3.h"
#include <stdio.h>
#include <string.h>
#include "../provincia/provincia.h"
#include "../hotel/hotel.h"

int validadAdmin(char*, char*, sqlite3*); // 0 es valido(el resto invalido)
int contarProvincias(sqlite3*);
int initProvincias (Provincias*, sqlite3*);
int contarHoteles(sqlite3*);
int initHoteles (Hoteles * hoteles, sqlite3 *db, Provincias * provincias);

#endif /* BASE_DATOS_H_ */
