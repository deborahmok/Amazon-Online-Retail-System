#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include "datastore.h"

/**
 * DataStore Interface needed for parsing and instantiating products and users
 *
 * A derived version of the DataStore can provide other services as well but
 * must support those below
 *
 * DO NOT EDIT
 */

class Mydatastore : public DataStore
{
public:
    ~Mydatastore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product *p);

    /**
     * Adds a user to the data store
     */
    void addUser(User *u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product *> search(std::vector<std::string> &terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream &ofile);


    std::vector<Product*> addCart(std::string u, Product *p);

    std::string viewCart(std::string u);

    void buyCart(std::string u);

private:
    std::vector<Product*> product_;
    std::map<std::string, User*> user_;
    std::map<std::string, std::set<Product*>> foundProduct_;
    std::map<User*, std::vector<Product*>> cart_;
};

#endif
