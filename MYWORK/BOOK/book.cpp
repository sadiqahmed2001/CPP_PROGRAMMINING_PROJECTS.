#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <sstream> 

class Book {
public:
    std::string title;
    std::string author;
    std::string isbn;
    bool isIssued;

    Book(std::string t, std::string a, std::string i) : title(t), author(a), isbn(i), isIssued(false) {}

    void display() const {
        std::cout << "Title: " << title << "\nAuthor: " << author << "\nISBN: " << isbn << "\nIssued: " << (isIssued ? "Yes" : "No") << "\n";
    }
};

class Member {
public:
    std::string name;
    std::string memberId;
    std::vector<Book> borrowedBooks;

    Member(std::string n, std::string id) : name(n), memberId(id) {}

    void display() const {
        std::cout << "Name: " << name << "\nMember ID: " << memberId << "\n";
    }
};

class Library {
private:
    std::vector<Book> books;
    std::vector<Member> members;

public:
    void addBook(const std::string& title, const std::string& author, const std::string& isbn) {
        books.emplace_back(title, author, isbn);
        std::cout << "Book added successfully.\n";
    }

    void updateBook(const std::string& isbn, const std::string& newTitle, const std::string& newAuthor) {
        auto it = std::find_if(books.begin(), books.end(), [&](const Book& b) { return b.isbn == isbn; });
        if (it != books.end()) {
            it->title = newTitle;
            it->author = newAuthor;
            std::cout << "Book updated successfully.\n";
        } else {
            std::cout << "Book not found.\n";
        }
    }

    void deleteBook(const std::string& isbn) {
        auto it = std::remove_if(books.begin(), books.end(), [&](const Book& b) { return b.isbn == isbn; });
        if (it != books.end()) {
            books.erase(it, books.end());
            std::cout << "Book deleted successfully.\n";
        } else {
            std::cout << "Book not found.\n";
        }
    }

    void listAllBooks() const {
        if (books.empty()) {
            std::cout << "No books to display.\n";
        } else {
            for (const auto& book : books) {
                book.display();
                std::cout << "----------------\n";
            }
        }
    }

    void addMember(const std::string& name, const std::string& memberId) {
        members.emplace_back(name, memberId);
        std::cout << "Member added successfully.\n";
    }

    void updateMember(const std::string& memberId, const std::string& newName) {
        auto it = std::find_if(members.begin(), members.end(), [&](const Member& m) { return m.memberId == memberId; });
        if (it != members.end()) {
            it->name = newName;
            std::cout << "Member updated successfully.\n";
        } else {
            std::cout << "Member not found.\n";
        }
    }

    void deleteMember(const std::string& memberId) {
        auto it = std::remove_if(members.begin(), members.end(), [&](const Member& m) { return m.memberId == memberId; });
        if (it != members.end()) {
            members.erase(it, members.end());
            std::cout << "Member deleted successfully.\n";
        } else {
            std::cout << "Member not found.\n";
        }
    }

    void listAllMembers() const {
        if (members.empty()) {
            std::cout << "No members to display.\n";
        } else {
            for (const auto& member : members) {
                member.display();
                std::cout << "----------------\n";
            }
        }
    }

    void issueBook(const std::string& isbn, const std::string& memberId) {
        auto bookIt = std::find_if(books.begin(), books.end(), [&](const Book& b) { return b.isbn == isbn; });
        auto memberIt = std::find_if(members.begin(), members.end(), [&](const Member& m) { return m.memberId == memberId; });

        if (bookIt != books.end() && memberIt != members.end()) {
            if (!bookIt->isIssued) {
                bookIt->isIssued = true;
                memberIt->borrowedBooks.push_back(*bookIt);
                std::cout << "Book issued successfully.\n";
            } else {
                std::cout << "Book is already issued.\n";
            }
        } else {
            std::cout << "Book or Member not found.\n";
        }
    }

    void returnBook(const std::string& isbn, const std::string& memberId) {
        auto bookIt = std::find_if(books.begin(), books.end(), [&](const Book& b) { return b.isbn == isbn; });
        auto memberIt = std::find_if(members.begin(), members.end(), [&](const Member& m) { return m.memberId == memberId; });

        if (bookIt != books.end() && memberIt != members.end()) {
            bookIt->isIssued = false;
            auto& borrowedBooks = memberIt->borrowedBooks;
            auto borrowedBookIt = std::remove_if(borrowedBooks.begin(), borrowedBooks.end(), [&](const Book& b) { return b.isbn == isbn; });
            borrowedBooks.erase(borrowedBookIt, borrowedBooks.end());
            std::cout << "Book returned successfully.\n";
        } else {
            std::cout << "Book or Member not found.\n";
        }
    }

    void listBorrowedBooks(const std::string& memberId) const {
        auto memberIt = std::find_if(members.begin(), members.end(), [&](const Member& m) { return m.memberId == memberId; });

        if (memberIt != members.end()) {
            if (memberIt->borrowedBooks.empty()) {
                std::cout << "No borrowed books to display.\n";
            } else {
                for (const auto& book : memberIt->borrowedBooks) {
                    book.display();
                    std::cout << "----------------\n";
                }
            }
        } else {
            std::cout << "Member not found.\n";
        }
    }

