//
// Created by utilizator2 on 09.05.2024.
//

#include "domain.h"

bool compTitle(const Book& book1,const Book& book2) {
    return book1.get_title() < book2.get_title();
}

bool compAuthor(const Book& book1,const Book& book2) {
    return book1.get_author() < book2.get_author();
}

bool compYearType(const Book& book1,const Book& book2){
    if (book1.get_year() == book2.get_year()) {
        return book1.get_type() < book2.get_type();
    }
    return book1.get_year() < book2.get_year();
}