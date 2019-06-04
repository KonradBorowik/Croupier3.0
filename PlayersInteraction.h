#pragma once

#include <string>
#include <vector>

class Player;

class PlayersInteraction {
public:
    int choose_option_with_chceck_and_bid(Player *);

    int choose_option_with_call_and_raise(Player *);

    int enter_amount(int min, int max);

    int number_of_players();

    std::string enter_name(int i);

    int enter_buyin();

    int enter_smallblind();

    int enter_bigblind();

    int winner(int min, int max);

    void deal_counter(int d);

    void round_counter(int r);

    void print_info(Player* p);

    void print_list_of_players(std::vector<Player*> ap);

    void print_bank_balance();

    void who_lost(int i);
};