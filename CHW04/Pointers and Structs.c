#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma region Menu
const char * main_interface = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"\
"Welcome to Candy market!\n"\
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"\
"Manage market menu :\n"\
"	1. Add Candy\n"\
"	2. Remove Candy\n"\
"	3. Print all the products\n"\
"	4. EXIT SYSTEM\n"\
"Please choose operation[1 - 4]:";
#pragma endregion

typedef struct Candy
{
	int price;
	char* name;
} Candy;

typedef struct Child
{
	int age;
	char* name;
} Child;

char* GetString() {
	char inputChar;
	char* string = NULL;
	int size = 1;

	inputChar = getchar();

	while (inputChar != '\n') {
		size++;
		string = (char*)realloc(string, size * sizeof(char));

		if (string == NULL) {
			return NULL;
		}

		string[size - 2] = inputChar;

		inputChar = getchar();
	}

	string[size - 1] = '\0';
	return string;
}

Candy* new_candy(int price, const char* name) {
	Candy* candy = (Candy*)malloc(sizeof(Candy));

	candy->price = price;
	candy->name = (char*)malloc(strlen(name));
	strcpy(candy->name, name);

	return candy;
}

int main() {
	#pragma region Pointers

	#pragma region Pointer to a number

	int number = 15;
	int* numberPtr = &number;

	/*printf("\n-----\n\n");

	printf("number: %d, number memory address: %d", number, numberPtr);

	printf("\n\n-----\n\n");

	printf("number: %d, number value: %d", number, *numberPtr);*/

	#pragma endregion

	#pragma region Pointer to a pointer

	/*printf("\n\n-----\n\n");

	int** numberPtrPtr = &numberPtr;

	printf("-number: %d\n-number memory address: %d\n-number memory adress, memory adress: %d", number, numberPtr, numberPtrPtr);

	printf("\n\n-----\n\n");*/

	#pragma endregion

	#pragma region Types of pointers

	//// Variables
	//double doubleValue = 0.5;
	//float floatValue = 0.546f;
	//unsigned int uIntValue = -270;
	//char charValue = 'B';

	//// Pointers
	//double* doublePtr = &doubleValue;
	//float* floatPtr = &floatValue;
	//unsigned int* uIntPtr = &uIntValue;
	//char* charPtr = &charValue;
	//// Show in memory
	//*(charPtr + 1) = 'A';

	//// DoublePointers
	//double** doublePPtr = &doublePtr;
	//float** floatPPtr = &floatPtr;
	//unsigned int** uIntPPtr = &uIntPtr;
	//char** charPPtr = &charPtr;

	#pragma endregion

	#pragma region Pointer Operations

	//int number2 = 15;
	//int number3 = 20;
	//int* number2Ptr = &number2;
	//int* number2Ptr2 = &number2;

	//*number2Ptr = 16;
	////number2Ptr2 = 50; // Error
	//number2Ptr2 = &number3;

	//int addition = *number2Ptr + *number2Ptr2;

	#pragma endregion


	#pragma endregion

	#pragma region Structs

	Candy myCandy;
	
	myCandy.name = "Chocolate";
	
	myCandy.price = 5;

	myCandy.name = "Chocolate2";

	Candy* candyPtr = &myCandy;

	candyPtr->name = "Bubblegum";
	candyPtr->price = 1;

	(*candyPtr).name = "Kinder";
	(*candyPtr).price = 3;

	#pragma endregion

	#pragma region Dynamic Allocation
	
	/*int* daIntZeros = (int*)calloc(5, sizeof(int));
	int* daInt = (int*)malloc(sizeof(int) * 5);

	*daInt = 10;
	*(daInt + 1) = 20;
	*(daInt + 2) = 30;
	*(daInt + 3) = 40;
	*(daInt + 4) = 50;
	daInt = (int*)realloc(daInt, sizeof(int) * 6);
	*(daInt + 5) = 50;*/

	/*int* array = NULL;
	int input = -1;
	int size = 0;
	int index = 0;

	printf("Enter a new number or -1 to exit: ");
	scanf("%d", &input);

	while (input != -1) {
		size++;
		array = (int*)realloc(array, sizeof(int) * size);
		array[index] = input;
		index++;

		printf("Enter a new number or -1 to exit: ");
		scanf("%d", &input);
	}
	
	free(array);

	printf("\n");*/

	#pragma endregion
	
	#pragma region Reading Strings
	
	/*char* string = GetString();

	free(string);*/

	#pragma endregion

	#pragma region Struct Pointers

	//Candy* candyPtr = new_candy(7, "Magnum Double Chocolate");

	#pragma endregion

	#pragma region Array of arrays

	/*int matrix[2][2];
	int** dynamicMatrix = (int**)malloc(sizeof(int*) * 2);

	for (int i = 0; i < 2; i++) {
		*(dynamicMatrix + i) = (int*)calloc(2, sizeof(int));

		for (int j = 0; j < 2; j++) {
			*(*(dynamicMatrix + i) + j) = (j + 1) * 100;
		}
	}

	free(dynamicMatrix);

	int size = 5;
	char* anotherMatrix = (int*)calloc(size * size, sizeof(char));

	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			int index = (row * size) + col;

			*(anotherMatrix + (row * size) + col) = 'a' + col;

			printf("%c ", *(anotherMatrix + (row * size) + col));
		}
		printf("\n");
	}

	free(anotherMatrix);*/

	#pragma endregion

	#pragma region Array of structs

	Candy candyArray[10];

	Candy** candyStore = (Candy**)malloc(sizeof(Candy*));

	*(candyStore) = new_candy(1, "Bazooka");

	candyStore = (Candy**)realloc(candyStore, sizeof(Candy*) * 2);
	*(candyStore + 1) = new_candy(12, "Magnum White Chocolate");

	candyStore = (Candy**)realloc(candyStore, sizeof(Candy*) * 3);
	*(candyStore + 2) = new_candy(50, "Glidoniot");

	free(candyStore);

	#pragma endregion

	return 0;
}