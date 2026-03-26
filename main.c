/*
Name = Samiksha Mane
Date = 14 oct 2025
Description = Address Book Management System to perform various operations like create, edit, search, delete, list and save contacts.
*/

//header files
#include <stdio.h>
#include "contact.h"
#include "populate.h"
//#include "file.h"
int main()
{
    int choice;
    AddressBook s1;

   initialize(&s1); // Initialize the address book
    //populate_contact(&s1);// Populate with dummy contacts for testing
    loadContacts(&s1); //Loads saved data from file

   //menu driven program
    do{
    printf("\nAddress Book Menu:\n");
    printf("\n1.Create Contact");
    printf("\n2.Edit Contact");
    printf("\n3.Search Contact");
    printf("\n4.Delete Contact");
    printf("\n5.List Contact");
    printf("\n6.Save Contact");
    printf("\n7.Exit Contact\n");
    
    printf("\nEnter your Choice : ");

    scanf("%d",&choice);
     //case selection
    switch(choice)
    {
        //case 1 Create Contact
        case 1:
        printf("\nCreate Contact is Selected\n");
        createContact(&s1);
        break;
        //case 2 Edit Contact
        case 2:
        printf("\nEdit Contact is Selected\n");
        editContact(&s1);
        break;
        //case 3 Search Contact
        case 3:
        printf("\nSearch Contact is Selected\n");
        searchContact(&s1);
        break;

        case 4:
        printf("\nDelete Contact is Selected\n");
        deleteContact(&s1);
        break;
        //case 5 List Contact
        case 5:
        printf("\nList Contact is Selected\n");
        listContacts(&s1);
        break;
        //case 6 Save Contact
        case 6:
        printf("\nSave Contact is Selected\n");
        saveContacts(&s1);
        break;
        
        
        //case 7 Exit
        case 7:
        printf("\nExiting From Contact.....\n");
        break;
    //default case
        default:
        printf("\nInvalid Option!! \nPlease Select Option From 1 to 7\n");
        break;
    }
    //end of switch
}while( choice != 7);

    //all function calls should be inside the main 
}

