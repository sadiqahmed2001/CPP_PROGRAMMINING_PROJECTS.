#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

// Class to represent a food item in the menu
class MenuItem {
private:
    string name;
    double price;
public:
    MenuItem(string n, double p) : name(n), price(p) {}

    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }
};

// Class to manage the restaurant menu
class RestaurantMenu {
private:
    vector<MenuItem> menu;

public:
    // Add a new item to the menu
    void addItem(string name, double price) {
        MenuItem newItem(name, price);
        menu.push_back(newItem);
    }

    // Display the menu
    void displayMenu() const {
        cout << "--------- Menu ---------" << endl;
        for (size_t i = 0; i < menu.size(); ++i) {
            cout << setw(3) << left << (i + 1) << ". " << setw(20) << left << menu[i].getName() << setw(10) << right << menu[i].getPrice() << " INR " << endl;
        }
        cout << "------------------------" << endl;
    }

    // Get the size of the menu
    int getMenuSize() const {
        return menu.size();
    }

    // Get a specific item from the menu
    MenuItem getItem(int index) const {
        return menu[index];
    }
};

// Function to take orders
// void takeOrder(const RestaurantMenu& menu) {
//     int choice;
//     int quantity;
//     double totalBill=0.0;

//     cout << "Welcome to the restaurant!" << endl;
//     cout << "Please select items from the menu below:" << endl;

//     // Display menu
//     menu.displayMenu();

//     // Take orders
//     do {
//         cout << "Enter the item number you want to order (1-" << menu.getMenuSize() << ") (0 to finish): ";
//         cin >> choice;

//         if (choice >= 1 && choice <= menu.getMenuSize()) {
//             cout << "Enter quantity: ";
//             cin >> quantity;

//             MenuItem item = menu.getItem(choice - 1);
//             double itemPrice = item.getPrice();
//             double orderTotal = itemPrice * quantity;

//             cout << item.getName() << " - " << quantity << " x " << itemPrice << " INR = " << orderTotal << " INR" << endl;

//             totalBill += orderTotal; // Accumulate order total into totalBill
//         } else if (choice < 0 || choice > menu.getMenuSize()) {
//             cout << "Invalid choice. Please enter a valid item number." << endl;
//         }

//     } while (choice != 0);

//     // Display total bill
//     cout << "Your total bill is: " << totalBill << " INR" << endl;
//     cout << "Thank you for visiting us!" << endl;
// }

void takeOrder(const RestaurantMenu& menu) {
    int choice;
    int quantity;
    double orderTotal = 0.0;

    cout << "Welcome to the restaurant!" << endl;
    cout << "Please select items from the menu below:" << endl;

    // Display menu
    menu.displayMenu();

    // Take orders
    do {
        cout << "Enter the item number you want to order (1-" << menu.getMenuSize() << ") (0 to finish): ";
        cin >> choice;

        if (choice >= 1 && choice <= menu.getMenuSize()) {
            cout << "Enter quantity: ";
            cin >> quantity;

            MenuItem item = menu.getItem(choice - 1);
            double itemPrice = item.getPrice();
            double orderTotal = itemPrice * quantity;

            cout << item.getName() << " - " << quantity << " x " << itemPrice << " INR = " << orderTotal << " INR" << endl;

            // totalBill += orderTotal; // Accumulate order total into totalBill
        } else if (choice != 0) {
            cout << "Invalid choice. Please enter a valid item number." << endl;
        }

    } while (choice != 0);

    // Display total bill
    cout << "Your total bill is: " << orderTotal << " INR" << endl;
    cout << "Thank you for visiting us!" << endl;
}

int main() {
    // Create a RestaurantMenu object
    RestaurantMenu menu;

    // Adding menu items interactively
    char addMore;
    do {
        string name;
        double price;

        cout << "Enter the name of the menu item: ";
        cin.ignore(); // Ignore newline character left in the buffer
        getline(cin, name);

        cout << "Enter the price of the menu item (INR): ";
        cin >> price;

        menu.addItem(name, price);

        cout << "Do you want to add another item? (y/n): ";
        cin >> addMore;

    } while (addMore == 'y' || addMore == 'Y');

    // Take order from the customer
    takeOrder(menu);

    return 0;
}
