//#define _CRT_SECURE_NO_WARNINGS
//#define MAX_NUM_PRODUCTS 20
//#define MAX_PRODUCT_NAME_LENGTH 20
//#define MAX_CATEGORY_LENGTH 10
//#define BARCODE_LENGTH 12
//
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//
//typedef struct date
//{
//	int year;
//	int month;
//	int day;
//} date;
//
//typedef struct product
//{
//	char * product_name;
//	char * product_category;
//	char * barcode;
//	int available;
//	double price;
//	date * expire_date;
//} product;
//
//typedef struct super_market
//{
//	product ** product_list;
//	int number_of_products;
//} super_market;
//
//void PrintHelper(char * str) //Inputs: str pointer, output: Adjusted string (without extra \n)
//{
//	int len = (int)strlen(str);
//	if (len > 0 && str[len - 1] == '\n')
//		str[len - 1] = '\0';
//}
//
//date * New_date(char *date_s, super_market *sm1) { //Inputs: Super market pointer,date string Output: Date pointer after allocating memory 
//	date *res = malloc(sizeof(date));
//	if (res == NULL) {
//		printf("Memory allocation failed");//Free Memory in case memory allocation failed
//		return res;
//	}
//	res->day = (int)(date_s[0] - '0') * 10 + (int)(date_s[1] - '0'); // (char - '0') Casting Char input to int
//	res->month = (int)(date_s[3] - '0') * 10 + (int)(date_s[4] - '0');
//	res->year = (int)(date_s[6] - '0') * 10 + (int)(date_s[7] - '0');
//
//	return res;
//}
//
//void freeProductMemory(super_market* sm1, int index) //Input: Super market pointer, index of the product we wish to remove. Freeing memory of the product
//{
//	if (sm1->product_list[index]->product_name != NULL)//Free memory  of each attribute of product 
//		free(sm1->product_list[index]->product_name);
//	if (sm1->product_list[index]->product_category != NULL)
//		free(sm1->product_list[index]->product_category);
//	if (sm1->product_list[index]->expire_date != NULL)
//		free(sm1->product_list[index]->expire_date);
//	if (sm1->product_list[index]->barcode != NULL)
//		free(sm1->product_list[index]->barcode);
//	if (sm1->product_list[index] != NULL)
//		free(sm1->product_list[index]);
//}
//void Replaceproduct(super_market* sm1, int index) // //Input: Super market pointer, index of product, Adjusting index of product to fill spaces in the array
//{
//	if (index != sm1->number_of_products - 1)  // Check if product(index) is in the end of array 
//	{
//		freeProductMemory(sm1, index);
//		sm1->product_list[index] = sm1->product_list[sm1->number_of_products - 1];
//	}
//	else
//	{
//		freeProductMemory(sm1, index);
//	}
//}
//
//void ExpiredDates(super_market* sm1) { //Input:Super market pointer,Output:None,Scanning a date and Checking which Products are expired 
//	int year, month, day;
//	char  str_date[10];
//	printf("What date you want to check[dd/mm/yy]:");
//	scanf("%s", str_date);//Scanning Date
//	day = (str_date[0] - '0') * 10 + (str_date[1] - '0');
//	month = (str_date[3] - '0') * 10 + (str_date[4] - '0');
//	year = (str_date[6] - '0') * 10 + (str_date[7] - '0');
//	printf("~~~~~~~~~~~~~~~Expired Products~~~~~~~~~~~~~~~\n");
//	for (int i = 0; i < sm1->number_of_products; i++) {
//		if (sm1->product_list[i]->expire_date->year < year) // Checking year  
//		{
//			printf("Product name: %s\n", sm1->product_list[i]->product_name);//Printing Expired product details
//			printf("Product barcode: %s\n", sm1->product_list[i]->barcode);
//			printf("Product expiration date: %d/%d/%d\n", sm1->product_list[i]->expire_date->day, sm1->product_list[i]->expire_date->month, sm1->product_list[i]->expire_date->year);
//		}
//		if (sm1->product_list[i]->expire_date->year == year) // Checking year and month 
//			if (sm1->product_list[i]->expire_date->month < month)
//			{
//				printf("Product name: %s\n", sm1->product_list[i]->product_name);
//				printf("Product barcode: %s\n", sm1->product_list[i]->barcode);
//				printf("Product expiration date: %d/%d/%d\n", sm1->product_list[i]->expire_date->day, sm1->product_list[i]->expire_date->month, sm1->product_list[i]->expire_date->year);
//			}
//		if (sm1->product_list[i]->expire_date->month == month)  // Checking year month and day 
//			if (sm1->product_list[i]->expire_date->day < day) {
//				printf("Product name: %s\n", sm1->product_list[i]->product_name);
//				printf("Product barcode: %s\n", sm1->product_list[i]->barcode);
//				printf("Product expiration date: %d/%d/%d\n", sm1->product_list[i]->expire_date->day, sm1->product_list[i]->expire_date->month, sm1->product_list[i]->expire_date->year);
//			}
//	}
//
//}
//
//int addProduct(super_market* sm1)//Inputs:Super market pointer,Output: 1-new Product , 0- Existing product,Scanning Barcode, checking if it exists, and allocating memory for a new product if needed
//{
//	char * barcode[BARCODE_LENGTH + 2], product_name[MAX_PRODUCT_NAME_LENGTH + 2], product_category[MAX_CATEGORY_LENGTH + 2], datestr[10];
//	int quantity;
//	int flag = 0, work = 0;//work- Return value
//	double price = 0;
//	if (sm1->number_of_products < MAX_NUM_PRODUCTS) //Check if there is room in the product list
//	{
//		setbuf(stdin, NULL);
//		printf("Please enter product barcode:");
//		fgets(barcode, BARCODE_LENGTH + 2, stdin);
//		PrintHelper(barcode);
//		setbuf(stdin, NULL);
//		for (int i = 0; i < sm1->number_of_products; i++)
//		{
//			if (strcmp(sm1->product_list[i]->barcode, barcode) == 0)//Checking if the barcode exists in the product list
//			{
//				printf("This product already exist, please enter the number of products to add: ");
//				scanf("%d", &quantity);
//				printf("Additional %d products of %s added\n", quantity, sm1->product_list[i]->product_name);
//				flag = 1;  //If a product with the scanned barcode if already exist
//				break;
//			}
//		}
//		if (flag == 0)  // flag = 0,New product; allocating memory for a new product and its attributes 
//		{
//			if (NULL == (sm1->product_list[sm1->number_of_products] = (product*)malloc(sizeof(product))))//Checking if allocating memory succeeded
//			{
//				printf("Memory allocation failed");
//				return 0;
//			}
//			if (NULL == (sm1->product_list[sm1->number_of_products]->barcode = (char*)malloc((BARCODE_LENGTH + 2) * sizeof(char)))) {
//				printf("Memory allocation failed");
//				free(sm1->product_list[sm1->number_of_products]);//Free all related allocated memory for the product when allocating memory for barcode failed
//				return 0;
//			}
//			strcpy(sm1->product_list[sm1->number_of_products]->barcode, barcode);
//
//			printf("Please enter product name:");
//			fgets(product_name, MAX_PRODUCT_NAME_LENGTH + 2, stdin);
//			setbuf(stdin, NULL);
//			PrintHelper(product_name);
//			if (NULL == (sm1->product_list[sm1->number_of_products]->product_name = (char*)malloc((MAX_PRODUCT_NAME_LENGTH + 2) * sizeof(char)))) {//Free all related allocated memory for the product when allocating memory for product name failed
//				printf("Memory allocation failed");
//				free(sm1->product_list[sm1->number_of_products]->barcode);
//				free(sm1->product_list[sm1->number_of_products]);
//				return 0;
//			}
//			strcpy(sm1->product_list[sm1->number_of_products]->product_name, product_name);
//
//			printf("Please enter product category:");
//			fgets(product_category, MAX_CATEGORY_LENGTH + 2, stdin);
//			setbuf(stdin, NULL);
//			PrintHelper(product_category);
//			if (NULL == (sm1->product_list[sm1->number_of_products]->product_category = (char*)malloc((MAX_CATEGORY_LENGTH + 2) * sizeof(char)))) {
//				printf("Memory allocation failed");
//				free(sm1->product_list[sm1->number_of_products]->product_name);
//				free(sm1->product_list[sm1->number_of_products]->barcode);
//				free(sm1->product_list[sm1->number_of_products]);
//				return 0;
//			}
//			strcpy(sm1->product_list[sm1->number_of_products]->product_category, product_category);
//
//			printf("Please enter number of products to add:");
//			scanf("%d", &quantity);
//			sm1->product_list[sm1->number_of_products]->available = quantity;
//
//			printf("Please enter the price of the product:");
//			scanf("%lf", &price);
//			sm1->product_list[sm1->number_of_products]->price = price;
//
//			printf("Please enter expiration date of the product[dd/mm/yy]:");
//			scanf("%s", datestr);
//			date *temp_date = New_date(datestr, sm1);
//			if (temp_date == NULL)
//			{
//				free(sm1->product_list[sm1->number_of_products]->product_category);
//				free(sm1->product_list[sm1->number_of_products]->product_name);
//				free(sm1->product_list[sm1->number_of_products]->barcode);
//				free(sm1->product_list[sm1->number_of_products]);
//				return 0;
//			}
//			sm1->product_list[sm1->number_of_products]->expire_date = temp_date;
//
//			printf("The product %s -barcode:%s ,added successfully\n", sm1->product_list[sm1->number_of_products]->product_name, sm1->product_list[sm1->number_of_products]->barcode);
//			work = 1;
//		}
//	}
//	else //If the product list is full
//		printf("Can't add more products, not enough space!\n");
//	return work;
//}
//int removeProduct(super_market* sm1)//Inputs:Super market pointer,Output:0- if product list is full, 1- Otherwise, Checking if barcode exist in the list, and deleting the suiable product
//{
//	int flag = 0, i;
//	char * barcode[BARCODE_LENGTH + 2];
//	if (sm1->number_of_products == 0)//If there are no products in the supermarket
//	{
//		printf("The store is empty!\n");
//		return 0;
//	}
//	else
//	{
//		printf("Please enter product barcode you want to delete:");
//		setbuf(stdin, NULL);
//		fgets(barcode, BARCODE_LENGTH + 2, stdin);
//		PrintHelper(barcode);
//		setbuf(stdin, NULL);
//		for (i = 0; i < sm1->number_of_products; i++)//Checking if the barcode exist
//			if (strcmp(sm1->product_list[i]->barcode, barcode) == 0)
//			{
//				flag++;//Incrementing flag if the barcode exist
//				break;
//			}
//		if (flag == 1)
//		{
//			Replaceproduct(sm1, i);
//			printf("The product deleted successfully!\n");//Removal Product Success
//			return 1;
//		}
//		else
//		{
//			printf("Couldn't find the product barcode, try again...\n");//Printed when didn't find barcode match
//			return(removeProduct(sm1));
//		}
//	}
//}
//void PrintAll(super_market* sm1)//Input:Super market pointer,output:None,Printing all products by index
//{
//	if (sm1->number_of_products == 0)//Checking if the product list is empty
//		printf("No products in the store!\n");
//	else
//	{
//		printf("~~~~~~~~~~~~~~~All Products~~~~~~~~~~~~~~~\n");
//		for (int i = 0; i < sm1->number_of_products; i++)//Product Details print
//		{
//			printf("----------\n");
//			printf("Product name: %s \n", sm1->product_list[i]->product_name);
//			printf("Product barcode: %s \n", sm1->product_list[i]->barcode);
//			printf("Product category: %s \n", sm1->product_list[i]->product_category);
//			printf("Product available quantity: %d \n", sm1->product_list[i]->available);
//			printf("Product price: %g \n", sm1->product_list[i]->price);
//			printf("Product expiration date: %d/%d/%d\n", sm1->product_list[i]->expire_date->day, sm1->product_list[i]->expire_date->month, sm1->product_list[i]->expire_date->year);
//		}
//		printf("Total number of products: %d \n", sm1->number_of_products);
//	}
//}
//void Updateproduct(super_market* sm1)//Inputs:Super market pointer,output:None,Updating product info by barcode
//{
//	char * barcode[BARCODE_LENGTH + 2], product_name[MAX_PRODUCT_NAME_LENGTH + 2], product_category[MAX_CATEGORY_LENGTH + 2], str_date[10];
//	int flag = 0, update_choice = 0, new_quantity = 0, i;
//	double new_price = 0.;
//	if (sm1->number_of_products == 0)//Checking if the list of products if empty
//		printf("No products in the store!\n");
//	else
//	{
//		printf("Please enter product barcode you want to update:");
//		setbuf(stdin, NULL);
//		fgets(barcode, BARCODE_LENGTH + 2, stdin);
//		PrintHelper(barcode);
//		setbuf(stdin, NULL);
//		for (i = 0; i < sm1->number_of_products; i++)//Checking if Barcode exists
//		{
//			if (strcmp(sm1->product_list[i]->barcode, barcode) == 0)
//			{
//				flag++;
//				break;
//			}
//		}
//		if (flag == 1)//If Barcode exists, entering the update menu
//		{
//			printf("What do you want to update?\n"\
//				"	1. Product name\n"\
//				"	2. Product category\n"\
//				"	3. Product quantity\n"\
//				"	4. Product price\n"\
//				"	5. Product expiration date\n"\
//				"Please choose operation [1-5]:");
//			scanf("%d", &update_choice);//Scanning the choice of user what info to update
//			if (update_choice == 1)
//			{
//				printf("Please enter new product name:");
//				setbuf(stdin, NULL);
//				fgets(product_name, MAX_PRODUCT_NAME_LENGTH + 2, stdin);
//				setbuf(stdin, NULL);
//				PrintHelper(product_name);//Adjusting string input
//				strcpy(sm1->product_list[i]->product_name, product_name);//Changing Value
//			}
//			if (update_choice == 2)
//			{
//				printf("Please enter new product category:");
//				setbuf(stdin, NULL);
//				fgets(product_category, MAX_CATEGORY_LENGTH + 2, stdin);
//				setbuf(stdin, NULL);
//				PrintHelper(product_category);//Ajusting string input
//				strcpy(sm1->product_list[i]->product_category, product_category);//Changing Value
//			}
//			if (update_choice == 3)
//			{
//				printf("Please enter new product quantity:");
//				setbuf(stdin, NULL);
//				scanf("%d", &new_quantity);//Scanning new value
//				sm1->product_list[i]->available = new_quantity;//Changing Value
//				setbuf(stdin, NULL);
//			}
//			if (update_choice == 4)
//			{
//				printf("Please enter new product price:");
//				scanf("%lf", &new_price);//Scanning new value
//				sm1->product_list[i]->price = new_price;//Changing Value
//				setbuf(stdin, NULL);
//			}
//			if (update_choice == 5)
//			{
//				printf("Please enter new product expiration date[dd/mm/yy]:");//Scanning new value
//				scanf("%s", str_date);
//				sm1->product_list[i]->expire_date->day = (str_date[0] - '0') * 10 + (str_date[1] - '0');//Assignning new date
//				sm1->product_list[i]->expire_date->month = (str_date[3] - '0') * 10 + (str_date[4] - '0');
//				sm1->product_list[i]->expire_date->year = (str_date[6] - '0') * 10 + (str_date[7] - '0');
//			}
//		}
//		else
//		{
//			printf("Couldn't find the product barcode, try again...\n");//If we didn't find suitable barcode
//			Updateproduct(sm1);
//		}
//	}
//}
//
//void mainfunc(super_market* sm1)//Main function, Inputs:a super market pointer, Output: None, Printing main interface and scanning the user Choice 
//{
//	int choice;
//	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"\
//		"Welcome to CORONA market!\n"\
//		"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"\
//		"Manage market menu:\n"\
//		"	1. Add product\n"\
//		"	2. Remove product\n"\
//		"	3. Check which products are expired\n"\
//		"	4. Print all the products\n"\
//		"	5. Update product\n"\
//		"	6. EXIT SYSTEM\n"\
//		"Please choose operation [1-6]:");
//	scanf("%d", &choice);
//	if (choice == 1)//Choosing to add product
//	{
//		int work = 0;//Indicator if Product was added or not
//		work = addProduct(sm1);
//		sm1->number_of_products += work;
//		choice = 0;
//		mainfunc(sm1);
//	}
//	if (choice == 2)//Choosing to remove product 
//	{
//		int work = 0;//Indicator if Product was removed or not
//		work = removeProduct(sm1);
//		sm1->number_of_products -= work;
//		choice = 0;
//		mainfunc(sm1);
//	}
//	if (choice == 3)//Choosing to Check expired dates
//	{
//		ExpiredDates(sm1);
//		choice = 0;
//		mainfunc(sm1);
//	}
//	if (choice == 4)//Choosing to Print all products
//	{
//		PrintAll(sm1);
//		choice = 0;
//		mainfunc(sm1);
//	}
//	if (choice == 5)//Choosing to Update Product
//	{
//		Updateproduct(sm1);
//		choice = 0;
//		mainfunc(sm1);
//	}
//	if (choice == 6)//Choosing to exit
//		printf("exit...");
//}
//
//void free_memory(super_market * sm1) { //Inputs: Super market pointer, Outputs:None, Free memory of all products in the list, final function
//	for (int i = 0; i < sm1->number_of_products; i++)//Iterating over the whole array of products and free allocated memory
//		freeProductMemory(sm1, i);
//	free(sm1->product_list);
//	free(sm1);
//}
//int main()
//{
//	super_market *sm1 = (super_market*)malloc(sizeof(super_market));//Allocating memory for super market pointer
//	if (sm1 == NULL)
//		return 1;
//	sm1->number_of_products = 0;
//	if (NULL == (sm1->product_list = (product**)malloc(MAX_NUM_PRODUCTS * sizeof(product*))))//Allocating memory for product list
//	{
//		printf("memory allocation failed");
//		free(sm1);
//		return 1;
//	}
//	mainfunc(sm1);
//	free_memory(sm1);
//
//	int value = _CrtDumpMemoryLeaks();
//	return 0;
//}