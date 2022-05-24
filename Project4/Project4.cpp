// CRM <Project4.cpp>
// EE 312 Project 4 submission by
// Ken Zhang
// ktz85
// Slip days used: <0>
// Fall 2021
// Copy-Paste the above lines at the top of your submitted files.

#include <stdio.h>
#include <assert.h>
#include "MyString.h"
#include "Invent.h"

#define MAX_CUSTOMERS 1000
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;

int numBottles = 0;
int numDiapers = 0;
int numRattles = 0;
/* you'll probably need several more global variables */
/* and of course, you have a few functions to write */

String bottles;
String diapers;
String rattles;

void initString(){
  bottles = StringCreate("Bottles");
  diapers = StringCreate("Diapers");
  rattles = StringCreate("Rattles");
}

void destroyString(){
  StringDestroy(&bottles);
  StringDestroy(&diapers);
  StringDestroy(&rattles);
}

int checkItemName(String* s){
  initString();
  int num = -1;
  if(StringIsEqualTo(s, &bottles))
    num = 0;
  else if(StringIsEqualTo(s, &diapers))
    num = 1;
  else if(StringIsEqualTo(s, &rattles))
    num = 2;
  destroyString();
  return num;

}

int findCustomer(String* s){
  for(int x = 0; x < num_customers; x++){
    if(StringIsEqualTo(s, &customers[x].name))
      return x;
  }
  return -1;
}


/* clear the inventory and reset the customer database to empty */
void reset(void) {
	for(int x = 0; x < num_customers; x++){
    StringDestroy(&customers[x].name);
    customers[x].bottles = 0;
    customers[x].diapers = 0;
    customers[x].rattles = 0;
  }
  num_customers = 0;
  numBottles = 0;
  numDiapers = 0;
  numRattles = 0;
}

void sumObjects(){
  int BMax = 0; int DMax = 0; int RMax = 0; int BIndex = -1; 
  int DIndex = -1; int RIndex = -1;
  for(int i = 0; i < num_customers; i++){
    if(customers[i].bottles > BMax){
      BMax = customers[i].bottles;
      BIndex = i;
    }
    if(customers[i].diapers > DMax){
      DMax = customers[i].diapers;
      DIndex = i;
    }
    if(customers[i].rattles > RMax){
      RMax = customers[i].rattles;
      RIndex = i;
    }
  }
  if(BIndex == -1){
    printf("no one has purchased any Bottles\n");
  }else{
  StringPrint(&customers[BIndex].name);
  printf(" has purchased the most Bottles (%d)\n", BMax);
  }

  if(DIndex == -1){
    printf("no one has purchased any Diapers\n");
  }else{
  StringPrint(&customers[DIndex].name);
  printf(" has purchased the most Diapers (%d)\n", DMax);
  }

  if(RIndex == -1){
    printf("no one has purchased any Rattles\n");
  }else{
  StringPrint(&customers[RIndex].name);
  printf(" has purchased the most Rattles (%d)\n", RMax);
  }

}






void processSummarize() {
  printf("There are %d Bottles %d Diapers and %d Rattles in inventory\n", numBottles, numDiapers, numRattles);

  printf("we have had a total of %d different customers\n", 
  num_customers);

  sumObjects();
}

void purchaseError(int boolean, String* s){
  switch(boolean){
    case 0: printf("Sorry ");
            StringPrint(s);
            printf(" we only have %d Bottles\n", numBottles);
    break;

    case 1: printf("Sorry ");  
            StringPrint(s);
            printf(" we only have %d Diapers\n", numDiapers);
    break;

    case 2: printf("Sorry ");
            StringPrint(s);
            printf(" we only have %d Rattles\n", numRattles);
    break;

    default: 
    break;

  }
}


void processPurchase() {
  String CustomerName;
  String itemName;
  int purchase;
  int confirmName;

  readString(&CustomerName);
  readString(&itemName);
  readNum(&purchase);

  confirmName = checkItemName(&itemName);
  StringDestroy(&itemName);

  int customerIndex = findCustomer(&CustomerName);
  if(purchase < 0){
    StringDestroy(&CustomerName);
    return;
  }

  if(confirmName == 0 && purchase > numBottles){
    purchaseError(confirmName, &CustomerName);
    StringDestroy(&CustomerName);
    return;
  }


  else if(confirmName == 1 && purchase > numDiapers){
    purchaseError(confirmName, &CustomerName);
    StringDestroy(&CustomerName);
    return;
  }


  else if(confirmName == 2 && purchase > numRattles){
    purchaseError(confirmName, &CustomerName);
    StringDestroy(&CustomerName);
    return;
  }


  // new customer
  if(customerIndex == -1){
    num_customers += 1;
    // add customer to the end of the struct customers
    customerIndex = num_customers - 1;
    customers[customerIndex].name = CustomerName;
  }else 
    StringDestroy(&CustomerName); // customer already exists in struct
  
  switch(confirmName){
    case 0: customers[customerIndex].bottles += purchase;
            numBottles -= purchase;
            break;
    case 1: customers[customerIndex].diapers += purchase;
            numDiapers -= purchase;
            break;
    case 2: customers[customerIndex].rattles += purchase;
            numRattles -= purchase;
            break;
    default: printf("Error\n");
             break;
  }
}

void processInventory() {
  String itemName;
  int newStock;
  int cmp;

  readString(&itemName);
  readNum(&newStock);
  if(newStock < 0){
    StringDestroy(&itemName);
    return;
  }
  cmp = checkItemName(&itemName);
  switch(cmp){
    case 0: numBottles += newStock;
            break;
    case 1: numDiapers += newStock;
            break;
    case 2: numRattles += newStock;
            break;
    default: printf("Not a valid item to stock\n");
             break;      
  }
  StringDestroy(&itemName);
}
