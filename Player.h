#pragma once

#include <string>

class Table;

class Player {
public:
	Table* newtable;
    std::string name;
    int cash;
    int current_bid;
    bool folded = false;
	bool active = true;

public:
    void smallblind();

    void bigblind();

    void check();

    void bid();

    void call();

    void raise();

    void fold();

    void all_in();

    void put_on_table(int amount);
};
