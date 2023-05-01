#include <iostream>
#include <iomanip>
#include <sstream>
#include "LinkedList.h"

LinkedList stockList;

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

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options.
 * Make sure free memory and close all files before exiting the program.
 **/
int main(int argc, char **argv)
{
    /* validate command line arguments */
    std::cout << "Just a test, nothing implemented yet!" << std::endl;

    add_item();
    add_item();
    //add_item();
    remove_item();
    /* print stockList */
    stockList.print();
    stockList.clear();

    return EXIT_SUCCESS;
}
