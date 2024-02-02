#ifndef BOOK_H
#define BOOK_H
#include "product.h"

class Book : public Product
{
public:
    Book(const std::string isbn, const std::string author, const std::string category, const std::string name, double price, int qty);
    virtual ~Book();
    /**
     * Returns the appropriate keywords that this product should be associated with
     */
    virtual std::set<std::string> keywords() const;

    /**
     * Allows for a more detailed search beyond simple keywords
     */
    virtual bool isMatch(std::vector<std::string> &searchTerms) const override;
    
    /**
     * Returns a string to display the product info for hits of the search
     */
    virtual std::string displayString() const;

    /**
     * Outputs the product info in the database format
     */
    virtual void dump(std::ostream &os) const override;

    /**
     * Accessors and mutators
     */
    std::string getIsbn() const;
    std::string getAuthor() const;

protected:
    std::string isbn_;
    std::string author_;
};

#endif