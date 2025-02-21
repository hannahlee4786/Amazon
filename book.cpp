#include <sstream>
#include <iomanip>
#include "book.h"

using namespace std;

// Constructor
Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author) :
  Product(category, name, price, qty) {
    isbn_ = isbn;
    author_ = author;
}

// Destructor
Book::~Book() {

}

// Returns set with keywords for a book (name/title, author, isbn)
std::set<std::string> Book::keywords() const {
  std::set<std::string> bookWords; // Container for book's keywords

  std::set<std::string> nameWords = parseStringToWords(name_);
  std::set<std::string> authorWords = parseStringToWords(author_);
  // Add name/title of book keywords
  bookWords = setUnion(nameWords, authorWords);

  // Add ISBN number
  bookWords.insert(isbn_);

  return bookWords;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const {
  return false;
}

// Returns a string of the book product
std::string Book::displayString() const {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(2) << price_;

  std::string b = name_ + "\nAuthor: " + author_ + " ISBN: " + isbn_ 
            + '\n' + oss.str() + " " + std::to_string(qty_) + " left.";
  return b;
}

// Prints out the string of the book product
void Book::dump(std::ostream& os) const {
  os << category_ << std::endl;
  os << name_ << std::endl;
  os << std::fixed << std::setprecision(2) << price_ << std::endl;
  os << qty_ << std::endl;
  os << isbn_ << std::endl;
  os << author_ << std::endl;
}
