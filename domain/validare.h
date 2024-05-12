//
// Created by utilizator2 on 09.05.2024.
//

#ifndef VALIDARE_H
#define VALIDARE_H

#include <iostream>
#include <vector>
#include "domain.h"

using std::string;
using std::vector;
using std::ostream;

class ValidateException {
    vector<string> errors;
public:
    ValidateException(const vector<string>& msg): errors{ msg }{}
    friend ostream& operator<<(ostream& out, const ValidateException& ex);
};

ostream& operator<<(ostream& out, const ValidateException& except);

class Validate {

public:
    void validate(const Book& book);
};

void test_validare();

#endif //VALIDARE_H
