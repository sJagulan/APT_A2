#include "LinkedList.h"

#include <sstream>
#include <iostream>
#include <iomanip>

LinkedList::LinkedList()
{
    head = nullptr;

    // TODO
}

LinkedList::~LinkedList()
{
    // TODO
}

unsigned LinkedList::size() const
{
    return count;
}

void LinkedList::insert(Stock *data)
{
    Node *newNode = new Node(data);
    newNode->data = data;
    newNode->next = nullptr;
    // increment the count
    count += 1;

    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node *current = head;
        // if the head node is greate than the new node, insert the new node at the head.
        if (head->data->name.compare(data->name) > 0)
        {
            newNode->next = head;
            head = newNode;
            return;
        }

        while (current->next != nullptr)
        {
            current = current->next;
            if (current->data->name.compare(data->name) > 0)
            {
                newNode->next = current->next;
                current->next = newNode;
                return;
            }
        }
        current->next = newNode;
    }
}

void LinkedList::reset_on_hand()
{
    Node *current = head;
    while (current != nullptr)
    {
        current->reset_item_count();
        current = current->next;
    }
}

Stock *LinkedList::find_and_remove_item_by_id(const std::string &id)
{
    Stock *result = nullptr;
    // find item by id
    Node *current = head;
    Node *prev = nullptr;
    while (current != nullptr)
    {
        if (current->data->id == id)
        {
            break;
        }
        prev = current;
        current = current->next;
    }

    // if the item is not found, return false
    if (current == nullptr)
    {
        return result;
    }

    // save the result
    result = current->data;
    // decrement the count
    count -= 1;

    // if the item is found, remove it from the list
    if (prev == nullptr)
    {
        head = current->next;
    }
    else
    {
        prev->next = current->next;
    }

    // delete the nodes
    delete current;

    // return the item
    return result;
}

std::string LinkedList::generate_id()
{
    std::string new_id;
    unsigned max_id = 0;
    Node * current = head;
    while (current != nullptr)
    {
        unsigned id = std::stoi(current->data->id.substr(1), nullptr, 10);
        if (id > max_id)
        {
            max_id = id;
        }
        current = current->next;
    }

    std::ostringstream id;
    id << "I" << std::setfill('0') << std::setw(4) << (max_id + 1);
    return id.str();
}

void LinkedList::clear()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current->data;
        delete current;
        current = next;
    }
    head = nullptr;
    count = 0;
}

/* print */
void LinkedList::print()
{
    Node *current = head;
    while (current != nullptr)
    {
        std::cout << current->data->id << " - " << current->data->name << " - " << current->data->description << std::endl;
        current = current->next;
    }
}

void LinkedList::print_items(){
    std::cout << "Items Menu" << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << "ID   |Name";
    for (int i = 0; i < 20; i++){
        std::cout << " ";
    }
    std::cout << "| Available | Price" << std::endl;
    for (int i = 0; i < 40; i++){
        std::cout << "-";
    }
    std::cout << std::endl;
    Node *current = head;
    while (current != nullptr)
    {
        std::cout << current->data->id << "|";
        int spaces = 14;
        std::cout << current->data->name;
        for (int i = 0; i < 24-(current->data->name.length()); i++){
            std::cout <<  " "; 
        }
        std::cout << "|" << current->data->on_hand;
        for (int i = 0; i < 11-std::to_string(current->data->on_hand).length(); i++){
            std::cout <<  " "; 
        }
        std::cout << "|" << (current->data->price.dollars) << "." << (current->data->price.cents) << std::endl;
        current = current->next;
    }
}
void LinkedList::reset_all_stock_counts_to_default()
{
    Node* current = head;
    while (current != nullptr) {
        current->data->on_hand = DEFAULT_STOCK_LEVEL;
        current = current->next;
    }
}

Node* LinkedList::get_head()
const {
    return head;
}


void LinkedList::purchase_item(const std::string &id){
    Stock *result = nullptr;
    // find item by id
    Node *current = head;
    Node *prev = nullptr;
    while (current != nullptr)
    {
        if (current->data->id == id)
        {
            break;
        }
        prev = current;
        current = current->next;
    }

    // if the item is not found, return false
    if (current == nullptr)
    {
        std::cout << "id is not found";
    }
    else{
        std::cout << "You have selected \"" << current->data->name << "\". This will cost you $";
        std::cout << current->data->price.dollars << "." << current->data->price.cents << std::endl;  
        float total = current->data->price.dollars + current->data->price.cents*(0.01);
        int paid;
        while (total > 0){
            std::cout << "you still need to pay: $" << total << std::endl;
            std::cin >> paid;
            if(Coin::is_valid(paid)){
                total = total - paid/100;
            }
            else{
                std::cout << "Error: $" << paid << " is not a valid denomination of Money. Please try again" << std::endl; 
            }
        }
    }
}
