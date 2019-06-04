#pragma once

#include <vector>

#include "Player.h"

class Table {
public:
    int stack = 0;
    std::vector<Player> players;
    int highest_bid = 0;
    int small_blind = 0;
    int big_blind = 0;
	int buy_in = 0;
	int round = 0;

    void winnings();
    void losers();
    bool all_players_called();
    int number_of_players_with_cash();
    int number_of_players_not_folded();
};