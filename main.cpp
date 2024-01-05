#include <iostream>
#include <fstream>
#include <string>

using namespace std;
  

void barcode_controller(string product_barcode, string target_barcode, char dollar_sign, double& product_price);
void product_buy(char dollar_sign, string barcode, float& credit_limit);
void product_lister(char dollar_sign, string barcode);
void app_menu(float& credit_limit, char dollar_sign, int& operation);

int main() {
    float credit_limit = 100;
    int operation;

    char dollar_sign = '$';

    while (true) {
        app_menu(credit_limit, dollar_sign, operation);

        if (operation == 3) {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        }
    }

    return 0;
}

void barcode_controller(string product_barcode, string target_barcode, char dollar_sign, double& product_price) {
    ifstream file("product_list.txt", ios::in | ios::binary);

    if (!file.is_open()) {
        cerr << "File does not run!" << endl;
        exit(1);
    }

    string barcode, product_name;
    double price;

    bool found = false;

    while (file >> barcode >> product_name >> price) {
        if (product_barcode == barcode) {
            found = true;
            cout << "Product found with barcode: " << barcode << endl;
            cout << "Product Name: " << product_name << "(Selected!)" << " " << price << dollar_sign << endl;
            product_price = price;
            break;
        }
    }
    
    file.close();

    if (!found) {
        cout << "Product not found with barcode: " << product_barcode << endl;
    }
}

void product_buy(char dollar_sign, string barcode, float& credit_limit) {
    double product_price = 0.0; // Ürün fiyatını saklamak için bir değişken
    product_lister(dollar_sign, barcode);

    string product_barcode;

    cout << "Enter a product barcode : ";
    cin >> product_barcode;

    barcode_controller(product_barcode, barcode, dollar_sign, product_price);

    // Ürün fiyatını kontrol et ve gerekli işlemleri gerçekleştir
    if (product_price > 0 && credit_limit >= product_price) {
        cout << "Product purchased successfully!" << endl;
        credit_limit -= product_price; // Kredi limitini güncelle
        cout << "Remaining credit limit: " << credit_limit << dollar_sign << endl;
    } else {
        cout << "Purchase failed! Insufficient credit or invalid product." << endl;
    }
}

void product_lister(char dollar_sign, string barcode) {
    string product_name;
    double product_price;

    ifstream file("product_list.txt", ios::in | ios::binary);

    if (!file.is_open()) {
        cerr << "File does not run!" << endl;
        exit(1);
    }

    while (file >> barcode >> product_name >> product_price) {
        cout << "Barkod : " << barcode << ", " << product_name << " : " << product_price << dollar_sign << endl;
    }

    file.close();
}

void app_menu(float& credit_limit, char dollar_sign, int& operation) {
    cout << "Payment System V-0.1" << "\n";
    cout << "Credit card limit : " << credit_limit << dollar_sign << "\n\n";

    cout << "1. List Products\n";
    cout << "2. Buy Product\n";
    cout << "3. Exit\n";
    cout << "Enter Operation : ";
    cin >> operation;

    switch (operation) {
        case 1:
            product_lister(dollar_sign, "");
            break;
        case 2:
            product_buy(dollar_sign, "", credit_limit);
            break;
        case 3:
            break;
        default:
            cout << "Invalid Operation!" << endl;
            break;
    }
}