    void searchBook(const std::string& keyword) const {
        for (const auto& book : books) {
            if (book.title.find(keyword) != std::string::npos || book.author.find(keyword) != std::string::npos || book.isbn.find(keyword) != std::string::npos) {
                book.display();
                std::cout << "----------------\n";
            }
        }
    }

    void searchMember(const std::string& keyword) const {
        for (const auto& member : members) {
            if (member.name.find(keyword) != std::string::npos || member.memberId.find(keyword) != std::string::npos) {
                member.display();
                std::cout << "----------------\n";
            }
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const auto& book : books) {
                outFile << book.title << "," << book.author << "," << book.isbn << "," << book.isIssued << "\n";
            }
            outFile.close();
            std::cout << "Data saved successfully.\n";
        } else {
            std::cout << "Unable to open file.\n";
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream inFile(filename);
        if (inFile.is_open()) {
            books.clear();
            std::string line;
            while (std::getline(inFile, line)) {
                std::stringstream ss(line);
                std::string title, author, isbn, isIssuedStr;
                bool isIssued;
                std::getline(ss, title, ',');
                std::getline(ss, author, ',');
                std::getline(ss, isbn, ',');
                std::getline(ss, isIssuedStr, ',');
                isIssued = (isIssuedStr == "1");
                books.emplace_back(title, author, isbn);
                books.back().isIssued = isIssued;
            }
            inFile.close();
            std::cout << "Data loaded successfully.\n";
        } else {
            std::cout << "Unable to open file.\n";
        }
    }
};

int main() {
    Library library;
    int choice;
    std::string title, author, isbn, memberId, name, filename;

    do {
        std::cout << "\nLibrary Management System\n";
        std::cout << "1. Add Book\n2. Update Book\n3. Delete Book\n4. List All Books\n5. Add Member\n6. Update Member\n7. Delete Member\n8. List All Members\n9. Issue Book\n10. Return Book\n11. List Borrowed Books\n12. Search Book\n13. Search Member\n14. Save to File\n15. Load from File\n0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                std::cout << "Enter title: ";
                std::getline(std::cin, title);
                std::cout << "Enter author: ";
                std::getline(std::cin, author);
                std::cout << "Enter ISBN: ";
                std::getline(std::cin, isbn);
                library.addBook(title, author, isbn);
                break;

            case 2:
                std::cout << "Enter ISBN of the book to update: ";
                std::getline(std::cin, isbn);
                std::cout << "Enter new title: ";
                std::getline(std::cin, title);
                std::cout << "Enter new author: ";
                std::getline(std::cin, author);
                library.updateBook(isbn, title, author);
                break;

            case 3:
                std::cout << "Enter ISBN of the book to delete: ";
                std::getline(std::cin, isbn);
                library.deleteBook(isbn);
                break;

            case 4:
                library.listAllBooks();
                break;

            case 5:
                std::cout << "Enter name: ";
                std::getline(std::cin, name);
                std::cout << "Enter member ID: ";
                std::getline(std::cin, memberId);
                library.addMember(name, memberId);
                break;

            case 6:
                std::cout << "Enter member ID of the member to update: ";
                std::getline(std::cin, memberId);
                std::cout << "Enter new name: ";
                std::getline(std::cin, name);
                library.updateMember(memberId, name);
                break;

            case 7:
                std::cout << "Enter member ID of the member to delete: ";
                std::getline(std::cin, memberId);
                library.deleteMember(memberId);
                break;

            case 8:
                library.listAllMembers();
                break;

            case 9:
                std::cout << "Enter ISBN of the book to issue: ";
                std::getline(std::cin, isbn);
                std::cout << "Enter member ID: ";
                std::getline(std::cin, memberId);
                library.issueBook(isbn, memberId);
                break;

            case 10:
                std::cout << "Enter ISBN of the book to return: ";
                std::getline(std::cin, isbn);
                std::cout << "Enter member ID: ";
                std::getline(std::cin, memberId);
                library.returnBook(isbn, memberId);
                break;

            case 11:
                std::cout << "Enter member ID: ";
                std::getline(std::cin, memberId);
                library.listBorrowedBooks(memberId);
                break;

            case 12:
                std::cout << "Enter keyword to search for books: ";
                std::getline(std::cin, title);
                library.searchBook(title);
                break;

            case 13:
                std::cout << "Enter keyword to search for members: ";
                std::getline(std::cin, name);
                library.searchMember(name);
                break;

            case 14:
                std::cout << "Enter filename to save: ";
                std::getline(std::cin, filename);
                library.saveToFile(filename);
                break;

            case 15:
                std::cout << "Enter filename to load: ";
                std::getline(std::cin, filename);
                library.loadFromFile(filename);
                break;

            case 0:
                std::cout << "Exiting...\n";
                break;

            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
