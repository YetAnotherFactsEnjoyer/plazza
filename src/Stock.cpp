#include "Stock.hpp"

#include <iostream>
#include <stdexcept>

Stock::Stock() {
  _ingredients[Ingredient::Dough] = 5;
  _ingredients[Ingredient::Tomato] = 5;
  _ingredients[Ingredient::Gruyere] = 5;
  _ingredients[Ingredient::Ham] = 5;
  _ingredients[Ingredient::Mushrooms] = 5;
  _ingredients[Ingredient::Steak] = 5;
  _ingredients[Ingredient::Eggplant] = 5;
  _ingredients[Ingredient::GoatCheese] = 5;
  _ingredients[Ingredient::ChiefLove] = 5;
}

std::vector<Ingredient> Stock::getIngredientsForPizza(const Pizza& pizza) const {
  switch (pizza.getType()) {
    case PizzaType::Margarita:
      return {
        Ingredient::Dough,
        Ingredient::Tomato,
        Ingredient::Gruyere
      };

    case PizzaType::Regina:
      return {
        Ingredient::Dough,
        Ingredient::Tomato,
        Ingredient::Gruyere,
        Ingredient::Ham,
        Ingredient::Mushrooms
      };

    case PizzaType::Americana:
      return {
        Ingredient::Dough,
        Ingredient::Tomato,
        Ingredient::Gruyere,
        Ingredient::Steak
      };

    case PizzaType::Fantasia:
      return {
        Ingredient::Dough,
        Ingredient::Tomato,
        Ingredient::Eggplant,
        Ingredient::GoatCheese,
        Ingredient::ChiefLove
      };
  }
  throw std::runtime_error("Unknown pizza type");
}

bool Stock::hasIngredients(const Pizza& pizza) const {
  std::vector<Ingredient> needed = getIngredientsForPizza(pizza);

  for (Ingredient ingredient : needed) {
    auto it = _ingredients.find(ingredient);
      if (it == _ingredients.end() || it->second <= 0)
        return false;
  }
  return true;
}

void Stock::consumeIngredients(const Pizza& pizza) {
  if (!hasIngredients(pizza))
    throw std::runtime_error("Not enough ingredients");

  std::vector<Ingredient> needed = getIngredientsForPizza(pizza);

  for (Ingredient ingredient : needed)
    _ingredients[ingredient]--;
}

void Stock::regenerate(){
  for (auto& pair : _ingredients)
    pair.second++;
}

std::string Stock::ingredientToString(Ingredient ingredient) const {
  switch (ingredient) {
    case Ingredient::Dough:
      return "dough";
    case Ingredient::Tomato:
      return "tomato";
    case Ingredient::Gruyere:
      return "gruyere";
    case Ingredient::Ham:
      return "ham";
    case Ingredient::Mushrooms:
      return "mushrooms";
    case Ingredient::Steak:
      return "steak";
    case Ingredient::Eggplant:
      return "eggplant";
    case Ingredient::GoatCheese:
      return "goat cheese";
    case Ingredient::ChiefLove:
      return "chief love";
  }
  return "unknown";
}

void Stock::display() const
{
  std::cout << "Stock:" << std::endl;

  for (const auto& pair : _ingredients) {
    std::cout << "- "
              << ingredientToString(pair.first)
              << ": "
              << pair.second
              << std::endl;
  }
}
