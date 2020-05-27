#define MAX_NUM_PRODUCTS 20
#define MAX_PRODUCT_NAME_LENGTH 20
#define MAX_CATEGORY_LENGTH 10
#define BARCODE_LENGTH 12
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


const char * main_interface = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"\
"Welcome to CORONA market!\n"\
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"\
"Manage market menu :\n"\
"	1. Add product\n"\
"	2. Remove product\n"\
"	3. Check which products are expired\n"\
"	4. Print all the products\n"\
"	5. Update product\n"\
"	6. EXIT SYSTEM\n"\
"Please choose operation[1-6]:";

//operation 1 constant strings

const char *  adding_product_barcode = "Please enter product barcode:";
const char * barcode_already_exist = "This product already exist, please enter the number of products to add:";
const char * too_much_products = "Can't add more products, not enough space";
const char * adding_product_name = "Please enter product name:";
const char * adding_product_category = "Please enter product category:";
const char * adding_product_number = "Please enter number of products to add:";
const char * adding_product_price = "Please enter the price of the product:";
const char * adding_product_date = "Please enter expiration date of the product[dd/mm/yy]:";

//operation 2 constant strings
const char * store_empty = "The store is empty!";
const char * delete_barcode = "Please enter product barcode you want to delete:";
const char * delete_barcode_cant_find = "Couldn't find the product barcode, try again...";
const char * delete_barcode_succeed = "The product deleted successfully!";


//operation 3 constant strings
const char * expired_date_check = "What date you want to check[dd/mm/yy]:";
const char * expired_products = "~~~~~~~~~~~~~~~Expired Products~~~~~~~~~~~~~~~\n";
const char * expired_product_name = "Product name: ";
const char * expired_product_barcode = "Product barcode: ";
const char * expired_product_date = "Product expiration date: ";


//operation 4 constant strings
const char * print_products_head = "~~~~~~~~~~~~~~~All Products~~~~~~~~~~~~~~~\n";
const char * print_no_products = "No products in the store!\n";
const char * print_products = "----------";
const char * print_product_name = "Product name: ";
const char * print_product_barcode = "Product barcode: ";
const char * print_product_category = "Product category: ";
const char * print_product_number = "Product available quantity: ";
const char * print_product_price = "Product price: ";
const char * print_product_expireDate = "Product expiration date: ";
const char * print_total_number = "Total number of products: ";

//operation 5 constant strings
const char * update_barcode = "Please enter product barcode you want to update:";
const char * update_barcode_notFound = "Couldn't find the product barcode, try again...";
const char * update_interface_string = ("What do you want to update?\n"\
	"	1. Product name\n"\
	"	2. Product category\n"\
	"	3. Product quantity\n"\
	"	4. Product price\n"\
	"	5. Product expiration date\n"\
	"Please choose operation [1-5]:");
const char * update_product_name = "Please enter new product name:";
const char * update_product_category = "Please enter new product category:";
const char * update_product_number = "Please enter new product quantity:";
const char * update_product_price = "Please enter new product price:";
const char * update_product_date = "Please enter new product expiration date[dd/mm/yy]:";

//operation 6 constant strings
const char * exitProgram = "exit...";

typedef struct date
{
	int year;
	int month;
	int day;
} date;

typedef struct product
{
	char * product_name;
	char * product_category;
	char * barcode;
	int available;
	double price;
	date * expire_date;
} product;

typedef struct super_market
{
	product ** product_list;
	int number_of_products;
} super_market;


//Getdate - get date from user 
date* Getdate() {
	date* expire_date = (date*)malloc(sizeof(date));

	if (expire_date == NULL) {
		exit(1);
	}

	int day, month, year;

	scanf("%d/%d/%d", &day, &month, &year);

	expire_date->day = day;
	expire_date->month = month;
	expire_date->year = year;

	return expire_date;
}

//  Barcode- Check - func to check if Barcode exist by str conpare 
int barcode_Check(const char *barcode, const super_market* ourSuperMarket) {
	for (int i = 0; i < ourSuperMarket->number_of_products; i++) {
		if (strcmp(ourSuperMarket->product_list[i]->barcode, barcode) == 0) //found same barcode 
			return i;
	}

	return -1;
}


