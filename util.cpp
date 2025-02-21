#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <string>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  std::set<std::string> words;
  int size = rawWords.size();
  int idx = 0;
  string current = "";

  while(idx < size) {
    // Check if character is punctuation or space
    if (std::ispunct(rawWords[idx]) || rawWords[idx] == ' ') {
      // Check if current string is empty and length is 2+
      if (!current.empty() && current.size() >= 2) {
        current = convToLower(current);
        words.insert(current); // Add word to set
      }
      current = ""; // Empty the current string
    }
    else {
      current += rawWords[idx]; // Add character to current
    }
    idx++;
   }

   // Insert last word if not empty
   if (!current.empty() && current.size() >= 2) {
      current = convToLower(current);
      words.insert(current);
   }
  return words;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
