/*
2. Se citesc n numere (n > 3) intregi fara semn (32 biti) din fisierul in.txt. Aceastea se vor depune
intr-o stiva in ordinea citirii lor. Dupa ce toate numerele au fost depuse in stiva se vor
executa urmatoarele operatii, pana cand nu mai exista numere in stiva:
a) daca numarul de elemente din stiva este >= 2, acestea se vor extrage si se va depune in sirul Sir[], numarul de biti de "1"
din cele doua numere.
b) daca numarul de elemente din stiva este <=1 atunci acesta (numarul extras din stiva) se va depune in sirul Sir[] cu bitul "6" setat.
Aceesul la tabloul Sir[] se va realiza prin pointeri.

Continutul vectorului Sir[] se va depune in fisierul out.txt.
*/

#define _CRT_SECURE_NO_WARNINGS
#define EROARE -1 
#define MAX_STACK_SIZE 17

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//prototipe functii

unsigned char IsStackEmpty(unsigned int *Stack_Local, unsigned int *SP_Local);
unsigned char IsStackFull(unsigned int *Stack_Local, unsigned int *SP_Local);
void Push(unsigned int *Stack_Local, unsigned int *SP_Local, unsigned int ValueToAdd);
unsigned int Pop(unsigned int *Stack_Local, unsigned int *SP_Local);
void CreateStack(unsigned int *Stack_Local, unsigned int *SP_Local);

int main() {

	FILE *FisierIntrare, *FisierIesire;
	unsigned int Value, Counter = 0, Index, ValueFromFile = 0, Stack[MAX_STACK_SIZE], StackPointer, *Sir, PopValue1, PopValue2, XOR, BitsOf0, BitsOf1;
	unsigned int IndexSir = 0, OK = 0;
	time_t t1;
	Sir = (unsigned int*)malloc(MAX_STACK_SIZE * sizeof(unsigned int));
	if (Sir == NULL) {
		printf("Eroare la alocarea dinamica de memorie");
		exit(EROARE);
	}
	CreateStack(&Stack, &StackPointer);
	FisierIntrare = fopen("in.txt", "w+");
	FisierIesire = fopen("out.txt", "w+");
	StackPointer = 0;

	if (FisierIesire == NULL || FisierIntrare == NULL) {
		printf("Eroare la deschidere fisiere");
		exit(EROARE);
	}
	//generam MAX_STACK_SIZE numere random in fisier intre 0 si 100
	srand((unsigned)time(&t1));
	while (Counter != MAX_STACK_SIZE) {
		Value = rand() % 100;
		fprintf(FisierIntrare, "%d ", Value);
		Counter++;
	}

	rewind(FisierIntrare); //resetam pointer-ul la prima adresa din fisier

	while (!feof(FisierIntrare)) {
		fscanf(FisierIntrare, "%d", &ValueFromFile);
		Push(&Stack, &StackPointer, ValueFromFile);
	}

	if (StackPointer == MAX_STACK_SIZE)
		printf("S-au pus toate numerele in stiva cu SUCCES\n");
	else
	{
		printf("EROARE in punerea elementelor in stiva!\n");
		exit(EROARE);
	}

	while (StackPointer != 0) {
		if (StackPointer >= 2) {
			XOR = 0;
			PopValue1 = Pop(&Stack, &StackPointer);
			PopValue2 = Pop(&Stack, &StackPointer);
			XOR = PopValue1 | PopValue2;
			BitsOf0 = 0;
			BitsOf1 = 0;
			while (XOR > 0) {
				if (XOR & 1)
					BitsOf1++;
				else
					BitsOf0++;
				XOR = XOR >> 1;
			}
			Sir[IndexSir] = BitsOf1;
			IndexSir++;
		}
		else if (StackPointer <= 1) {
			PopValue1 = Pop(&Stack, &StackPointer);
			PopValue1 = PopValue1 | (1 << 6);
			Sir[IndexSir] = PopValue1;
			OK = 1;
		}
	}
	if (OK == 0)
		IndexSir--;
	for (Index = 0; Index <= IndexSir; Index++) {
		fprintf(FisierIesire, "%d ", *(Sir + Index));
	}
	if (Index == IndexSir + 1)
		printf("S-au pus in out.txt numerele cerute\n");
	else
		printf("EROARE la punerea in fisierul out.txt\n");

	system("pause");
	return 0;
}

unsigned char IsStackEmpty(unsigned int SP_Local) {
	if (SP_Local == 0)
		return 1;
	else
		return 0;

}

unsigned char IsStackFull(unsigned int *SP_Local) {
	if (*SP_Local == MAX_STACK_SIZE)
		return 1;
	else
		return 0;
}


void Push(unsigned int *Stack_Local, unsigned int *SP_Local, unsigned int ValueToAdd) {
	if (!IsStackFull(SP_Local)) {
		Stack_Local[*SP_Local] = ValueToAdd;
		*SP_Local = *SP_Local + 1;
	}

}

unsigned int Pop(unsigned int *Stack_Local, unsigned int *SP_Local) {
	unsigned int ValueToBePopped;
	if (!IsStackEmpty(SP_Local)) {
		*SP_Local = *SP_Local - 1;
		ValueToBePopped = Stack_Local[*SP_Local];
		return ValueToBePopped;
	}
	else
		return 0;

}

void CreateStack(unsigned int *Stack_Local, unsigned int *SP_Local)
{
	unsigned int count;
	*SP_Local = 0;
	for (count = 0; count < MAX_STACK_SIZE; count++)
	{
		Stack_Local[count] = 0;
	}
}

