
/*
->This file contains predefined dummy contact data.
->It is used to populate the address book with sample contacts.
->The populate_contact function copies these dummy contacts into the address book during initialization.
->This helps in testing and demonstrating the application without manually adding contacts.
*/

#include "contact.h"

// Dummy contact data
  static Contact dummyContacts[] = {
    {"John Doe", "1234567890", "john@example.com"},
    {"Alice Smith", "0987654321", "alice@example.com"},
    {"Bob Johnson", "1112223333", "bob@company.com"},
    {"Carol White", "4445556666", "carol@company.com"},
    {"David Brown", "7778889999", "david@example.com"},
    {"Eve Davis", "6665554444", "eve@example.com"},
    {"Frank Miller", "3334445555", "frank@example.com"},
    {"Grace Wilson", "2223334444", "grace@example.com"},
    {"Hannah Clark", "5556667777", "hannah@example.com"},
    {"Ian Lewis", "8889990000", "ian@example.com"}
   };

// Populate address book with dummy contacts
   void populate_contact(AddressBook *addressBook)
   {
    //copy dummy contacts to address book
    addressBook->contactCount = 0;
    for(int i=0; i<10; i++)
    {
	addressBook->contacts[i]=dummyContacts[i];
  //increment contact count
	addressBook->contactCount++;
     }

   }

    
  
