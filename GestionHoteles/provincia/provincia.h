#ifndef PROVINCIA_H_
#define PROVINCIA_H_

#include "../hotel/hotel.h"

typedef struct {
	int id;
	char name[20];
	Hoteles hoteles;
} Provincia;

typedef struct {
	Provincia *provincias;
	int numProvincias;
} Provincias;

void imprimirProvincia(Provincia*);

#endif /* PROVINCIA_H_ */
