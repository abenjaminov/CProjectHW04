#define MAX_NUM_PRODUCTS 20
#define MAX_PRODUCT_NAME_LENGTH 20
#define MAX_CATEGORY_LENGTH 10
#define DATE_LENGTH 10
#define BARCODE_LENGTH 12

typedef int bool;
#define true 1
#define false 0

// Main Menu Enums
#define ADD 1
#define REMOVE 2
#define CHECK_EXPIRED 3
#define PRINT 4
#define UPDATE 5
#define EXIT 6

// Update Enums
#define UPDATE_PRODUCT_NAME 1
#define UPDATE_PRODUCT_CATEGORY 2
#define UPDATE_PRODUCT_QUANTITY 3
#define UPDATE_PRODUCT_PRICE 4
#define UPDATE_PRODUCT_EXPIRATION 5

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
const char * barcode_already_exist = "This product already exist, please enter the number of products to add: ";
const char * too_much_products = "Can't add more products, not enough space";
const char * adding_product_name = "Please enter product name:";
const char * adding_product_category = "Please enter product category:";
const char * adding_product_number = "Please enter number of products to add:";
const char * adding_product_price = "Please enter the price of the product:";
const char * adding_product_date = "Please enter expire date of the product[dd/mm/yy]:";


//operation 2 constant strings
const char * store_empty = "The store is empty!";
const char * delete_barcode = "Please enter product barcode you want to delete:";
const char * delete_barcode_cant_find = "Couldn't find the product barcode, try again...\n";
const char * delete_barcode_succeed = "The product deleted successfully!";


//operation 3 constant strings
const char * expired_date_check = "What date you want to check[dd/mm/yy]:";
const char * expired_products = "~~~~~~~~~~~~~~~Expired Products~~~~~~~~~~~~~~~\n";
const char * expired_product_name = "Product name: ";
const char * expired_product_barcode = "\nProduct barcode: ";
const char * expired_product_date = "\nProduct expire date: ";


//operation 4 constant strings
const char * print_no_products = "No products in the store!\n";
const char * print_products = "\n----------";
const char * print_product_name = "\nProduct name: ";
const char * print_product_barcode = "\nProduct barcode: ";
const char * print_product_category = "\nProduct category: ";
const char * print_product_number = "\nProduct available quantity: ";
const char * print_product_price = "\nProduct price: ";
const char * print_product_expireDate = "\nProduct expire date: ";
const char * print_total_number = "\nTotal number of products: ";


//operation 5 constant strings
const char * update_barcode = "Please enter product barcode you want to update:";
const char * update_barcode_notFound = "Couldn't find the product barcode, try again...\n";
const char * update_interface_string = ("What do you want to update?\n"\
	"        1. Product name\n"\
	"        2. Product category\n"\
	"        3. Product quantity\n"\
	"        4. Product price\n"\
	"        5. Product expire date\n"\
	"Please choose operation [1-5]:");
const char * update_product_name = "Please enter new product name:";
const char * update_product_category = "Please enter new product category:";
const char * update_product_number = "Please enter new product quantity:";
const char * update_product_price = "Please enter new product price:";
const char * update_product_date = "Please enter new product expire date[dd/mm/yy]:";


//operation 6 constant strings
const char * exitProgram = "\nexit...";

// ---------- TYPEDEFS -----------------

typedef struct date { int year; int month; int day; } date;
typedef struct product { char * product_name; char * product_category; char * barcode; int available; double price; date * expire_date; } product;
typedef struct super_market { product ** product_list; int number_of_products; } super_market;


int GetProductIndex(super_market* super, char* productBarcode) {
	/*
	Inputs: 
			:super: - pointer to the struct that holds supermarket data.
			:productBarcode: - pointer to a barcode string.
	Return: 
			-1 if the product is not found, 
			otherwise, it's index in the list.

	Functionality: Find if a product is already in the supermarket, and get it's index.
				   Used everywhere pretty much.
	*/

	for (int i = 0; i < super->number_of_products; i++) {
		if (strcmp(productBarcode, super->product_list[i]->barcode) == 0) {
			return i;
		}
	}
	return -1;
}


bool CanAddProducts(super_market* super, int amount) {
	/*
	Inputs: 
			:super:  - pointer to the struct that holds supermarket data.
			:amount: - how many products to add.
	Return: 
			1 if we can, 0 otherwise.

	Functionality: Check if we can add :amount: products to the supermarket.
	*/
	return super->number_of_products + amount <= MAX_NUM_PRODUCTS;
}


