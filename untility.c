#include "contact.h"

// validate if entered struct of data, is according to contraints
int validation(Contact *data)
{
    // validate name
    for (int i = 0; i < strlen(data->name); i++)
    {
        if (!(data->name[i] >= 'a' && data->name[i] <= 'z' || data->name[i] >= 'A' && data->name[i] <= 'Z' || data->name[i] == ' '))
        {
            printf("\033[0;31m"); // color red
            printf("\nWarning!\nPlease enter valid name!\n");
            printf("\033[0m"); // reset

            return 0;
        }
    }

    // validate phone
    if (strlen(data->phone) != 10)
    {
        printf("\033[0;31m"); // color red
        printf("\nWarning!\nPlease enter 10 digits phone no.\n");
        printf("\033[0m"); // reset

        return 0;
    }
    else
    {
        for (int i = 0; i < strlen(data->phone); i++)
        {
            if (data->phone[i] < '0' || data->phone[i] > '9')
            {
                printf("\033[0;31m"); // color red
                printf("\nWarning!\nPlease enter valid phone no.!\n");
                printf("\033[0m"); // reset

                return 0;
            }
        }
    }

    // validate email
    // 1st check it should have @gmail.com at end
    // 2nd check capital letter and symbol except [@ .] and digit, if present not valid
    if (strstr(data->email, "@gmail.com"))
    {
        for (int i = 1; i < strlen(data->email); i++)
        {   
            if(i==0){  //if 1st char is other than alpha
                if ((data->email[i] >= 'a' && data->email[i] <= 'z' || data->email[i] >= 'A' && data->email[i] <= 'Z')==0){
                    printf("\033[0;31m"); // color red
                    printf("\nWarning!\nPlease enter valid email!\n");
                    printf("\033[0m"); // reset
                    return 0;
                }
            }
            if ((data->email[i] >= 'a' && data->email[i] <= 'z' || data->email[i] == '@' || data->email[i] == '.' || data->email[i] >= '0' && data->email[i] <= '9') == 0)
            {
                printf("\033[0;31m"); // color red
                printf("\nWarning!\nPlease enter valid email!\n");
                printf("\033[0m"); // reset
                return 0;
            }
        }
    }
    else{
        printf("\033[0;31m"); // color red
        printf("\nWarning!\nPlease enter valid email!\n");
        printf("\033[0m"); // reset

        return 0;
    }
    return 1;
}

// compare 2 strings , case insensitive

int str_str( char s1[],  char s2[])
{    int len1 = strlen(s1);
     int len2 = strlen(s2);
    if (len2 > len1)
        return -1; // If s2 is longer, it can't be a substring

    for (int i = 0; i <= len1 - len2; i++)
    {
        int found = 1; 

        for (int j = 0; j < len2; j++)
        {
            if (tolower(s1[i + j]) != tolower(s2[j]))
            {
                found = 0; // Mismatch found
                break;
            }
        }

        if (found)
            return i; // Return starting index of match
    }

    return -1; // No match found
}

//printf contact for specific index and highlight that option(name,email,phone) from a TO b
void print_contact(int sr, int idx,int option, int a, int b, AddressBook *addressBook)
{    //sort list 
    sortList(addressBook);

    if (sr == 1)
        printf("\n\nSR NO.\tNAME\t\tMOBILE NO.\tEMAIL\n----------------------------------------------------------\n");
   
    //If both are given 
    if(option==1){
       //(staring index is passed with + 1, to fix 0th index condi) if (option == 1)
        {
            printf("%-5d\t", sr);
            for (int i = 0; i < strlen(addressBook->contacts[idx].name); i++)
            {
                if (i >= a && i <= b)
                {
                    printf("\033[0;31m");
                    printf("%c", addressBook->contacts[idx].name[i]);
                    printf("\033[0m");
                }
                else
                    printf("%c", addressBook->contacts[idx].name[i]);
            }
            printf("\t%-10s\t%-10s\n", addressBook->contacts[idx].phone, addressBook->contacts[idx].email);
        }
    }
       else if (option == 3)
       {
           printf("%-5d\t%-10s\t", sr,addressBook->contacts[idx].name);
           for (int i = 0; i < strlen(addressBook->contacts[idx].phone); i++)
           {
               if (i >= a && i <= b)
               {
                printf("\033[0;31m");
                printf("%c", addressBook->contacts[idx].phone[i]);
                printf("\033[0m");
               }
               else
                   printf("%c", addressBook->contacts[idx].phone[i]);
           }
           printf("\t%-10s\n", addressBook->contacts[idx].email);
       }
      else if (option == 2)
       {
           printf("%-5d\t%-10s\t%-10s\t", sr, addressBook->contacts[idx].name,addressBook->contacts[idx].phone);
           for (int i = 0; i < strlen(addressBook->contacts[idx].email); i++)
           {
               if (i >= a && i <= b)
               {
                printf("\033[0;31m");
                printf("%c", addressBook->contacts[idx].email[i]);
                printf("\033[0m");
               }
               else
                   printf("%c", addressBook->contacts[idx].email[i]);
           }
           printf("\n");
       }
    else
    printf("%-5d\t%-10s\t%-10s\t%-10s\n", sr, addressBook->contacts[idx].name, addressBook->contacts[idx].phone, addressBook->contacts[idx].email);
}

