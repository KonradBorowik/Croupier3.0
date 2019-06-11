#include "Table.h"

#include "PlayersInteraction.h"
#include <iostream>
#include <algorithm>

extern PlayersInteraction interaction;


int Table::number_of_players_not_folded() {
    return std::count_if(players.begin(), players.end(), [](Player &player) {return !player.folded;} );
}

int Table::number_of_active_players() {
	return std::count_if(players.begin(), players.end(), [](Player & player) {return player.active;});
}

bool Table::all_players_called() {
    bool result = true;

    for (auto &player : players) {
            if (!player.folded && player.current_bid != highest_bid) {
                result = false;
            }
        }

    return result;
}

int Table::number_of_players_with_cash() {
    return std::count_if(players.begin(), players.end(), [](Player &player) { return player.active && player.cash > 0 && !player.folded; });
}

Player& Table::winner() {
	return *std::find_if(players.begin(), players.end(), [](Player & player) {return player.active;});
}