/***************************************************************************************************  
This is to certify that this project is my own work, based on my personal efforts in studying and 
applying the concepts learned.  I have constructed the functions and their respective algorithms 
and corresponding code by myself.  The program was run, tested, and debugged by my own 
efforts.  I further certify that I have not  copied in part or  whole or otherwise plagiarized  the 
work of other students and/or persons. 
                                                        <Tan, Arvin Teri Limso>, DLSU ID# <12116304>  
***************************************************************************************************/

/*   
Description: A pizza vending machine system that takes orders and serves the user with their pizza needs
Programmed by: Arvin Teri L Tan S21B
Last modified: 01/10/2022
Version: 3
[Acknowledgements: 
https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c
https://stackoverflow.com/questions/12824703/array-format-for-define-c-preprocessor
https://stackoverflow.com/questions/5485324/why-it-gives-wrong-array-size
https://en.wikipedia.org/wiki/Buffer_overflow
https://stackoverflow.com/questions/6102948/why-does-modulus-division-only-work-with-integers
https://www.ibm.com/docs/en/zos/2.3.0?topic=functions-fmod-fmodf-fmodl-calculate-floating-point-remainder
https://stackoverflow.com/questions/33378000/passing-file-pointer-to-a-function
https://www.geeksforgeeks.org/basics-file-handling-c/
https://www.programiz.com/c-programming/c-file-input-output
]
*/

#include <stdio.h>
#include <ctype.h>
#include <math.h>
/* data for crust */
#define cAvailableCrust (char[]){'a','b'}
#define nAvailableCrustSize sizeof(cAvailableCrust)/sizeof(cAvailableCrust[0])
/* data for sizes */
#define cAvailableSizes (char[]){'s','m','l'}
#define fSizesPrize (float[]){100.00, 175.00, 225.00}
#define fToppingMultiplier (float[]){1.00, 1.5, 1.75}
#define nAvailableSizeLength sizeof(cAvailableSizes)/sizeof(cAvailableSizes[0])
/* data for topppings */
#define cAvailableToppings (char[]){'h','p','s','c','o'}
#define cToppingsPrize (float[]){10.00, 6.00, 15.00, 12.00, 10.00}
#define nAvailToppingsSize sizeof(cAvailableToppings)/sizeof(cAvailableToppings[0])
/* data for cheeses */
#define cAvailableCheese (char[]){'m','g','f','p'}
#define nAvailCheeseSize sizeof(cAvailableCheese)/sizeof(cAvailableCheese[0])
/* data for stuffings */
#define cAvailableStuffings (char[]){'c','s','b'}
#define fStuffingsPrize (float[]){30.00, 25.00, 35.00}
#define nStuffingSize sizeof(cAvailableStuffings)/sizeof(cAvailableStuffings[0])
/* data for fiat */
#define cAvailableCashOptions (char[]){'a','b','c','d','e','f','g','h','i','j','k','l'}
#define fAvailableCash (float[]){1000.00, 500.00, 100.00, 50.00, 20.00, 10.00, 5.00, 1.00, 0.25, 0.10, 0.05, 0.01}
#define nAvailableCashSize sizeof(fAvailableCash)/sizeof(fAvailableCash[0])
/*text for menu */
#define crustText (char[][15]) {"Thin Crust","Thick Crust"}
#define sizeText (char[][10]) {"Small","Meduim","Large"}
#define toppingText (char[][10]) {"Ham","Pineapple","Sausage","Cheese","Olives"}
#define cheeseText (char[][15]) {"Mozarella","Gorgonzola","Fontina","Parmesan"}
#define stuffingText (char[][10]) {"Cheese","Spam","Both"}

/*This function clears the input stream to avoid causing an infinite loop*/
void 
clear_Buffer ()
{
    int userInput;
    /*clear input until a newline and if it is the end of a file*/
    while
		( (userInput = fgetc (stdin)) != EOF && userInput != '\n');
}

/* 
This function performs a linear search to get the index of the character being searched
Precondition: the character being searched is inside the array
@param cSearched - option that is the target of the search
@param cCharArray - array that holds the available data which is going to be searched
@param nArraySize - size of the array to be searched
returns the position of the searched item
*/
int
get_Index (char cSearched, 
		   char* cCharArray, 
		   int nArraySize)
{
	int index;
	
	for (index = 0; index < nArraySize; index++){
		
		if (cSearched == cCharArray[index])
				return index;
	}
	/*placed to avoid warning on compilation*/
	return index;
}

/*This function prints a line for repetitive interface use*/
void 
print_Line ()
{
	int i;
	
	for (i = 0;i < 40; i++) 
		printf ("%c",'-'); 
	printf ("\n");
}

/* 
This function prints available items for each step of the program
Precondition: machine is not under maintenance
@param nMenu - current step the machine is operating
*/
void
print_Menu (int nMenu)
{	
	int i;
	
	switch (nMenu){
		/*prints welcome message*/
		case 0: 
			print_Line ();
			printf ("|%5c%28s%5c|\n",'\0',"Welcome to Jeff's pizzeria",'\0');
			print_Line ();
			break;
			
		/*loop through corresponding str array to print menu for each step*/
		case 1: 
			printf ("\n");
			print_Line ();
			printf ("|%5c%s%6c|\n",'\0',"Pick the crust of the pizza",'\0'); 
			print_Line ();
			for (i = 0; i <  nAvailableCrustSize; i++)
				printf ("|%5c(%d) %-15s%14c|\n",'\0',i+1,crustText[i],'\0');	
			print_Line ();
			printf ("\n");
			break;
			
		case 2: 
			printf ("\n");
			print_Line ();
			printf ("|  %s |\n","Pick the size of the pizza you want");
			print_Line ();
			for (i = 0; i <  nAvailableSizeLength; i++)
				printf ("|  %c or %c %-4c%-9s%c  Php %4.2f   |\n",
					   toupper (cAvailableSizes[i]),
					   cAvailableSizes[i],
					   '|',
					   sizeText[i],
					   '|',
					   fSizesPrize[i]);	
			print_Line ();
			printf ("|   %c or %-4c%-9s%7c\n",'X','x',"To Cancel your order" ,'|');
			print_Line ();
			printf ("\n");
			break;
			
		case 3:
			printf ("\n");
			print_Line ();
			printf ("|   Select atleast one pizza topping   |\n");
			print_Line ();
			printf ("| Input Code |   Toppings  |    Price  |\n");
			print_Line ();
			for (i = 0; i <  nAvailToppingsSize; i++)
				printf ("|  %c or %c%5c %-10s%3c Php %-5.2f |\n",
					   toupper (cAvailableToppings[i]),
					   cAvailableToppings[i],
					   '|',
					   toppingText[i],
					   '|',
					   cToppingsPrize[i]);
			print_Line ();
			printf ("|   %c or %-4c%-9s%7c\n",'N','n',"Proceed to next step",'|');
			printf ("|   %c or %-4c%-9s%7c\n",'X','x',"To Cancel your order",'|');
			print_Line ();
			printf ("\n");
			break;
			
		case 4:
			printf ("\n");
			print_Line ();
			printf ("|    Pick the cheese of the pizza      |\n");
			print_Line ();
			for (i = 0; i <  nAvailCheeseSize; i++)
				printf ("|  %c or %c%7c   %-10s%11c\n",
					   toupper (cAvailableCheese[i]),
					   cAvailableCheese[i],
					   '|',
					   cheeseText[i],
					   '|');
			print_Line ();
			printf ("|   %c or %-4c%-9s%7c\n",'X','x',"To Cancel your order" ,'|');
			print_Line ();
			printf ("\n");
			break;
			
		case 5:
			printf ("\n");
			print_Line ();
			printf ("| Input Code |   Stuffing  |    Price  |\n");
			print_Line ();
			for (i = 0; i <  nStuffingSize; i++)
				printf ("|  %c or %c%5c %-10s%3c Php %-5.2f |\n",
				toupper (cAvailableStuffings[i]),
				cAvailableStuffings[i],
				'|',
				stuffingText[i],
				'|',
				fStuffingsPrize[i]);	
			print_Line ();
			printf ("|   %c or %-4c%-9s%7c\n",'N','n',"Proceed to next step",'|');
			printf ("|   %c or %-4c%-9s%7c\n",'X','x',"To Cancel your order",'|');
			print_Line ();
			printf ("\n");
			break;
			
		case 6:
			printf ("\n");
			print_Line ();
			printf ("| Input Code    |  	Peso value     |\n");
			print_Line ();
			for (i = 0; i <   nAvailableCashSize; i++) 
				/*check if digit has 1 or 2 digits for spacing*/
				if (i < 9)
					printf ("|%5c(%d)%8c%15.2f%7c|\n",'\0',i+1,'|',fAvailableCash[i],'\0');
				else
					printf ("|%5c(%2d)%7c%15.2f%7c|\n",'\0',i+1 ,'|',fAvailableCash[i],'\0');
			print_Line ();
			printf ("|     (%d)   %-14s%8c\n",0,"To Cancel your order",'|');
			print_Line ();
			printf ("\n");
			break;
	}
}

