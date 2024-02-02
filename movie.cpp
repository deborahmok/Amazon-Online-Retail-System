#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

Movie::Movie(const std::string genre, const std::string rating, const std::string category, const std::string name, double price, int qty) : 
    Product(category, name, price, qty),
    genre_(genre),
    rating_(rating)
{

}

Movie::~Movie()
{
}

std::string Movie::getGenre() const
{
    return genre_;
}

std::string Movie::getRating() const
{
    return rating_;
}

/**
 * Returns the appropriate keywords that this product should be associated with
 */
std::set<std::string> Movie::keywords() const
{
    std::set<std::string> keywords_;
    std::set<std::string> nameSet = parseStringToWords(name_);
    std::set<std::string> genreSet = parseStringToWords(genre_);
    keywords_ = setUnion(nameSet, genreSet);
    return keywords_;
}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Movie::displayString() const
{
    std::string display = name_ + "\n"
              + "Genre: " + genre_ + " Rating: " + rating_ + "\n"
              + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
    return display;
}

/**
 * Allows for a more detailed search beyond simple keywords
 */
bool Movie::isMatch(std::vector<std::string> &searchTerms) const
{
    return false;
}

/**
 * Outputs the product info in the database format
 */
void Movie::dump(std::ostream &os) const
{
    Product::dump(os);
    os << genre_ << "\n"
       << rating_ << std::endl;
}