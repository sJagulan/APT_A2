#ifndef COIN_H
#include <string>
#define COIN_H

// Coin.h defines the coin structure for managing currency in the system. 
#define DELIM ","  // delimiter 

// enumeration representing the various types of currency available in the system. 
enum Denomination
{
    FIVE_CENTS, TEN_CENTS, TWENTY_CENTS, FIFTY_CENTS, ONE_DOLLAR, 
    TWO_DOLLARS, FIVE_DOLLARS, TEN_DOLLARS
};


// represents a coin type stored in the cash register perhaps. Each demonination
// will have exactly one of these in the cash register.
class Coin
{
public:
    Coin();
    Coin(int denom, unsigned int qty) : denomination(denom), quantity(qty) {
        // Constructor implementation
    }

    int denomination;
    unsigned int quantity;
    static bool is_valid(int num);

    Coin(Denomination denomination, int count);
    enum Denomination denom;
    bool load_coin_data(const std::string &coinsfile);
    void reset_coin_count();
    void display_coins();
    std::string denom_to_string(Denomination denom);
    int get_count_for_denomination(Denomination denom);
    unsigned count;
    // the count of how many of these are in the cash register
    Coin* next;
    static Coin* coins_head;
};

#endif // COIN_H
