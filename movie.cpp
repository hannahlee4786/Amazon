#include <sstream>
#include <iomanip>
#include "movie.h"

using namespace std;

// Constructor
Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) :
  Product(category, name, price, qty) {
    genre_ = genre;
    rating_ = rating;
}

// Destructor
Movie::~Movie() {

}

// Function: returns set with keywords for a movie (name/title, genre)
std::set<std::string> Movie::keywords() const {
  std::set<std::string> movieWords; // Container for movie keywords
  
  std::set<std::string> nameWords = parseStringToWords(name_);
  std::set<std::string> genreWords = parseStringToWords(genre_);
  // Add name/genre key words
  movieWords = setUnion(nameWords, genreWords);

  return movieWords;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const {
  return false;
}

// Returns a string of the movie product
std::string Movie::displayString() const {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(2) << price_;

  std::string m = name_ + "\nGenre: " + genre_ + " Rating: " + rating_ 
                  + '\n' + oss.str() + " " + std::to_string(qty_) + " left.";
  return m;
}

// Prints out the string of the movie product
void Movie::dump(std::ostream& os) const {
  os << category_ << std::endl;
  os << name_ << std::endl;
  os << std::fixed << std::setprecision(2) << price_ << std::endl;
  os << qty_ << std::endl;
  os << genre_ << std::endl;
  os << rating_ << std::endl;
}
