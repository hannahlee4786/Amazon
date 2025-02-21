#ifndef CLOTHING_H
#define CLOTHING_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "util.h"

class Clothing : public Product {
  public:
  Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
  ~Clothing();
  std::set<std::string> keywords() const override;
  bool isMatch(std::vector<std::string>& searchTerms) const override;
  std::string displayString() const override;
  void dump(std::ostream& os) const override;
  
  private:
  std::string size_; 
  std::string brand_;
};

#endif