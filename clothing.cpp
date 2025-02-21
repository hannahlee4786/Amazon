#include <sstream>
#include <iomanip>
#include "clothing.h"

using namespace std;

// Constructor
Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) :
  Product(category, name, price, qty) {
    size_ = size;
    brand_ = brand;
}

// Destructor
Clothing::~Clothing() {

}

// Function: returns set with keywords for clothing item (name, brand)
std::set<std::string> Clothing::keywords() const {
  std::set<std::string> clothingWords; // Container for clothing's keywords
  
  std::set<std::string> nameWords = parseStringToWords(name_);
  std::set<std::string> brandWords = parseStringToWords(brand_);
  // Add name/brand of clothing keywords
  clothingWords = setUnion(nameWords, brandWords);

  return clothingWords;
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const {
  return false;
}

// Returns a string of the clothing product
std::string Clothing::displayString() const {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(2) << price_;

  std::string c = name_ + "\nSize: " + size_ + " Brand: "
                  + brand_ + '\n' + oss.str() + " " + std::to_string(qty_) + " left.";
  return c;
}

// Prints out the string of the clothing product
void Clothing::dump(std::ostream& os) const {
  os << category_ << std::endl;
  os << name_ << std::endl;
  os << std::fixed << std::setprecision(2) << price_ << std::endl;
  os << qty_ << std::endl;
  os << size_ << std::endl;
  os << brand_ << std::endl;
}
