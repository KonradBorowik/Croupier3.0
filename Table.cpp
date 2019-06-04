#include "Table.h"

#include "PlayersInteraction.h"
#include <iostream>
#include <algorithm>

extern PlayersInteraction interaction;

void Table::winnings() {

    std::vector<Player *> active_players;
    for (auto &player : players) {
        if (!player.folded) {
            active_players.push_back(&player);
        }
    }
    interaction.print_list_of_players(active_players);

    int player_who_won = active_players.size() > 1 ? interaction.winner(1, active_players.size()) : 1;

    (active_players[player_who_won - 1])->cash += stack;

    interaction.print_bank_balance();
}

int Table::number_of_players_not_folded() {
    return std::count_if(players.begin(), players.end(), [](Player &player) {return !player.folded;} );
}

void Table::losers() {
    for (int i = players.size() - 1; i > 0 - 1; i--) {
        if (players[i].cash == 0) {
            interaction.who_lost(i);
            players.erase(players.begin() + i);
        }
    }
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
    return std::count_if(players.begin(), players.end(), [](Player &player) { return player.cash > 0; });
}