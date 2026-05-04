#ifndef MOVE_FACTORY_HPP
#define MOVE_FACTORY_HPP
#include <unordered_map>
#include "Moves.hpp"

class MoveFactory
{
    public:
        std::unordered_map<int, Moves> compendium;
        MoveFactory();
        static MoveFactory& get_move();
        Moves create_move(int id);
        void register_move(int id, const Moves& move);
};

#endif