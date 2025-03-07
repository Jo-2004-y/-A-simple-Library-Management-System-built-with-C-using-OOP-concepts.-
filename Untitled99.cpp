#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class LibraryItem {
protected:
    string title;
    bool availability;
public:
    LibraryItem(string t) : title(t), availability(true) {}

    virtual void display() const = 0;

    virtual ~LibraryItem() {}

    bool isAvailable() const {
        return availability;
    }

    void borrowItem() {
        if (availability) {
            availability = false;
            cout << title << " has been borrowed successfully.\n";
        } else {
            cout << title << " is already borrowed.\n";
        }
    }

    void returnItem() {
        if (!availability) {
            availability = true;
            cout << title << " has been returned successfully.\n";
        } else {
            cout << title << " was not borrowed.\n";
        }
    }

    string getTitle() const {
        return title;
    }
};

class Book : public LibraryItem {
private:
    string author;
    string ISBN;
public:
    Book(string t, string a, string isbn) : LibraryItem(t), author(a), ISBN(isbn) {}

    void display() const override {
        cout << "Book: " << title << " | Author: " << author
             << " | ISBN: " << ISBN
             << " | Available: " << (availability ? "Yes" : "No") << endl;
    }
};

class Magazine : public LibraryItem {
private:
    int issueNumber;
    string publisher;
public:
    Magazine(string t, int issue, string pub) : LibraryItem(t), issueNumber(issue), publisher(pub) {}

    void display() const override {
        cout << "Magazine: " << title << " | Issue: " << issueNumber
             << " | Publisher: " << publisher
             << " | Available: " << (availability ? "Yes" : "No") << endl;
    }
};

class DVD : public LibraryItem {
private:
    string director;
    int duration;
public:
    DVD(string t, string dir, int dur) : LibraryItem(t), director(dir), duration(dur) {}

    void display() const override {
        cout << "DVD: " << title << " | Director: " << director
             << " | Duration: " << duration
             << " mins | Available: " << (availability ? "Yes" : "No") << endl;
    }
};

class LibrarySystem {
private:
    vector<LibraryItem*> items;
public:
    void addItem(LibraryItem* item) {
        items.push_back(item);
        cout << item->getTitle() << " has been added to the library.\n";
    }

    void displayItems() const {
        cout << "\n===== Library Collection =====\n";
        if (items.empty()) {
            cout << "The library is empty.\n";
            return;
        }
        for (const auto& item : items) {
            item->display();
        }
    }

    void borrowItem(const string& title) {
        for (auto& item : items) {
            if (item->getTitle() == title) {
                item->borrowItem();
                return;
            }
        }
        cout << "Item not found in the library.\n";
    }

    void returnItem(const string& title) {
        for (auto& item : items) {
            if (item->getTitle() == title) {
                item->returnItem();
                return;
            }
        }
        cout << "Item not found in the library.\n";
    }

    ~LibrarySystem() {
        for (auto& item : items) {
            delete item;
        }
    }
};

void menu(LibrarySystem& library) {
    int choice;
    do {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. Add Magazine\n";
        cout << "3. Add DVD\n";
        cout << "4. Borrow Item\n";
        cout << "5. Return Item\n";
        cout << "6. Display All Items\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number: ";
            cin >> choice;
        }
        cin.ignore();

        string title, author, ISBN, publisher, director;
        int issueNumber, duration;

        switch (choice) {
            case 1:
                cout << "Enter Book Title: ";
                getline(cin, title);
                cout << "Enter Author: ";
                getline(cin, author);
                cout << "Enter ISBN: ";
                getline(cin, ISBN);
                library.addItem(new Book(title, author, ISBN));
                break;

            case 2:
                cout << "Enter Magazine Title: ";
                getline(cin, title);
                cout << "Enter Issue Number: ";
                cin >> issueNumber;
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Enter a number: ";
                    cin >> issueNumber;
                }
                cin.ignore();
                cout << "Enter Publisher: ";
                getline(cin, publisher);
                library.addItem(new Magazine(title, issueNumber, publisher));
                break;

            case 3:
                cout << "Enter DVD Title: ";
                getline(cin, title);
                cout << "Enter Director: ";
                getline(cin, director);
                cout << "Enter Duration (in minutes): ";
                cin >> duration;
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Enter a number: ";
                    cin >> duration;
                }
                cin.ignore();
                library.addItem(new DVD(title, director, duration));
                break;

            case 4:
                cout << "Enter the title of the item to borrow: ";
                getline(cin, title);
                library.borrowItem(title);
                break;

            case 5:
                cout << "Enter the title of the item to return: ";
                getline(cin, title);
                library.returnItem(title);
                break;

            case 6:
                library.displayItems();
                break;

            case 7:
                cout << "Exiting Library System...\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 7);
}

int main() {
    LibrarySystem library;
    menu(library);
    return 0;
}
