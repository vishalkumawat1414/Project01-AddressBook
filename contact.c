#include "contact.h"

void initialize(AddressBook *addressBook)
{
    FILE *fp = fopen("Contacts.txt", "r");
    char fname[50];
    char fphone[20];
    char femail[50];

    // no. of line in contacts.txt
    int lines = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '.')
            lines++;
    }
    fseek(fp, 0, SEEK_SET);

    addressBook->contactCount = 0;
    for (int i = 0; i < lines; i++)
    {
        fscanf(fp, "%[^,],%[^,],%[^\n]\n", fname, fphone, femail);
        strcpy(addressBook->contacts[i].name, fname);
        strcpy(addressBook->contacts[i].phone, fphone);
        strcpy(addressBook->contacts[i].email, femail);
        addressBook->contactCount++;
    }
    fclose(fp);
}

void listContacts(AddressBook *addressBook)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        print_contact(i + 1, i, 0, 0, 0, addressBook);
    }
}

void createContact(AddressBook *addressBook)
{
    Contact data;
    // getting user data

    printf("Please enter new member's data\n");
    printf("Enter name: ");
    printf("\033[0;33m");
    scanf(" %[^\n]", data.name);
    if (!isValid_name(data.name))
        return;
    printf("\033[0m");

    printf("Enter phone: ");
    printf("\033[0;33m");
    scanf(" %[^\n]", data.phone);
    if (!isValid_phone(data.phone))
        return;
    printf("\033[0m");

    printf("Enter email: ");
    printf("\033[0;33m");
    scanf(" %[^\n]", data.email);
    if (!isValid_email(data.email))
        return;
    printf("\033[0m");

    // check if user's name,phone,email already present
    int found = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (str_str(addressBook->contacts[i].name, data.name) != -1 && strlen(addressBook->contacts[i].name) == strlen(data.name))
        {
            found = 1;
            printf("\033[0;31m");
            printf("Warning!\nUser already present.\n");
            printf("\033[0m");
            break;
        }
        else if (strcmp(addressBook->contacts[i].phone, data.phone) == 0)
        {
            found = 1;
            printf("\033[0;31m");
            printf("Warning!\nPhone no. already present!\n\n");
            printf("\033[0m");
            break;
        }
        else if (strcmp(addressBook->contacts[i].email, data.email) == 0)
        {
            found = 1;
            printf("\033[0;31m");
            printf("Warning!\nEmail already present!\n\n");
            printf("\033[0m");
            break;
        }
    }
    // after checking in entire list
    if (found == 0)
    {
        // user not found =>add
        addressBook->contacts[addressBook->contactCount] = data;
        addressBook->contactCount++;
        printf("\033[0;32m");
        printf("\nUser added successfully!!\n\n");
        printf("\033[0m");
    }
}

void searchContact(AddressBook *addressBook)
{ // Options for search
    int found = 0;
    char search_user[50];

    // create options and search
    option_search(addressBook, search_user, &found);

    if (found == 0)
    {
        printf("\033[0;31m");
        printf("\nUser not found!\n");
        printf("\033[0m");
    }
}

