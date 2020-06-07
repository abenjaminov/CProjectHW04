#define MAX_NUM_PRODUCTS 20
#define MAX_PRODUCT_NAME_LENGTH 20
#define MAX_CATEGORY_LENGTH 10
#define BARCODE_LENGTH 12

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct date
{
	int year;
	int month;
	int day;
} date;

typedef struct product
{
	char* product_name;
	char* product_category;
	char* barcode;
	int available;
	double price;
	date* expire_date;
} product;

typedef struct super_market
{
	product** product_list;
	int number_of_products;
} super_market;

const char* main_interface = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"\
"Welcome to CORONA market!\n"\
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"\
"Manage market menu:\n"\
"	1. Add product\n"\
"	2. Remove product\n"\
"	3. Check which products are expired\n"\
"	4. Print all the products\n"\
"	5. Update product\n"\
"	6. EXIT SYSTEM\n"\
"Please choose operation [1-6]:";

//operation 1 constant strings

const char* adding_product_barcode = "Please enter product barcode:";
const char* barcode_already_exist = "This product already exist, please enter the number of products to add:";
const char* too_much_products = "Can't add more products, not enough space";
const char* adding_product_name = "Please enter product name:";
const char* adding_product_category = "Please enter product category:";
const char* adding_product_number = "Please enter number of products to add:";
const char* adding_product_price = "Please enter the price of the product:";
const char* adding_product_date = "Please enter expiration date of the product[dd/mm/yy]:";

//operation 2 constant strings
const char* store_empty = "The store is empty!";
const char* delete_barcode = "Please enter product barcode you want to delete:";
const char* delete_barcode_cant_find = "Couldn't find the product barcode, try again...";
const char* delete_barcode_succeed = "The product deleted successfully!";


//operation 3 constant strings
const char* expired_date_check = "What date you want to check[dd/mm/yy]:";
const char* expired_products = "~~~~~~~~~~~~~~~Expired Products~~~~~~~~~~~~~~~\n";
const char* expired_product_name = "Product name: ";
const char* expired_product_barcode = "Product barcode: ";
const char* expired_product_date = "Product expiration date: ";


//operation 4 constant strings
const char* print_products_head = "~~~~~~~~~~~~~~~All Products~~~~~~~~~~~~~~~\n";
const char* print_no_products = "No products in the store!\n";
const char* print_products = "----------";
const char* print_product_name = "Product name: ";
const char* print_product_barcode = "Product barcode: ";
const char* print_product_category = "Product category: ";
const char* print_product_number = "Product available quantity: ";
const char* print_product_price = "Product price: ";
const char* print_product_expireDate = "Product expiration date: ";
const char* print_total_number = "Total number of products: ";

//operation 5 constant strings
const char* update_barcode = "Please enter product barcode you want to update:";
const char* update_barcode_notFound = "Couldn't find the product barcode, try again...";
const char* update_interface_string = ("What do you want to update?\n"\
	"	1. Product name\n"\
	"	2. Product category\n"\
	"	3. Product quantity\n"\
	"	4. Product price\n"\
	"	5. Product expiration date\n"\
	"Please choose operation [1-5]:");
const char* update_product_name = "Please enter new product name:";
const char* update_product_category = "Please enter new product category:";
const char* update_product_number = "Please enter new product quantity:";
const char* update_product_price = "Please enter new product price:";
const char* update_product_date = "Please enter new product expiration date[dd/mm/yy]:";

//operation 6 constant strings
const char* exitProgram = "exit...";


int is_empty(super_market super) {               //Input - Super_market struct - super
	if (super.number_of_products == 0) {         //Return - Boolean - 1 if super is empty (no products), 0 if not
		return 1;                                //Functionality - Compares number of products in super with 0.
	}
	return 0;
}

int is_full(super_market* super) {                                      //Input - Super_market struct - super
	if (super->number_of_products == MAX_NUM_PRODUCTS) {                //Return - Boolean - 1 if super is full, 0 if not
		return 1;                                                      //Functionality - compares number of products in super with MAX_NUM_PRODUCTS
	}
	return 0;
}

