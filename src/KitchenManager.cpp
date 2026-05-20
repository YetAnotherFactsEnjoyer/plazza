#include "KitchenManager.hpp"

#include <iostream>
#include <stdexcept>

KitchenManager::KitchenManager(int cooksPerKitchen, double multiplier, int restockTime)
  : _cooksPerKitchen(cooksPerKitchen),
    _multiplier(multiplier),
    _restockTime(restockTime),
    _nextKitchenId(1)
{
  createKitchen();
}

void KitchenManager::createKitchen() {
  int id = _nextKitchenId++;

  _kitchens.push_back(
    std::make_unique<Kitchen>(
        id,
        _cooksPerKitchen,
        _multiplier,
        _restockTime
    )
  );
  std::cout << "Kitchen " << id << " created" << std::endl;
}

Kitchen& KitchenManager::getBestKitchen() {
  Kitchen* bestKitchen = nullptr;

  for (const auto& kitchen : _kitchens) {
    if (!kitchen->canAcceptPizza())
      continue;

    if (bestKitchen == nullptr || kitchen->getLoad() < bestKitchen->getLoad())
      bestKitchen = kitchen.get();
  }

  if (bestKitchen == nullptr) {
    createKitchen();
    return *_kitchens.back();
  }

  return *bestKitchen;
}

void KitchenManager::assignPizza(const Pizza& pizza) {
  Kitchen& kitchen = getBestKitchen();

  kitchen.addPizza(pizza);
}

void KitchenManager::displayStatus() const {
  for (const auto& kitchen : _kitchens)
    kitchen->displayStatus();
}
