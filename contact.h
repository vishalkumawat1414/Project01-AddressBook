#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;


typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContacts(AddressBook*addressBook);

 // utility functions
// int validation(Contact *);
int str_str(char[], char[]);
void print_contact(int ,int,int,int,int, AddressBook *);
int search_by(int, char[], AddressBook*);  // pass 1 for name based search, 2 for email,3 for phone
int isValid_email(char []);
int isValid_phone(char []);
int isValid_name(char []);
int option_search(AddressBook *, char [], int *); //creates options for search, read input , search and list
int get_idx_fr_serial(AddressBook *, char []);  //get the exact index of contact from list
void header(void);
void sortList(AddressBook*);
#endif