/*This function displays a warning to user because chosen is invalid*/
void 
invalid_Message ()
{
	printf ("\n");
	print_Line ();
	printf ("|     Please input a valid option !    |\n");
	print_Line ();
}

/* 
This function checks if the user input is available
Precondition: the user provided an option to be checked
@param cChosen - option that a user chose
@param cAvailableValues - array that stores the available items 
@param nArrSize - size of the array to be searched
@return either 1 or 0 to denote if the option the user chose is available
*/
int
check_Availability (char cChosen, 
					char* cAvailableValues, 
					int nArrSize)
{
	int index;
	
	/*perform a linear search to check if chosen value is valid*/
	for (index = 0; index < nArrSize; index++){
		
		if (cChosen == cAvailableValues[index])
			return 1;
	}
	return 0;
}

/* 
This function asks for the type of crust the user wants
Precondition: the user provided an integer of his choice for the crust
@return a character that denotes the crust the user chose
*/
char
choose_Crust ()
{
	int nChoice,
		nValidInput = 0;

	char cChoice;
	
	print_Menu (0);
	/*keep scanning if invalid*/
	while (nValidInput == 0){
		print_Menu (1);
		printf ("Input crust: ");
	
		scanf ("%d",&nChoice);
		clear_Buffer ();
		/* valid options*/
		if (nChoice == 1 || nChoice == 2 || nChoice == 80808)
			nValidInput = 1; 
		else
			invalid_Message ();
	}
	/*convert so all arrays being check is char type*/
	if (nChoice == 80808)
		cChoice = 'c'; /*c for close machine*/
	else
		cChoice = nChoice + 96; /*convert lowercase letter*/
	return cChoice;
}

/* 
This function asks for the size of the pizza the user wants
Precondition: user provided a character for the chosen crust
@param fTotalPrice - address that stores the total price of the order
@return a character that denotes the size the user chose
*/
char 
choose_Size (float* fTotalPrice)
{

	char cSizeChoice;
	int nValidInput = 0,
		nValidSize = 0,
		nIndex;
	/*keep scanning if invalid*/
	while (nValidInput == 0){
		print_Menu (2);
		printf ("Input size: ");
		
		scanf ("%c",&cSizeChoice);
		clear_Buffer ();
		/*convert char to lowercase to reduce uppercase condition*/
		cSizeChoice = tolower (cSizeChoice);
		
		nValidSize = check_Availability (cSizeChoice, 
										 cAvailableSizes, 
										 nAvailableSizeLength);
		/*user cancels order*/
		if (cSizeChoice == 'x')
			nValidInput = 1;
		/*valid size chosen*/
		else if (nValidSize){
			/*get the price of item and add to total*/
			nIndex = get_Index (cSizeChoice, 
							    cAvailableSizes, 
							    nAvailableSizeLength);				   
			*fTotalPrice += fSizesPrize[nIndex];
			nValidInput = 1;
		}
		else
			invalid_Message ();		
	}
	return cSizeChoice;
}

/* 
This function will take the order of what toppings does the user want
Precondition: the user provided a character for his choice for the topping
@param nToppingQuantity - array that stores the quantity of a topping a user chose
@param fTotalPrice - an address that stores the total price of the order
@param cSize - a character that denotes the size the user picked
@return a character that denotes if a user cancels and order or move onto the next step
*/
char
choose_Toppings (int* nToppingQuantity,
				 float* fTotalPrice,
				 char* cSize)
{
	char cChosenTopping;
	
	int nValidInput = 0,
		nValidTopping = 0,
		nIndex = 0,
		nMultiplier = 0,
		nToppingCount = 0;
	/*keep scanning if invalid*/
	while (nValidInput == 0){
		print_Menu (3);
		
		printf ("Input Topping: ");
		scanf ("%c",&cChosenTopping);
		clear_Buffer ();
		/*convert char to lowercase to reduce uppercase condition*/
		cChosenTopping = tolower (cChosenTopping);
		/*check if the chosen topping is valid*/
		nValidTopping = check_Availability (cChosenTopping,
										    cAvailableToppings,
										    nAvailToppingsSize); 
		/*move on to next step since atleast 1 chosen*/
		if (cChosenTopping == 'n' && nToppingCount > 0) 
			nValidInput = 1;
		/*cant move on no topping chosen*/
		else if (cChosenTopping == 'n' && nToppingCount == 0){
			printf ("\n");
			print_Line ();
			printf ("| Please select atleast one topping !  |\n");
			print_Line ();
		}
		/*user cancels order*/
		else if (cChosenTopping  == 'x')
			nValidInput = 1;
		/*user chose an available topping*/
		else if (nValidTopping){
			/*get index of chosen topping from availble data*/
			nIndex = get_Index (cChosenTopping, 
							    cAvailableToppings, 
							    nAvailToppingsSize);
			/*get the index of size chosen from available data */				   
			nMultiplier = get_Index (*cSize,
									 cAvailableSizes,
									 nAvailableSizeLength);
			
			nToppingQuantity[nIndex] += 1; /*add 1 to type of topping used*/
			/*add the price of the topping with multiplier*/
			*fTotalPrice += cToppingsPrize[nIndex] * fToppingMultiplier[nMultiplier];
			nToppingCount += 1; /*add 1 to toppings chosen*/
		}
		else
			invalid_Message ();
	}
	return cChosenTopping;
}

