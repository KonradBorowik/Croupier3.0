#include "PlayersInteraction.h"
#include "Player.h"
#include "Table.h"
#include <iostream>
#include <msclr\marshal_cppstd.h>

extern Table newtable;
PlayersInteraction interaction;

int PlayersInteraction::enter_amount(int min, int max) {
	int amount = 0;
	auto prompt = std::string("Enter amount (" + std::to_string(min) + " - " + std::to_string(max) + ")");
	while (amount < min || amount > max) {
		auto input = Microsoft::VisualBasic::Interaction::InputBox(msclr::interop::marshal_as<System::String^>(prompt), "Action", "", -1, -1);
		amount = System::Convert::ToInt32(input);
	}
	return amount;
}
