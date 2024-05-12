//
// Created by utilizator2 on 09.05.2024.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <functional>
#include <memory>
#include <map>
#include "../repository/repository.h"
#include "../domain/validare.h"
#include "../shopping_cart/cart.h"
#include "../undo.h"
#include <vector>

using std::vector;
using std::function;

class Library {
    RepoAbstract& repo;

    Validate& valid;
    ShoppingCart& cart;

    vector<std::unique_ptr<ActiuneUndo>> undoAct;

public:
    //contructor librarie
    Library(RepoAbstract& book_repo, Validate& book_valid,ShoppingCart& cart) :repo{ book_repo }, valid{ book_valid },cart{cart}{}

    //Nu se permite copierea
    Library(const Library& library) = delete;

    const vector<Book>& getAll() const {
        return repo.get_all();
    }

    //Adauga o carte
    void addBook(string book_title, string book_author, string book_type, int year);

    //Sterge o carte
    void deleteBook(string book_title, string book_author);

    //Modifica carte
    void modifyBook(string title1, string author1, string title2, string author2, string type2, int year2);

    vector<Book> filter_books_by_title(string title);

    vector<Book> filter_books_by_year(int year1,int year2);

    bool cont_find_book(string title,string author);

    //vector<Book>  generalSort(bool(*mai_mic)(const Book&, const Book&));

    //Returneaza produsele din cos
    const vector<Book> getAll_cart();

    //Adauga o carte in cosul de cumparaturi
    void add_in_cart(string title,string author);

    //Goleste cosul de cumparaturi
    void empty_cart();

    //Adauga elemente random in cosul de cumparaturi
    void random_cart(int nr);

    //Sortare dupa titlu
    vector<Book>  TitleSort();

    //Sortare dupa autor
    vector<Book>  AuthorSort();

    //Sortare dupa an + gen
    vector<Book> Year_typeSort();

    void cartExport(const string &filename);

    map<string,int> report();

    void undo();

    friend class ShoppingCart;
};


#endif //CONTROLLER_H