date* GetNewDate() {
	date* new_date = (date*)malloc(sizeof(date));

	if (new_date == NULL) exit(1);

	return new_date;
}


product* GetNewProduct() {
	/*
	Inputs: None.
	Return: A pointer to a block in memory, allocated for a product.
	Functionality: Allocate memory for the product we are about to add, used as a constructor.
	*/

	product* new_product = (product*) malloc(sizeof(product));

	if (new_product == NULL) exit(1); //check if we failed to allocate size for a product

	new_product->barcode = (char*)malloc(sizeof(char) * (BARCODE_LENGTH + 1));
	new_product->available = 0;
	new_product->price = 0;
	new_product->product_category = (char*)malloc(sizeof(char) * (MAX_CATEGORY_LENGTH + 1));
	new_product->product_name = (char*)malloc(sizeof(char) * (MAX_PRODUCT_NAME_LENGTH + 1));
	new_product->expire_date = GetNewDate();

	// Check if any allocations failed
	if (new_product->barcode == NULL || 
		new_product->product_category == NULL || 
		new_product->product_name == NULL) exit(1);

	return new_product;
}


void FillDate(char* strDate, date* date) {
	/*
	Inputs: 
			:strDate: - a string in dd/mm/yy format to represent a date.
			:date: - pointer to the struct date (of a product).
	Return: None.
	Functionality: Populate the expiration date of a product easily.
	*/

	date->day = ((strDate[0] - '0') * 10) + (strDate[1] - '0');
	date->month = ((strDate[3] - '0') * 10) + (strDate[4] - '0');
	date->year = ((strDate[6] - '0') * 10) + ((strDate[7] - '0') * 1);
}


void AddProduct(super_market* super) {
	/*
	Inputs: :super: - pointer to the struct that holds supermarket data.
	Return: None.
	Functionality: Add another item to the store as a product struct, populate all fields.
	*/

	// Guard Expression : More than 20 products cant be added
	if (!CanAddProducts(super, 0)) {
		printf(too_much_products);
		return;
	}
	
	char temp_barcode[BARCODE_LENGTH+1];
	char temp_name[MAX_PRODUCT_NAME_LENGTH+1];
	char temp_category[MAX_CATEGORY_LENGTH+1];
	char strDate[DATE_LENGTH + 1];

	product* new_product = GetNewProduct();

	printf(adding_product_barcode);
	scanf("%s", &temp_barcode);
	strcpy(new_product->barcode, temp_barcode);

	int existing_product_index = GetProductIndex(super, new_product->barcode);

	if (existing_product_index != -1)
	{
		int availableToAdd;
		printf(barcode_already_exist);
		scanf(" %d", &availableToAdd);
		super->product_list[existing_product_index]->available += availableToAdd;
		printf("Additional %d products of %s added\n", availableToAdd, super->product_list[existing_product_index]->product_name);
	}
	else {
		printf(adding_product_name);
		scanf("\n%[^\n]", &temp_name);
		strcpy(new_product->product_name, temp_name);

		printf(adding_product_category);
		scanf("\n%[^\n]", &temp_category);
		strcpy(new_product->product_category, temp_category);

		printf(adding_product_number);
		scanf(" %d", &new_product->available);
		printf(adding_product_price);
		scanf(" %lf", &new_product->price);
		printf(adding_product_date);
		scanf(" %s", &strDate);

		FillDate(strDate, new_product->expire_date);

		super->number_of_products++;
		super->product_list = (product**)realloc(super->product_list, super->number_of_products * sizeof(product*));

		(super->product_list)[super->number_of_products - 1] = new_product;
		printf("The product %s -barcode:%s ,added successfully\n", new_product->product_name, new_product->barcode);
	}
}


void _freeProduct(product* prod){
	/*
	Inputs: :prod: - pointer to the product we want to free.
	Return: None.
	Functionality: Free dynamically allocated memory of a product.
	*/

	free(prod->barcode);
	free(prod->product_name);
	free(prod->product_category);
	free(prod->expire_date);
	free(prod);
}


