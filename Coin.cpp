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

    int denomination, count;
    while (infile >> denomination >> count)
    {
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

    for (int i = 0; i < 8; i++) {
        Denomination denom = static_cast<Denomination>(i);
        std::string denomStr = denom_to_string(denom);
        int count = get_count_for_denomination(denom);

        std::cout << denomStr << " | " << count << std::endl;
    }
}

std::string Coin::denom_to_string(Denomination denom) {
    switch (denom) {
        case Denomination::FIVE_CENTS:
            return "5";
        case Denomination::TEN_CENTS:
            return "10";
        case Denomination::TWENTY_CENTS:
            return "20";
        case Denomination::FIFTY_CENTS:
            return "50";
        case Denomination::ONE_DOLLAR:
            return "100";
        case Denomination::TWO_DOLLARS:
            return "200";
        case Denomination::FIVE_DOLLARS:
            return "500";
        case Denomination::TEN_DOLLARS:
            return "1000";
        default:
            return "Unknown";
    }
}

bool Coin::is_valid(int num){

    if (num == 1000){
        return true;
    }
    else if (num == 500){
        return true;
    }
    else if (num == 200){
        return true;
    }
    else if (num == 100){
        return true;
    }
    else if (num == 50){
        return true;
    }
    else if (num == 20){
        return true;
    }
    else if (num == 10){
        return true;
    }
    else if (num == 5){
        return true;
    }
    else {
        return false;
    }
}
