#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include "datastore.h"
#include "movie.h"
#include "book.h"
#include "clothing.h"
#include "util.h"

class MyDataStore : public DataStore {
  public:
  MyDataStore();
  ~MyDataStore();

  // Functions from base class
  void addProduct(Product* p);
  void addUser(User* u);
  std::vector<Product*> search(std::vector<std::string>& terms, int type);
  void dump(std::ostream& ofile);

  // Functions to add item to cart, display cart, make a purchase, 
  // and check if user exists in data store
  void addToCart(std::string username, Product* p);
  std::string displayCart(std::string username);
  void buyingCart(std::string username);
  bool checkUser(std::string user);

  // Data members
  private:
  std::map<std::string, User*> users_;
  std::vector<Product*> products_;
  std::map<std::string, std::set<Product*>> searchProducts_;
  std::map<User*, std::vector<Product*>> userCarts_;
};

#endif