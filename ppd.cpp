#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "Coin.h"
#include "LinkedList.h"

LinkedList stockList;

void display_menu(bool admin){
    if (admin == true){
        std::cout << "Main Menu:" << std::endl;
        std::cout << "\t1. Display Items" << std::endl;
        std::cout << "\t2. Purchase Items" << std::endl;
        std::cout << "\t3. Save and Exit" << std::endl;
        std::cout << "Administrator-Only Menu:" << std::endl;
        std::cout << "\t4. Add Item" << std::endl;
        std::cout << "\t5. Remove Item" << std::endl;
        std::cout << "\t6. Display Coins" << std::endl;
        std::cout << "\t7. Reset Stock" << std::endl;
        std::cout << "\t8. Reset Coins" << std::endl;
        std::cout << "\t9. Abort Program" << std::endl;
        std::cout << "Select your option (1-9): " << std::endl;
    }
    else {
        std::cout << "Main Menu:" << std::endl;
        std::cout << "\t1. Display Items" << std::endl;
        std::cout << "\t2. Purchase Items" << std::endl;
        std::cout << "\t3. Save and Exit" << std::endl;
        std::cout << "Select your option (1-3): " << std::endl;
    }
}


int add_item(void)
{
    // The id of the new stock will be: I0006
    // Enter the item name: Baklava
    // Enter the item description: rich, sweet pastry made of layers of filo filled with chopped
    // nuts and sweetened and held together with syrup or honey.
    // Enter the price for the item: 8.00
    // This item "Baklava - rich, sweet pastry made of layers of filo filled with chopped nuts
    // and sweetened and held together with syrup or honey." has now been added to the menu."

    // create a new stock item
    Stock *newItem = new Stock;

    // set the id of the new stock item
    newItem->id = stockList.generate_id();

    std::cout << "The id of the new stock will be: " << newItem->id << std::endl;
    // read item name
    std::cout << "Enter the item name: ";
    std::getline(std::cin, newItem->name);
    // read item description
    std::cout << "Enter the item description: ";
    std::getline(std::cin, newItem->description);
    // read price
    std::string price;
    std::cout << "Enter the price for the item: ";
    std::getline(std::cin, price);
    newItem->price = Price::parsePrice(price);
    // set on_hand to DEFAULT_STOCK_LEVEL
    newItem->on_hand = DEFAULT_STOCK_LEVEL;

    // add the new stock item to the list
    stockList.insert(newItem);

    // print a message to the user
    std::cout << "This item \"" << newItem->name << " - " << newItem->description
              << "\" has now been added to the menu." << std::endl;

    return 0;
}

int remove_item()
{
    std::string id;

    std::cout << "Enter the item id of the item to remove from the menu: ";
    std::getline(std::cin, id);

    // find and remove the item from the list
    auto item = stockList.find_and_remove_item_by_id(id);
    if (item != nullptr)
    {
        std::cout << item->id << " - " << item->name << " - " << item->description
                  << " has been removed from the system." << std::endl;
        delete item;
        //abort
    }
    else
    {
        std::cout << "Item not found." << std::endl;
    }

    return 0;
}
std::string priceToString(double price) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << price;
    return ss.str();
}
void save_stock_data(const std::string &stock_file, const LinkedList &stock_list) {
    std::ofstream outfile(stock_file);
    if (!outfile) {
        std::cerr << "Error: Unable to open stock file for writing." << std::endl;
        exit(EXIT_FAILURE);
    }
 
    Node *current = stock_list.get_head();
    while (current != nullptr) {
        Stock *item = current->data;
        outfile << item->id << "|" << item->name << "|" << item->description << "|"
                << priceToString(item->price.getPrice()) << "|" << item->on_hand << std::endl;
        current = current->next;
    }
 
    outfile.close();
}

