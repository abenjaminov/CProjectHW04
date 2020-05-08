#define MAX_NUM_PRODUCTS 20
#define MAX_PRODUCT_NAME_LENGTH 20
#define MAX_CATEGORY_LENGTH 10
#define DATE_LENGTH 10
#define BARCODE_LENGTH 12
typedef int bool;
#define true 1
#define false 0

#define ADD 1
#define REMOVE 2
#define CHECK_EXPIRED 3
#define PRINT 4
#define UPDATE 5
#define EXIT 6

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

int ProductExists(super_market* super, char* productBarcode) {
	for (int i = 0; i < super->number_of_products; i++) {
		if (strcmp(productBarcode, super->product_list[i]->barcode) == 0) {
			return i;
		}
	}

	return -1;
}

bool CanAddProducts(super_market* super, int amount) {
	return super->number_of_products + amount <= MAX_NUM_PRODUCTS;
}

product* GetNewProduct() {
	product* new_product = (product*) malloc(sizeof(product));

	if (new_product == NULL) exit(1);

	new_product->barcode = (char*)malloc(sizeof(char) * (BARCODE_LENGTH + 1));
	new_product->available = 0;
	new_product->price = 0;
	new_product->product_category = (char*)malloc(sizeof(char) * (MAX_CATEGORY_LENGTH + 1));
	new_product->product_name = (char*)malloc(sizeof(char) * (MAX_PRODUCT_NAME_LENGTH + 1));
	new_product->expire_date = (date*)malloc(sizeof(date));

	if (new_product->barcode == NULL || 
		new_product->product_category == NULL || 
		new_product->product_name == NULL || 
		new_product->expire_date == NULL) exit(1);

	return new_product;
}

void FillDate(char* strDate, date* date) {
	date->day = ((strDate[0] - '0') * 10) + (strDate[1] - '0');
	date->month = ((strDate[3] - '0') * 10) + (strDate[4] - '0');
	date->year = ((strDate[6] - '0') * 1000) + ((strDate[7] - '0') * 100) + ((strDate[8] - '0') * 10) + (strDate[9] - '0');
}

void AddProduct(super_market* super) {
	// Guard
	// More than 20 products cant be added
	if (!CanAddProducts(super, 0)) {
		printf("Can't add more products, not enough space!");
		return;
	}
	
	char strDate[DATE_LENGTH + 1];

	product* new_product = GetNewProduct();

	// Get Input, and add
	printf("Please enter product barcode:\t");
	scanf("%s", (new_product->barcode));

	int prod_index = ProductExists(super, new_product->barcode);

	if (prod_index != -1)
	{
		int availableToAdd;
		printf("This product already exist, please enter the number of products to add\t");
		scanf(" %d", &availableToAdd);
		super->product_list[prod_index]->available += availableToAdd;
	}
	else 
	{
		printf("Please enter product name:\t");
		scanf("\n%[^\n]", new_product->product_name);
		printf("Please enter product category:\t");
		scanf("\n%[^\n]", new_product->product_category);
		printf("Please enter number of products to add:\t");
		scanf(" %d", &new_product->available);
		printf("Please enter the price of the product:\t");
		scanf(" %lf", &new_product->price);
		printf("Please enter expiration date of the product[dd/mm/yy]:\t");
		scanf(" %s", &strDate);

		// TODO : Check if can add, check amount and finally allocate if possible

		FillDate(&strDate, new_product->expire_date);

		super->number_of_products++;
		realloc(super->product_list, super->number_of_products * sizeof(product*));

		(super->product_list)[super->number_of_products - 1] = new_product;

		printf("The product %s -barcode:%s, added successfully\n", new_product->product_name, new_product->barcode);
	}
}

void RemoveProduct(super_market* super) {

}

void CheckExpiredProducts(super_market* super) {

}

void PrintProducts(super_market* super) {
	for (int i = 0; i < super->number_of_products; i++) {
		product* prod = super->product_list[i];

		printf("-------------\n");
		printf("Product name: %s\n", prod->product_name);
		printf("Product barcode: %s\n", prod->barcode);
		printf("Product category: %s\n", prod->product_category);
		printf("Product available quantity: %d\n", prod->available);
		printf("Product price: %0.2f\n", prod->price);
		printf("Product expiration date: %d/%d/%d\n", prod->expire_date->day, prod->expire_date->month, prod->expire_date->year);
	}
}

void UpdateProduct(super_market* super) {

}

int GetAction() {
	int res = 0;
	printf("%s", main_interface);

	scanf_s("%d", &res);

	while (res > EXIT || res < ADD) {
		printf("\nInvalid Action, please retype your action:");
		scanf_s(" %d", &res);
	}

	return res;
}

int main() {
	super_market super;
	int action = 0;
	super.product_list = (product**)calloc(0, sizeof(product*));
	super.number_of_products = 0;

	action = GetAction();

	while (action != EXIT) {
		switch(action)
		{
			case ADD:
				AddProduct(&super);
				break;
			case REMOVE:
				RemoveProduct(&super);
				break;
			case CHECK_EXPIRED:
				CheckExpiredProducts(&super);
				break;
			case PRINT:
				PrintProducts(&super);
				break;
			case UPDATE:
				UpdateProduct(&super);
				break;
			default:
				break;
		}

		action = GetAction();
	}

	printf("Exit...");

	return 0;
}