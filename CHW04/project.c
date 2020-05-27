#define MAX_NUM_PRODUCTS 20;
#define MAX_PRODUCT_NAME_LENGTH 20;
#define MAX_CATEGORY_LENGTH 10;
#define BARCODE_LENGTH 12;

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
"Please choose operation[1 - 6]:";

//operation 1 constant strings

const char *  adding_product_barcode = "Please enter product barcode:";
const char * barcode_already_exist = "This product already exist, please enter the number of products to add:";
const char * too_much_products = "Can't add more products, not enough space";
const char * adding_product_name = "Please enter product name:";
const char * adding_product_category = "Please enter product category:";
const char * adding_product_number = "Please enter number of products to add:";
const char * adding_product_price = "Please enter the price of the product:";
const char * adding_product_date = "Please enter expire date of the product[dd/mm/yy]:";

//operation 2 constant strings
const char * store_empty = "\nThe store is empty!";
const char * delete_barcode = "\nPlease enter product barcode you want to delete:";
const char * delete_barcode_cant_find = "\nCouldn't find the product barcode, try again...";
const char * delete_barcode_succeed = "\nThe product deleted successfully!";


//operation 3 constant strings
const char * expired_date_check = "\nWhat date you want to check[dd/mm/yy]:";
const char * expired_products = "\n~~~~~~~~~~~~~~~Expired Products~~~~~~~~~~~~~~~\n";
const char * expired_product_name = "Product name: ";
const char * expired_product_barcode = "\nProduct barcode: ";
const char * expired_product_date = "\nProduct expire date: ";


//operation 4 constant strings
const char * print_no_products = "\nNo products in the store!\n";
const char * print_products = "\n----------";
const char * print_product_name = "\nProduct name: ";
const char * print_product_barcode = "\nProduct barcode: ";
const char * print_product_category = "\nProduct category: ";
const char * print_product_number = "\nProduct available quantity: ";
const char * print_product_price = "\nProduct price: ";
const char * print_product_expireDate = "\nProduct expire date: ";
const char * print_total_number = "\nTotal number of products: ";

//operation 5 constant strings
const char * update_barcode = "\nPlease enter product barcode you want to update:";
const char * update_barcode_notFound = "\nCouldn't find the product barcode, try again...";
const char * update_interface_string = ("\nWhat do you want to update?\n"\
	"        1. Product namet\n"\
	"        2. Product category\n"\
	"        3. Product quantity\n"\
	"        4. Product price\n"\
	"        5. Product expire date\n"\
	"Please choose operation [1-5]:");
const char * update_product_name = "\nPlease enter new product name:";
const char * update_product_category = "\nPlease enter new product category:";
const char * update_product_number = "\nPlease enter new product quantity:";
const char * update_product_price = "\nPlease enter new product price:";
const char * update_product_date = "\nPlease enter new product expire date[dd/mm/yy]:";

//operation 6 constant strings
exitProgram = "\nexit...";

typedef struct date { int year; int month; int day; } date;
typedef struct product { char * product_name; char * product_category; char * barcode; int available; double price; date * expire_date; } product;
typedef struct super_market { product ** product_list; int number_of_products; } super_market;

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

product* new_product(const char* product_name, const char* product_category, const char* barcode) {
	product* newProduct = (product*)malloc(sizeof(product));
	
	newProduct->product_name = (char*)malloc(strlen(product_name));
	strcpy(newProduct->product_name, product_name);

	newProduct->product_category = (char*)malloc(strlen(product_category));
	strcpy(newProduct->product_category, product_category);

	newProduct->barcode = (char*)malloc(strlen(barcode));
	strcpy(newProduct->barcode, barcode);

	newProduct->expire_date = (date*)malloc(sizeof(date));

	return newProduct;
}

void AddProduct(super_market super) {
	
}

void RemoveProduct(super_market super) {

}

void CheckExpiredProducts(super_market super) {

}

void PrintProducts(super_market super) {
	
}

void UpdateProduct(super_market super) {

}

int main() {

	super_market* mySuper = (super_market*)malloc(sizeof(super_market));
	mySuper->number_of_products = 0;

	char* productName = NULL;
	char* productCategory = NULL;
	char* productBarcode = NULL;

	productName = GetString();
	productCategory = GetString();
	productBarcode = GetString();

	product* newProduct = new_product(productName, productCategory, productBarcode);
	mySuper->number_of_products++;

	mySuper->product_list = (product**)realloc(mySuper->product_list, sizeof(product*) * mySuper->number_of_products);

	*(mySuper->product_list + (mySuper->number_of_products - 1)) = newProduct;

	productName = GetString();
	productCategory = GetString();
	productBarcode = GetString();

	product* newProduct2 = new_product(productName, productCategory, productBarcode);
	mySuper->number_of_products++;

	mySuper->product_list = (product**)realloc(mySuper->product_list, sizeof(product*) * mySuper->number_of_products);
	*(mySuper->product_list + (mySuper->number_of_products - 1)) = newProduct;

	return 0;
}