//
// Created by utilizator2 on 09.05.2024.
//

#include <iostream>
#include <random>
#include <algorithm>
#include "cart.h"

void ShoppingCart::empty_cart(){
    while(!cart.empty())
        cart.pop_back();
}

const vector <Book>& ShoppingCart::getAll_cart() noexcept{
    return cart;
}

void ShoppingCart::add_in_cart(Book& book) {
    cart.push_back(book);
}

void ShoppingCart::add_random(vector<Book> books,size_t nr_books){
    shuffle(books.begin(), books.end(), std::default_random_engine(std::random_device{}()));
    while (cart.size() < nr_books && !books.empty()) {
        cart.push_back(books.back());
        books.pop_back();
    }
}