/* 
This function will take the order of what toppings does the user want
Precondition: the user provided a character for his choice for the cheese
@param nCheeseCount - quantity of cheese the user choose on the last step
@param nCheeseQuantity - array that stores the quantity of a cheese type that a user chose
@return a character that denotes if a user cancels and order or move onto the next step
*/
char
choose_Cheese (int nCheeseCount,
			   int* nCheeseQuantity)
{
	char cChosenCheese;
	
	int nValidInput = 0,
		nValidCheese = 0,
		nIndex = 0;
	/*keep scanning if invalid and lacking cheese chosen*/
	while (nValidInput == 0  && nCheeseCount >= 1){
		print_Menu (4);
		
		printf ("Input cheese: ");
		scanf ("%c",&cChosenCheese);
		clear_Buffer ();
		/*convert char to lowercase to reduce uppercase condition*/
		cChosenCheese = tolower (cChosenCheese);
		/*check if input is valid*/
		nValidCheese = check_Availability (cChosenCheese,
										   cAvailableCheese,
										   nAvailCheeseSize);
		/*user cancels order*/
		if (cChosenCheese  == 'x')
			nValidInput = 1;
		/*enough cheese selected moving on*/
		else if (nCheeseCount == 0)
			nValidInput = 1;
		/*the user selected a valid cheese option*/
		else if (nValidCheese){
			nIndex = get_Index (cChosenCheese,
							    cAvailableCheese,
							    nAvailCheeseSize);
			/*add 1 to cheese type*/				   
			nCheeseQuantity[nIndex] += 1;
			/*less 1 cheese to be chosen*/
			nCheeseCount -= 1;
		}
		else
			invalid_Message ();
		
	}
	return cChosenCheese;
}

/* 
This function will take the order of what stuffing the user wants
Precondition: the user chose thick crust on the first step
@param fTotalPrice - an address that stores the total price of the order
@return a character that denotes the stuffing the user wants
*/
char
choose_Stuffing (float* fTotalPrice)
{
	char cChosenStuffing;
	
	int nValidInput = 0,
		nValidStuffing = 0,
		nIndex;
	/*keep scanning if invalid*/
	while (nValidInput == 0){
		print_Menu (5);
		
		printf ("Input stuffing: ");
		scanf ("%c",&cChosenStuffing);
		clear_Buffer ();
		/*convert char to lowercase to reduce uppercase conditions*/
		cChosenStuffing = tolower (cChosenStuffing);
		/*checks if the chosen input is available*/
		nValidStuffing = check_Availability (cChosenStuffing, 
											 cAvailableStuffings, 
											 nStuffingSize);
		/*user cancels the order or move on the next step*/
		if (cChosenStuffing  == 'n' || cChosenStuffing  == 'x')
			nValidInput = 1;
		/*chose a valid stuffing*/
		else if (nValidStuffing){
			/*get the price of the item and add it to the total*/
			nIndex = get_Index (cChosenStuffing, 
							    cAvailableStuffings, 
							    nStuffingSize);
			*fTotalPrice += fStuffingsPrize[nIndex];
			nValidInput = 1;
		}	 
		else
			invalid_Message ();
	}	
	return cChosenStuffing;
}

/* 
This function process the payment of the user
Precondition: user finish choosing the desired pizza
@param fTotalPrice - float which is the total price of the order
@param fPaid - address that store how much the user currently paid
@param nBillsInserted - array that stores how many bills per denomination the user added
@param nChangeBill - array that stores how many bills per denomination the user receive as change
@return a character that denotes the stuffing the user wants
*/
char
user_payment (float fTotalPrice, 
			  float* fPaid, 
			  int* nBillInserted,
			  int* nChangeBill)
{
	int nValidInput = 0,
		nIndex = 0,
		nInput = -1,
		i = 0;
		
	float fChange = 0;	
	
	char cChosenChar = '\0';
	/*keep scanning if invalid*/
	while (nValidInput == 0){
		print_Menu (6);
		
		printf ("Input bill: ");
		scanf ("%d",&nInput);
		clear_Buffer ();
		/*user cancels order*/
		if (nInput == 0){
			nValidInput = 1;
			cChosenChar = 'x';
		}
		/*user chose a valid denomination*/
		else if (nInput >= 1 && nInput <= 12){
			/*convert to lowercase letter*/
			cChosenChar = nInput + 96;
			/* get index of the denomination*/
			nIndex = get_Index (cChosenChar, 
							    cAvailableCashOptions, 
							    nAvailableCashSize);
			/*add denomination to amount paid*/				   
			*fPaid += fAvailableCash[nIndex];
			/*add 1 to quantity of denomination inserted*/
			nBillInserted[nIndex] += 1;
			/*user paid enough*/
			if (fTotalPrice <= *fPaid){
				nValidInput = 1;
				/*compute the change*/
				fChange = *fPaid - fTotalPrice;
				/*change is available*/
				if (fChange){
					printf ("\n");
					print_Line ();
					printf ("|%5c%s%7c|\n", '\0',"  Dispensing your change  ",'\0');
					print_Line ();
					printf ("|    Peso value     |     Quantity     |\n");
					print_Line ();
					/*iterate over the available denominations*/
					for (i = 0; i < nAvailableCashSize; i++){
						/*The count of bill for the denomination*/
						nChangeBill[i] += fChange / fAvailableCash[i];
						/*fmodf to compute the reaminder of the change*/
						fChange = fmodf (fChange,fAvailableCash[i]);
						/*the count of bill is greater than 0  output it*/
						if (nChangeBill[i])
							printf ("|%4c%8.2f%8c%9d%9c|\n",'\0',fAvailableCash[i] ,'|',nChangeBill[i],'\0');
					}
					print_Line ();
				}
			}
			nInput = -1;
		}	
		else
			invalid_Message ();
	}
	return cChosenChar;
}

/* 
This function resets the values inside the array back to 0
Precondition: The machine either completed an order or the customer cancelled an order
@param nArray - array that is going to be reinitialized
@param nArraySize - size of array
*/
void
reset_array (int* nArray, 
			 int nArraySize)
{
	int index;
	
	for (index = 0; index < nArraySize; index++){
		nArray[index] = 0; 
	}
}

