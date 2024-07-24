#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

class Product {
public:
    std::string id;
    std::string name;
    double price;
    int quantity;

    Product(const std::string& i, const std::string& n, double p, int q)
        : id(i), name(n), price(p), quantity(q) {}

    void printDetails() const {
        std::cout << "Product ID: " << id << "\nName: " << name
                  << "\nPrice: $" << price << "\nQuantity: " << quantity << std::endl;
    }
};

class Customer {
public:
    std::string id;
    std::string name;
    std::string email;

    Customer(const std::string& i, const std::string& n, const std::string& e)
        : id(i), name(n), email(e) {}

    void printDetails() const {
        std::cout << "Customer ID: " << id << "\nName: " << name
                  << "\nEmail: " << email << std::endl;
    }
};

class Order {
public:
    std::string id;
    std::string customerId;
    std::vector<std::string> productIds;

    Order(const std::string& i, const std::string& c)
        : id(i), customerId(c) {}

    void addProduct(const std::string& productId) {
        productIds.push_back(productId);
    }

    void printDetails() const {
        std::cout << "Order ID: " << id << "\nCustomer ID: " << customerId << "\nProducts: ";
        for (const auto& pid : productIds) {
            std::cout << pid << " ";
        }
        std::cout << std::endl;
    }
};

class Inventory {
private:
    std::vector<Product> products;
    std::vector<Customer> customers;
    std::vector<Order> orders;

    Product* findProduct(const std::string& id) {
        for (auto& product : products) {
            if (product.id == id) return &product;
        }
        return nullptr;
    }

    Customer* findCustomer(const std::string& id) {
        for (auto& customer : customers) {
            if (customer.id == id) return &customer;
        }
        return nullptr;
    }

    Order* findOrder(const std::string& id) {
        for (auto& order : orders) {
            if (order.id == id) return &order;
        }
        return nullptr;
    }

public:
    void addProduct(const std::string& id, const std::string& name, double price, int quantity) {
        products.emplace_back(id, name, price, quantity);
        std::cout << "Product added successfully.\n";
    }

    void updateProduct(const std::string& id, const std::string& name, double price, int quantity) {
        Product* product = findProduct(id);
        if (product) {
            product->name = name;
            product->price = price;
            product->quantity = quantity;
            std::cout << "Product updated successfully.\n";
        } else {
            std::cout << "Product not found.\n";
        }
    }

    void deleteProduct(const std::string& id) {
        auto it = std::remove_if(products.begin(), products.end(), [&id](const Product& p) { return p.id == id; });
        if (it != products.end()) {
            products.erase(it, products.end());
            std::cout << "Product deleted successfully.\n";
        } else {
            std::cout << "Product not found.\n";
        }
    }

    void addCustomer(const std::string& id, const std::string& name, const std::string& email) {
        customers.emplace_back(id, name, email);
        std::cout << "Customer added successfully.\n";
    }

    void updateCustomer(const std::string& id, const std::string& name, const std::string& email) {
        Customer* customer = findCustomer(id);
        if (customer) {
            customer->name = name;
            customer->email = email;
            std::cout << "Customer updated successfully.\n";
        } else {
            std::cout << "Customer not found.\n";
        }
    }

    void deleteCustomer(const std::string& id) {
        auto it = std::remove_if(customers.begin(), customers.end(), [&id](const Customer& c) { return c.id == id; });
        if (it != customers.end()) {
            customers.erase(it, customers.end());
            std::cout << "Customer deleted successfully.\n";
        } else {
            std::cout << "Customer not found.\n";
        }
    }

    void createOrder(const std::string& id, const std::string& customerId) {
        if (findCustomer(customerId)) {
            orders.emplace_back(id, customerId);
            std::cout << "Order created successfully.\n";
        } else {
            std::cout << "Customer not found.\n";
        }
    }

    void addProductToOrder(const std::string& orderId, const std::string& productId) {
        Order* order = findOrder(orderId);
        if (order && findProduct(productId)) {
            order->addProduct(productId);
            std::cout << "Product added to order successfully.\n";
        } else {
            std::cout << "Order or Product not found.\n";
        }
    }

    void printProducts() const {
        for (const auto& product : products) {
            product.printDetails();
            std::cout << "-----------------------------\n";
        }
    }

    void printCustomers() const {
        for (const auto& customer : customers) {
            customer.printDetails();
            std::cout << "-----------------------------\n";
        }
    }

