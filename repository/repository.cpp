//
// Created by utilizator2 on 09.05.2024.
//

#include "repository.h"
#include <iostream>
#include <algorithm>

void BookRepo::add_book(const Book& book) {
    if (exist(book)) {
        throw RepoException("Exista deja cartea " + book.get_title() + " scrisa de " + book.get_author());
    }
    books.push_back(book);
}

int BookRepo::get_poz(const Book& book) {
    int i = 0;
    for (const auto& bk : books)
        if (book.get_title() == bk.get_title() && book.get_author() == bk.get_author())
            return i;
        else i++;
    return -1;
}

bool BookRepo::exist(const Book& book) const {
    try {
        find_book(book.get_title(), book.get_author());
        return true;
    }
    catch (RepoException&){
        return false;
    }}

const Book& BookRepo::find_book(string title, string author) const {
    auto f = std::find_if(books.begin(), books.end(), [=](const Book &o) {
        return (o.get_title() == title && o.get_author() == author);
    });
    if(f!=books.end())
        return (*f);
    throw RepoException("Nu exista cartea " + title + " scrisa de " + author + "\n");}

void BookRepo::delete_book(const Book& book) {
    if (!exist(book)) {
        throw RepoException("Cartea " + book.get_title() + " scris de " + book.get_author() + "nu exista");
    }
    int ok = 0;
    size_t i = 0;
    while(i < this->books.size()) {
        if (book.get_title() == books[i].get_title() && book.get_author() == books[i].get_author() && ok == 0)
            ok = 1;
        if (ok == 1)
        {
            books[i].title = books[i+1].get_title();
            books[i].author = books[i+1].get_author();
            books[i].type = books[i+1].get_type();
            books[i].app_year = books[i+1].get_year();
        }
        i++;
    }
    books.pop_back();
}

void BookRepo::modify_book(const Book& book, string title, string author){
    auto founded_book = find_book(title,author);

    int i = get_poz(founded_book);
    books[i].title = book.get_title();
    books[i].author = book.get_author();
    books[i].type = book.get_type();
    books[i].app_year = book.get_year();
}

const vector<Book>& BookRepo::get_all() const noexcept {
    return books;
}

ostream& operator<<(ostream& out,const RepoException& except) {
    out << except.message;
    return out;
}

