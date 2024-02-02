#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

Book::Book(const std::string isbn, const std::string author, const std::string category, const std::string name, double price, int qty) : 
    Product(category, name, price, qty),
    isbn_(isbn),
    author_(author)
{

}

Book::~Book()
{

}

std::string Book::getIsbn() const
{
    return isbn_;
}

std::string Book::getAuthor() const
{
    return author_;
}

/**
 * Returns the appropriate keywords that this product should be associated with
 */
std::set<std::string> Book::keywords() const
{
    std::set<std::string> keywords_;
    std::set<std::string> nameSet = parseStringToWords(name_);
    std::set<std::string> authorSet = parseStringToWords(author_);
    keywords_ = setUnion(nameSet, authorSet);
    keywords_.insert(isbn_); //.insert only takes the string
    return keywords_;
}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Book::displayString() const
{
    std::string display = name_ + "\n"
              + "Author: " + author_ + " ISBN: " + isbn_ + "\n"
              + std::to_string(price_) + " " + std::to_string(qty_) + "left";
    return display;
}

/**
 * Allows for a more detailed search beyond simple keywords
 */
bool Book::isMatch(std::vector<std::string> &searchTerms) const
{
    return false;
}

/**
 * Outputs the product info in the database format
 */
void Book::dump(std::ostream &os) const
{
    Product::dump(os);
    os << isbn_ << "\n"
       << author_ << std::endl;
}