#include "product.h"

Product::Product() {}

Product::Product(std::string name,
                 std::string barcode,
                 std::string category,
                 std::string expiry_date,
                 std::string brand,
                 double price,
                 int stock) : name(name),
                              barcode(barcode),
                              category(category),
                              expiry_date(expiry_date),
                              brand(brand),
                              price(price),
                              stock(stock)
{
}