/* 
This function resets the values of the current order
Precondition: The machine either completed an order or the customer cancelled an order
@param nStep - address where the current step that the machine is operating is stored
@param cCrust - address where the chosen crust of the user is stored
@param cSize - address where the chosen size of the user is stored
@param nToppingQuantity - array where the quantity of each topping the user chose is stored
@param nCheeseQuantity - array where the quantity of each cheese the user chose is stored
@param cStuffing - address where the chosen stuffing of the user is stored
@param fTotalPrice - address where the total price of the order is stored
@param nBillInserted - array where the quantity of each denomination inserted by the user is stored
@param nChangeBill - array where the quantity of each denomination of change recieved by the user is stored
@param fPaid - address where the total amount paid of the order is stored
*/
void 
reinitialize_Values (int* nStep, 
					 char* cCrust, 
					 char* cSize, 
					 int* nToppingQuantity, 
					 int* nCheeseQuantity, 
					 char* cStuffing, 
					 float* fTotalPrice,
					 int* nBillInserted,
					 int* nChangeBill, 
					 float* fPaid)
{
	/*reset the respective values stored to default*/
	*nStep = 1;
	*cCrust = '\0';
	*cSize = '\0';
	*cStuffing = '\0';
	*fTotalPrice = 0.0;
	*fPaid = 0.0;
	reset_array (nToppingQuantity,
				 nAvailToppingsSize);
	reset_array (nCheeseQuantity,
				 nAvailCheeseSize);
	reset_array (nBillInserted, 
				 nAvailableCashSize);
	reset_array (nChangeBill,
				 nAvailableCashSize);
}

/* 
This function cancels the current order and reverts the state of the machine back to step 1
Precondition: The user cancelled an order
@param nStep - address where the current step that the machine is operating is stored
@param cCrust - address where the chosen crust of the user is stored
@param cSize - address where the chosen size of the user is stored
@param nToppingQuantity - array where the quantity of each topping the user chose is stored
@param nCheeseQuantity - array where the quantity of each cheese the user chose is stored
@param cStuffing - address where the chosen stuffing of the user is stored
@param fTotalPrice - address where the total price of the order is stored
@param nBillInserted - array where the quantity of each denomination inserted by the user is stored
@param nChangeBill - array where the quantity of each denomination of change recieved by the user is stored
@param fPaid - address where the total amount paid of the order is stored
*/
void 
cancel_Order (int* nStep,
			  char* cCrust,
			  char* cSize,
			  int* nToppingQuantity,
			  int* nCheeseQuantity,
			  char* cStuffing,
			  float* fTotalPrice,
			  int* nBillInserted,
			  int* nChangeBill,
			  float* fPaid)
{
	/* reset values since the order is cancelled */
	reinitialize_Values (nStep,
						 cCrust,
						 cSize,
						 nToppingQuantity,
						 nCheeseQuantity,
						 cStuffing,
						 fTotalPrice,
						 nBillInserted,
						 nChangeBill,
						 fPaid);
	printf ("\n");
	print_Line ();
	printf ("|     Order has been cancelled !       |\n");
	print_Line ();
	printf ("\n");
}

/* 
This function prints the user total for the pizza size
Precondition: The machine is moving to the next step
@param cCrust - crust the user chose
@param cSize - size the user chose
*/
void 
print_CrustSize (char cCrust,
				 char cSize)
{
	/*get the index of the crust chosen and the size chosen*/
	int nCrustIndex = get_Index (cCrust,
								 cAvailableCrust,
								 nAvailableCrustSize),
		nSizeIndex = get_Index (cSize,
							    cAvailableSizes,
							    nAvailableSizeLength);
							    
	printf ("|%-12s(%c)%23.2f|\n",
		    crustText[nCrustIndex],
		    toupper (cAvailableSizes[nSizeIndex]),
		    fSizesPrize[nSizeIndex]); 
}

/* 
This function prints the user total for each pizza topping
Precondition: The machine is moving to the next step
@param nStep - step which the machine is operating
@param fMultiplier - multiplier based on the pizza size
@param nToppingQuantity - array where the quantity of each topping the user chose is stored
*/
void 
print_Toppings (int nStep,
				float fMultiplier,
				int* nToppingQuantity)
{
	int i;
	/*print topping if it is chosen atleast once with price*/
	if (nStep == 3){
		for (i = 0; i < nAvailToppingsSize; i++){
			
			if (nToppingQuantity[i] > 0)
				printf ("|%-15s%23.2f|\n",
					    toppingText[i],
					    cToppingsPrize[i] * nToppingQuantity[i] * fMultiplier);
		}
	}
	/*print topping except cheese if it is chosen atleast once with price*/
	else{
		for (i = 0; i < nAvailToppingsSize; i++){
			
			if (nToppingQuantity[i] > 0 && i != 3)
				printf ("|%-15s%23.2f|\n",
					    toppingText[i],
					    cToppingsPrize[i] * nToppingQuantity[i] * fMultiplier);
		}
	}
}

/* 
This function prints the user total for each cheese
Precondition: The machine is moving to the next step
@param fMultiplier - multiplier based on the pizza size
@param nCheeseQuantity - array where the quantity of each cheese the user chose is stored
*/
void 
print_Cheese (float fMultiplier,
			  int* nCheeseQuantity)
{
	int i;
	/*print cheese if it is chosen atleast once with price*/
	for (i = 0; i < nAvailCheeseSize; i++){
		
		if (nCheeseQuantity[i] > 0)
			printf ("|%-15s%23.2f|\n",
				    cheeseText[i],
				    cToppingsPrize[3] * nCheeseQuantity[i] * fMultiplier);
	}
}

/* 
This function prints the user total for the stuffing
Precondition: The user chose thick crust and a stuffing, the machine is also moving to the next step
@param cStuffing - stuffing the user chose
*/
void
print_Stuffing (char cStuffing)
{
	int nStuffingIndex;
	/*Check if the user chose a stuffing if yes print else no*/
	if (check_Availability (cStuffing,
							cAvailableStuffings,
							nStuffingSize)){
		
		nStuffingIndex = get_Index (cStuffing,
									cAvailableStuffings,
									nStuffingSize);
		
		printf ("|%-6s(Stuffing)%22.2f|\n",
			    stuffingText[nStuffingIndex],
			    fStuffingsPrize[nStuffingIndex]);
	}
}