void editContact(AddressBook *addressBook)
{
    int found = 0;
    char search_user[50];

    // create options and search
    option_search(addressBook, search_user, &found);

    if (found)
    {
        // get serial no. for search
        int finalIdx = get_idx_fr_serial(addressBook, search_user);

        // printing the final name
        print_contact(1, finalIdx, 0, 0, 0, addressBook);

        // edit options
        printf("\n----------------------------------------\n|  1.Name  |  2.Email  |  3.Phone No.  |\n----------------------------------------\n");
        printf("Select what to edit: ");
        int option;
        scanf("%d", &option);

        int interation = 1;
        while (interation--)
        {

            if (option == 1)
            {
                printf("Enter new name: ");
                char new_name[50];
                printf("\033[0;33m");
                scanf(" %50[^\n]", new_name);
                printf("\033[0m");

                // check if this new name already present
                if (search_by(1, new_name, addressBook))
                {
                    printf("\033[0;31m");
                    printf("Warning!\nUser already present.\n");
                    printf("\033[0m");
                    break;
                }

                if (isValid_name(new_name))
                {
                    strcpy(addressBook->contacts[finalIdx].name, new_name);
                    printf("\033[0;32m");
                    printf("\nEdited successfully!\n");
                    printf("\033[0m");
                    break;
                }
            }
            else if (option == 2)
            {
                printf("Enter new email: ");
                char new_email[50];
                printf("\033[0;33m");
                scanf(" %[^\n]", new_email);
                printf("\033[0m");

                // check if new_email already present
                if (search_by(1, new_email, addressBook))
                {
                    printf("\033[0;31m");
                    printf("Warning!\nUser already present.\n");
                    printf("\033[0m");
                    break;
                }
                // validation
                if (isValid_email(new_email))
                {
                    strcpy(addressBook->contacts[finalIdx].email, new_email);
                    printf("\033[0;32m");
                    printf("\nEdited successfully!\n");
                    printf("\033[0m");
                    break;
                }
            }
            else if (option == 3)
            {
                printf("Enter new phone no.: ");
                char new_phone[20];
                printf("\033[0;33m");
                scanf(" %[^\n]", new_phone);
                printf("\033[0m");

                // check new_phone already there
                if (search_by(1, new_phone, addressBook))
                {
                    printf("\033[0;31m");
                    printf("Warning!\nUser already present.\n");
                    printf("\033[0m");
                    break;
                }
                if (isValid_phone)
                {
                    strcpy(addressBook->contacts[finalIdx].phone, new_phone);
                    printf("\033[0;32m");
                    printf("\nEdited successfully!\n");
                    printf("\033[0m");
                    break;
                }
            }
            if (interation == 0)
            {
                char conti;
                printf("\033[0;31m");
                printf("Do u want to continue (y/n): ");
                printf("\033[0m");
                printf("\033[0;33m"); // yello clr
                scanf(" %c", &conti);
                printf("\033[0m");
                if (conti == 'y' || conti == 'Y')
                    interation = 1;
                else
                    break;
            }
        }
    }
    else
    {
        printf("\033[0;31m");
        printf("\nUser not found!\n");
        printf("\033[0m");
    }
}

void deleteContact(AddressBook *addressBook)
{
    // Options for search
    int found = 0;
    char search_user[50];

    // create options and search
    option_search(addressBook, search_user, &found);

    if (found)
    {
        // get serial no. for search
        int finalIdx = get_idx_fr_serial(addressBook, search_user);
        // printing the final name
        print_contact(1, finalIdx, 0, 0, 0, addressBook);

        printf("\033[0;31m"); // color red
        printf("\nDo you want to continue \033[0;31m y/n\033[0m? ");
        printf("\033[0m"); // color red

        char c;
        getchar();
        printf("\033[0;33m");
        scanf("%c", &c);
        printf("\033[0m");
        if (c != 'y')
            return;
        // 2case : 1st target idx is last in list , 2nd in mid or at first
        //  for 2nd case we have to swap all right elements
        addressBook->contacts[finalIdx].name[0] = '\0';
        addressBook->contacts[finalIdx].phone[0] = '\0';
        addressBook->contacts[finalIdx].email[0] = '\0';

        if (finalIdx < addressBook->contactCount)
        {
            // swaping
            for (int i = finalIdx + 1; i < addressBook->contactCount; i++)
            {
                addressBook->contacts[i - 1] = addressBook->contacts[i];
            }
        }
        // reduce list size
        addressBook->contactCount--;
        printf("\033[0;32m");
        printf("\nDeleted Successfully!\n");
        printf("\033[0m");
    }
}

void saveContacts(AddressBook *addressBook)
{

    char conti;
    printf("\033[0;31m");
    printf("Do you want to save changes (y/n): ");
    printf("\033[0m");
    printf("\033[0;33m"); // yello clr
    scanf(" %c", &conti);
    printf("\033[0m");
    if (conti == 'y' || conti == 'Y')
    {

        FILE *fp = fopen("Contacts.txt", "w");
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            fprintf(fp, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
        printf("\033[0;32m");
        printf("\nContacts saved Successfully!\n");
        printf("\033[0m");
        fclose(fp);
    }
    else
        return;
}