void RemoveProduct(super_market* super) {
	/*
	Inputs: :super: - pointer to the struct that holds supermarket data.
	Return: None.
	Functionality: Remove a product from the supermarket, freeing all it's memory.
	*/

	char barcode[BARCODE_LENGTH+1];
	int prod_idx = -1;

	// Check if the store is empty
	if (super->number_of_products == 0) {printf(store_empty); printf("\n");}
	else {
			while (prod_idx == -1){
			printf(delete_barcode);
			scanf("%s", barcode);

			// Get the index of the product that we want to remove
			prod_idx = GetProductIndex(super, barcode);
			if (prod_idx == -1){
				// No such product
				printf(delete_barcode_cant_find);
			}

		}
		
		_freeProduct(super->product_list[prod_idx]);

		// roll back indices to fill the gap
		for (int i = prod_idx + 1; i <= super->number_of_products - 1; i++){
			super->product_list[i-1] = super->product_list[i];
		}

		super->number_of_products--; //decrement amount of products in the supermarket.

		// Re-allocate space for the newly shrunk product list
		super->product_list = realloc(super->product_list, sizeof(product*) * super->number_of_products);
		printf(delete_barcode_succeed);
		printf("\n");
	}
}


bool _isExpired(date* inDate, date* prod_date){
	/*
	Inputs: 
			:inDate:    - date string in the required format.
			:prod_date: - pointed to the date field in the product struct.
	Return: 1 if the product is expired, 0 if it is not.
	Functionality: Check if :inDate: > :prod_date:.
	*/

	if (inDate->year > prod_date->year) return true;
	if ((inDate->month > prod_date->month) && (inDate->year == prod_date->year)) return true;
	if ((inDate->day > prod_date->day) && (inDate->month == prod_date->month)) return true;
	return false;
}


void _printExpired(super_market* super, int index){
	/*
	Inputs: 
			:super: - pointer to the struct that holds supermarket data.
			:index: - number of the product in the products array which we want to print
					  the values of.
	Return: None.
	Functionality: Print in the required format.
	*/
	printf(expired_product_name);
	printf("%s", super->product_list[index]->product_name);
	printf(expired_product_barcode);
	printf("%s", super->product_list[index]->barcode);
	printf(expired_product_date);
	printf("%d/%d/%d\n", super->product_list[index]->expire_date->day,
					     super->product_list[index]->expire_date->month,
					     super->product_list[index]->expire_date->year);
}


void CheckExpiredProducts(super_market* super) {
	/*
	Inputs: :super: - pointer to the struct that holds supermarket data.
	Return: None.
	Functionality: Check which products are expired, call the _printExpired function.
	*/

	char date_to_check[DATE_LENGTH+1];
	printf(expired_date_check);
	scanf("%s", date_to_check);

	date* expired_date = GetNewDate();

	FillDate(date_to_check, expired_date);
	printf(expired_products);
	for (int counter=0; counter < super->number_of_products; counter++){
		if (_isExpired(expired_date, super->product_list[counter]->expire_date)){
			_printExpired(super, counter);
		}
	}
}


void PrintProducts(super_market* super) {
	/*
	Inputs: :super: - pointer to the struct that holds supermarket data.
	Return: None.
	Functionality: Print all fields of all products in the store.
	*/
	if (super->number_of_products == 0) printf(print_no_products);
	else{
		for (int i = 0; i < super->number_of_products; i++) {
			product* prod = super->product_list[i];
			printf("~~~~~~~~~~~~~~~All Products~~~~~~~~~~~~~~~\n");
			printf("-------------\n");
			printf("Product name: %s\n", prod->product_name);
			printf("Product barcode: %s\n", prod->barcode);
			printf("Product category: %s\n", prod->product_category);
			printf("Product available quantity: %d\n", prod->available);
			printf("Product price: %g\n", prod->price);
			printf("Product expiration date: %d/%d/%d\n", prod->expire_date->day, prod->expire_date->month, prod->expire_date->year);
		}
	}
}

void UpdateProductExpirationDate(product* product)
{
	printf(update_product_date);
	char temp_date[DATE_LENGTH];
	scanf(" %s", &temp_date);
	FillDate(temp_date, product->expire_date);
}

void UpdateProductPrice(product* product)
{
	printf(update_product_price);
	scanf(" %lf", &(product->price));
}

void UpdateProductQuantity(product* product)
{
	printf(update_product_number);
	scanf(" %d", &(product->available));
}

