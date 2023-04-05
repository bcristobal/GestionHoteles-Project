#ifndef HOTEL_H_
#define HOTEL_H_

typedef struct {
	int id;
	char name[20];
	int estrellas;
} Hotel;

typedef struct {
	Hotel *hoteles;
	int numHoteles;
} Hoteles;

void imprimirHotel(Hotel*);

#endif /* HOTEL_H_ */