    void printOrders() const {
        for (const auto& order : orders) {
            order.printDetails();
            std::cout << "-----------------------------\n";
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& product : products) {
                file << "P," << product.id << "," << product.name << "," << product.price << "," << product.quantity << "\n";
            }
            for (const auto& customer : customers) {
                file << "C," << customer.id << "," << customer.name << "," << customer.email << "\n";
            }
            for (const auto& order : orders) {
                file << "O," << order.id << "," << order.customerId;
                for (const auto& pid : order.productIds) {
                    file << "," << pid;
                }
                file << "\n";
            }
            file.close();
            std::cout << "Data saved successfully.\n";
        } else {
            std::cout << "Unable to open file.\n";
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::stringstream ss(line);
                std::string type;
                std::getline(ss, type, ',');
                if (type == "P") {
                    std::string id, name;
                    double price;
                    int quantity;
                    std::getline(ss, id, ',');
                    std::getline(ss, name, ',');
                    ss >> price;
                    ss.ignore();
                    ss >> quantity;
                    products.emplace_back(id, name, price, quantity);
                } else if (type == "C") {
                    std::string id, name, email;
                    std::getline(ss, id, ',');
                    std::getline(ss, name, ',');
                    std::getline(ss, email);
                    customers.emplace_back(id, name, email);
                } else if (type == "O") {
                    std::string id, customerId;
                    std::getline(ss, id, ',');
                    std::getline(ss, customerId, ',');
                    Order order(id, customerId);
                    std::string productId;
                    while (std::getline(ss, productId, ',')) {
                        order.addProduct(productId);
                    }
                    orders.push_back(order);
                }
            }
            file.close();
            std::cout << "Data loaded successfully.\n";
        } else {
            std::cout << "Unable to open file.\n";
        }
    }
};

int main() {
    Inventory inventory;

    int choice;
    do {
        std::cout << "\n1. Add Product\n2. Update Product\n3. Delete Product\n4. Add Customer\n5. Update Customer\n6. Delete Customer\n7. Create Order\n8. Add Product to Order\n9. Print All Products\n10. Print All Customers\n11. Print All Orders\n12. Save Data\n13. Load Data\n0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        std::string id, name, email, customerId, productId, filename;
        double price;
        int quantity;

        switch (choice) {
            case 1: {
                std::cout << "Enter product ID, name, price, quantity: ";
                std::getline(std::cin, id);
                std::getline(std::cin, name);
                std::cin >> price >> quantity;
                std::cin.ignore();
                inventory.addProduct(id, name, price, quantity);
                break;
            }
            case 2: {
                std::cout << "Enter product ID, new name, new price, new quantity: ";
                std::getline(std::cin, id);
                std::getline(std::cin, name);
                std::cin >> price >> quantity;
                std::cin.ignore();
                inventory.updateProduct(id, name, price, quantity);
                break;
            }
            case 3: {
                std::cout << "Enter product ID to delete: ";
                std::getline(std::cin, id);
                inventory.deleteProduct(id);
                break;
            }
            case 4: {
                std::cout << "Enter customer ID, name, email: ";
                std::getline(std::cin, id);
                std::getline(std::cin, name);
                std::getline(std::cin, email);
                inventory.addCustomer(id, name, email);
                break;
            }
            case 5: {
                std::cout << "Enter customer ID, new name, new email: ";
                std::getline(std::cin, id);
                std::getline(std::cin, name);
                std::getline(std::cin, email);
                inventory.updateCustomer(id, name, email);
                break;
            }
            case 6: {
                std::cout << "Enter customer ID to delete: ";
                std::getline(std::cin, id);
                inventory.deleteCustomer(id);
                break;
            }
            case 7: {
                std::cout << "Enter order ID, customer ID: ";
                std::getline(std::cin, id);
                std::getline(std::cin, customerId);
                inventory.createOrder(id, customerId);
                break;
            }
            case 8: {
                std::cout << "Enter order ID, product ID to add: ";
                std::getline(std::cin, id);
                std::getline(std::cin, productId);
                inventory.addProductToOrder(id, productId);
                break;
            }
            case 9: {
                inventory.printProducts();
                break;
            }
            case 10: {
                inventory.printCustomers();
                break;
            }
            case 11: {
                inventory.printOrders();
                break;
            }
            case 12: {
                std::cout << "Enter filename to save data: ";
                std::getline(std::cin, filename);
                inventory.saveToFile(filename);
                break;
            }
            case 13: {
                std::cout << "Enter filename to load data: ";
                std::getline(std::cin, filename);
                inventory.loadFromFile(filename);
                break;
            }
            case 0: {
                std::cout << "Exiting...\n";
                break;
            }
            default: {
                std::cout << "Invalid choice. Try again.\n";
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
