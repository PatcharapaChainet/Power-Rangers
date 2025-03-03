#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "cost.h" 
class Item {
public:
    Item(const std::string& code = "", const std::string& name = "", double cost = 0.0, double price = 0.0, int quantity = 0)
        : code(code), name(name), Cprice(cost), Sprice(price), quantity(quantity) {
    }

    std::string getcode() const { return code; }
    std::string getName() const { return name; }
    double getCost() const { return Cprice; }
    double getPrice() const { return Sprice; }
    int getQuantity() const { return quantity; }

    void decItem(int);

    
    static void LoadProductsFromFile(std::vector<Item>& productList, const std::string& filename = "stock.txt") {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::stringstream ss(line);
                std::string code, name;
                double cost, price;
                int quantity;

                std::getline(ss, code, ',');
                std::getline(ss, name, ',');
                ss >> cost;
                ss.ignore(1); 
                ss >> price;
                ss.ignore(1); 
                ss >> quantity;

                productList.push_back(Item(code, name, cost, price, quantity));
            }
            file.close();
        }
    }


    static void SaveProductsToFile(const std::vector<Item>& productList, const std::string& filename = "stock.txt") {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& product : productList) {
                file << product.getcode() << "," << product.getName() << ","
                    << product.getCost() << "," << product.getPrice() << ","
                    << product.getQuantity() << "\n";
            }
            file.close();
        }
    }

private:
    std::string code;
    std::string name;
    double Cprice;
    double Sprice;
    int quantity;
};

void Item::decItem(int nq) {
    quantity = quantity - nq;
    addcost("Sold " + name, nq * (Sprice - Cprice));
}
#endif 
