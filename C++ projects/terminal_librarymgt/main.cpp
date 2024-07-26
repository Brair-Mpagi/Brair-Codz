#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

// Book class to handle book details
class Book {
public:
    string title;
    string author;
    int id;
    bool isAvailable;
    string location;

    Book(string t, string a, int i, bool avail, string loc) : title(t), author(a), id(i), isAvailable(avail), location(loc) {}
};

// User class to handle user details
class User {
public:
    string name;
    int id;
    string role;
    bool hasReturned;

    User(string n, int i, string r, bool hR) : name(n), id(i), role(r), hasReturned(hR) {}
};

// Borrowing class to handle borrowing details
class Borrowing {
public:
    int bookId;
    int userId;
    time_t borrowDate;
    time_t returnDate;
    double lateFee;

    Borrowing(int bId, int uId, time_t bDate, time_t rDate, double lFee) : bookId(bId), userId(uId), borrowDate(bDate), returnDate(rDate), lateFee(lFee) {}
};

vector<Book> books;
vector<User> users;
vector<Borrowing> borrowings;

void loadBooksFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string title, author, location, isAvailableStr;
        int id;
        bool isAvailable;

        getline(ss, title, ',');
        getline(ss, author, ',');
        ss >> id;
        ss.ignore(1);
        getline(ss, isAvailableStr, ',');
        isAvailable = (isAvailableStr == "true");
        getline(ss, location);

        books.push_back(Book(title, author, id, isAvailable, location));
    }

    file.close();
}

void loadUsersFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, role, hasReturnedStr;
        int id;
        bool hasReturned;

        getline(ss, name, ',');
        ss >> id;
        ss.ignore(1);
        getline(ss, role, ',');
        getline(ss, hasReturnedStr);
        hasReturned = (hasReturnedStr == "true");

        users.push_back(User(name, id, role, hasReturned));
    }

    file.close();
}

void loadBorrowingsFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int bookId, userId;
        time_t borrowDate, returnDate;
        double lateFee;

        ss >> bookId;
        ss.ignore(1);
        ss >> userId;
        ss.ignore(1);
        ss >> borrowDate;
        ss.ignore(1);
        ss >> returnDate;
        ss.ignore(1);
        ss >> lateFee;

        borrowings.push_back(Borrowing(bookId, userId, borrowDate, returnDate, lateFee));
    }

    file.close();
}

void saveUsersToCSV(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file " << filename << endl;
        return;
    }

    for (const auto& user : users) {
        file << user.name << "," << user.id << "," << user.role << "," << (user.hasReturned ? "true" : "false") << endl;
    }

    file.close();
}

void saveBorrowingsToCSV(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file " << filename << endl;
        return;
    }

    for (const auto& borrowing : borrowings) {
        file << borrowing.bookId << "," << borrowing.userId << "," << borrowing.borrowDate << "," << borrowing.returnDate << "," << borrowing.lateFee << endl;
    }

    file.close();
}

void saveBooksToCSV(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file " << filename << endl;
        return;
    }

    for (const auto& book : books) {
        file << book.title << "," << book.author << "," << book.id << "," << (book.isAvailable ? "true" : "false") << "," << book.location << endl;
    }

    file.close();
}

void addUser() {
    string name, role;
    int id;
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter user ID: ";
    cin >> id;
    cout << "Enter user role (student/faculty/staff): ";
    cin >> role;
    users.push_back(User(name, id, role, true)); // Initially, the user has returned the book
    cout << "User added successfully!" << endl;

    // Update CSV
    saveUsersToCSV("users.csv");
}

void viewBooks() {
    for (const auto& book : books) {
        cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author 
             << ", Available: " << (book.isAvailable ? "Yes" : "No") << ", Location: " << book.location << endl;
    }
}

void borrowBook() {
    int userId, bookId;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book ID: ";
    cin >> bookId;

    auto user = find_if(users.begin(), users.end(), [userId](const User& u) { return u.id == userId; });
    auto book = find_if(books.begin(), books.end(), [bookId](const Book& b) { return b.id == bookId; });

    if (user != users.end() && book != books.end() && book->isAvailable) {
        time_t now = time(0);
        borrowings.push_back(Borrowing(bookId, userId, now, 0, 0.0));
        book->isAvailable = false;
        user->hasReturned = false;
        cout << "Book borrowed successfully!" << endl;

        // Update CSV
        saveBorrowingsToCSV("borrowings.csv");
        saveBooksToCSV("books.csv");
        saveUsersToCSV("users.csv");
    } else {
        cout << "User or Book not found, or Book is already borrowed." << endl;
    }
}

void returnBook() {
    int userId, bookId;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "Enter book ID: ";
    cin >> bookId;

    auto book = find_if(books.begin(), books.end(), [bookId](const Book& b) { return b.id == bookId; });
    auto borrowing = find_if(borrowings.begin(), borrowings.end(), [userId, bookId](const Borrowing& b) { return b.userId == userId && b.bookId == bookId; });
    auto user = find_if(users.begin(), users.end(), [userId](const User& u) { return u.id == userId; });

    if (book != books.end() && borrowing != borrowings.end()) {
        time_t now = time(0);
        borrowing->returnDate = now;

        double lateFee = difftime(now, borrowing->borrowDate) / (60 * 60 * 24) - 14; // 14 days borrowing period
        if (lateFee > 0) {
            borrowing->lateFee = lateFee * 1.0; // $1 per day late fee
            cout << "Book returned with a late fee of $" << borrowing->lateFee << endl;
        } else {
            borrowing->lateFee = 0;
            cout << "Book returned on time. No late fee." << endl;
        }
        book->isAvailable = true;
        user->hasReturned = true;

        // Update CSV
        saveBorrowingsToCSV("borrowings.csv");
        saveBooksToCSV("books.csv");
        saveUsersToCSV("users.csv");
    } else {
        cout << "Borrowing record not found." << endl;
    }
}

void searchBooks() {
    string query;
    cout << "Enter book title or author to search: ";
    cin.ignore();
    getline(cin, query);

    bool found = false;
    for (const auto& book : books) {
        if (book.title.find(query) != string::npos || book.author.find(query) != string::npos) {
            cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author 
                 << ", Available: " << (book.isAvailable ? "Yes" : "No") << ", Location: " << book.location << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No books found matching the search query." << endl;
    }
}

int main() {
    loadBooksFromCSV("books.csv");
    loadUsersFromCSV("users.csv");
    loadBorrowingsFromCSV("borrowings.csv");

    while (true) {
        int choice;
        cout << "\n\n\t\tLibrary Management System\n";
        cout << "1. Add User\n";
        cout << "2. View Books\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. Search Books\n";
        cout << "6. Exit\n\n\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addUser();
                break;
            case 2:
                viewBooks();
                break;
            case 3:
                borrowBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                searchBooks();
                break;
            case 6:
                exit(0);
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}