/* 
This function prints the total of the user per step
Precondition: The user completed a step in the order process 
@param nStep - current step that the machine is operating is stored
@param cCrust - the chosen crust of the user is stored
@param cSize - the chosen size of the user is stored
@param nToppingQuantity - array where the quantity of each topping the user chose is stored
@param nCheeseQuantity - array where the quantity of each cheese the user chose is stored
@param cStuffing - chosen stuffing of the user is stored
@param fTotalPrice - total price of the order is stored
@param nBillInserted - array where the quantity of each denomination inserted by the user is stored
@param nChangeBill - array where the quantity of each denomination of change recieved by the user is stored
@param fPaid - total amount paid of the order is stored
@param nTransactionId - nth transaction of the machine 
*/
void
print_Total (int nStep,
			 char cCrust,
			 char cSize,
			 int* nToppingQuantity,
			 int* nCheeseQuantity,
			 char cStuffing,
			 float fTotalPrice,
			 int* nBillInserted,
			 int* nChangeBill,
			 float fPaid,
			 int nTransactionId)
{
	/*get the multiplier base on the size for the toppings*/
	float fMultiplier = fToppingMultiplier[get_Index (cSize,
													  cAvailableSizes,
													  nAvailableSizeLength)];
	printf ("\n");
	print_Line ();
	printf ("|%11c%s%12c|\n", '\0',"Jeff's pizzeria",'\0');
	print_Line ();
	/*add to ntransaction since it starts with 0 transactions completed*/
	printf ("|%-16s%-5d%17c|\n","Transaction ID: ", nTransactionId+1,'\0');
	/*print the necessary items in the receipt per step*/
	switch (nStep){
		case 2:
			print_CrustSize (cCrust,
							 cSize);
			break;
			
		case 3:
			print_CrustSize (cCrust,
							 cSize);
			print_Toppings (nStep,
							fMultiplier,
							nToppingQuantity);
			break;
			
		case 4:
			print_CrustSize (cCrust,
							 cSize);
			print_Toppings (nStep,
						    fMultiplier,
						    nToppingQuantity);
			print_Cheese (fMultiplier,
						  nCheeseQuantity);
			break;
			
		case 5:
			print_CrustSize (cCrust,
							 cSize);
			print_Toppings (nStep,
						    fMultiplier,
						    nToppingQuantity);
			print_Cheese (fMultiplier,
						  nCheeseQuantity);
			print_Stuffing (cStuffing);
			break;
			
		case 6:
			print_CrustSize (cCrust,
							 cSize);
			print_Toppings (nStep,
						    fMultiplier,
						    nToppingQuantity);
			print_Cheese (fMultiplier,
						  nCheeseQuantity);
			print_Stuffing (cStuffing);
			break;
	}
	print_Line ();
	printf ("|%-7s%31.2f|\n","Total: ", fTotalPrice);
	/* print the amount paid and change on last step*/
	if (nStep == 6){
		printf ("|%-12s%26.2f|\n","Amount Paid:", fPaid);
		printf ("|%-8s%30.2f|\n","Change: ", fPaid-fTotalPrice);
	}
	print_Line ();
}

/* 
This function compute the time required to cook the pizza and output in minutes:seconds format
Precondition: The user has completed placing the order
@param nToppingQuantity - array where the quantity of each topping the user chose is stored
@param cStuffing - chosen stuffing of the user is stored
*/
void cookPizza (int* nToppingQuantity,
			    char cStuffing)
{
	/*base time is 3 mins*/
	int seconds = 180,
		i = 0;
	/*topping that is chosen atleast once multiply it by 2 and add it to total seconds*/
	for (i = 0; i < nAvailToppingsSize; i++){
		
		if (nToppingQuantity[i] > 0)
			seconds += nToppingQuantity[i] * 2;
	}
	/*cheese or spam add 5 seconds*/
	if (cStuffing == 'c' || cStuffing == 's')
		seconds += 5;
	/*both add 10 seconds*/
	else if (cStuffing == 'b')
		seconds += 10;
		
	printf ("\n");
	print_Line ();
	printf ("|%-9c%s%9c|\n", '\0',"Preparing your pizza",'\0');
	print_Line ();
	/*timer to cook pizza countdown*/
	while (seconds >= 0){
		printf ("|%16c%2d:%02d%17c|\n",'\0',seconds/60,seconds%60,'\0'); 
		print_Line ();
		seconds -= 1;
	}
	print_Line ();
	printf ("|%4c%s%4c|\n", '\0',"Enjoy your freshly made pizza!",'\0');
	print_Line ();
	printf ("\n");
}

/* 
This function adds the values of an array to another array
Precondition: The machine completed an order
@param nOrderArray - array that holds the current order datta
@param nDataArray - array that holds the total run data
@param nSize - size of the arrays 
*/
void
add_ToArray (int* nOrderArray,
			 int* nDataArray,
			 int nSize)
{
	int i = 0;
	
	for (i = 0; i < nSize; i++)
		nDataArray[i] += nOrderArray[i];
}

/* 
This function adds the current order data to the total data of the run
Precondition: The machine completed an order
@param cCrust - the chosen crust of the user is stored
@param cSize - the chosen size of the user is stored
@param nToppingQuantity - array where the quantity of each topping the user chose is stored
@param nCheeseQuantity - array where the quantity of each cheese the user chose is stored
@param cStuffing - chosen stuffing of the user is stored
@param nBillInserted - array where the quantity of each denomination inserted by the user is stored
@param nChangeBill - array where the quantity of each denomination of change recieved by the user is stored
@param nCrustUsed - array where the quantity of each crusted used in the current machine run is stored
@param nSizeUsed - array where the quantity of each size used in the current machine run is stored
@param nStuffingUsed - array where the quantity of each stuffing used in the current machine run is stored
@param nToppingsUsed - array where the quantity of each topping used in the current machine run is stored
@param nCheeseUsed - array where the quantity of each cheese used in the current machine run is stored
@param nBillInsertData - array where the quantity of each denomination inserted by the user is stored 
						 in the current machine run is stored
@param nChangeBillUsed - array where the quantity of each denomination change recieved by the user is
						 stored in the current machine run is stored
*/
void 
addUsedIngredients (char cCrust,
				    char cSize,
				    int* nToppingQuantity,
				    int* nCheeseQuantity,
				    char cStuffing,
				    int* nBillInserted,
				    int* nChangeBill,
				    int* nCrustUsed,
				    int* nSizeUsed,
				    int* nStuffingUsed,
				    int* nToppingsUsed,
				    int* nCheeseUsed,
				    int* nBillInsertData,
				    int* nChangeBillUsed)
{
	int nCrustIndex = get_Index (cCrust,
								 cAvailableCrust,
								 nAvailableCrustSize),
		nSizeIndex = get_Index (cSize,
							    cAvailableSizes,
							    nAvailableSizeLength),
		nStuffingIndex = 0,
		nValidStuffing = 0;
		
	nCrustUsed[nCrustIndex] += 1;
	nSizeUsed[nSizeIndex] += 1;
	
	nValidStuffing = check_Availability (cStuffing,
										 cAvailableStuffings,
										 nStuffingSize);
	
	if (nValidStuffing){
		nStuffingIndex = get_Index (cStuffing,
								    cAvailableStuffings,
								    nStuffingSize); 
		nStuffingUsed[nStuffingIndex] += 1;
	}
	
	add_ToArray (nToppingQuantity,
				 nToppingsUsed,
				 nAvailToppingsSize);
				
	add_ToArray (nCheeseQuantity,
				 nCheeseUsed,
				 nAvailCheeseSize);
				
	add_ToArray (nBillInserted,
				 nBillInsertData,
				 nAvailableCashSize);
				
	add_ToArray (nChangeBill,
				 nChangeBillUsed,
				 nAvailableCashSize);
}

