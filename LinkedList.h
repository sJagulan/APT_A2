#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"

class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    // more functions to be added perhaps...

    // get the number of nodes in the list
    unsigned size() const;

    // insert a new node to the of the list sorted by stock name
    void insert(Stock *data);

    // reset the number of items on hand to the default value
    void reset_on_hand();
    
    // find and remove a node from the list by id
    Stock * find_and_remove_item_by_id(const std::string &id);

    // generate new available and unique id
    std::string generate_id();
    
    // clear the list
    void clear();

    // print the list
    void print();
private:
    // the beginning of the list
    Node *head;

    // how many nodes are there in the list?
    unsigned count;
};

#endif // LINKEDLIST_H
