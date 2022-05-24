// CRM in C++ Project7.cpp
// EE 312 Project 7 submission by
// Ken Zhang
// ktz85
// Slip days used: 1 (technically 2/3)
// Fall 2021

#include <stdio.h>
#include "UTString.h"
#include "Customer.h"
#include "CustomerDB.h"
#include <iostream>


void readString(UTString&);
void readNum(int&);

CustomerDB database;

int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;

/* clear the inventory and reset the customer database to empty */
void reset(void) {
    database.clear();
    num_bottles = 0;
    num_rattles = 0;
    num_diapers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Bottles", "Diapers" or "Rattles"
 * for example the expression *selectInventItem("Bottles") returns the
 * current global variable for the number of bottls in the inventory
 */
int* selectInventItem(UTString word) {
    if (word == "Bottles") {
        return &num_bottles;
    } else if (word == "Diapers") {
        return &num_diapers;
    } else if (word == "Rattles") {
        return &num_rattles;
    }

    /* NOT REACHED */
    return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above, however
 * this overload takes a Customer as a second argument and selects the data member
 * of that Customer that matches "word". The function returns a pointer to one of the three data
 * members from the specified customer.
 */
int* selectInventItem(UTString word, Customer& cust) {
    if (word == "Bottles") {
        return &cust.bottles;
    } else if (word == "Diapers") {
        return &cust.diapers;
    } else if (word == "Rattles") {
        return &cust.rattles;
    }

    /* NOT REACHED */
    return 0;
}

/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Bottles", "Rattles" or "Diapers".
 *
 * Note: if two or more Customers are tied for having purchased the most of that item type
 * then findMax returns the first Customer in the CustomerDB who has purchased that maximal
 * quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in the
 * CustomerDB, fundMax returns a null pointer (0)
 */
Customer* findMax(UTString type) {
    Customer* result = 0;
    int max = 0;
    for (int k = 0; k < database.size(); k += 1) {
        Customer& cust = database[k];
        int *p = selectInventItem(type, cust);
        if (*p > max) {
            max = *p;
            result = &cust;
        }
    }

    return result;
}

void processPurchase() {
  UTString customerName;
  UTString itemName;
  int purchase;

  readString(customerName);
  readString(itemName);
  readNum(purchase);

  if(purchase > 0){
    int* item = selectInventItem(itemName);
    if(*item < purchase){
      std::cout << "Sorry " << customerName.c_str() << " we only have " << *item << " " << itemName.c_str() << std::endl;
    }
    else{
      *item -= purchase;
      *selectInventItem(itemName, database[customerName]) += purchase;
    }
  }
}

void sumItems(UTString itemName){
  if(database.size() == 0)
    std::cout << "no one has purchased any " << itemName.c_str() << std::endl;
  else{
    Customer greatest = database[0];
    for(int x = 1; x < database.size(); x++){
      if(*selectInventItem(itemName, database[x]) > *selectInventItem(itemName, greatest))
        greatest = database[x];
    }
      if(*selectInventItem(itemName, greatest) == 0)
        std::cout << "no one has purchased any " << itemName.c_str() << std::endl;
      else
        std::cout << greatest.name.c_str() << " has purchased the most " << itemName.c_str() << " (" << *selectInventItem(itemName, greatest) << ")" << std::endl;
    
  }

}


void processSummarize() {
  std::cout << "there are " << num_bottles << " Bottles, "
  << num_diapers << " Diapers and " 
  << num_rattles << " Rattles in inventory" << std::endl;

  std::cout << "we have had a total of " << database.size() << " different customers" << std::endl;

  sumItems("Bottles");
  sumItems("Diapers");
  sumItems("Rattles");
}

void processInventory() {
    UTString itemName;
    int itemCount;
    readString(itemName);
    readNum(itemCount);
    if(itemCount >= 0){
      *selectInventItem(itemName) += itemCount;
    }
}