/* 
This function displays that handles user data and the operations the machine step by step 
Precondition: the machine is not under maintenance
@param nStep - address that stores the current step that the machine is operating
@param nMaintenance - address that stores the state of the machine
@param cCrust - address that stores chosen crust of the user
@param cSize - address that stores chosen size of the user
@param nToppingQuantity - array where the quantity of each topping the user chose is stored
@param nCheeseQuantity - array where the quantity of each cheese the user chose is stored
@param cStuffing - address that stores chosen stuffing of the user
@param fTotalPrice - address that stores the total prize of the user's order
@param nBillInserted - array where the quantity of each denomination inserted by the user is stored
@param nChangeBill - array where the quantity of each denomination of change recieved by the user is stored
@param fPaid - address that stores the total amount paid of the user
@param nTransactionId - address that stores nth transaction of the machine 
@param nCrustUsed - array where the quantity of each crusted used in the current machine run is stored
@param nSizeUsed - array where the quantity of each size used in the current machine run is stored
@param nStuffingUsed - array where the quantity of each stuffing used in the current machine run is stored
@param nToppingsUsed - array where the quantity of each topping used in the current machine run is stored
@param nCheeseUsed - array where the quantity of each cheese used in the current machine run is stored
@param nBillInsertData - array where the quantity of each denomination inserted by the user is stored 
						 in the current machine run is stored
@param nChangeBillUsed - array where the quantity of each denomination change recieved by the user is 
						 stored in the current machine run is stored
*/
void 
main_Menu (int* nStep,
		   int* nMaintenance,
		   char* cCrust,
		   char* cSize,
		   int* nToppingQuantity,
		   int* nCheeseQuantity,
		   char* cStuffing,
		   float* fTotalPrice,
		   int* nBillInserted,
		   int* nChangeBill,
		   float* fPaid,
		   int* nTransactionId,
		   int* nCrustUsed,
		   int* nSizeUsed,
		   int* nStuffingUsed,
		   int* nToppingsUsed,
		   int* nCheeseUsed,
		   int* nBillInsertData,
		   int* nChangeBillUsed)
{
	/*while machine is not closed*/
	while (*nMaintenance != 1){
		char cOption = '\0';
		switch (*nStep){
			/*
			For Each step retrieve user choice and evaluate it
			Print running total if going to next step
			*/
		    case 1:
		        *cCrust = choose_Crust ();
		        
		        if (*cCrust == 'c')
					*nMaintenance = 1;
				else
		        	*nStep = 2;
		        break;
		        
		    case 2:
		        *cSize = choose_Size (fTotalPrice);
		        
		        if (*cSize == 'x')
					cancel_Order (nStep,
								  cCrust,
								  cSize,
								  nToppingQuantity,
								  nCheeseQuantity,
								  cStuffing,
								  fTotalPrice,
								  nBillInserted,
								  nChangeBill,
								  fPaid);
				else{
					print_Total (*nStep,
								 *cCrust,
								 *cSize,
								 nToppingQuantity,
								 nCheeseQuantity,
								 *cStuffing,
								 *fTotalPrice,
								 nBillInserted,
								 nChangeBill,
								 *fPaid,
								 *nTransactionId);
					*nStep = 3;
				}
				break;
				
		    case 3:
		    	cOption = choose_Toppings (nToppingQuantity,
										   fTotalPrice,
										   cSize);
										  
				if (cOption == 'x')
					cancel_Order (nStep,
								  cCrust,
								  cSize,
								  nToppingQuantity,
								  nCheeseQuantity,
								  cStuffing,
								  fTotalPrice,
								  nBillInserted,
								  nChangeBill,
								  fPaid);
				else{
					print_Total (*nStep,
								 *cCrust,
								 *cSize,
								 nToppingQuantity,
								 nCheeseQuantity,
								 *cStuffing,
								 *fTotalPrice,
							 	 nBillInserted,
								 nChangeBill,
								 *fPaid,
								 *nTransactionId);
					/*go to cheese selection since the user chose cheese atleast once*/
					if(nToppingQuantity[3] > 0)
						*nStep = 4;
					/*go to stuffing selection no cheese selected and thick crust*/
					else if(*cCrust == 'b' && nToppingQuantity[3] == 0)
						*nStep = 5;
					/*go to payment option since no cheese and thin crust*/
					else if(nToppingQuantity[3] == 0)
						*nStep = 6;
				}
				break;
				
			case 4:
				cOption = choose_Cheese (nToppingQuantity[3], 
										 nCheeseQuantity);
										  
				if (cOption == 'x')
					cancel_Order (nStep,
								 cCrust,
								 cSize,
								 nToppingQuantity,
								 nCheeseQuantity,
								 cStuffing,
								 fTotalPrice,
								 nBillInserted,
								 nChangeBill,
								 fPaid);
				else{
					print_Total (*nStep,
								 *cCrust,
								 *cSize,
								 nToppingQuantity,
								 nCheeseQuantity,
								 *cStuffing,
								 *fTotalPrice,
								 nBillInserted,
								 nChangeBill,
								 *fPaid,
								 *nTransactionId);
					/*go to stuffing selection since the user wants thick crust*/
					if (*cCrust == 'b')
						*nStep = 5;
					/*go to payment option since the user does not want thcik crust*/
					else
						*nStep = 6;
				}
				break;
				
			case 5:
				*cStuffing = choose_Stuffing (fTotalPrice);
				
				if (*cStuffing  == 'x')
					cancel_Order (nStep,
								  cCrust,
								  cSize,
								  nToppingQuantity,
								  nCheeseQuantity,
								  cStuffing,
								  fTotalPrice,
								  nBillInserted,
								  nChangeBill,
								  fPaid);
				else{
					print_Total (*nStep,
								 *cCrust,
								 *cSize,
								 nToppingQuantity,
								 nCheeseQuantity,
								 *cStuffing,
								 *fTotalPrice,
								 nBillInserted,
								 nChangeBill,
								 *fPaid,
								 *nTransactionId);
					*nStep = 6;
				}
				break;
				
			case 6:
				cOption = user_payment (*fTotalPrice,
										fPaid,
										nBillInserted,
										nChangeBill);
										
				if (cOption == 'x')
					cancel_Order (nStep,
								  cCrust,
								  cSize,
								  nToppingQuantity,
								  nCheeseQuantity,
								  cStuffing,
								  fTotalPrice,
								  nBillInserted,
								  nChangeBill,
								  fPaid);
				else{
					print_Total (*nStep,
								 *cCrust,
								 *cSize,
								 nToppingQuantity,
								 nCheeseQuantity,
								 *cStuffing,
								 *fTotalPrice,
								 nBillInserted,
								 nChangeBill,
								 *fPaid,
								 *nTransactionId);
					*nStep = 7;
				}
				break;
				
			case 7: /*order complete and prepare the pizza for the user*/
				*nTransactionId += 1; /*add 1 to transactions made*/
				/*cook the pizza*/
				cookPizza (nToppingQuantity,
						   *cStuffing);
				/*add order data to the total data*/
				addUsedIngredients (*cCrust,
								    *cSize,
								    nToppingQuantity,
								    nCheeseQuantity,
								    *cStuffing,
								    nBillInserted,
								    nChangeBill,
								    nCrustUsed,
								    nSizeUsed,
								    nStuffingUsed,
								    nToppingsUsed,
								    nCheeseUsed,
								    nBillInsertData,
								    nChangeBillUsed);
				/*reset order data since the current order is completed*/
				reinitialize_Values (nStep,
									 cCrust,
									 cSize,
									 nToppingQuantity,
									 nCheeseQuantity,
									 cStuffing,
									 fTotalPrice,
									 nBillInserted,
									 nChangeBill,
									 fPaid);
				*nStep = 1; /*go back to start*/
		}
	}
}

