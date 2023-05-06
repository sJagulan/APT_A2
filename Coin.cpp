#include "Coin.h"
#include "Node.h"
#include <iostream>
#include <fstream>
#include <vector>
std::vector<Coin> coins;
void Coin::load_coin_data(const std::string &coinsfile) {
    std::ifstream infile(coinsfile);
    if (!infile.is_open()) {
        std::cerr << "Error opening coins file: " << coinsfile << std::endl;
        exit(1);
    }

    int denomination, count;
    while (infile >> denomination >> count) {
        Coin coin;
        coin.denom = static_cast<Denomination>(denomination);
        coin.count = count;
        coins.push_back(coin);
    }

    infile.close();
}

void Coin::reset_coin_count() {
    // Assume default count is provided in a constant variable or function
    int default_count = DEFAULT_COIN_COUNT;

    for (Coin &coin : coins) {
        coin.count = default_count;
    }

    std::cout << "All coins have been reset to the default level of " << default_count << std::endl;
}
void Coin::display_coins() {
    std::cout << "Coins Summary\n";
    std::cout << "-------------\n";
    std::cout << "Denomination | Count\n";
    std::cout << "---------------------------\n";

    for (const Coin &coin : coins) {
        std::cout << coin.denom << " Cents | " << coin.count << '\n';
    }
}
