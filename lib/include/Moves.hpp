#ifndef MOVES_HPP
#define MOVES_HPP
#include <string>
#include "Element.hpp"

struct Moves
{
std::string name;
    int power;
    int cost;
    int value;
    Element type_move;

    Moves(std::string n = "None", int p = 0, int c = 0, int v = 0, Element t = NEUTRAL) : name(n), power(p), cost(c), value(v), type_move(t) {}
};

#endif