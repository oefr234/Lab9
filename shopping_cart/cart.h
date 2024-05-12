//
// Created by utilizator2 on 09.05.2024.
//

#ifndef CART_H
#define CART_H

#include <iostream>
#include <vector>
#include <string>
#include "../domain/domain.h"

using namespace std;

class ShoppingCart{
private:
    vector <Book> cart;

public:
    ShoppingCart() = default;

    void empty_cart();

    void add_in_cart(Book& book);

    void add_random(vector<Book> books,size_t nr_books);

    const vector <Book>& getAll_cart() noexcept;
};




#endif //CART_H