/*
This function displays the total ingredients used in the run
Precondition: the machine is going under maintenance
@param nTransactionId - the nth transaction of the machine 
@param nCrustUsed - array where the quantity of each crusted used in the current machine run is stored
@param nSizeUsed - array where the quantity of each size used in the current machine run is stored
@param nStuffingUsed - array where the quantity of each stuffing used in the current machine run is stored
@param nToppingsUsed - array where the quantity of each topping used in the current machine run is stored
@param nCheeseUsed - array where the quantity of each cheese used in the current machine run is stored
@param nBillInsertData - array where the quantity of each denomination inserted by the user is stored 
						 in the current machine run is stored
@param nChangeBillUsed - array where the quantity of each denomination change recieved by the user 
						 is stored in the current machine run is stored
*/
void
printRunData (int nTransactionId,
			  int* nCrustUsed,
			  int* nSizeUsed,
			  int* nStuffingUsed,
			  int* nToppingsUsed,
			  int* nCheeseUsed,
			  int* nBillInsertData,
			  int* nChangeBillUsed,
			  float* fTotalInsert,
			  float* fTotalChange)
{
	int i = 0;
	
	/* iterate through every array and print the quantity per item */
	print_Line ();
	printf ("|%2c%s%4c|\n", '\0',"Ingredient report of the machine",'\0');
	print_Line ();
	printf ("|%-12s %-9d%15c|\n","Transactions:", nTransactionId,'\0');
	
	print_Line ();
	printf ("| Type Of Crust    |  	Quantity       |\n");
	print_Line ();
	for (i = 0; i < nAvailableCrustSize;i++)
		printf ("|%-12s%26d|\n",crustText[i],nCrustUsed[i]);
	
	print_Line ();
	printf ("| Size Of Dough    |  	Quantity       |\n");
	print_Line ();
	for (i = 0; i < nAvailableSizeLength;i++)
		printf ("|%-12s%26d|\n",sizeText[i],nSizeUsed[i]);
	
	print_Line ();
	printf ("| Stuffing Of Pizza |  	Quantity       |\n");
	print_Line ();
	for (i = 0; i < nStuffingSize;i++)
		printf ("|%-12s%26d|\n",stuffingText[i],nStuffingUsed[i]);	
	
	print_Line ();
	printf ("| Toppings of Pizza |  	Quantity       |\n");
	print_Line ();
	for (i = 0; i < nAvailToppingsSize;i++)
		printf ("|%-12s%26d|\n",toppingText[i],nToppingsUsed[i]);
	
	print_Line ();
	printf ("| Type of Cheese   |  	Quantity       |\n");
	print_Line ();
	for (i = 0; i < nAvailCheeseSize;i++)
		printf ("|%-12s%26d|\n",cheeseText[i],nCheeseUsed[i]);
	
	print_Line();
	printf ("| Bills Inserted   |  	Quantity       |\n");
	print_Line ();
	for (i = 0; i < nAvailableCashSize;i++){
		printf ("|Php %-10.2f%24d|\n",fAvailableCash[i],nBillInsertData[i]);
		*fTotalInsert += fAvailableCash[i] * nBillInsertData[i];
	}
	
	print_Line ();
	printf ("|%-12s%26.2f|\n","Total", *fTotalInsert);
	print_Line ();
	
	printf ("| Change Dispensed |  	Quantity       |\n");
	print_Line ();
	for (i = 0; i < nAvailableCashSize;i++){
		printf ("|Php %-10.2f%24d|\n",fAvailableCash[i],nChangeBillUsed[i]);
		*fTotalChange += fAvailableCash[i] * nChangeBillUsed[i];
	}
	
	print_Line ();
	printf ("|%-12s%26.2f|\n","Total",*fTotalChange);
	print_Line ();
}

/*
This function signals that the machine will be under maintenace
Precondition: the machine is going under maintenance
@param nTransactionId - the nth transaction of the machine 
@param nCrustUsed - array where the quantity of each crusted used in the current machine run is stored
@param nSizeUsed - array where the quantity of each size used in the current machine run is stored
@param nStuffingUsed - array where the quantity of each stuffing used in the current machine run is stored
@param nToppingsUsed - array where the quantity of each topping used in the current machine run is stored
@param nCheeseUsed - array where the quantity of each cheese used in the current machine run is stored
@param nBillInsertData -  array where the quantity of each denomination inserted by the user is stored
						  in the current machine run is stored
@param nChangeBillUsed -  array where the quantity of each denomination change recieved by the user
						  is stored in the current machine run is stored
*/
void 
maintenance (int nTransactionId,
			 int* nCrustUsed,
			 int* nSizeUsed,
			 int* nStuffingUsed,
			 int* nToppingsUsed,
			 int* nCheeseUsed,
			 int* nBillInsertData,
			 int* nChangeBillUsed,
			 float* fTotalInsert,
			 float* fTotalChange)
{
	print_Line ();
	printf ("|  Machine will undergo maintenance !  |\n");
	print_Line ();
	printf ("\n");
	
	/* print the total ingredients used*/
	printRunData (nTransactionId,
				  nCrustUsed,
				  nSizeUsed,
				  nStuffingUsed,
				  nToppingsUsed,
				  nCheeseUsed,
				  nBillInsertData,
				  nChangeBillUsed,
				  fTotalInsert,
				  fTotalChange);
}

/*
This function reads array data from a file
Precondition: the machine just started its' operations
@param fPtr - file pointer which allows file operations
@param  nArray - array that stores the data to be loaded
@param nSize - size of the array that accepts the file data
*/
void
storeArrayData (FILE** fPtr,
			    int* nArray,
			    int sSize)
{
	int i = 0,
		nData;

	for (i = 0; i < sSize; i++){
		fscanf (*fPtr, "%d", &nData);
		nArray[i] += nData;
	}
}


