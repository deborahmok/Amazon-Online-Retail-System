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
    // update the map here
    
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
    // you need a map that stores term -> results (set of products)
    std::set<Product*> answer;
    // std::cout<<"begin priting" <<std::endl;
    // for (std::map<std::string, std::set<Product*>>::iterator it = foundProduct_.begin(); it != foundProduct_.end(); ++it)
    // { 
    //     std::cout << it->first << ": ";
    //     for (std::set<Product*>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
    //     { 
    //     std::cout << *it2 << " ";
    //     }
    //     std::cout<< std::endl;
    // }
    // std::cout << "end print" <<std::endl;

    // go through all of the terms one by one, you'll get bunch of sets of products.
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
    // convert the "answer" set to vector and return that.
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
    // std::cout << username << std::endl;
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
        // std::cout << cart_[newUser].size() << std::endl;
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
        // std::cout << newUser->getName() << std::endl;
        // std::cout << cart_.size() << std::endl;
        if (cart_.find(newUser) == cart_.end())
        {
            message = "Invalid username";
        }
        else
        {
            // std::cout << "hi" << std::endl;
            for (std::vector<Product*>::iterator it = cart_[newUser].begin(); it != cart_[newUser].end(); ++it)
            {
                message += (*it)->displayString();
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
        for (std::vector<Product*>::iterator it = cart_[newUser].begin(); it != cart_[newUser].end(); ++it)
        {
            Product* currentProduct = *it;
            if(currentProduct->getQty() > 0 && (newUser->getBalance() >= currentProduct->getPrice()))
            {
                currentProduct->subtractQty(1);
                newUser->deductAmount(currentProduct->getPrice());
            }
        }
    }
}