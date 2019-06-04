#include "PlayersInteraction.h"
#include "Player.h"
#include "Table.h"
#include <iostream>
#include <msclr\marshal_cppstd.h>

extern Table newtable;

int PlayersInteraction::enter_amount(int min, int max) {
    int amount = 0;
	auto prompt = std::string("Enter amount (") + std::to_string(min) + " - " + std::to_string(max) + ")";
    while (amount < min || amount > max) {
		auto input = Microsoft::VisualBasic::Interaction::InputBox(msclr::interop::marshal_as<System::String^>(prompt), "b", "", -1, -1);
		amount = System::Convert::ToInt32(input);
    }
    return amount;
}

int PlayersInteraction::number_of_players() {//to bedzie niepotrzebne
    std::cout << "How many players: ";
    int number;
    std::cin >> number;
    return number;
}

std::string PlayersInteraction::enter_name(int i) {
    std::string name;
    std::cout << "Enter name for player " << i << " ";
    std::cin >> name;
    return name;
}

int PlayersInteraction::enter_buyin() {
    std::cout << "Buy-in: ";
    int bi;
    std::cin >> bi;
    return bi;
}

int PlayersInteraction::enter_smallblind() {
    int sb;
    std::cout << "Small blind: ";
    std::cin >> sb;
    return sb;
}

int PlayersInteraction::enter_bigblind() {
    int bb;
    std::cout << "Big blind: ";
    std::cin >> bb;
    return bb;
}

int PlayersInteraction::winner(int min, int max) {
    int number = 0;
    std::cout << "Who won? ";
    while (number < min || number > max) {
        std::cin >> number;
        if (number < min || number > max) {
            std::cout << "No such player moron" << std::endl;
        }
    }
    return number;
}

void PlayersInteraction::deal_counter(int d) {
    std::cout << "Deal: " << d << std::endl;
}

void PlayersInteraction::round_counter(int r) {
    if (r == 1) {
        std::cout << "Preflop" << std::endl;
    } else if (r == 2) {
        std::cout << "flop" << std::endl;
    } else if (r == 3) {
        std::cout << "Turn" << std::endl;
    } else if (r == 4) {
        std::cout << "River" << std::endl;
    }
}

void PlayersInteraction::print_info(Player* p) {
    std::cout << p->name << "'s account: " << p->cash << "; Current bid: " << p->current_bid << "; Money on table: "
              << newtable.stack << "; Highest bid: " << newtable.highest_bid << std::endl;
}

int PlayersInteraction::choose_option_with_call_and_raise(Player *p) {
    int number_of_option = 0;
    std::cout << p->name << " choose: 1 for call, 2 for raise, 3 for all-in, 4 for fold ";

    while (number_of_option < 1 || number_of_option > 4) {
        std::cin >> number_of_option;
        if (number_of_option < 1 || number_of_option > 4) {
            std::cout << "Invalid option, choose again ";
            std::cin >> number_of_option;
        }
    }

    return number_of_option;
}

int PlayersInteraction::choose_option_with_chceck_and_bid(Player *p) {
    int number_of_option = 0;
    std::cout << p->name << " choose: 1 for check, 2 for bid, 3 for all-in, 4 for fold. ";

    while (number_of_option < 1 || number_of_option > 4) {
        std::cin >> number_of_option;
        if (number_of_option < 1 || number_of_option > 4) {
            std::cout << "Invalid option, choose again ";
            std::cin >> number_of_option;
        }
    }

    return number_of_option;
}

void PlayersInteraction::print_bank_balance() {
    for (auto & player : newtable.players) {
        std::cout << player.name << " has " << player.cash << "$$$" << std::endl;
    }
}

void PlayersInteraction::print_list_of_players(std::vector<Player*> ap) {
    for (int i = 0; i < ap.size(); i++) {
        std::cout << i + 1 << " for " << ap[i]->name << std::endl;
    }
}

void PlayersInteraction::who_lost(int i){
    std::cout << newtable.players[i].name << " has lost. " << std::endl;
}