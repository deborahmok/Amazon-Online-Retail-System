#include <sstream>
#include <iomanip>
#include <string>
#include <set>
#include <vector>
#include <map>
#include "mydatastore.h"
#include "util.h"


Mydatastore::~Mydatastore() 
{
    for(typename std::vector<Product*>::iterator it = product_.begin(); it != product_.end(); ++it)
    {
        delete *it;
    }
    for(typename std::map<std::string, User*>::iterator it = user_.begin(); it != user_.end(); ++it)
    {
        delete it->second;
    }
}

/**
 * Adds a product to the data store
 */
void Mydatastore::addProduct(Product *p)
{
    // p already has all the information    
    product_.push_back(p);
    // updating the map here
    // Extract the keyword of product p here,
    std::set<std::string> kWord =  p->keywords();
    for(typename std::set<std::string>::iterator it = kWord.begin(); it != kWord.end(); ++it)
    {
        if(foundProduct_.find(*it) != foundProduct_.end()) //it exists
        {
            foundProduct_[*it].insert(p);
        }
        else
        {
            std::set<Product*> temp;
            temp.insert(p);
            foundProduct_.insert(std::pair<std::string, std::set<Product *>>(*it, temp));   
        }
    }
}

/**
 * Adds a user to the data store
 */
void Mydatastore::addUser(User *u)
{
    user_[u -> getName()] = u;
    cart_[u] = std::vector<Product*>(); //calling the vector constructor
    //guarentees every user has a cart
}

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
std::vector<Product*> Mydatastore::search(std::vector<std::string> &terms, int type)
{
    // a map that stores term -> results (set of products)
    std::set<Product*> answer;
    // go through all of the terms one by one, getting bunch of sets of products.
    for (unsigned int i = 0; i < terms.size(); ++i)
    {
        std::set<Product *> one = foundProduct_[terms[i]];
        if (i == 0)
        {
            answer = one;
        }
        else if (type == 0)
        {
            answer = setIntersection(answer, one);
        }
        else
        {
            answer = setUnion(answer, one);
        }
    }
    // convert the "answer" set to vector and return.
    std::vector<Product*> result(answer.begin(), answer.end());
    return result;
}

/**
 * Reproduce the database file from the current Products and User values
 */
void Mydatastore::dump(std::ostream &ofile)
{
    ofile << "<products>" << std::endl;
    for(typename std::vector<Product *>::iterator it = product_.begin(); it != product_.end(); ++it)
    {
        (*it)->dump(ofile);
    }
    ofile << "</products>" << std::endl << "<users>" << std::endl;
    for(typename std::map<std::string, User*>::iterator it = user_.begin(); it != user_.end(); ++it)
    {
        (it->second)->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}

void Mydatastore::addCart(std::string username, Product* p)
{
    if(user_.find(username) != user_.end())
    {
        User* newUser = user_.find(username) -> second;
        if (cart_.find(newUser) != cart_.end())
        {
            cart_[newUser].push_back(p);
        }
        else
        {
            std::vector<Product*> temp;
            temp.push_back(p);
            cart_[newUser] = temp;
        }
    }
    else
    {
        std::cout << "Invalid request";
    }
}

std::string Mydatastore::viewCart(std::string username)
{
    std::string message = "";
    if(user_.find(username) != user_.end())
    {
        User* newUser = user_.find(username) -> second;
        if (cart_.find(newUser) == cart_.end())
        {
            message = "Invalid username";
        }
        else
        {
            int count = 1;
            for (std::vector<Product*>::iterator it = cart_[newUser].begin(); it != cart_[newUser].end(); ++it)
            {
                message += "Item " + std::to_string(count) + "\n";
                message += (*it)->displayString() + "\n";
                count++;
            }
        }
    }
    return message;
}

void Mydatastore::buyCart(std::string username)
{
    if(user_.find(username) != user_.end())
    {
        User* newUser = user_.find(username) -> second;
        std::vector<Product*> temp_Cart;
        //create a new vector which has all the items that user isn't able to buy
        for (std::vector<Product*>::iterator it = cart_[newUser].begin(); it != cart_[newUser].end(); ++it)
        {
            Product* currentProduct = *it;
            if(currentProduct->getQty() > 0 && (newUser->getBalance() >= currentProduct->getPrice()))
            {
                currentProduct->subtractQty(1);
                //it should be removed from the user's cart
                newUser->deductAmount(currentProduct->getPrice());
            }
            else
            {
                //add to the vector if they can't afford
                temp_Cart.push_back(currentProduct);
            }
        }
        //set the cart of the user to the new vector; updating the cart
        cart_[newUser] = temp_Cart;
    }
}

bool Mydatastore::checkUser(std::string user)
{
    if(user_.find(user) != user_.end())
    {
        return false;
    }
    else
    {
        return true;
    }
}