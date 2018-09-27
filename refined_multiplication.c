#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void shiftToRight(char product[]) {
	for (int i = 0; i < 62; i++) {
		product[63 - i] = product[63 - i - 1];
	}
	product[0] = '0';
}

void addRemainder(char product[], int i) {
	product[i] = '0';
	if ( 0 != i ) {
		if ( '0' == product[i - 1] ) {
			product[i - 1] = '1';
		} else {
			addRemainder(product, i - 1);
		}
	}
}

int addBits(char a, char b) {
	if ( '0' == a ) {
		if ( '0' == b ) {
			return 0;
		} else {
			return 1;
		}
	} else if ( '0' == b ) {
		return 1;
	} else {
		return 2;
	}
}

void addMultiplicant(char multiplicant[], char product[]) {
	for (int i = 0; i < 32; i++) {
		int sum = addBits(multiplicant[31 - i], product[31 - i]);
		if ( 1 == sum ) {
			product[31 - i] = '1';
		} else if ( 2 == sum ) {
			addRemainder(product, 31 - i);
		}
	}
}

int main(int argc, char const *argv[]) {
	char multiplicant[] = "00000000000000000000000001100010";
	char product[] = "0000000000000000000000000000000000000000000000000000000000010010";
	printf("%8s | %20s | %32s | %64s\n", "iteration", "step", "multiplicant", "product");
	printf("%4d%5s | %20s | %32s | %64s\n", 0, "", "initialize values", multiplicant, product);
	for (int i = 0; i < 32; i++) {
		if (product[63] == '1') {
			addMultiplicant(multiplicant, product);
			printf("%4d%5s | %20s | %32s | %64s\n", i + 1, "", "a. 1 -> add multplct", multiplicant, product);
		} else {
			printf("%4d%5s | %20s | %32s | %64s\n", i + 1, "", "a. 0 -> no operation", multiplicant, product);
		}
		shiftToRight(product);
		printf("%4d%5s | %20s | %32s | %64s\n", i + 1, "", "b. shift right", multiplicant, product);
	}
	return 0;
}
