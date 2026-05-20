#pragma once

#include "Pizza.hpp"
#include "Stock.hpp"
#include "ThreadPool.hpp"

class Kitchen {
public:
  Kitchen(int id, int cooksCount, double multiplier, int restockTime);
  ~Kitchen();
  bool canAcceptPizza() const;
  void addPizza(const Pizza& pizza);
  void displayStatus() const;
private:
  int getCurrentLoad() const;
  int _id;
  int _cooksCount;
  double _multiplier;
  int _restockTime;
  int _currentLoad;
  int _maxCapacity;
  Stock _stock;
  ThreadPool _threadPool;
};
