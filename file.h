// Header guard to prevent multiple inclusions

#ifndef FILE_H
#define FILE_H
// Include the contact.h header file for AddressBook definition 
#include "contact.h"
// Function prototypes for file operations
void saveContacts(AddressBook *addressBook);      // For saving contacts to CSV
void loadContacts(AddressBook *addressBook);

#endif
