#include "GameMaster.hpp"

GameMaster::GameMaster() 
    : generator(std::random_device{}()), distribution(1, 6) 
{
    //Empty
}

int GameMaster::roll_dice()
{
// Simulamos el lanzamiento de dos dados independientes
    int dado1 = distribution(generator);
    int dado2 = distribution(generator);
    int total = dado1 + dado2;

    // Imprimimos el detalle para que el equipo vea los valores individuales
    std::cout << "Dados: [" << dado1 << "] + [" << dado2 << "] = " << total << std::endl;
    
    return total;
}

void GameMaster::play_turn(Player& p)
{
    int result = roll_dice();
    p.move(result);
}