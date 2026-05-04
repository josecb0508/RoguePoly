#include "MoveFactory.hpp"

MoveFactory::MoveFactory()
{
    compendium[1] = Moves("Golpe", 10, 0, 0, NEUTRAL);
    compendium[2] = Moves("Bola de Fuego", 30, 10, 0, FIRE);
    compendium[3] = Moves("Mega Voltaje", 25, 8, 0, THUNDER);
    compendium[4] = Moves("Ventisca Eterna", 35, 12, 0, ICE);
    compendium[5] = Moves("Tiro Vendaval", 20, 6, 0, WIND);
}

MoveFactory& MoveFactory::get_move()
{
    static MoveFactory move;
    return move;
}

Moves MoveFactory::create_move(int id)
{
    if(compendium.find(id) != compendium.end())
    {
        return compendium[id];
    }
    return Moves("Move not valid", 0 ,0 ,0, NEUTRAL);
}