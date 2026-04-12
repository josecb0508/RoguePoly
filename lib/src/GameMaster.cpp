#include "GameMaster.hpp"

int GameMaster::RollDice()
{
    static std::random_device rd;
    std::mt19937 gen(rd());
    static std::uniform_int_distribution<> d12(1, 12);
    int result = d12(gen);
    std::cout <<"Dado: " << result << std::endl;
    return result;
}

void GameMaster::PlayTurn(Player& p)
{
    int result = RollDice();
    p.move(result);
}