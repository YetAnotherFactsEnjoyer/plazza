#include "Kitchen.hpp"

#include <iostream>
#include <stdexcept>

Kitchen::Kitchen(int id, int cooksCount, double multiplier, int restockTime)
  : _id(id),
    _cooksCount(cooksCount),
    _multiplier(multiplier),
    _restockTime(restockTime),
    _currentLoad(0),
    _maxCapacity(cooksCount * 2),
    _threadPool(cooksCount, multiplier, _stock)
{
}

Kitchen::~Kitchen()
{
}

int Kitchen::getCurrentLoad() const {
  return _threadPool.getBusyCooks() + _threadPool.getWaitingTasks();
}


bool Kitchen::canAcceptPizza() const {
  return _currentLoad < _maxCapacity;
}

void Kitchen::addPizza(const Pizza& pizza) {
  if (!canAcceptPizza())
    throw std::runtime_error("Kitchen is full");

  std::cout << "Kitchen " << _id
              << " received "
              << pizza.typeToString()
              << " "
              << pizza.sizeToString()
              << std::endl;

  _threadPool.addTask(pizza);
}

void Kitchen::displayStatus() const {
  std::cout << "Kitchen " << _id << ":" << std::endl;
  std::cout << "- cooks: " << _cooksCount << std::endl;
  std::cout << "- busy cooks: " << _threadPool.getBusyCooks() << "/" << _cooksCount << std::endl;
  std::cout << "- waiting pizzas: " << _threadPool.getWaitingTasks() << std::endl;
  std::cout << "- load: " << getCurrentLoad() << "/" << _maxCapacity << std::endl;
  std::cout << "- restock time: " << _restockTime << " ms" << std::endl;
  _stock.display();
}
