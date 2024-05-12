//
// Created by utilizator2 on 12.05.2024.
//
#include <random>
#include <algorithm>
#include "repository/repository.h"

void RepoLab::random() const {
    cout << "Probabilitatea: " << prob << "\n";
    throw RepoException("Nu se poate executa aceasta functie!!!");
}

void RepoLab::add_book(const Book& book) {
    random();
    if (exist(book)) {
        throw RepoException("Exista deja cartea " + book.get_title() + " scrisa de " + book.get_author());
    }
    auto poz = books.size();
    books.insert(std::make_pair(poz,book));
}

int RepoLab::get_poz(const Book& book) {
    int i = 0;
    for (const auto& bk : books)
        if (book.get_title() == bk.second.get_title() && book.get_author() == bk.second.get_author())
            return i;
        else i++;
    return -1;
}

bool RepoLab::exist(const Book& book) const {
    try {
        find_book(book.get_title(), book.get_author());
        return true;
    }
    catch (RepoException&){
        return false;
    }}

const Book& RepoLab::find_book(string title, string author) const {
    random();
    auto f= find_if(books.begin(), books.end(), [=](const std::pair<int,Book> o) {
        return (o.second.get_title() == title && o.second.get_author() == author);
    });
    if(f!=books.end())
        return (*f).second;
    throw RepoException("Nu exista cartea " + title + " scrisa de " + author);}

void RepoLab::delete_book(const Book& book) {
    random();
    if (!exist(book)) {
        throw RepoException("Cartea " + book.get_title() + " scris de " + book.get_author() + "nu exista");
    }
    int ok = 0;
    unsigned long i = 0;
    while(i < books.size()) {
        if (book.get_title() == books[i].get_title() && book.get_author() == books[i].get_author() && ok == 0)
            ok = 1;
        if (ok == 1)
            books.at(i) = books.at(i + 1);
        i++;
    }
    books.erase((int) books.size() -1);
}

void RepoLab::modify_book(const Book& book, string title, string author){
    random();
    auto founded_book = find_book(title,author);

    int i = get_poz(founded_book);
    books.at(i) = book;

}

vector <Book> Books;

const vector<Book>& RepoLab::get_all() const noexcept {
    random();
    Books.clear();
    for(auto &book : books){
        Books.push_back(book.second);
    }
    return Books;
}

void RepoLab::set_prob(double p) {
    prob = p;
}