int bar_exists(char new_barcode[], super_market* super) {               //Input - Super_market struct - super, Barcode string
																//Return - int value - MAX_NUM_PRODUCTS or less
	for (int i = 0; i < super->number_of_products; i++) {              //Functionality - if there's a product with super, with Barcode...
		if (!strcmp(new_barcode, super->product_list[i]))              //... return its index in product list, else, returns MAX_NUM_PRODUCTS
			return i;
	}
	return MAX_NUM_PRODUCTS;
}

void print_expired_help(product* product) {

	printf("%s ", expired_product_name);
	printf("%s\n", ((*product).product_name));
	printf("%s ", expired_product_barcode);
	printf("%s\n", ((*product).barcode));
	printf("%s ", expired_product_date);
	printf("%d//%d//%d\n", ((*product).expire_date->day), product->expire_date->month, product->expire_date->year);
}

int current_capacity(super_market super) {
	int count = 0, i;
	for (i = 0; i < MAX_NUM_PRODUCTS; i++)
		if (super.product_list[i] != NULL) {
			count += 1;
		}
	return count;
}

int expired(date today, date temp) {

	if (today.year > temp.year)
		return 1;
	if (today.year < temp.year)
		return 0;
	if (today.month > temp.month)
		return 1;
	if (today.month < temp.month)
		return 0;
	if (today.day > temp.day)
		return 1;
	if (today.day <= temp.day)
		return 0;
}

void add_product(super_market* super) {

	char new_barcode[BARCODE_LENGTH + 1];
	product* new_product = NULL;
	int addition = 0, i;

	printf("%s\n", adding_product_barcode);
	scanf("%s[^\n]", new_barcode);

	if ((i = bar_exists(new_barcode, super) != MAX_NUM_PRODUCTS)) {
		printf("%s\n", barcode_already_exist);
		scanf("%d\n", addition);
		super->product_list[i]->available += addition;
		printf("Additional %d products of %s added", super.product_list[i]->available, super.product_list[i]->product_name);
	}
	if (is_full(super)) {
		printf("%s\n", too_much_products);
	}
	new_product = (product*)malloc(sizeof(product));
	if (new_product == NULL) {
		printf("Memory allocation failed!");
		return;
	}

	new_product->barcode = new_barcode;
	printf("%s ", adding_product_name);
	fgets(new_product->product_name, MAX_PRODUCT_NAME_LENGTH, stdin);
	printf("%s", adding_product_category);
	fgets(new_product->product_category, MAX_CATEGORY_LENGTH, stdin);
	printf("%s ", adding_product_barcode);
	scanf("%d", &new_product->available);
	printf("%s ", adding_product_price);
	scanf("%lf", &new_product->price);
	printf("%s ", adding_product_date);
	scanf("%d/%d/%d", &new_product->expire_date->day, new_product->expire_date->month, new_product->expire_date->year);

	super->number_of_products += 1;
	super->product_list = (product**)realloc(super->product_list, sizeof(product*) * super->number_of_products);

	super->product_list[super->number_of_products - 1] = new_product;
	
}

void print_expired(super_market super) {
	date today;
	int day = 0, month = 0, year = 0;
	printf("%s\n", *expired_date_check);
	scanf("%d/%d/%d", day, month, year);
	today.day = day;
	today.month = month;
	today.year = year;
	printf("%s\n", *expired_products);
	for (int i = 0; i < super.number_of_products; i++) {

		if (expired(today, *super.product_list[i]->expire_date))
			print_expired_help(super.product_list[i]);
	}
}

