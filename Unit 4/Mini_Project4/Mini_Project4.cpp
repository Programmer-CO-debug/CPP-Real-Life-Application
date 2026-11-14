#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

class Book {
public:
    string isbn, title, author, category;
    bool available;

    Book() : available(true) {}
    Book(string i, string t, string a, string c, bool status = true)
        : isbn(i), title(t), author(a), category(c), available(status) {}

    void display() const {
        cout << left << setw(15) << isbn
             << setw(25) << title.substr(0, 23)
             << setw(22) << author.substr(0, 20)
             << setw(16) << category.substr(0, 14)
             << (available ? "Available" : "Issued") << '\n';
    }
};

class Library {
private:
    vector<Book> books;
    const string filename = "library_books.txt";

    int findIndex(const string& isbn) const {
        for (size_t i = 0; i < books.size(); ++i)
            if (books[i].isbn == isbn) return static_cast<int>(i);
        return -1;
    }

    void saveToFile() const {
        ofstream file(filename);
        if (!file) {
            cerr << "Error: Could not open " << filename << " for writing.\n";
            return;
        }
        for (const Book& b : books)
            file << b.isbn << '|' << b.title << '|' << b.author << '|'
                 << b.category << '|' << (b.available ? 1 : 0) << '\n';
    }

    void loadFromFile() {
        ifstream file(filename);
        if (!file) return; // First run: the file will be created when a book is added.

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string isbn, title, author, category, status;
            if (getline(ss, isbn, '|') && getline(ss, title, '|') &&
                getline(ss, author, '|') && getline(ss, category, '|') &&
                getline(ss, status)) {
                books.emplace_back(isbn, title, author, category, status == "1");
            }
        }
    }

public:
    Library() { loadFromFile(); }

    void addBook() {
        string isbn, title, author, category;
        cout << "Enter ISBN: "; getline(cin, isbn);
        if (isbn.empty() || findIndex(isbn) != -1) {
            cout << "Invalid or duplicate ISBN. Book not added.\n";
            return;
        }
        cout << "Enter title: "; getline(cin, title);
        cout << "Enter author: "; getline(cin, author);
        cout << "Enter category: "; getline(cin, category);

        if (title.empty() || author.empty() || category.empty() ||
            isbn.find('|') != string::npos || title.find('|') != string::npos ||
            author.find('|') != string::npos || category.find('|') != string::npos) {
            cout << "Fields must not be empty or contain the | character.\n";
            return;
        }

        books.emplace_back(isbn, title, author, category, true);
        saveToFile();
        cout << "Book added successfully.\n";
    }

    void searchBook() const {
        string key;
        cout << "Enter ISBN to search: "; getline(cin, key);
        int index = findIndex(key);
        if (index == -1) cout << "Book not found.\n";
        else {
            cout << "\nISBN           Title                    Author                Category        Status\n";
            books[index].display();
        }
    }

    void issueBook() {
        string isbn;
        cout << "Enter ISBN to issue: "; getline(cin, isbn);
        int index = findIndex(isbn);
        if (index == -1) cout << "Book not found.\n";
        else if (!books[index].available) cout << "Book is already issued.\n";
        else {
            books[index].available = false;
            saveToFile();
            cout << "Book issued successfully.\n";
        }
    }

    void returnBook() {
        string isbn;
        cout << "Enter ISBN to return: "; getline(cin, isbn);
        int index = findIndex(isbn);
        if (index == -1) cout << "Book not found.\n";
        else if (books[index].available) cout << "This book is already marked available.\n";
        else {
            books[index].available = true;
            saveToFile();
            cout << "Book returned successfully.\n";
        }
    }

    void updateBook() {
        string isbn;
        cout << "Enter ISBN of book to update: "; getline(cin, isbn);
        int index = findIndex(isbn);
        if (index == -1) {
            cout << "Book not found.\n";
            return;
        }

        string title, author, category;
        cout << "Enter new title: "; getline(cin, title);
        cout << "Enter new author: "; getline(cin, author);
        cout << "Enter new category: "; getline(cin, category);

        if (title.empty() || author.empty() || category.empty() ||
            title.find('|') != string::npos || author.find('|') != string::npos ||
            category.find('|') != string::npos) {
            cout << "Invalid details. Update cancelled.\n";
            return;
        }
        books[index].title = title;
        books[index].author = author;
        books[index].category = category;
        saveToFile();
        cout << "Book details updated successfully.\n";
    }

    void availabilityReport() const {
        cout << "\n================ LIBRARY BOOK REPORT ================\n";
        cout << left << setw(15) << "ISBN" << setw(25) << "Title"
             << setw(22) << "Author" << setw(16) << "Category" << "Status\n";
        cout << string(90, '-') << '\n';

        int availableCount = 0;
        for (const Book& b : books) {
            b.display();
            if (b.available) ++availableCount;
        }
        cout << string(90, '-') << '\n';
        cout << "Total books: " << books.size()
             << " | Available: " << availableCount
             << " | Issued: " << books.size() - availableCount << '\n';
    }
};

int main() {
    Library library;
    int choice;

    do {
        cout << "\n========== LIBRARY BOOK MANAGEMENT SYSTEM ==========\n"
             << "1. Add book\n"
             << "2. Search book by ISBN\n"
             << "3. Issue book\n"
             << "4. Return book\n"
             << "5. Update book details\n"
             << "6. Availability report\n"
             << "0. Exit\n"
             << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: library.addBook(); break;
            case 2: library.searchBook(); break;
            case 3: library.issueBook(); break;
            case 4: library.returnBook(); break;
            case 5: library.updateBook(); break;
            case 6: library.availabilityReport(); break;
            case 0: cout << "Thank you for using the Library Management System.\n"; break;
            default: cout << "Please select a valid option.\n";
        }
    } while (choice != 0);

    return 0;
}