void save_coin_data(const std::string &coins_file, const Coin *coins_list) {
    std::ofstream outfile(coins_file);
    if (!outfile) {
        std::cerr << "Error: Unable to open coins file for writing." << std::endl;
        exit(EXIT_FAILURE);
    }

    Coin *current = coins_list->coins_head;
    while (current != nullptr) {
        outfile << static_cast<int>(current->denom) << "," << current->count << std::endl;
        current = current->next;
    }

    outfile.close();
}


// Add this function to load coins data from the file
void load_coins(const std::string &coins_file, Coin* &coins_head) {
    std::ifstream infile(coins_file);
    if (!infile) {
        std::cerr << "Error: Unable to open coins file." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    Coin* last_coin = nullptr;
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        int denom;
        unsigned quantity;

        if (std::getline(ss, line, ',')) {
            denom = std::stoi(line);
        } else {
            std::cerr << "Error: Invalid coins file format." << std::endl;
            exit(EXIT_FAILURE);
        }

        if (std::getline(ss, line, ',')) {
            quantity = std::stoi(line);
        } else {
            std::cerr << "Error: Invalid coins file format." << std::endl;
            exit(EXIT_FAILURE);
        }

        Coin* new_coin = new Coin(denom, quantity);
        if (last_coin == nullptr) {
            coins_head = new_coin;
        } else {
            last_coin->next = new_coin;
        }
        last_coin = new_coin;
    }
}



/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options.
 * Make sure free memory and close all files before exiting the program.
 **/
int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <stockfile> <coinsfile>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string stockFile = argv[1];
    std::string coinsFile = argv[2];

    // Load stock data
    std::ifstream infile(stockFile);
    if (!infile) {
        std::cerr << "Error: Unable to open stock file." << std::endl;
        return EXIT_FAILURE;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        Stock *newItem = new Stock;

        if (std::getline(ss, newItem->id, '|') &&
            std::getline(ss, newItem->name, '|') &&
            std::getline(ss, newItem->description, '|')) {

            std::string price_str;
            if (std::getline(ss, price_str, '|')) {
                newItem->price = Price::parsePrice(price_str);
            } else {
                std::cerr << "Error: Invalid stock file format." << std::endl;
                exit(EXIT_FAILURE);
            }

            if (std::getline(ss, line, '|')) {
                newItem->on_hand = std::stoi(line);
            } else {
                std::cerr << "Error: Invalid stock file format." << std::endl;
                exit(EXIT_FAILURE);
            }

            stockList.insert(newItem);
        } else {
            std::cerr << "Error: Invalid stock file format." << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    infile.close();

    // Load coins data
    Coin* coins_head = nullptr;
    load_coins(coinsFile, coins_head);
    
    //std::cout << "Just a test, nothing implemented yet!" << std::endl;
    std::string inp;
    while(inp != "3" && inp != "9"){
        display_menu(true);
        std::getline(std::cin >> std::ws, inp);
        if (inp == "1"){
            stockList.print_items();
        }
        if (inp == "2"){
            std::cout << "Purchase Item" << std::endl;
            std::cout << "-------------" << std::endl;
            std::cout << "Please enter the id of the item you wish to purchase:" << std::endl;
            std::string choice;
            std::getline(std::cin, choice);
            stockList.purchase_item(choice);
        }
        if (inp == "4"){
            add_item();
        }
        if (inp == "5"){
            remove_item();
        }
        
        if (inp == "6") {
            if (coins_head != nullptr) {
                coins_head->display_coins();
            } 
            else {
                std::cout << "No coins available." << std::endl;
            }
        }
        if (inp == "7"){
            stockList.reset_all_stock_counts_to_default();
        }
        if (inp == "8") {
            if (coins_head != nullptr) {
                coins_head->reset_coin_count();
            } 
            else {
                std::cout << "No coins available to reset." << std::endl;
            }
        }
        
    }
    if (inp == "3"){
        save_stock_data(stockFile, stockList);
        save_coin_data(coinsFile, Coin::coins_head);
        std::cout << "Data saved. Exiting program." << std::endl;
    }
    
    stockList.clear();
    return EXIT_SUCCESS;
}
