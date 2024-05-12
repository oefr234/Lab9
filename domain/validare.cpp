//
// Created by utilizator2 on 09.05.2024.
//

#include <iostream>
#include <sstream>
#include <assert.h>
#include "domain.h"
#include "validare.h"


void Validate::validate(const Book& book) {
    vector<string> errors;
    if (book.get_title().size() == 0) errors.push_back("Titlu invalid\n");
    if (book.get_author().size() == 0) errors.push_back("Nume autor invalid\n");
    if (book.get_type().size() == 0) errors.push_back("Tip invalid\n");
    if (book.get_year() < 0 || book.get_year() > 2024) errors.push_back("An invalid\n");
    if (errors.size() > 0)
        throw ValidateException(errors);
}

ostream& operator<<(ostream& out,const ValidateException& except) {
    for (const auto& ex : except.errors) {
        out << ex<< " ";
    }
    return out;
}