void UpdateProductCategory(product* product)
{
	printf(update_product_category);
	char temp_category[MAX_CATEGORY_LENGTH];
	scanf("\n%[^\n]", &temp_category);

	realloc(product->product_category, strlen(temp_category));
	strcpy(product->product_category, temp_category);
}

void UpdateProductName(product* product)
{
	printf(update_product_name);
	char temp_name[MAX_PRODUCT_NAME_LENGTH];
	scanf("\n%[^\n]", &temp_name);

	realloc(product->product_name, strlen(temp_name));
	strcpy(product->product_name, temp_name);
}

void _updateField(super_market* super, int idx_to_update, int field) {
	/*
	Inputs:
			:super: - pointer to the struct that holds supermarket data. (super_market*)
			:idx_to_update: - index of the product in the store. (int)
			:field: - which field to update, based on popup message. (int)
	Return: None.
	Functionality: Function that updates a specific field in an existing product,
				   based on user selection.
	*/
	switch (field)
	{
	case UPDATE_PRODUCT_NAME:
		UpdateProductName(super->product_list[idx_to_update]);
		break;

	case UPDATE_PRODUCT_CATEGORY:
		UpdateProductCategory(super->product_list[idx_to_update]);
		break;

	case UPDATE_PRODUCT_QUANTITY:
		UpdateProductQuantity(super->product_list[idx_to_update]);
		break;
	case UPDATE_PRODUCT_PRICE:
		UpdateProductPrice(super->product_list[idx_to_update]);
		break;

	case UPDATE_PRODUCT_EXPIRATION:
		UpdateProductExpirationDate(super->product_list[idx_to_update]);
		break;
	}
}


void UpdateProduct(super_market* super) {
	/*
	Inputs: :super: - pointer to the struct that holds supermarket data.
	Return: None.
	Functionality: Function that updates a field in an existing product.
	*/
	char barcode[BARCODE_LENGTH+1] = {'\0'};
	int idx_to_update = -1, selection = 0;

	// Check if the supermarket is empty
	if (super->number_of_products == 0){
		printf("No products in the store!\n");
	}
	else{
		printf(update_barcode);
		scanf("%s", barcode);

		// Ask for ther user's barcode
		while (idx_to_update == -1){
			printf(update_barcode_notFound);

			idx_to_update = GetProductIndex(super, barcode);
		}

		// update product at :idx_to_update: with the new details:
		printf(update_interface_string);
		scanf("%d", &selection);
		_updateField(super, idx_to_update, selection);
	}
}


void CleanupAndExit(super_market* super){
	/*
	Inputs: :super: - pointer to the struct that holds supermarket data.
	Return: None.
	Functionality: Iter
	ates over the pointer array and clears the allocated memory.
	*/
	for (int idx=0; idx < super->number_of_products; idx++){
		_freeProduct(super->product_list[idx]);
	}
	free (super->product_list);
	free (super);
	printf(exitProgram);
}


int GetAction() {
	/*
	Inputs: None.
	Return: The user's selection as a main menu navigation number (int).
	Functionality: Allow users to traverse the main menu.
	*/

	int res = 0;
	printf("%s", main_interface);

	scanf("%d", &res);

	while (res > EXIT || res < ADD) {
		printf("\nInvalid Action, please retype your action:");
		scanf(" %d", &res);
	}
	return res;
}


void UserSelect(int enumerator, super_market* super){
	switch(enumerator)
		{
		case ADD:
			AddProduct(super);
			break;
		case REMOVE:
			RemoveProduct(super);
			break;
		case CHECK_EXPIRED:
			CheckExpiredProducts(super);
			break;
		case PRINT:
			PrintProducts(super);
			break;
		case UPDATE:
			UpdateProduct(super);
			break;
		default:
			break;
	}
}

super_market* GetNewSupermarket() {
	super_market* super = (super_market*)malloc(sizeof(super_market));
	int action = 0;
	super->product_list = (product**)calloc(0, sizeof(product*));
	super->number_of_products = 0;

	return super;
}

int main() {
	super_market* super = GetNewSupermarket();
	int action = 0;

	action = GetAction();  // Get user selection

	while (action != EXIT) {
		UserSelect(action, super);
		action = GetAction();
	}

	// Exit was selected, clean up and exit.
	CleanupAndExit(super);
	return 0;
}
