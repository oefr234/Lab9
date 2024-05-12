//
// Created by utilizator2 on 09.05.2024.
//

#ifndef CONSOLA_H
#define CONSOLA_H


#include <vector>
#include "../controller/controller.h"

class Console {
    Library& controller;

    //ui-adauga o carte
    void ui_add_book();

    //ui-sterge o carte
    void ui_delete_book();

    //ui-modifica o carte
    void ui_modify_book();

    //tipareste lista de carti
    void print_books(const vector<Book>& books);

    //filtrare dupa an
    void ui_filter_by_year();

    //filtrare dupa titlu
    void ui_filter_by_title();

    //cautare carte
    void ui_find_book();

    void ui_sort_by_crit();

    //Genereaza carti random
    void ui_random_cart();

    //Adauga carte in cosul de cumparaturi
    void ui_add_in_cart();

    void add_10_books();

    void ui_cartExport();

    void ui_report();

    //undo
    void ui_undo();

public:
    Console(Library& contr) :controller{ contr } {}

    void print_commands();

    void start_UI();
};



#endif //CONSOLA_H