int search_by(int by,char str[], AddressBook*addressBook){
            if(by==1) {   //by = 1 means name
                for(int i=0;i<addressBook->contactCount;i++){
                if(str_str(addressBook->contacts[i].name,str)!=-1&&(strlen(addressBook->contacts[i].name)==strlen(str))){
                    return 1;
                 }
                }
                return 0;
             }
             else if (by == 2)
             { // by = 2 means email
                 for (int i = 0; i < addressBook->contactCount; i++)
                 {
                     if (strcmp(addressBook->contacts[i].email, str) )
                     {
                         return 1;
                     }
                 }
                 return 0;
             }
             else if (by == 3)
             { // by = 3 means phone
                 for (int i = 0; i < addressBook->contactCount; i++)
                 {
                     if (strcmp(addressBook->contacts[i].phone, str) )
                     {
                         return 1;
                     }
                 }return 0;
             }
}

int isValid_email(char email[]){
    if (strstr(email, "@gmail.com"))
    {
        for (int i = 1; i < strlen(email); i++)
        {
            if ((email[i] >= 'a' && email[i] <= 'z' || email[i] == '@' || email[i] == '.' || email[i] >= '0' && email[i] <= '9') == 0)
            {
                printf("\033[0;31m"); // color red
                printf("\nWarning!\nPlease enter valid email!\n");
                printf("\033[0m"); // reset
                return 0;
            }
        }
    }
    else
    {
        printf("\033[0;31m"); // color red
        printf("\nWarning!\nPlease enter valid email!\n");
        printf("\033[0m"); // reset
        return 0;
    }
    return 1;
}

int isValid_name(char name[]){
    // validate name
    for (int i = 0; i < strlen(name); i++)
    {
        if (!(name[i] >= 'a' && name[i] <= 'z' || name[i] >= 'A' && name[i] <= 'Z' || name[i] == ' ' && name[0]!=' '))
        {
            printf("\033[0;31m"); // color red
            printf("Warning!\nPlease enter valid name!\n");
            printf("\033[0m"); // reset
            return 0;
        }
    }
}

int isValid_phone(char phone[]){
    // validate phone
    if (strlen(phone) != 10)
    {
        printf("\033[0;31m"); // color red
        printf("Warning!\nPlease enter 10 digits phone no.\n");
        printf("\033[0m"); // reset
        return 0;
    }
    else
    {

        for (int i = 0; i < strlen(phone); i++)
        {
            if (phone[i] < '0' || phone[i] > '9')
            {
                printf("\033[0;31m"); // color red
                printf("Warning!\nPlease enter valid phone no.!\n");
                printf("\033[0m"); // reset
                return 0;
            }
        }
    }
}

//search using options and tell wethear found or not
int option_search(AddressBook *addressBook, char search_user[],int*found)
{
    // Options for search
    printf("\n----------------------------------------\n|  1.Name  |  2.Email  |  3.Phone No.  |\n----------------------------------------\nSearch using above option : ");
    int option;
    printf("\033[0;33m"); //color yellow 
    scanf("%d", &option);
    printf("\033[0m");  //reset
    printf("\n");

    if (option == 1)
        printf("Please enter name: ");
    else if (option == 2)
        printf("Please enter email: ");
    else
        printf("Please enter phone no. :");

    printf("\033[0;33m");  //color yellow
    scanf(" %[^\n]", search_user);
    printf("\033[0m"); // reset

    // finding search_user in addressbook with matching
 
    int sr = 1;
    for (int i = 0; i < addressBook->contactCount; i++)
    {

        if (option == 1 && str_str(addressBook->contacts[i].name, search_user)!=-1)
        {
            print_contact(sr++, i, option, str_str(addressBook->contacts[i].name, search_user), str_str(addressBook->contacts[i].name, search_user) + strlen(search_user) - 1, addressBook);
            *found = 1;
        }
        else if (option == 2 && str_str(addressBook->contacts[i].email, search_user)!=-1)
        {
            print_contact(sr++, i, option, str_str(addressBook->contacts[i].email, search_user), str_str(addressBook->contacts[i].email, search_user)+strlen(search_user)-1, addressBook);
            *found = 1;
        }
        else if (option == 3 && str_str(addressBook->contacts[i].phone, search_user)!=-1)
        {
            print_contact(sr++, i, option, str_str(addressBook->contacts[i].phone, search_user), str_str(addressBook->contacts[i].phone, search_user)+strlen(search_user)-1, addressBook);
            *found = 1;
        }
    }
}

int get_idx_fr_serial(AddressBook*addressBook,char search_user[]){
    int serial, finalIdx = 1;
    printf("\nPlease enter S.no: ");
    scanf("%d", &serial);
    printf("\n");
    int i = 0;
    while (i < addressBook->contactCount)
    {
        if (str_str(addressBook->contacts[i].name, search_user)!=-1)
        {
            if (serial == 0)
                break;
            finalIdx = i;
            serial--;
        }
        i++;
    }
    return finalIdx;
}

void header(){
    printf("\n----------------------------------------------------------\n");
    printf("\033[1;34m");
    printf("\t\t\tADDRESSBOOK\t\t");
    printf("\033[0m");
    printf("\n----------------------------------------------------------\n");
    printf("\033[1;34m1\033[0m.List Contacts\n\033[1;34m2\033[0m.Search Contact\n\033[1;34m3\033[0m.Create Contact\n\033[1;34m4\033[0m.Edit Contact\n\033[1;34m5\033[0m.Delete Contact\n\033[1;34m6\033[0m.Save Contacts\n\033[1;34m7\033[0m.Exit\n\n");
}

void sortList(AddressBook*addressBook){
    int n = addressBook->contactCount;
    for (int i = 1; i < n; i++)
    {   
        for (int j = 0; j < n - i; j++)
        {    //make all name's starting char in upper case.
            addressBook->contacts[j].name[0] = toupper(addressBook->contacts[j].name[0]);
            addressBook->contacts[j + 1].name[0] = toupper(addressBook->contacts[j + 1].name[0]);

            if (addressBook->contacts[j].name[0] > addressBook->contacts[j + 1].name[0])
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
}