// Initial Memory Allocation to NewProduct
product* new_product(const char* barcode,
	const char* product_category,
	const char* product_name,
	int available,
	double price,
	date * expire_date) {

	product*  newProduct = (product*)malloc(sizeof(product));
	if (newProduct == NULL) {// check if memory allocated
		printf("Unable to Allocate Product Memory");
		exit(1);
	}

	newProduct->product_name = (char*)malloc(MAX_PRODUCT_NAME_LENGTH);
	if (newProduct->product_name == NULL) {// check if memory allocated
		printf("Unable to Allocate Product Name Memory");
		exit(1);
	}
	strcpy(newProduct->product_name, product_name);


	newProduct->product_category = (char*)malloc(MAX_CATEGORY_LENGTH);
	if (newProduct->product_category == NULL) {// check if memory allocated
		printf("Unable to Allocate Product Category Memory");
		exit(1);
	}
	strcpy(newProduct->product_category, product_category);


	newProduct->barcode = (char*)malloc(BARCODE_LENGTH);
	if (newProduct->barcode == NULL) {// check if memory allocated
		printf("Unable to Allocate Barcode Memory");
		exit(1);
	}
	strcpy(newProduct->barcode, barcode);

	newProduct->expire_date = expire_date;

	newProduct->price = price;
	newProduct->available = available;

	return newProduct;
}

// Add Product Function 
void AddProduct(super_market* ourSuperMarket) {
	//reset pointers
	char product_name[MAX_PRODUCT_NAME_LENGTH];
	char product_category[MAX_CATEGORY_LENGTH];
	char barcode[BARCODE_LENGTH];
	date * expire_date = NULL;
	int available;
	double price;
	int change = 0; // if the barcode exists, change is the num of products to add.

	if (product_name == NULL || product_category == NULL || barcode == NULL) {
		exit(1);
	}

	if (ourSuperMarket->number_of_products == MAX_NUM_PRODUCTS) {
		printf(too_much_products);
		free(product_name);
		free(product_category);
		free(barcode);
		free(expire_date);
		return;
	}

	// get product info
	printf(adding_product_barcode);
	scanf("%s", barcode);

	int product_index = barcode_Check(barcode, ourSuperMarket);

	//check if barcode exists & update num of product if barcode exists
	if (product_index != -1) { // the product  already exists
		printf(barcode_already_exist);
		scanf("%d", &change);
		ourSuperMarket->product_list[product_index]->available += change;
		return;
	}

	printf(adding_product_name);
	scanf("%s", product_name);

	printf(adding_product_category);
	scanf("%s", product_category);

	printf(adding_product_number);
	scanf("%d", &available);

	printf(adding_product_price);
	scanf("%lf", &price);

	printf(adding_product_date);
	expire_date = Getdate();

	printf("The product %s -barcode:%s ,added successfully\n", product_name, barcode);


	product* newProduct = new_product(barcode, product_name, product_category, available, price, expire_date);
	ourSuperMarket->number_of_products++;

	ourSuperMarket->product_list = (product**)realloc(ourSuperMarket->product_list, sizeof(product*) * ourSuperMarket->number_of_products);
	ourSuperMarket->product_list[ourSuperMarket->number_of_products - 1] = newProduct;
}


// Interface Func - user choose operation num
int menu() {
	int Choice = 0;

	printf(main_interface);

	scanf("%d", &Choice);
	return Choice;
}

