#include "GameMaster.hpp"

int GameMaster::roll_dice()
{
    static std::random_device rd;
    std::mt19937 gen(rd());
    static std::uniform_int_distribution<> d12(1, 12);
    int result = d12(gen);
    std::cout <<"Dado: " << result << std::endl;
    return result;
}

void GameMaster::play_turn(Player& p)
{
    int result = roll_dice();
    p.move(result);
}