void remove_product(super_market super) {
	int i, b = 0;
	char* bar_to_remove;

	if (is_empty(super))
		printf("%s ", *store_empty);
	return;

	while (b = 0) {

		printf("%s ", *delete_barcode);
		fgets(bar_to_remove, BARCODE_LENGTH, stdin);
		if (i = bar_exists(bar_to_remove, super) != MAX_NUM_PRODUCTS) {
			free(super.product_list[i]);
			super.number_of_products -= 1;
			b = 1;
			printf("%s ", *delete_barcode_succeed);
		}
		else {
			printf("%s ", *delete_barcode_cant_find);
		}
	}
}

void print_all_the_products(super_market super)
{
	int i;
	if (is_empty(super) == 1)
		printf("%c\n", print_no_products);
	else
	{
		printf("%c\n", print_products_head);
		for (i = 0; i < super.number_of_products; i++)
		{
			printf("%c\n", print_products);
			printf("%c", print_product_name);
			printf("%s\n", super.product_list[i]->product_name);
			printf("%c", print_product_barcode);
			printf("%s\n", super.product_list[i]->barcode);
			printf("%c", print_product_category);
			printf("%s\n", super.product_list[i]->product_category);
			printf("%c", print_product_number);
			printf("%n\n", super.product_list[i]->available);
			printf("%c", print_product_price);
			printf("%s\n", super.product_list[i]->price);
			printf("%c", print_product_expireDate);
			printf("%d\n", super.product_list[i]->expire_date);
		}
		printf("%c", print_total_number);
		printf("%s\n", super.number_of_products);
	}
}

void update(super_market super)
{
	char* new_bar = NULL;
	int b = 0;
	int c = 0;
	if (is_empty(super) == 1) {
		printf("No products in the store!\n");
	}
	else
	{
		while (b == 1)
		{
			printf("%s ", *update_barcode);
			fgets(new_bar, BARCODE_LENGTH, stdin);
			int i = bar_exists(new_bar, super);
			if (i != MAX_NUM_PRODUCTS)
			{
				printf("%s", update_interface_string);
				scanf("%d", &c);
				if (c == 1)
				{
					char* name = NULL;
					printf("%s", update_product_name);
					scanf("%s[^\n]", name);
					super.product_list[i]->product_name = name;
				}
				if (c == 2)
				{
					char category[MAX_CATEGORY_LENGTH];
					printf("%s", update_product_category);
					scanf("%s", &category);
					super.product_list[i]->product_category = category;
				}
				if (c == 3)
				{
					int num = 0;
					printf("%s", update_product_number);
					scanf("%d", &num);
					super.product_list[i]->available = num;
				}

				if (c == 4)
				{
					double price = 0;
					printf("%s", update_product_price);
					scanf("%lf", &price);
					super.product_list[i]->price = price;
				}

				if (c == 5)
				{
					int day = 0, month = 0, year = 0;
					date ex_d;
					printf("%s", update_product_date);
					scanf("%d %d %d", day, month, year);
					ex_d.day = day;
					ex_d.month = month;
					ex_d.year = year;
					super.product_list[i]->expire_date->day = ex_d.day;
					super.product_list[i]->expire_date->month = ex_d.month;
					super.product_list[i]->expire_date->year = ex_d.year;
				}
				b = 1;
			}
		}
	}
}

void exit_super(super_market super) {
	int i;
	for (i = 0; i < super.number_of_products; i++)
		free(super.product_list[i]);
	printf("%s", *exitProgram);
}

void choice(super_market* super) {
	int b = 0, c = 0;

	while (b == 0) {
		printf("%s ", main_interface);
		scanf("%d", &c);
		switch (c) {
		case 1:
			add_product(super);
			break;
		case 2:
			remove_product(super);
			break;
		case 3:
			print_expired(super);
			break;
		case 4:
			print_all_the_products(super);
			break;
		case 5:
			update(super);
			break;
		case 6:
			exit_super(super);
			b = 1;
			break;
		}
	}
}

int main() {
	super_market* super = (super_market*)malloc(sizeof(super_market));
	super->number_of_products = 0;
	super->product_list = (product**)malloc(super->product_list, sizeof(product*));
	choice(super);
	return 0;
}

