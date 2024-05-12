//
// Created by utilizator2 on 09.05.2024.
//

#ifndef DOMAIN_H
#define DOMAIN_H

#pragma once
#include <iostream>
#include <string>

using std::string;
using std::cout;

class Book{

private:
    string title;
    string author;
    string type;
    int app_year;
public:
    Book() = default;

    Book(const string title_b,const string author_b,const string type_b,int year_b):
            title{title_b},author{author_b},type{type_b},app_year{year_b}{};


    // Book(const Book& book):
    //      title{ book.title }, author{ book.author }, type{ book.type }, app_year{ book.app_year } {
    //cout << "Hiiii\n";
    //}

    string get_title() const {
        return title;
    }
    string get_author() const {
        return author;
    }
    string get_type() const {
        return type;
    }
    int get_year() const {
        return app_year;
    }
    friend class BookRepo;
};


bool compTitle(const Book& book1,const Book& book2);

bool compAuthor(const Book& book1,const Book& book2);

bool compYearType(const Book& book1,const Book& book2);

#endif //DOMAIN_H
