#include <stdio.h>
#include "hotel.h"

void imprimirHotel(Hotel *hotel) {
	printf("%s ", hotel->name);
	for (int n = 0; n < hotel->estrellas; ++n) {
		printf("*");
	}
	printf("\n");
}