/*
This function loads data from a file
Precondition: the machine just started its' operations
@param sFileName - string that stores the filename
@param fPtr - file pointer which allows file operations
@param nTransactionId - the nth transaction of the machine
@param nCrustUsed - array where the quantity of each crusted used in the current machine run is stored
@param nSizeUsed - array where the quantity of each size used in the current machine run is stored
@param nStuffingUsed - array where the quantity of each stuffing used in the current machine run is stored
@param nToppingsUsed - array where the quantity of each topping used in the current machine run is stored
@param nCheeseUsed - array where the quantity of each cheese used in the current machine run is stored
@param nBillInsertData -  array where the quantity of each denomination inserted by the user is stored
						  in the current machine run is stored
@param nChangeBillUsed -  array where the quantity of each denomination change recieved by the user
						  is stored in the current machine run is stored
*/
void
retrieveFileData (char* sFileName,
				  FILE** fPtr,
				  int* nTransactionId,
				  int* nCrustUsed,
				  int* nSizeUsed,
				  int* nStuffingUsed,
				  int* nToppingsUsed,
				  int* nCheeseUsed,
				  int* nBillInsertData,
				  int* nChangeBillUsed)
{
	int nId;
	
	*fPtr = fopen(sFileName, "r");
	
	if (*fPtr == NULL){
		printf ("\n");
		print_Line ();
		printf ("|  Data from previous runs not loaded! |\n");
		print_Line ();
		printf ("\n");
	}
	else{
		fscanf (*fPtr,"%d ",&nId);
		
		*nTransactionId += nId;
		
		storeArrayData (fPtr,
					    nCrustUsed,
					    nAvailableCrustSize);
		storeArrayData (fPtr,
					    nSizeUsed,
					    nAvailableSizeLength);
		storeArrayData (fPtr,
					    nStuffingUsed,
					    nStuffingSize);
		storeArrayData (fPtr,
					    nToppingsUsed,
					    nAvailToppingsSize);
		storeArrayData (fPtr,
					    nCheeseUsed,
					    nAvailCheeseSize);
		storeArrayData (fPtr,
					    nBillInsertData,
					    nAvailableCashSize);
		storeArrayData (fPtr,
					    nChangeBillUsed,
					    nAvailableCashSize);
		printf ("\n");
		print_Line ();
		printf ("|    Data from previous runs loaded!   |\n");
		print_Line ();
		printf ("\n");
	}
	fclose (*fPtr);
}

/*
This function writes array data to a file
Precondition: the machine is going under maintenance
@param fPtr - file pointer which allows file operations
@param  nArray - array that stores the data to be saved
@param nSize - size of the array that stores the data
*/
void
writeArrayData (FILE** fPtr,
				int* nArray,
				int sSize)
{
	int i = 0;
	
	for (i = 0; i < sSize; i++)
		fprintf (*fPtr, "%d ", nArray[i]);
}

/*
This function saves data to a file
Precondition: the machine is going under maintenance
@param sFileName - string that stores the filename
@param fPtr - file pointer which allows file operations
@param nTransactionId - the nth transaction of the machine  
@param nCrustUsed - array where the quantity of each crusted used in the current machine run is stored
@param nSizeUsed - array where the quantity of each size used in the current machine run is stored
@param nStuffingUsed - array where the quantity of each stuffing used in the current machine run is stored
@param nToppingsUsed - array where the quantity of each topping used in the current machine run is stored
@param nCheeseUsed - array where the quantity of each cheese used in the current machine run is stored
@param nBillInsertData - array where the quantity of each denomination inserted by the user is stored 
						 in the current machine run is stored
@param nChangeBillUsed - array where the quantity of each denomination change recieved by the user 
						 is stored in the current machine run is stored
*/
void 
saveInFile (char* sFileName,
		    FILE** fPtr,
		    int nTransactionId,
		    int* nCrustUsed,
		    int* nSizeUsed,
		    int* nStuffingUsed,
		    int* nToppingsUsed,
		    int* nCheeseUsed,int* nBillInsertData,
		    int* nChangeBillUsed)
{
	*fPtr = fopen(sFileName, "w");
	
	if (fPtr != NULL){
		fprintf (*fPtr, "%d ", nTransactionId);
		
		writeArrayData (fPtr,
					    nCrustUsed,
					    nAvailableCrustSize);
		writeArrayData (fPtr,
					    nSizeUsed,
					    nAvailableSizeLength);
		writeArrayData (fPtr,
					    nStuffingUsed,
					    nStuffingSize);
		writeArrayData (fPtr,
					    nToppingsUsed,
					    nAvailToppingsSize);
		writeArrayData (fPtr,
					    nCheeseUsed,
					    nAvailCheeseSize);
		writeArrayData (fPtr,
					    nBillInsertData,
					    nAvailableCashSize);
		writeArrayData (fPtr,
					    nChangeBillUsed,
					    nAvailableCashSize);
					    
		printf ("\n");
		print_Line ();
		printf ("|   Machine data successfully saved!   |\n");
		print_Line ();
	}
	else{
		printf ("\n");
		print_Line ();
		printf ("|     Machine data was not saved!      |\n");
		print_Line ();
	}
	fclose (*fPtr);
}

int 
main ()
{
    int nTransactionId = 0,
    	nMaintenance = 0,
		nStep = 1;
		
	char cSize = '\0',
		 cCrust = '\0',
		 cStuffing = '\0';
    
    float fTotalPrice = 0.0,
    	  fPaid = 0.0,
    	  fTotalInsert = 0.0,
    	  fTotalChange = 0.0;
		  	
    int nToppingQuantity[5] = {0, 0, 0, 0, 0},
		nCheeseQuantity[4] = {0, 0, 0, 0},
		nBillInserted[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		nChangeBill[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		nCrustUsed[3] = {0, 0, 0},
    	nSizeUsed[3] = {0, 0, 0},
    	nStuffingUsed[3] = {0, 0, 0},
		nToppingsUsed[5] = {0, 0, 0, 0, 0},
		nCheeseUsed[4] = {0, 0, 0,0},
		nBillInsertData[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		nChangeBillUsed[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	
	FILE *fptr;
	
    main_Menu (&nStep,
			   &nMaintenance,
			   &cCrust,
			   &cSize,
			   nToppingQuantity,
			   nCheeseQuantity,
			   &cStuffing,
			   &fTotalPrice,
			   nBillInserted,
			   nChangeBill,
			   &fPaid,
			   &nTransactionId,
			   nCrustUsed,
			   nSizeUsed,
			   nStuffingUsed,
			   nToppingsUsed,
			   nCheeseUsed,
			   nBillInsertData,
			   nChangeBillUsed);
	
	retrieveFileData ("Data.txt",
					  &fptr,
					  &nTransactionId,
					  nCrustUsed,
					  nSizeUsed,
					  nStuffingUsed,
					  nToppingsUsed,
					  nCheeseUsed,
					  nBillInsertData,
					  nChangeBillUsed);
	
	maintenance (nTransactionId,
				 nCrustUsed,
				 nSizeUsed,
				 nStuffingUsed,
				 nToppingsUsed,
				 nCheeseUsed,
				 nBillInsertData,
				 nChangeBillUsed,
				 &fTotalInsert,
				 &fTotalChange);
	
	saveInFile ("Data.txt",
			    &fptr,
			    nTransactionId,
			    nCrustUsed,
			    nSizeUsed,
			    nStuffingUsed,
			    nToppingsUsed,
			    nCheeseUsed,
			    nBillInsertData,
			    nChangeBillUsed);	
	
    return 0;
}
