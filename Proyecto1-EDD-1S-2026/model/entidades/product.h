#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>

class Product
{

private:
    std::string name;
    std:: string barcode;
    std:: string category;
    std:: string expiry_date;
    std:: string brand;
    double price;
    int stock;

public:
    Product();
    Product(std::string name,
            std:: string barcode,
            std:: string category,
            std:: string expiry_date,
            std:: string brand,
            double price,
            int stock);
};

#endif // PRODUCT_H
