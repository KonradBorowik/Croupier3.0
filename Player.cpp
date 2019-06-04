#include "Player.h"

#include <iostream>
#include "Table.h"
#include "PlayersInteraction.h"
#include <algorithm>

extern PlayersInteraction interaction;

void Player::put_on_table(int amount) {
    newtable->stack += amount;
    cash -= amount;
    current_bid += amount;
    newtable->highest_bid = current_bid;
    interaction.print_info(this);
}

void Player::smallblind() {
    put_on_table(std::min(cash, newtable->small_blind));
}

void Player::bigblind() {
    put_on_table(std::min(cash, newtable->big_blind));
}

void Player::check() {
}

void Player::bid() {
    put_on_table(interaction.enter_amount(1, cash));
}

void Player::call() {
    put_on_table(std::min(cash, newtable->highest_bid - current_bid));
}

void Player::raise() {
    put_on_table(interaction.enter_amount(1, cash - newtable->highest_bid + current_bid) + newtable->highest_bid - current_bid);
}

void Player::fold() {
    folded = true;
}

void Player::all_in() {
    put_on_table(cash);
}