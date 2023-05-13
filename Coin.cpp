#include "Coin.h"
#include "Node.h"
#include <iostream>
#include <sstream>
#include <fstream>

Coin* Coin::coins_head = nullptr;
Coin::Coin()
{
    next = nullptr;
}

Coin::Coin(Denomination denomination, int count)
{
    denom = denomination;
    this->count = count;
    next = nullptr;
}


bool Coin::load_coin_data(const std::string &coinsfile)
{
    std::ifstream infile(coinsfile);
    if (!infile.is_open())
    {
        return false;
    }

    std::string line;
    while (std::getline(infile, line))
    {
        std::stringstream ss(line);
        std::string denominationStr, countStr;

        // Extract denomination and count from line
        if (std::getline(ss, denominationStr, ',') && std::getline(ss, countStr, ','))
        {
            int denomination = std::stoi(denominationStr);
            int count = std::stoi(countStr);

            // Create a new Coin object and insert it into the linked list in ascending order of denomination.
            Coin* new_coin = new Coin(static_cast<Denomination>(denomination), count);
            if (coins_head == nullptr || coins_head->denom > new_coin->denom) {
                new_coin->next = coins_head;
                coins_head = new_coin;
            } else {
                Coin* current = coins_head;
                while (current->next != nullptr && current->next->denom < new_coin->denom) {
                    current = current->next;
                }
                new_coin->next = current->next;
                current->next = new_coin;
            }
        }
    }

    infile.close();
    return true;
}

void Coin::reset_coin_count() {
    // Assume default count is provided in a constant variable or function
    int default_count = DEFAULT_COIN_COUNT;

    Coin* current = coins_head;
    while (current != nullptr) {
        current->count = default_count;
        current = current->next;
    }

    std::cout << "All coins have been reset to the default level of " << default_count << std::endl;
}

int Coin::get_count_for_denomination(Denomination denom) {
    Coin* current = coins_head;
    while (current != nullptr) {
        if (current->denom == denom) {
            return current->count;
        }
        current = current->next;
    }

    // If the denomination is not found in the linked list, return 0
    return 0;
}

void Coin::display_coins() {
    std::cout << "Coins Summary\n";
    std::cout << "-------------\n";
    std::cout << "Denomination | Count\n";
    std::cout << "---------------------------\n";

    // Create an array with the actual integer denominations
    int denominations[] = {5, 10, 20, 50, 100, 200, 500, 1000};

    for (int i = 0; i < 8; i++) {
        // Convert the integer denomination to the corresponding enum value for the denom_to_string call
        Denomination denom = static_cast<Denomination>(int_to_denom(denominations[i]));
        // debug denom
        //std::cout << "denom: " << denom << std::endl;
        std::string denomStr = denom_to_string(denom);
        // Call get_count_for_denomination with the Denomination denom
        //int count = get_count_for_denomination(denom);

        std::cout << denomStr << " | " << denom << std::endl;
    }
}


std::string Coin::denom_to_string(Denomination denom) {
    if (denom == FIVE_CENTS)
        return "5 Cents";
    else if (denom == TEN_CENTS)
        return "10 Cents";
    else if (denom == TWENTY_CENTS)
        return "20 Cents";
    else if (denom == FIFTY_CENTS)
        return "50 Cents";
    else if (denom == ONE_DOLLAR)
        return "1 Dollar";
    else if (denom == TWO_DOLLARS)
        return "2 Dollars";
    else if (denom == FIVE_DOLLARS)
        return "5 Dollars";
    else if (denom == TEN_DOLLARS)
        return "10 Dollars";
    else
        return "Unknown";
}

Denomination Coin::int_to_denom(int num){

    if (num == 1000){
        return TEN_DOLLARS;
    }
    else if (num == 500){
        return FIVE_DOLLARS;
    }
    else if (num == 200){
        return TWO_DOLLARS;
    }
    else if (num == 100){
        return ONE_DOLLAR;
    }
    else if (num == 50){
        return FIFTY_CENTS;
    }
    else if (num == 20){
        return TWENTY_CENTS;
    }
    else if (num == 10){
        return TEN_CENTS;
    }
    else if (num == 5){
        return FIVE_CENTS;
    }
    else {
        return static_cast<Denomination>(-1);
    }
}

void Coin::deduct_coin(Denomination denomination){
    Coin* current = coins_head;
    while (current != nullptr) {
        if (current->denom == denom) {
            current->count = current->count - 1;
        }
        current = current->next;
    }
}

