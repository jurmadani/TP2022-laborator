/*
1. Se citesc dintr-un fisier in.txt un set de numere naturale (pe 32 biti). Sa se implementeze urmatoarele operatii, iar apoi sa se depuna
in fisier rezultatul fiecarei operatii:
a) sa se sorteze sirul citit in ordine crescatoare a numerelor folosing o metoda cunoscuta si sa se depuna sirul sortat in fisierul out.txt
b) sa se caute in sirul sortat utilizand cautarea binara, numarul de pe pozitia 2, in forma complementata. (e.g. daca elementul de pe pozitia
2 este 0x23 atunci numarul care se cauta in sir este 0xBA). Sa se depuna pozitia pe care se gaseste numarul. Daca acesta nu este gasit, atunci
se va depune 0.
c) Pentru toate numerele din sir, se va seta bitul 3 si se vor depune toate elementele sirului in out.txt
d) Pentru toate numerele din sir, se va numara totalul de biti de 1 si se va depune in fiser.
e) sa se implementeze o functie care copiaza sirul rezultat la punctul a) intr-un alt sir destinatie care va contine copia primului sir.
Prototipul functie va fi void memcopy( tip_32_biti * dest, tip_32_biti * src, tip_32_biti length);
*/


#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define EXIT_WITH_ERROR 0
#define MAX_SIZE_VECTOR_INTEGER 50
#define LinieNoua printf("\n");

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//prototipe functii
unsigned char SortareSir(unsigned int *Array, unsigned int MaxSize);
unsigned int SetBit(unsigned int Value);
void memcopy(unsigned int *dest, unsigned int *src, unsigned int length);

int main() {

	FILE *FisierIntrare, *FisierIesire;
	unsigned int IntegerFromFile = 0, NumberOfElements = 0, VectorElemente[MAX_SIZE_VECTOR_INTEGER], Index = 0, Auxiliary, NumarBiti = 0;
	unsigned int VectorElemente_2[MAX_SIZE_VECTOR_INTEGER];
	FisierIntrare = fopen("in.txt", "r");
	FisierIesire = fopen("out.txt", "w+");
	if (FisierIntrare == NULL || FisierIesire == NULL) {
		printf("Eroare la deschidere fisier!");
		exit(EXIT_WITH_ERROR);
	}
	while (!feof(FisierIntrare))
	{
		fscanf(FisierIntrare, "%d", &IntegerFromFile);
		VectorElemente[NumberOfElements] = IntegerFromFile;
		NumberOfElements++;
	}

	fclose(FisierIntrare);

	//punctul a
	printf("a)");
	if (SortareSir(&VectorElemente, NumberOfElements) == 1) {
		for (Index = 0; Index < NumberOfElements; Index++) {
			printf("%d ", VectorElemente[Index]);
		}
	}
	else
	{
		printf("Eroare la sortare!");
	}
	memcopy(&VectorElemente_2, &VectorElemente, NumberOfElements);
	/*
	punctul b nu stiu
	*/

	//punctul c

	for (Index = 0; Index < NumberOfElements; Index++) {
		Auxiliary = SetBit(VectorElemente[Index]);
		VectorElemente[Index] = Auxiliary;
	}
	LinieNoua;
	for (Index = 0; Index < NumberOfElements; Index++) {
		fprintf(FisierIesire, "%d ", VectorElemente[Index]);
	}
	printf("b)Nu stiu\n");
	if (Index == NumberOfElements)
		printf("c)S-a realizat scrierea in fisierul out.txt\n");
	else
		printf("c)Nu s-a putut scrie in fisierul out.txt\n");

	//punctul d
	for (Index = 0; Index < NumberOfElements; Index++) {
		NumarBiti = 0;
		Auxiliary = VectorElemente[Index];
		fprintf(FisierIesire, "\n");
		fprintf(FisierIesire, "%d", Auxiliary);
		while (Auxiliary) {
			if (Auxiliary & 1 == 1)
				NumarBiti++;
			Auxiliary = Auxiliary >> 1;
		}
		fprintf(FisierIesire, " are %d biti de 1", NumarBiti);
	}
	if (Index == NumberOfElements)
		printf("d)S-a scris in fisierul out.txt numarul de biti\n");
	else
		printf("%d)Eroare la scriere in fisier\n");

	//punctul e
	printf("e)Sirul copiat cu ajutorul functiei 'memcopy': ");
	for (Index = 0; Index < NumberOfElements; Index++) {
		printf("%d ", VectorElemente_2[Index]);
	}

	LinieNoua;
	system("pause");
	return 0;
}

unsigned char SortareSir(unsigned int *Array, unsigned int MaxSize) {
	unsigned int Index1 = 0, Index2 = 0, Auxiliary;

	for (Index1 = 0; Index1 < MaxSize - 1; Index1++) {
		for (Index2 = Index1 + 1; Index2 < MaxSize; Index2++) {
			if (*(Array + Index1) > *(Array + Index2)) {
				Auxiliary = *(Array + Index1);
				*(Array + Index1) = *(Array + Index2);
				*(Array + Index2) = Auxiliary;
			}
		}
	}
	if (Index1 == MaxSize - 1 && Index2 == MaxSize)
		return 1;
	else
		return 0;
}

unsigned int SetBit(unsigned int Value) {

	unsigned int BitPosition = 3;
	return (Value | (1 << (BitPosition)));

}

void memcopy(unsigned int *dest, unsigned int *src, unsigned int length) {
	unsigned int Index = 0,Index2=0;
	for (Index; Index < length; Index++) {
		*(dest + Index2) = *(src + Index);
		Index2++;
	}

}