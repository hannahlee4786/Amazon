#include <sstream>
#include <set>
#include <vector>
#include <map>
#include "mydatastore.h"

using namespace std;

// Constructor
MyDataStore::MyDataStore() {
}

// Destructor
MyDataStore::~MyDataStore() {
  // Deallocate products
  for (typename std::vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
    delete *it;
  }
  // Deallocate users
  for (typename std::map<std::string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
    delete it->second;
  }
}

// Adds a product to data store
void MyDataStore::addProduct(Product* p) {
  // Add p to the products_ vector
  products_.push_back(p);

  // Update the searchProducts_ map with keywords
  std::set<std::string> words = p->keywords();
  for(typename std::set<std::string>::iterator it = words.begin(); it != words.end(); ++it) {
    if(searchProducts_.find(*it) != searchProducts_.end()) {
      searchProducts_[*it].insert(p);
    }
    else {
      std::set<Product*> temp;
      temp.insert(p);
      searchProducts_.insert(std::pair<std::string, std::set<Product *>>(*it, temp));;   
    }
  }
}

// Adds a user to data store
void MyDataStore::addUser(User* u) {
  // Adds user to users_vector
  users_[u->getName()] = u;
  // Also adds a cart for the user
  userCarts_[u] = std::vector<Product*>();
}

// Searches for products with key words
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
  // Set for products
  std::set<Product*> s;

  // Go through all terms 
  for (int i = 0; i < terms.size(); ++i) {
    // Default set of products
    std::set<Product*> def = searchProducts_[terms[i]];
    if (i == 0){
      s = def;
    }
    else if (type == 0) {
      s = setIntersection(s, def);
    }
    else {
      s = setUnion(s, def);
    }
  }
  std::vector<Product*> answer(s.begin(), s.end()); // Turn set into vector
  return answer;
}

// Prints out to file
void MyDataStore::dump(std::ostream& ofile) {
  ofile << "<products>" << std::endl;
  for (int i = 0; i < products_.size(); i++) {
    products_[i]->dump(ofile);
  }

  ofile << "</products>" << std::endl;
  ofile << "<users>" << std::endl;

  for(typename std::map<std::string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
    (it->second)->dump(ofile);
  }
  
  ofile << "</users>" << std::endl;
}

// Adds product to user's cart
void MyDataStore::addToCart(std::string username, Product* p) {
  // Check if user exists in data store
  if(users_.find(username) != users_.end()) {
    User* newUser = users_.find(username)->second;
    if (userCarts_.find(newUser) != userCarts_.end()) {
      userCarts_[newUser].push_back(p);
    }
    else {
      std::vector<Product*> temp;
      temp.push_back(p);
      userCarts_[newUser] = temp;
    }
  }
  else{
    std::cout << "Invalid request";
  }
}

// Displays user's cart
std::string MyDataStore::displayCart(std::string username) {
  string message = "";

  if(users_.find(username) != users_.end()) {
    User* newUser = users_.find(username)->second;
    if (userCarts_.find(newUser) == userCarts_.end()) {
      message = "Invalid username";
    }
    else {
      int count = 1;
      for (std::vector<Product*>::iterator it = userCarts_[newUser].begin(); it != userCarts_[newUser].end(); ++it) {
        message += "Item " + std::to_string(count) + "\n";
        message += (*it)->displayString() + "\n";
        count++;
      }
    }
  }
  return message;
}

// User makes purchase of their cart
void MyDataStore::buyingCart(std::string username) {
  // Checks for valid user
  if (users_.find(username) != users_.end()) {
    User* newUser = users_.find(username)->second;
    std::vector<Product*> tempCart; // Temporary cart after valid purchases

    // Go through each product in the cart
    for (std::vector<Product*>::iterator it = userCarts_[newUser].begin(); it != userCarts_[newUser].end(); ++it) {
      Product* currentProduct = *it;
      // Checks if product is available AND user has enough credit
      if(currentProduct->getQty() > 0 && (newUser->getBalance() >= currentProduct->getPrice())) {
        currentProduct->subtractQty(1);
        newUser->deductAmount(currentProduct->getPrice());
      }
      else { // User can't affort, add it to temporary cart
        tempCart.push_back(currentProduct);
      }
    }
    // Update user's cart
    userCarts_[newUser] = tempCart;
  }
}

// Checks if user exists in data store
bool MyDataStore::checkUser(std::string user) {
  if(users_.find(user) != users_.end()) {
    return false;
  }
  else {
    return true;
  }
}