//RESTAURANT MANAGEMENT SYSTEM
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;


class MenuItem {
public:
    string name;
    double price;

    MenuItem(string n, double p) : name(n), price(p) {}
};

class Order {
public:
    string itemName;
    int quantity;

    Order(string item, int qty) : itemName(item), quantity(qty) {}
};

void displayMenu(const vector<MenuItem>& menu);
void placeOrder(vector<Order>& orders, const vector<MenuItem>& menu);
void displayOrders(const vector<Order>& orders, const vector<MenuItem>& menu);
double calculateTotalBill(const vector<Order>& orders, const vector<MenuItem>& menu);
void cancelOrder(vector<Order>& orders);

int main() {

    vector<MenuItem> menu = {{"Burger", 200}, {"Pizza",400}, {"Salad", 100}};


    vector<Order> orders;

    int choice;
    do {
        cout << "\nRestaurant Management System" << endl;
        cout << "1. Display Menu" << endl;
        cout << "2. Place Order" << endl;
        cout << "3. Display Orders" << endl;
        cout << "4. Calculate Total Bill" << endl;
        cout << "5. Cancel Order" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayMenu(menu);
                break;
            case 2:
                placeOrder(orders, menu);
                break;
            case 3:
                displayOrders(orders, menu);
                break;
            case 4:
                cout << "Total Bill: $" << fixed << setprecision(2) << calculateTotalBill(orders, menu) << endl;
                break;
            case 5:
                cancelOrder(orders);
                break;
            case 6:
                cout << "Exiting the system. Thank you!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}


void displayMenu(const vector<MenuItem>& menu) {
    cout << "\nMenu:" << endl;
    cout << setw(15) << "Item" << setw(10) << "Price" << endl;
    cout << "------------------------" << endl;
    for (const auto& item : menu) {
        cout << setw(15) << item.name << setw(10) << item.price << endl;
    }
}


void placeOrder(vector<Order>& orders, const vector<MenuItem>& menu) {
    string itemName;
    int quantity;

    cout << "Enter the item name to order: ";
    cin >> itemName;


    auto item = find_if(menu.begin(), menu.end(), [&itemName](const MenuItem& menuItem) {
        return menuItem.name == itemName;
    });

    if (item != menu.end()) {
        cout << "Enter the quantity: ";
        cin >> quantity;


        orders.push_back(Order(itemName, quantity));

        cout << "Order placed successfully!" << endl;
    } else {
        cout << "Invalid item. Please choose from the menu." << endl;
    }
}


void displayOrders(const vector<Order>& orders, const vector<MenuItem>& menu) {
    if (orders.empty()) {
        cout << "No orders to display." << endl;
        return;
    }

    cout << "\nList of Orders:" << endl;
    cout << setw(15) << "Item" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
    cout << "-----------------------------" << endl;

    for (const auto& order : orders) {
        auto menuItem = find_if(menu.begin(), menu.end(), [&order](const MenuItem& menuItem) {
            return menuItem.name == order.itemName;
        });

        if (menuItem != menu.end()) {
            cout << setw(15) << order.itemName << setw(10) << order.quantity << setw(10)
                 << order.quantity * menuItem->price << endl;
        }
    }
}


double calculateTotalBill(const vector<Order>& orders, const vector<MenuItem>& menu) {
    double totalBill = 0.0;

    for (const auto& order : orders) {
        auto menuItem = find_if(menu.begin(), menu.end(), [&order](const MenuItem& menuItem) {
            return menuItem.name == order.itemName;
        });

        if (menuItem != menu.end()) {
            totalBill += order.quantity * menuItem->price;
        }
    }

    return totalBill;
}


void cancelOrder(vector<Order>& orders) {
    string itemName;
    cout << "Enter the item name to cancel the order: ";
    cin >> itemName;

    auto orderToRemove = find_if(orders.begin(), orders.end(), [&itemName](const Order& order) {
        return order.itemName == itemName;
    });

    if (orderToRemove != orders.end()) {
        orders.erase(orderToRemove);
        cout << "Order canceled successfully." << endl;
    } else {
        cout << "Order not found. Please enter a valid item name." << endl;
    }
}