// Remove Product Function
void Remove_Product(const char* barcode, super_market*  ourSuperMarket) {
	int index;
	char new_barcode;

	if (barcode_Check(barcode, ourSuperMarket) == -1) {//product was not found 
		printf(delete_barcode_cant_find);
		printf("\n");
		printf(delete_barcode);
		scanf("%s", &new_barcode);
		Remove_Product(&new_barcode, ourSuperMarket);
	}

	index = barcode_Check(barcode, ourSuperMarket);

	if (index != -1) { //the barcode of the product was found -> delete the product 
		free(ourSuperMarket->product_list[index]->expire_date);
		free(ourSuperMarket->product_list[index]->product_name);
		free(ourSuperMarket->product_list[index]->barcode);
		free(ourSuperMarket->product_list[index]->product_category);
		free(ourSuperMarket->product_list[index]);

		for (int i = index + 1; i < ourSuperMarket->number_of_products - 1; i++) {
			ourSuperMarket->product_list[i - 1] = ourSuperMarket->product_list[i];
		}
		ourSuperMarket->number_of_products--;
		ourSuperMarket->product_list = (product**)realloc(ourSuperMarket->product_list, sizeof(product*) * ourSuperMarket->number_of_products);
		printf(delete_barcode_succeed);
		printf("\n");
	}

	return;
}



void print_expierd(int i, super_market*  ourSuperMarket) {
	printf(expired_product_name);
	printf(ourSuperMarket->product_list[i]->product_name);
	printf("\n");
	printf(expired_product_barcode);
	printf(ourSuperMarket->product_list[i]->barcode);
	printf("\n");
	printf(expired_product_date);
	printf("%d/%d/%d", ourSuperMarket->product_list[i]->expire_date->day, ourSuperMarket->product_list[i]->expire_date->month, ourSuperMarket->product_list[i]->expire_date->year);
	printf("\n");

	return;
}


//Expier date 
void which_expierd(super_market*  ourSuperMarket) {
	date* date_to_check = (date*)malloc(sizeof(date));

	if (date_to_check == NULL) // check if memory allocated
		exit(1);

	printf(expired_date_check);
	date_to_check = Getdate();
	printf(expired_products);

	for (int i = 0; i < ourSuperMarket->number_of_products; i++) {
		if (ourSuperMarket->product_list[i]->expire_date->year < date_to_check->year) {
			print_expierd(i, ourSuperMarket);

		}
		else if (ourSuperMarket->product_list[i]->expire_date->month < date_to_check->month && ourSuperMarket->product_list[i]->expire_date->year == date_to_check->year) {
			print_expierd(i, ourSuperMarket);

		}
		else if (ourSuperMarket->product_list[i]->expire_date->day < date_to_check->day && ourSuperMarket->product_list[i]->expire_date->year == date_to_check->year && ourSuperMarket->product_list[i]->expire_date->month == date_to_check->month) {
			print_expierd(i, ourSuperMarket);

		}
	}

	free(date_to_check);

	return;
}

//Print all products 
void Print_all(super_market* ourSuperMarket) {

	if (ourSuperMarket->number_of_products == 0) {
		printf(print_no_products);
		return;

	}

	printf(print_products_head);

	for (int i = 0; i < ourSuperMarket->number_of_products; i++) {
		printf(print_products);
		printf("\n");
		printf(print_product_name);
		printf("%s\n", ourSuperMarket->product_list[i]->product_name);
		printf(print_product_barcode);
		printf("%s\n", ourSuperMarket->product_list[i]->barcode);
		printf(print_product_category);
		printf("%s\n", ourSuperMarket->product_list[i]->product_category);
		printf(print_product_number);
		printf("%d\n", ourSuperMarket->product_list[i]->available);
		printf(print_product_price);
		printf("%g\n", ourSuperMarket->product_list[i]->price);
		printf(print_product_expireDate);
		printf("%d/%d/%d\n", ourSuperMarket->product_list[i]->expire_date->day, ourSuperMarket->product_list[i]->expire_date->month, ourSuperMarket->product_list[i]->expire_date->year);

		if (i == ourSuperMarket->number_of_products - 1) {
			printf(print_total_number);
			printf("%d\n", ourSuperMarket->number_of_products);
		}
	}
	return;
}

// Update Product Function

