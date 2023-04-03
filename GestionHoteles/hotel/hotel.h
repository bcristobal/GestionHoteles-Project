#ifndef HOTEL_H_
#define HOTEL_H_

typedef struct {
	char name[20];
	int estrellas;
} Hotel;

typedef struct {
	Hotel *hoteles;
	int numHoteles;
} Hoteles;

void imprimirHotel(Hotel*);

#endif /* HOTEL_H_ */
