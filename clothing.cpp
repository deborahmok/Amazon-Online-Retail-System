#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

Clothing::Clothing(const std::string size, const std::string brand, const std::string category, const std::string name, double price, int qty) : 
    Product(category, name, price, qty),
    size_(size),
    brand_(brand)
{

}

Clothing::~Clothing()
{
}

std::string Clothing::getSize() const
{
    return size_;
}

std::string Clothing::getBrand() const
{
    return brand_;
}

/**
 * Returns the appropriate keywords that this product should be associated with
 */
std::set<std::string> Clothing::keywords() const
{
    std::set<std::string> keywords_;
    std::set<std::string> nameSet = parseStringToWords(name_);
    std::set<std::string> brandSet = parseStringToWords(brand_);
    keywords_ = setUnion(nameSet, brandSet);
    return keywords_;
}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Clothing::displayString() const
{
    std::string display = name_ + "\n"
              + "Size: " + size_ + " Brand: " + brand_ + "\n"
              + std::to_string(price_) + " " + std::to_string(qty_) + " left";
    return display;
}

/**
 * Allows for a more detailed search beyond simple keywords
 */
bool Clothing::isMatch(std::vector<std::string> &searchTerms) const
{
    return false;
}

/**
 * Outputs the product info in the database format
 */
void Clothing::dump(std::ostream &os) const
{
    Product::dump(os);
    os << size_ << "\n"
       << brand_ << std::endl;
}