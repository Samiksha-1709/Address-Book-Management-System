//header files
/*
->This file contains the main operations of the Address Book.
->It includes functions to initialize data, create new contacts,display all contacts, search contacts, edit contact details,and delete contacts.
->Validations are applied for name, phone number, and email.
->Duplicate phone numbers and emails are not allowed.
->Searching is supported using name (partial match), phone number, and email. 
->Editing and deletion are done after selecting the required contact.
-> Data is stored using structures and managed through arrays.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "contact.h"
#include "populate.h"
#include "file.h"
#include <ctype.h>

//list contacts
void listContacts(AddressBook *addressBook) 
{
    //check if there are no contacts
    if (addressBook->contactCount == 0) {
        printf("\nNo contacts found.\n");
        return;
    }

    printf("\n---------------------------------------------------------------");
    printf("\n| %-3s | %-20s | %-15s | %-25s |", "No", "Name", "Phone Number", "Email");
    printf("\n---------------------------------------------------------------");

    // print each contact
    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("\n| %-3d | %-20s | %-15s | %-25s |",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf("\n---------------------------------------------------------------\n");
}

//initialize address book
void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0; 
    populate_contact(addressBook);
}



//create contact
void createContact(AddressBook *addressBook) 
{
    //declare variables
    Contact newContact;
    int valid, unique,found;

    printf("-----------------------------------------------------\n");
    printf("\n         ENTER NEW CONTACT DETAILS\n");
    printf("-----------------------------------------------------\n");

    // ---------------- Name Validation ----------------
   
do {
    valid = 1;
    int i = 0;
    char ch;
   //ask for name
    printf("\nEnter name: ");

    // read until newline
    while ((ch = getchar()) != '\n' && ch != EOF) {
        // only allow alphabets and space
        if (!((ch >= 'a' && ch <= 'z') ||
              (ch >= 'A' && ch <= 'Z') ||
               ch == ' ')) {
            valid = 0;
        }
        newContact.name[i++] = ch;

        // stop if size exceeds
        if (i >= sizeof(newContact.name) - 1)
            break;
    }
    newContact.name[i] = '\0'; // terminate string
// check if valid
    if (!valid) {
        printf("Invalid name! Only letters and spaces allowed.\n");
    }

    if (i == 0) {
        valid = 0;
        printf("Name cannot be empty.\n");
    }

} while (!valid);


    // ---------------- Phone Number Validation ----------------
    do {
        valid = 1;
        unique = 1;
        found = 0;
        //ask for phone number
        printf("\nEnter Phone Number: ");
        fgets(newContact.phone, sizeof(newContact.phone), stdin);

        // remove newline
        int i = 0;
        while (newContact.phone[i] != '\0') {
            if (newContact.phone[i] == '\n') {
                newContact.phone[i] = '\0';
                break;
            }
            i++;
        }

        // digits check
        for (i = 0; newContact.phone[i] != '\0'; i++) {
            if (newContact.phone[i] < '0' || newContact.phone[i] > '9') {
                valid = 0;
                printf("Phone number must contain only digits.\n");
                break;
            }
        }

        // length check
        
        if (i != 10) {
            //if not 10 digits
            valid = 0;
            printf("Phone number must be 10 digits long.\n");
        }

        // uniqueness check
        for (i = 0; i < addressBook->contactCount; i++) {
            // check if phone numbers match
            if (strcmp(newContact.phone, addressBook->contacts[i].phone) == 0) {
                // not unique
                unique = 0;
                printf("Phone number already exists.\n");
                //print existing contact
                printf("\nName : %s \nPhone : %s \nemail : %s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                found = 1;
                break;
            }
        }

    } while (!valid || !unique);

    // ---------------- Email Validation ----------------
do {
    valid = 1;
    //ask for email
    printf("\nEnter Email: ");
    fgets(newContact.email, sizeof(newContact.email), stdin);

    // remove newline
    int i = 0;
    while (newContact.email[i] != '\0') {
        if (newContact.email[i] == '\n') {
            newContact.email[i] = '\0';
            break;
        }
        i++;
    }

    int atIndex = -1, dotIndex = -1;

    // find positions of '@' and ".com"
    for (i = 0; newContact.email[i] != '\0'; i++) {
        if (newContact.email[i] == '@' && atIndex == -1) {
            atIndex = i;
        }
        if (newContact.email[i] == '.' &&
            newContact.email[i + 1] == 'c' &&
            newContact.email[i + 2] == 'o' &&
            newContact.email[i + 3] == 'm') {
            dotIndex = i;
        }
    }

    // check for '@' and ".com"
    if (atIndex == -1 || dotIndex == -1) {
        valid = 0;
        //if either is missing
        printf("Invalid email! Must contain '@' and end with '.com'.\n");
        continue;
    }

    // '@' cannot be first or last, and ".com" must come after '@'
    if (atIndex == 0 || dotIndex < atIndex) {
        valid = 0;
        //if '@' is at start or ".com" is before '@'
        printf("Invalid email format! '@' cannot be at the start and must come before '.com'.\n");
        continue;
    }

    // check for duplicate email
    for (int j = 0; j < addressBook->contactCount; j++) {
        if (strcmp(addressBook->contacts[j].email, newContact.email) == 0) {
            //if duplicate email found
            valid = 0;
            printf("This email is already used by another contact!\n");
            break;
        }
    }

} while (!valid);

// ---------------- Save Contact ----------------
addressBook->contacts[addressBook->contactCount] = newContact;
addressBook->contactCount++;
//confirmation message
printf("\nContact created successfully!\n");
printf("-----------------------------------------------------\n");


}



// helper to convert string to lowercase
void toLowerCase(char str[]) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}
//search contact
void searchContact(AddressBook *addressBook) 
{
    //declare variables
    int choice;
    char input[100];
    int found = 0;

    printf("-----------------------------------------------------\n");
    printf("\nENTER YOUR CHOICE TO SEARCH CONTACT\n");
    printf("-----------------------------------------------------\n");
//search by name, phone or email
    printf("\nSearch By : \n1. Name\n2. Phone Number\n3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // clear leftover newline

    switch(choice)
    {
        //search by name
        case 1:
            printf("Enter Name to search: ");
            fgets(input, sizeof(input), stdin);

            // remove newline manually
            int i = 0;
            while (input[i] != '\0') {
                if (input[i] == '\n') {
                    input[i] = '\0';
                    break;
                }
                i++;
            }

            found = 0;
            char searchName[100];
            //copy input to searchName
            strcpy(searchName, input);
            
            toLowerCase(searchName);  // convert input to lowercase
             //search for partial match
            for(int j = 0; j < addressBook->contactCount; j++) {
                char contactName[100];
                //copy contact name to contactName
                strcpy(contactName, addressBook->contacts[j].name);
                toLowerCase(contactName);  // convert contact name to lowercase
                 //check if input is part of contact name
                if (strstr(contactName, searchName) != NULL) { // partial match
                    printf("-----------------------------------------------------\n");
                    //print matching contact
                    printf("\nContact Found:\n");
                    printf("Name: %s\n", addressBook->contacts[j].name);
                    printf("Phone: %s\n", addressBook->contacts[j].phone);
                    printf("Email: %s\n", addressBook->contacts[j].email);
                    printf("-----------------------------------------------------\n");
                    found = 1;
                }
            }
             //if no match found
            if(!found) {
                printf("-----------------------------------------------------\n");
                printf("\nNo contacts found matching '%s'.\n", input);
                printf("-----------------------------------------------------\n");
            }
            break;

        //search by phone number
        case 2:
            printf("Enter Phone Number to search: ");
            fgets(input, sizeof(input), stdin);

            // remove newline manually
            i = 0;
            while (input[i] != '\0') {
                if (input[i] == '\n') {
                    input[i] = '\0';
                    break;
                }
                i++;
            }
             //exact match for phone number
            found = 0;
            for(int j = 0; j < addressBook->contactCount; j++) {
                //check if phone numbers match
                if (strcmp(addressBook->contacts[j].phone, input) == 0) {
                    printf("-----------------------------------------------------\n");
                    //print matching contact
                    printf("\nContact Found:\n");
                    printf("Name: %s\n", addressBook->contacts[j].name);
                    printf("Phone: %s\n", addressBook->contacts[j].phone);
                    printf("Email: %s\n", addressBook->contacts[j].email);
                    printf("-----------------------------------------------------\n");
                    found = 1;
                    break;
                }
            }
            //if no match found
            if(!found) {
                printf("-----------------------------------------------------\n");
                printf("\nContact with phone number '%s' not found.\n", input);
                printf("-----------------------------------------------------\n");
            }
            break;
        //search by email
        case 3:
            printf("Enter Email to search: ");
            fgets(input, sizeof(input), stdin);

            // remove newline manually
            i = 0;
            while (input[i] != '\0') {
                if (input[i] == '\n') {
                    input[i] = '\0';
                    break;
                }
                i++;
            }
            //exact match for email
            found = 0;
            for(int j = 0; j < addressBook->contactCount; j++) {
                //check if emails match
                if (strcmp(addressBook->contacts[j].email, input) == 0) {
                    printf("-----------------------------------------------------\n");
                    //print matching contact
                    printf("\nContact Found:\n");
                    printf("Name: %s\n", addressBook->contacts[j].name);
                    printf("Phone: %s\n", addressBook->contacts[j].phone);
                    printf("Email: %s\n", addressBook->contacts[j].email);
                    printf("-----------------------------------------------------\n");
                    found = 1;
                    break;
                }
            }
            //if no match found
            if(!found) {
                printf("-----------------------------------------------------\n");
                printf("\nContact with email '%s' not found.\n", input);
                printf("-----------------------------------------------------\n");
            }
            break;

        default:
            printf("Invalid choice!\n");
    }
}


//edit contact
void editContact(AddressBook *addressBook) {
    int searchChoice, editChoice;
    char input[100], newValue[100];
    int flag = 0;

    printf("\n--------------------------------------");
    printf("\n     YOU ENTERED INTO EDIT CONTACT");
    printf("\n--------------------------------------\n");
    //ask how to search contact to edit
    printf("Search By:\n");
    printf("1. Name\n2. Phone number\n3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &searchChoice);
    getchar();  // clear enter key
    //ask for search input
    printf("Enter the ");
    if (searchChoice == 1) printf("name: ");
    else if (searchChoice == 2) printf("phone number: ");
    else if (searchChoice == 3) printf("email: ");
    else {
        printf("Invalid choice.\n");
        return;
    }

    fgets(input, sizeof(input), stdin);
    int k = 0;
    while (input[k] != '\0') {
        if (input[k] == '\n') {
            input[k] = '\0';
            break;
        }
        k++;
    }

    // Show all matching contacts first
    int matchIndexes[100];
    int matchCount = 0;

    for (int i = 0; i < addressBook->contactCount; i++) {
        int match = 0;

        // Case-insensitive partial match for name
        if (searchChoice == 1) {
            char nameLower[100], inputLower[100];
            // Copy contact name and input to lowercase buffers
            strcpy(nameLower, addressBook->contacts[i].name);
            //strcpy(inputLower, input);
            strcpy(inputLower, input);

            // Convert to lowercase
            for (int a = 0; nameLower[a]; a++)
                nameLower[a] = tolower(nameLower[a]);
            for (int a = 0; inputLower[a]; a++)
                inputLower[a] = tolower(inputLower[a]);

            // Check if input is part of the name
            if (strstr(nameLower, inputLower) != NULL)
                match = 1;
        }
        // Exact match for phone and email
        else if (searchChoice == 2 && strcmp(addressBook->contacts[i].phone, input) == 0)
            match = 1;
            
        else if (searchChoice == 3 && strcmp(addressBook->contacts[i].email, input) == 0)
            match = 1;
           //  if match found, print contact
        if (match) {
            printf("\n[%d] %s\t%s\t%s\n", matchCount + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            matchIndexes[matchCount++] = i;
            flag = 1;
        }
    }
  //if no match found
    if (!flag) {
        printf("\n----------------------------------");
        printf("\nContact not found.");
        printf("\n----------------------------------\n");
        return;
    }
  //    ask which contact to edit if multiple found
    int select;
    if (matchCount > 1) {
        printf("\nMultiple contacts found. Enter the number to edit: ");
        scanf("%d", &select);
        getchar();
        if (select < 1 || select > matchCount) {
            printf("Invalid selection.\n");
            return;
        }
    } else {
        select = 1;
    }
    // get actual index in address book
    int index = matchIndexes[select - 1];
  //ask which field to edit
    printf("\nYou want to edit:\n1. Name\n2. Phone Number\n3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &editChoice);
    getchar();
  //    ask for new value
    printf("Enter the new value: ");
    fgets(newValue, sizeof(newValue), stdin);
    int j = 0;
    while (newValue[j] != '\0') {
        if (newValue[j] == '\n') {
            newValue[j] = '\0';
            break;
        }
        j++;
    }
  //update the selected field
    if (editChoice == 1)
        strcpy(addressBook->contacts[index].name, newValue);
    else if (editChoice == 2)
        strcpy(addressBook->contacts[index].phone, newValue);
    else if (editChoice == 3)
        strcpy(addressBook->contacts[index].email, newValue);
    else {
        printf("Invalid field choice.\n");
        return;
    }
  //confirmation message
    printf("\n----------------------------------");
    printf("\nContact updated successfully!");
    printf("\n----------------------------------\n");
}


// delete contact
void deleteContact(AddressBook *addressBook) {
    char input[100];
    int foundIndexes[100];
    int foundCount = 0;

    printf("\n--------------------------------------");
    printf("\n     YOU ENTERED INTO DELETE CONTACT");
    printf("\n--------------------------------------\n");

    printf("Enter the name of the contact to delete: ");
    getchar(); // clear leftover newline
    fgets(input, sizeof(input), stdin);

    // remove newline manually
    int i = 0;
    while (input[i] != '\0') {
        if (input[i] == '\n') {
            input[i] = '\0';
            break;
        }
        i++;
    }

    // convert input to lowercase
    char inputLower[100];
    strcpy(inputLower, input);
    toLowerCase(inputLower);

    // find all contacts with matching name (case-insensitive)
    for (i = 0; i < addressBook->contactCount; i++) {
        char nameLower[100];
        strcpy(nameLower, addressBook->contacts[i].name);
        toLowerCase(nameLower);

        if (strstr(nameLower, inputLower) != NULL) { // partial match allowed
            foundIndexes[foundCount++] = i;
        }
    }

    if (foundCount == 0) {
        printf("\nNo contacts found matching '%s'.\n", input);
        return;
    }

    // show results
    printf("\n%-5s %-15s %-15s %-25s\n", "No.", "Name", "Phone Number", "Email");
    printf("---------------------------------------------------------------\n");
    for (i = 0; i < foundCount; i++) {
        int idx = foundIndexes[i];
        printf("%-5d %-15s %-15s %-25s\n",
               i + 1,
               addressBook->contacts[idx].name,
               addressBook->contacts[idx].phone,
               addressBook->contacts[idx].email);
    }

    // ask which one to delete
    int choice;
    printf("\nEnter the index of contact to delete: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > foundCount) {
        printf("Invalid choice!\n");
        return;
    }

    int del = foundIndexes[choice - 1];

    // confirm deletion
    char confirm;
    printf("\nYou selected:\n");
    printf("Name: %s, Phone: %s, Email: %s\n",
           addressBook->contacts[del].name,
           addressBook->contacts[del].phone,
           addressBook->contacts[del].email);
    printf("\nAre you sure you want to delete this contact (y/n)? ");
    getchar(); // clear leftover newline
    scanf("%c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        // shift contacts
        for (i = del; i < addressBook->contactCount - 1; i++) {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }
        addressBook->contactCount--;
        printf("\nContact deleted successfully.\n");
    } else {
        printf("\nDeletion cancelled.\n");
    }
}
/*void saveContacts(AddressBook *addressBook) 
{
    FILE *file = fopen("contacts.csv", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(file, "%s,%s,%s\n", 
                addressBook->contacts[i].name, 
                addressBook->contacts[i].phone, 
                addressBook->contacts[i].email);
    }

    fclose(file);
    printf("Contacts saved successfully to contacts.csv\n");
}
*/