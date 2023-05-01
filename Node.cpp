#include "Node.h"

#include <algorithm>
#include <string>

Node::Node(Stock * data){
    data = data;
    default_num_on_hand = data->on_hand;
};

Node::~Node(){
}

void Node::reset_item_count(){
    data->on_hand = default_num_on_hand;
};

Price Price::parsePrice(const std::string &price)
{

    Price p;
    auto dot_pos = std::find(price.begin(), price.end(), '.');
    p.dollars = std::stoi(std::string(price.begin(), dot_pos));
    p.cents = std::stoi(std::string(dot_pos + 1, price.end()));
    return p;
};