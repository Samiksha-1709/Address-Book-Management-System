
// Header guard to prevent multiple inclusions
#ifndef CONTACT_H
#define CONTACT_H
// Maximum number of contacts in the address book
#define MAX_CONTACTS 100
// Include necessary standard libraries
#include <stdio.h>
#include <string.h>

// Define the Contact structure
typedef struct {
    char name[100];
    char phone[100];
    char email[100];
} Contact;

// Define the AddressBook structure
typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

// Function prototypes for address book operations
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContacts(AddressBook *addressBook);
void loadContacts(AddressBook *addressBook);

#endif
