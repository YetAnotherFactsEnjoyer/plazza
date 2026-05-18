#pragma once

#include "Pizza.hpp"

#include <map>
#include <string>
#include <vector>

enum class Ingredient {
    Dough,
    Tomato,
    Gruyere,
    Ham,
    Mushrooms,
    Steak,
    Eggplant,
    GoatCheese,
    ChiefLove
};

class Stock {
public:
    Stock();

    bool hasIngredients(const Pizza& pizza) const;
    void consumeIngredients(const Pizza& pizza);
    void regenerate();
    void display() const;

private:
    std::vector<Ingredient> getIngredientsForPizza(const Pizza& pizza) const;
    std::string ingredientToString(Ingredient ingredient) const;

    std::map<Ingredient, int> _ingredients;
};
