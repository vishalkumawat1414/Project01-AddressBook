#include "contact.h"
#include <stdlib.h>

int main() {

    AddressBook addressbook;
    
    initialize(&addressbook);
    while (1)
    {
        int option;
        header();

        printf("Select the option given above: ");
        
        printf("\033[0;33m"); // color yellow
        scanf("%d",&option);
        printf("\033[0m"); // reset

        switch (option)
        { 
            case 1:
                listContacts(&addressbook);
                break;
            case 2:
                searchContact(&addressbook);
                break;
            case 3:
                createContact(&addressbook);
                break;
            case 4:
                editContact(&addressbook);
                break;
            case 5:
                deleteContact(&addressbook);
                break;
            case 6:
                 saveContacts(&addressbook);
                 break;
            case 7:
                exit(0);
    }
    }
}
