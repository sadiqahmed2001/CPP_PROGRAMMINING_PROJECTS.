#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

class Book {
public:
    std::string title;
    std::string author;
    std::string isbn;
    bool isAvailable;

    Book(std::string t, std::string a, std::string i, bool avail = true)
        : title(t), author(a), isbn(i), isAvailable(avail) {}

    void display() const {
        std::cout << "Title: " << title << "\nAuthor: " << author << "\nISBN: " << isbn << "\nAvailable: " << (isAvailable ? "Yes" : "No") << "\n";
    }
};

class LibraryManager {
private:
    std::vector<Book> books;

public:
    void addBook(const std::string& title, const std::string& author, const std::string& isbn, bool isAvailable = true) {
        books.emplace_back(title, author, isbn, isAvailable);
        std::cout << "Book added successfully.\n";
    }

    void searchBook(const std::string& query) const {
        auto it = std::find_if(books.begin(), books.end(), [&](const Book& b) { return b.title == query || b.author == query; });
        if (it != books.end()) {
            it->display();
        } else {
            std::cout << "Book not found.\n";
        }
    }

    void updateBook(const std::string& isbn, const std::string& newTitle, const std::string& newAuthor, bool newAvailability) {
        auto it = std::find_if(books.begin(), books.end(), [&](const Book& b) { return b.isbn == isbn; });
        if (it != books.end()) {
            it->title = newTitle;
            it->author = newAuthor;
            it->isAvailable = newAvailability;
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

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& book : books) {
                file << book.title << "\n" << book.author << "\n" << book.isbn << "\n" << book.isAvailable << "\n";
            }
            file.close();
            std::cout << "Books saved to file successfully.\n";
        } else {
            std::cout << "Unable to open file.\n";
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            books.clear();
            std::string title, author, isbn;
            bool isAvailable;
            while (std::getline(file, title) && std::getline(file, author) && std::getline(file, isbn) && file >> isAvailable) {
                file.ignore(); // to ignore the newline character after isAvailable input
                books.emplace_back(title, author, isbn, isAvailable);
            }
            file.close();
            std::cout << "Books loaded from file successfully.\n";
        } else {
            std::cout << "Unable to open file.\n";
        }
    }
};

int main() {
    LibraryManager manager;
    int choice;
    std::string title, author, isbn, filename;
    bool isAvailable;

    do {
        std::cout << "Library Management System\n";
        std::cout << "1. Add Book\n";
        std::cout << "2. Search Book\n";
        std::cout << "3. Update Book\n";
        std::cout << "4. Delete Book\n";
        std::cout << "5. List All Books\n";
        std::cout << "6. Save to File\n";
        std::cout << "7. Load from File\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // to ignore the newline character after choice input

        switch (choice) {
            case 1:
                std::cout << "Enter title: ";
                std::getline(std::cin, title);
                std::cout << "Enter author: ";
                std::getline(std::cin, author);
                std::cout << "Enter ISBN: ";
                std::getline(std::cin, isbn);
                std::cout << "Is the book available (1 for yes, 0 for no): ";
                std::cin >> isAvailable;
                std::cin.ignore(); // to ignore the newline character after availability input
                manager.addBook(title, author, isbn, isAvailable);
                break;

            case 2:
                std::cout << "Enter title or author to search: ";
                std::getline(std::cin, title); // using title variable for query input
                manager.searchBook(title);
                break;

            case 3:
                std::cout << "Enter ISBN to update: ";
                std::getline(std::cin, isbn);
                std::cout << "Enter new title: ";
                std::getline(std::cin, title);
                std::cout << "Enter new author: ";
                std::getline(std::cin, author);
                std::cout << "Is the book available (1 for yes, 0 for no): ";
                std::cin >> isAvailable;
                std::cin.ignore(); // to ignore the newline character after availability input
                manager.updateBook(isbn, title, author, isAvailable);
                break;

            case 4:
                std::cout << "Enter ISBN to delete: ";
                std::getline(std::cin, isbn);
                manager.deleteBook(isbn);
                break;

            case 5:
                manager.listAllBooks();
                break;

            case 6:
                std::cout << "Enter filename to save: ";
                std::getline(std::cin, filename);
                manager.saveToFile(filename);
                break;

            case 7:
                std::cout << "Enter filename to load: ";
                std::getline(std::cin, filename);
                manager.loadFromFile(filename);
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
