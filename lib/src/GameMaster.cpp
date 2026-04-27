#include "GameMaster.hpp"

int GameMaster::roll_dice()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> d12(1, 12);
    int result = d12(gen);
    std::cout << "Dado: " << result << std::endl;
    return result;
}

void GameMaster::play_turn(Player& p)
{
    int result = roll_dice();
    p.move(result);
}


template <typename T>
void insertion_sort(std::vector<T>& c)
{
    for (size_t i = 1; i < c.size(); ++i)
    {
        T key = c[i];
        int j = (int)i - 1;
        while (j >= 0 && c[j].second < key.second) 
        {
            c[j + 1] = c[j];
            j--;
        }
        c[j + 1] = key;        
    }
}

void GameMaster::set_turn_player(std::vector<Player>& players)
{
    std::vector<std::pair<size_t, int>> player_rolls;

    for (size_t i = 0; i < players.size(); ++i)
    {
        int current_roll = 0;
        bool number_repeated = true;

        while (number_repeated)
        {
            current_roll = roll_dice();
            bool found_collision = false;

            for (size_t j = 0; j < player_rolls.size(); ++j)
            {
                if (player_rolls[j].second == current_roll)
                {
                    found_collision = true;
                }
            }

            if (!found_collision) 
            {
                number_repeated = false; 
            }
        }
        player_rolls.push_back({i, current_roll});
    }

    insertion_sort(player_rolls);

    std::vector<Player> sorted_players;
    std::cout << "\n=== RESULTADOS DEL SORTEO ===" << std::endl;

    for (size_t i = 0; i < player_rolls.size(); ++i) 
    {
        size_t original_index = player_rolls[i].first;
        std::string final_name = "Player " + std::to_string(i + 1);
        players[original_index].set_name(final_name);
        players[original_index].set_order((int)i);
        
        std::cout << final_name << " saco: " << player_rolls[i].second << " (Posicion " << i+1 << ")" << std::endl;
        
        sorted_players.push_back(players[original_index]);
    }

    players = sorted_players; 
    std::cout << "=============================\n" << std::endl;
}

void GameMaster::give_properties(Player&p, Square& s)
{
    char choice;
    if(s.type == TERRITORY)
    {
        if (s.type == TERRITORY) 
        {
            if (s.propietary == nullptr) 
            {
                char choice = 'n'; 
                std::cout << "¿Deseas adquirir " << s.name << "? (y/n): ";
                std::cin >> choice;

            if (choice == 'y' || choice == 'Y') 
            {
                s.propietary = &p;
                p.add_property(&s);
                std::cout << "Propiedad adquirida." << std::endl;
            }
            else
            {
                std::cout << "No compras la casilla. La casilla sigue disponible." << std::endl;
            }
        } 
        else 
        {
            if (s.propietary != &p) 
            {
                std::cout << "Esta casilla ya tiene dueño." << std::endl;
            }
        }
        }
    }
}