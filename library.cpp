#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <direct.h>  
using namespace std;

struct Book {
    int id;
    string title;
    string author;
    int year;
    int quantity;
};

void displayMenu();
void addNewBook();
void viewAllBooks();
void searchAndBorrow();
void returnBook();
void saveAndExit();
int getCurrentYear();
bool isBookIdUnique(int id);
int countBooks();

int main() {
    int choice;
    
    cout << "Library Management System";
    cout << "Student: Javlonbek";
    
    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error! Please enter numbers only";
            continue;
        }
        
        cout << "\n";
        
        switch (choice) {
            case 1:
                addNewBook();
                break;
            case 2:
                viewAllBooks();
                break;
            case 3:
                searchAndBorrow();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                saveAndExit();
                return 0;
            default:
                cout << "Invalid ! Please enter a number between 1-5.";
        }
    }
    
    return 0;
}

void displayMenu() {
    cout << "MAIN MENU\n";
    cout << "1. Add New Book\n";
    cout << "2. View All Books\n";
    cout << "3. Search and Borrow Book\n";
    cout << "4. Return Book\n";
    cout << "5. Save and Exit\n\n";
}

int getCurrentYear() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return 1900 + ltm->tm_year;
}

bool isBookIdUnique(int id) {
    ifstream file("books.txt");
    if (!file.is_open()) {
        return true; 
    }
    
    Book b;
    while (file >> b.id >> ws) {
        getline(file, b.title, '|');
        getline(file, b.author, '|');
        file >> b.year >> b.quantity;
        
        if (b.id == id) {
            file.close();
            return false;
        }
    }
    
    file.close();
    return true;
}

int countBooks() {
    ifstream file("books.txt");
    if (!file.is_open()) return 0;
    
    int count = 0;
    Book b;
    while (file >> b.id >> ws) {
        getline(file, b.title, '|');
        getline(file, b.author, '|');
        file >> b.year >> b.quantity;
        count++;
    }
    
    file.close();
    return count;
}

void addNewBook() {
    Book newBook;
    
    cout << "ADD NEW BOOK";
    
    while (true) {
        cout << "Book ID: ";
        cin >> newBook.id;
        
        if (cin.fail() || newBook.id <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error! Please enter a positive number.";
            continue;
        }
        
        if (!isBookIdUnique(newBook.id)) {
            cout << "Error! This ID already exists. Please enter a different ID.";
            continue;
        }
        
        break;
    }
    
    cin.ignore(); 
    
    
    cout << "Book Title: ";
    getline(cin, newBook.title);
    
    cout << "Author: ";
    getline(cin, newBook.author);
    
    int currentYear = getCurrentYear();
    while (true) {
        cout << "Publication Year (1900-" << currentYear << "): ";
        cin >> newBook.year;
        
        if (cin.fail() || newBook.year < 1900 || newBook.year > currentYear) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error! Year must be between 1900 and " << currentYear << ".\n";
            continue;
        }
        
        break;
    }

    while (true) {
        cout << "Quantity: ";
        cin >> newBook.quantity;
        
        if (cin.fail() || newBook.quantity <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error! Please enter a positive number.\n";
            continue;
        }
        
        break;
    }
    
    ofstream file("books.txt", ios::app);
    if (!file.is_open()) {
        cout << "Error! Could not open file.";
        return;
    }
    
    file << newBook.id << " " << newBook.title << "|" 
         << newBook.author << "|" << newBook.year << " " 
         << newBook.quantity << "\n";
    
    file.close();
    
    cout << "\nBook added successfully!";
}

void viewAllBooks() {
    cout << "ALL BOOKS IN LIBRARY\n\n";
    
    ifstream file("books.txt");
    if (!file.is_open()) {
        cout << "No books found in the library.";
        return;
    }
    
    int count = countBooks();
    if (count == 0) {
        cout << "No books found in the library.";
        file.close();
        return;
    }
    
    cout << left << setw(8) << "ID" 
         << setw(30) << "Title" 
         << setw(20) << "Author"
         << setw(8) << "Year" 
         << setw(8) << "Qty" << "\n";
    cout << string(74, '-') << "\n";
    
    Book b;
    while (file >> b.id >> ws) {
        getline(file, b.title, '|');
        getline(file, b.author, '|');
        file >> b.year >> b.quantity;
        
        cout << left << setw(8) << b.id
             << setw(30) << b.title.substr(0, 28)
             << setw(20) << b.author.substr(0, 18)
             << setw(8) << b.year
             << setw(8) << b.quantity << "\n";
    }
    
    file.close();
    cout << "\nTotal books: " << count << "\n\n";
}