void Update_product(super_market* ourSuperMarket) {
	//reset pointers
	char* up_product_name = (char*)malloc(MAX_PRODUCT_NAME_LENGTH);
	char* up_product_category = (char*)malloc(MAX_CATEGORY_LENGTH);
	char* up_barcode = (char*)malloc(BARCODE_LENGTH);
	date * up_expire_date = NULL;
	int User_choice_update = 0;

	if (up_product_name == NULL || up_product_category == NULL || up_barcode == NULL) {  // check if memory allocated 
		exit(1);
	}

	if (ourSuperMarket->number_of_products == 0) { // super  market empty 
		printf(print_no_products);
	}

	printf(update_barcode);
	scanf("%s", up_barcode);

	int update_index = barcode_Check(up_barcode, ourSuperMarket);

	if (update_index == -1) { //  the barcode wasnt found
		printf(update_barcode_notFound);
		printf("\n");
		free(up_barcode);
		Update_product(ourSuperMarket);
	}

	printf(update_interface_string);

	scanf("%d", &User_choice_update);

	if (User_choice_update == 1) { //update product name
		printf(update_product_name);
		scanf("%s", up_product_name);
		strcpy(ourSuperMarket->product_list[update_index]->product_name, up_product_name);
		free(up_product_name);
		free(up_product_category);
		free(up_expire_date);
	}

	else if (User_choice_update == 2) { //update product category 
		printf(update_product_category);
		scanf("%s", up_product_category);
		strcpy(ourSuperMarket->product_list[update_index]->product_category, up_product_category);
		free(up_product_name);
		free(up_product_category);
		free(up_expire_date);
	}

	else if (User_choice_update == 3) { //update quantity
		printf(update_product_number);
		scanf("%d", ourSuperMarket->product_list[update_index]->available);
	}

	else if (User_choice_update == 4) { //update price
		printf(update_product_price);
		scanf("%lf", ourSuperMarket->product_list[update_index]->price);
	}

	else if (User_choice_update == 5) { //update expired date 
		printf(update_product_date);
		up_expire_date = Getdate();
		ourSuperMarket->product_list[update_index]->expire_date->day = up_expire_date->day;
		ourSuperMarket->product_list[update_index]->expire_date->month = up_expire_date->month;
		ourSuperMarket->product_list[update_index]->expire_date->year = up_expire_date->year;
		free(up_product_name);
		free(up_product_category);
		free(up_expire_date);
	}
	return;
}


//exit function 
void Exit_func(super_market* ourSuperMarket) {

	for (int i = 0; i < ourSuperMarket->number_of_products; i++) {
		free(ourSuperMarket->product_list[i]->product_name);
		free(ourSuperMarket->product_list[i]->product_category);
		free(ourSuperMarket->product_list[i]->barcode);
		free(ourSuperMarket->product_list[i]->expire_date);
		free(ourSuperMarket->product_list[i]);
	}
	free(ourSuperMarket->product_list);
	free(ourSuperMarket);
	return;
}


int main() {
	super_market* ourSuperMarket = (super_market*)malloc(sizeof(super_market));
	if (ourSuperMarket == NULL) // check if memory allocated
		return 1;

	ourSuperMarket->number_of_products = 0;
	ourSuperMarket->product_list = (product**)malloc(sizeof(product*));

	int User_Choice = 0;
	User_Choice = menu();

	while (User_Choice != 6) {
		// user choose to add product
		if (User_Choice == 1) {

			AddProduct(ourSuperMarket);

			User_Choice = 0;
		}
		// user choose to remove product
		else if (User_Choice == 2) {
			char barcode[BARCODE_LENGTH];
			printf(delete_barcode);
			scanf("%s", &barcode);

			Remove_Product(&barcode, ourSuperMarket);
		}

		// user choose to check which products are expired
		else if (User_Choice == 3) {
			which_expierd(ourSuperMarket);

		}

		//user choose to print all products 
		else if (User_Choice == 4) {
			Print_all(ourSuperMarket);

		}

		// user choose to update product info 
		else if (User_Choice == 5) {
			Update_product(ourSuperMarket);
		}
		User_Choice = menu();
	}


	// user choose to exit
	printf(exitProgram);
	Exit_func(ourSuperMarket);
	int value = _CrtDumpMemoryLeaks();
	if (_CrtDumpMemoryLeaks() == 0)//Remove!
	{
		printf("\n\n\n Memory Good Ya Gever\n\n\n");
	}

	return 0;

}

