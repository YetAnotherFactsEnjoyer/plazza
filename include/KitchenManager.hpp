#pragma once

#include "Kitchen.hpp"
#include "Pizza.hpp"

#include <memory>
#include <vector>

class KitchenManager {
public:
  KitchenManager(int cooksPerKitchen, double multiplier, int restockTime);

  void assignPizza(const Pizza& pizza);
  void displayStatus() const;
private:
  Kitchen& getBestKitchen();
  void createKitchen();

  int _cooksPerKitchen;
  double _multiplier;
  int _restockTime;
  int _nextKitchenId;

  std::vector<std::unique_ptr<Kitchen>> _kitchens;
};
