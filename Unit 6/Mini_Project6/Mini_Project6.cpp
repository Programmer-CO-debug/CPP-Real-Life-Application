#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct Product {
    int id;
    string name;
    string category;
    double price;
    int discount; // Percentage discount
};

struct CartItem {
    int productId;
    int quantity;
};

class ShoppingCart {
private:
    map<int, Product> catalog;
    vector<CartItem> cart;
    set<string> categories;
    priority_queue<pair<int, int>> featured; // {discount percentage, product ID}

    double discountedPrice(const Product& p) const {
        return p.price * (100 - p.discount) / 100.0;
    }

public:
    ShoppingCart() {
        addProduct({101, "Wireless Mouse", "Electronics", 799.00, 15});
        addProduct({102, "Keyboard", "Electronics", 1299.00, 10});
        addProduct({103, "Notebook", "Stationery", 120.00, 5});
        addProduct({104, "Backpack", "Accessories", 1499.00, 20});
        addProduct({105, "USB Drive", "Electronics", 499.00, 25});
    }

    void addProduct(const Product& p) {
        catalog[p.id] = p;
        categories.insert(p.category);
        featured.push({p.discount, p.id});
    }

    void showCatalog() const {
        cout << "\n================ PRODUCT CATALOG ================\n";
        cout << left << setw(8) << "ID" << setw(22) << "Product"
             << setw(16) << "Category" << right << setw(12) << "Price"
             << setw(12) << "Discount" << '\n';
        cout << string(70, '-') << '\n';

        for (const auto& entry : catalog) {
            const Product& p = entry.second;
            cout << left << setw(8) << p.id << setw(22) << p.name
                 << setw(16) << p.category << right << setw(12)
                 << fixed << setprecision(2) << p.price
                 << setw(11) << p.discount << "%\n";
        }
    }

    void showCategories() const {
        cout << "\nAvailable categories: ";
        for (const string& category : categories)
            cout << category << "  ";
        cout << '\n';
    }

    void showFeaturedProducts() const {
        cout << "\n======= HIGHEST DISCOUNT PRODUCTS =======\n";
        auto temp = featured;
        int shown = 0;
        while (!temp.empty() && shown < 3) {
            int id = temp.top().second;
            temp.pop();
            auto it = catalog.find(id);
            if (it != catalog.end()) {
                cout << it->second.name << " - "
                     << it->second.discount << "% off\n";
                ++shown;
            }
        }
    }

    void addToCart() {
        int id, quantity;
        cout << "Enter product ID: ";
        if (!(cin >> id)) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Invalid product ID.\n"; return;
        }
        auto it = catalog.find(id);
        if (it == catalog.end()) {
            cout << "Product not found.\n"; return;
        }

        cout << "Enter quantity: ";
        if (!(cin >> quantity) || quantity <= 0) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Quantity must be a positive number.\n"; return;
        }

        auto cartIt = find_if(cart.begin(), cart.end(),
            [id](const CartItem& item) { return item.productId == id; });

        if (cartIt != cart.end())
            cartIt->quantity += quantity;
        else
            cart.push_back({id, quantity});

        cout << "Product added to cart.\n";
    }

    void sortCatalogByPrice() const {
        vector<Product> sortedProducts;
        for (const auto& entry : catalog)
            sortedProducts.push_back(entry.second);

        sort(sortedProducts.begin(), sortedProducts.end(),
            [](const Product& a, const Product& b) {
                return a.price < b.price;
            });

        cout << "\n======= PRODUCTS SORTED BY PRICE (LOW TO HIGH) =======\n";
        for (const Product& p : sortedProducts)
            cout << p.id << " | " << left << setw(20) << p.name
                 << " Rs. " << fixed << setprecision(2) << p.price << '\n';
    }

    void searchProduct() const {
        int id;
        cout << "Enter product ID to search: ";
        if (!(cin >> id)) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Invalid ID.\n"; return;
        }

        auto it = find_if(catalog.begin(), catalog.end(),
            [id](const pair<const int, Product>& entry) {
                return entry.first == id;
            });

        if (it == catalog.end())
            cout << "Product not found.\n";
        else
            cout << "Found: " << it->second.name << " | Category: "
                 << it->second.category << " | Price: Rs. "
                 << fixed << setprecision(2) << it->second.price << '\n';
    }

    void showCategoryCounts() const {
        cout << "\n======= CATEGORY-WISE PRODUCT COUNT =======\n";
        for (const string& category : categories) {
            int count = static_cast<int>(count_if(catalog.begin(), catalog.end(),
                [&category](const pair<const int, Product>& entry) {
                    return entry.second.category == category;
                }));
            cout << category << ": " << count << " product(s)\n";
        }
    }

    void generateInvoice() const {
        cout << "\n================ CUSTOMER INVOICE ================\n";
        if (cart.empty()) {
            cout << "Your cart is empty.\n";
            return;
        }

        cout << left << setw(22) << "Product" << right << setw(8) << "Qty"
             << setw(14) << "Unit Price" << setw(14) << "Amount\n";
        cout << string(58, '-') << '\n';

        double total = 0.0;
        for (const CartItem& item : cart) {
            auto it = catalog.find(item.productId);
            if (it == catalog.end()) continue;

            const Product& p = it->second;
            double unitPrice = discountedPrice(p);
            double amount = unitPrice * item.quantity;
            total += amount;

            cout << left << setw(22) << p.name << right << setw(8)
                 << item.quantity << setw(14) << fixed << setprecision(2)
                 << unitPrice << setw(14) << amount << '\n';
        }

        cout << string(58, '-') << '\n';
        cout << right << setw(44) << "Grand Total: Rs. "
             << fixed << setprecision(2) << total << '\n';
        cout << "Thank you for shopping!\n";
    }
};

int main() {
    ShoppingCart shop;
    int choice;

    do {
        cout << "\n========== E-COMMERCE SHOPPING CART ==========\n"
             << "1. View product catalog\n"
             << "2. View product categories\n"
             << "3. View top discount products\n"
             << "4. Add product to cart\n"
             << "5. Sort products by price\n"
             << "6. Search product by ID\n"
             << "7. Category-wise product count\n"
             << "8. Generate invoice\n"
             << "0. Exit\n"
             << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Please enter a valid number.\n";
            continue;
        }

        switch (choice) {
            case 1: shop.showCatalog(); break;
            case 2: shop.showCategories(); break;
            case 3: shop.showFeaturedProducts(); break;
            case 4: shop.addToCart(); break;
            case 5: shop.sortCatalogByPrice(); break;
            case 6: shop.searchProduct(); break;
            case 7: shop.showCategoryCounts(); break;
            case 8: shop.generateInvoice(); break;
            case 0: cout << "Exiting shopping cart. Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