void searchAndBorrow() {
    cout << "SEARCH AND BORROW BOOK\n\n";
    
    int searchChoice;
    cout << "Search by:\n";
    cout << "1. Book ID\n";
    cout << "2. Book Title\n";
    cout << "Enter choice: ";
    cin >> searchChoice;
    cin.ignore();
    
    if (searchChoice != 1 && searchChoice != 2) {
        cout << "Invalid choice!\n\n";
        return;
    }
    
    ifstream file("books.txt");
    if (!file.is_open()) {
        cout << "No books found in the library.\n\n";
        return;
    }
    
    bool found = false;
    Book books[100];
    int bookCount = 0;
    int foundIndex = -1;
    
    while (file >> books[bookCount].id >> ws) {
        getline(file, books[bookCount].title, '|');
        getline(file, books[bookCount].author, '|');
        file >> books[bookCount].year >> books[bookCount].quantity;
        bookCount++;
    }
    file.close();
    
    if (searchChoice == 1) {
        int searchId;
        cout << "Enter Book ID: ";
        cin >> searchId;
        
        for (int i = 0; i < bookCount; i++) {
            if (books[i].id == searchId) {
                found = true;
                foundIndex = i;
                break;
            }
        }
    } else {
        string searchTitle;
        cout << "Enter Book Title: ";
        getline(cin, searchTitle);
        
        for (int i = 0; i < bookCount; i++) {
            if (books[i].title.find(searchTitle) != string::npos) {
                found = true;
                foundIndex = i;
                break;
            }
        }
    }
    
    if (!found) {
        cout << "\nBook not found!";
        return;
    }
  
    cout << "\nBook found:\n";
    cout << "ID: " << books[foundIndex].id << "\n";
    cout << "Title: " << books[foundIndex].title << "\n";
    cout << "Author: " << books[foundIndex].author << "\n";
    cout << "Year: " << books[foundIndex].year << "\n";
    cout << "Available Quantity: " << books[foundIndex].quantity << "\n\n";
    

    if (books[foundIndex].quantity <= 0) {
        cout << "Sorry, this book is currently not available.\n\n";
        return;
    }
    
    char borrowChoice;
    cout << "Do you want to borrow this book? (Y/N): ";
    cin >> borrowChoice;
    
    if (borrowChoice == 'Y' || borrowChoice == 'y') {
        books[foundIndex].quantity--;
        
       
        ofstream outFile("books.txt");
        for (int i = 0; i < bookCount; i++) {
            outFile << books[i].id << " " << books[i].title << "|" 
                   << books[i].author << "|" << books[i].year << " " 
                   << books[i].quantity << "\n";
        }
        outFile.close();
        
        cout << "\nBook borrowed successfully! Remaining quantity: " 
             << books[foundIndex].quantity << "\n\n";
    } else {
        cout << "\nBorrow cancelled.\n\n";
    }
}

void returnBook() {
    cout << "RETURN BOOK\n\n";
    
    int returnId;
    cout << "Enter Book ID to return: ";
    cin >> returnId;
    
    ifstream file("books.txt");
    if (!file.is_open()) {
        cout << "No books found in the library.\n\n";
        return;
    }
    
    bool found = false;
    Book books[100];
    int bookCount = 0;
    int foundIndex = -1;
    
    while (file >> books[bookCount].id >> ws) {
        getline(file, books[bookCount].title, '|');
        getline(file, books[bookCount].author, '|');
        file >> books[bookCount].year >> books[bookCount].quantity;
        
        if (books[bookCount].id == returnId) {
            found = true;
            foundIndex = bookCount;
        }
        
        bookCount++;
    }
    file.close();
    
    if (!found) {
        cout << "\nBook not found!\n\n";
        return;
    }
    
    books[foundIndex].quantity++;
    
    ofstream outFile("books.txt");
    for (int i = 0; i < bookCount; i++) {
        outFile << books[i].id << " " << books[i].title << "|" 
               << books[i].author << "|" << books[i].year << " " 
               << books[i].quantity << "\n";
    }
    outFile.close();
    
    cout << "\nBook returned successfully! New quantity: " 
         << books[foundIndex].quantity << "\n\n";
}

void saveAndExit() {
    cout << "SAVE AND EXIT\n\n";
    
    _mkdir("saved_data");
    
    ifstream source("books.txt");
    ofstream dest("saved_data/backup.txt");
    
    if (source.is_open() && dest.is_open()) {
        string line;
        while (getline(source, line)) {
            dest << line << "\n";
        }
        source.close();
        dest.close();
        cout << "Library data saved successfully. Goodbye!\n";
    } else {
        cout << "Warning: Could not create backup file.\n";
        cout << "Goodbye!";
    }
}