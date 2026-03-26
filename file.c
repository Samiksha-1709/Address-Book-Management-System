//header files
/*
->This file handles file operations for the Address Book.
->It includes functions to save contacts to a CSV file and load contacts from the file.
->Contact details are stored in "contacts.csv" in a comma-separated format (name, phone, email).
->While saving, all contacts are written to the file.
-> While loading, data is read from the file and stored into the address book structure.
->If the file is not present, an empty contact list is used.
*/
#include <stdio.h>
#include <string.h>
#include "file.h"
#include "contact.h"
// Function to save contacts to a CSV file
void saveContacts(AddressBook *addressBook) 
{
    //open file in write mode
    FILE *file = fopen("contacts.csv", "w");
    //check if file opened successfully
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    //write each contact to file
    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(file, "%s,%s,%s\n", 
                addressBook->contacts[i].name, 
                addressBook->contacts[i].phone, 
                addressBook->contacts[i].email);
    }
//close file
    fclose(file);
    //confirmation message
    printf("Contacts saved successfully to contacts.csv\n");
}

// Function to load contacts from a CSV file
void loadContacts(AddressBook *addressBook)
{ 
    //initialize contact count to 0
    addressBook->contactCount = 0;
//open file in read mode    
    FILE *fp = fopen("contacts.csv", "r");
    if (fp != NULL)
    {
        //read each line and parse contact details
        char line[200];
        while (fscanf(fp, " %[^\n]", line) == 1)
        {
            //parse line using strtok
            char *token = strtok(line, ",");
            if (token) strcpy(addressBook->contacts[addressBook->contactCount].name, token);

            token = strtok(NULL, ",");
            if (token) strcpy(addressBook->contacts[addressBook->contactCount].phone, token);

            token = strtok(NULL, ",");
            if (token) strcpy(addressBook->contacts[addressBook->contactCount].email, token);

            addressBook->contactCount++;

            if (addressBook->contactCount >= MAX_CONTACTS) 
                break;
        }
        //close file
        fclose(fp);
        //confirmation message
        printf("Contacts loaded successfully from contacts.csv\n");
    }
    //if file does not exist, start with empty contact list
    else
    {
        //file does not exist
        printf("No contacts.csv found. Starting with empty contact list.\n");
    }
}
