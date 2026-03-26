# 📒 Address Book Application in C

## 🔍 Overview

The Address Book Application is a console-based project developed in C to manage contact details efficiently. It allows users to store, retrieve, update, and delete contact information such as name, phone number, and email. The project demonstrates the use of fundamental programming concepts and simulates a real-world contact management system.

---

## 🎯 Objective

The main objective of this project is to understand how data can be managed using structures and file handling in C. It also focuses on implementing real-time operations like search, edit, and delete in a structured manner.

---

## ✨ Features

* ➕ Add new contacts with validation
* 📋 Display all saved contacts in tabular format
* 🔍 Search contacts by name (partial match), phone number, or email
* ✏️ Edit existing contact details
* ❌ Delete contacts with confirmation
* 💾 Save contacts to a file (CSV format)
* 📂 Load contacts from file on program start
* 🔐 Validation for name, phone number, and email
* 🚫 Prevent duplicate phone numbers and emails

---

## 🛠️ Technologies Used

* **Language:** C
* **Concepts:**

  * Structures
  * Arrays
  * File Handling
  * String 

---

## 🧠 Key Concepts Implemented

* Use of `struct` to represent contact data
* File operations using `fopen`, `fprintf`, `fscanf`
* Input handling using `fgets()` to avoid buffer issues
* Data validation and error handling
* Case-insensitive and partial search implementation

---

## 📁 Project Structure

AddressBook/
│── contact.c        // Core logic (create, search, edit, delete)
│── file.c           // File handling (save & load contacts)
│── populate.c       // Dummy data initialization
│── contact.h
│── file.h
│── populate.h
│── main.c
│── contacts.csv     // Stored contact data

---

## ▶️ How to Run

1. Compile the program:
   gcc *.c

2. Run the executable:
   ./addressbook

3. Follow menu options to perform operations

---

## 🎓 Training

This project was developed as part of training at **Emertxe Information Technologies, Bengaluru**, where practical exposure to C programming, data structures, and real-time project development was gained.

---

## 🚀 Future Enhancements

* Add GUI interface
* Store data using database (MySQL)
* Add sorting functionality
* Improve email validation
* Export contacts to different formats

---

## 👩‍💻 Author

**Samiksha Mane**
B.Tech Electronics & Telecommunication Engineering

---

## 📎 Conclusion

This project provides a strong foundation in C programming by combining data structures, file handling, and real-world problem-solving. It enhances logical thinking and prepares for system-level programming concepts.
