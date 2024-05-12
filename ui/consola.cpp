//
// Created by utilizator2 on 09.05.2024.
//


#include "consola.h"
#include <iostream>
#include <map>

using std::cin;
using std::cout;
using std::string;

void Console::print_commands() {
    cout << "              ____________BIBLIOTECA____________              \n\n";
    cout << "1 Adauga o carte\n" << "2 Sterge o carte\n" << "3 Modifica o carte\n" << "4 Tipareste cartile\n" << "5 Filtrare dupa an\n" << "6 Filtrare dupa titlu\n";
    cout << "7 Cauta carte\n" << "8 Sortare\n" << "9 Pune carti random in cos\n" << "10 Goleste cosul\n" << "11 Adauga carte in cos\n" << "12 Export\n" << "13 Report\n" << "14 Undo\n";
    cout << "Introduceti o comanda:";
}

void Console::print_books(const vector<Book>& books) {
    cout << "Carti in stoc\n";
    cout << "_________________________________________________________\n";
    for (auto& book : books) {
        cout << book.get_title() << "   " << book.get_author() << "   " << book.get_type() << "   " << book.get_year();
        cout << "\n";
    }
    if (books.size() == 0)
        cout << "Nu exista carti in stoc\n";
    cout << "_________________________________________________________\n\n";
}

void Console::ui_add_book() {
    string title, author, type;
    int year;
    cin.get();
    cout << "Introduceti titlul cartii:";
    getline(cin, title, '\n');
    cin.get();
    cout << "Introduceti numele autorului:";
    getline(cin, author, '\n');
    cin.get();
    cout << "Introduceti genul cartii:";
    getline(cin, type, '\n');
    cout << "Introduceti anul publicarii cartii:";
    cin >> year;
    try {
        controller.addBook(title, author, type, year);
        cout << "Cartea s a adaugat cu succes\n";
    }
    catch (ValidateException& ex) {
        cout << ex << "\n";
    }
    catch (RepoException& re) {
        cout << re << "\n";
    }
}

void Console::ui_modify_book() {
    string title, author, type, title2, author2;
    int year;
    cout << "Cartea de modificat:\n";
    cin.get();
    cout << "Introduceti titlul cartii:";
    getline(cin, title2, '\n');
    cin.get();
    cout << "Introduceti numele autorului:";
    getline(cin, author2, '\n');
    cin.get();
    cout << "Cartea pentru modificat:\n";
    cout << "Introduceti titlul cartii:";
    getline(cin, title, '\n');
    cin.get();
    cout << "Introduceti numele autorului:";
    getline(cin, author, '\n');
    cin.get();
    cout << "Introduceti genul cartii:";
    getline(cin, type, '\n');
    cout << "Introduceti anul publicarii cartii:";
    cin >> year;
    try {
        controller.modifyBook(title2, author2, title, author, type, year);
        cout << "Carte modificata cu succes\n";
    }
    catch (RepoException& ex) {
        cout << ex << "\n";
    }
    catch (ValidateException& val) {
        cout << val << "\n";
    }
}

void Console::ui_delete_book() {
    string title, author;
    cin.get();
    cout << "Introduceti titlul cartii:";
    getline(cin, title, '\n');
    cin.get();
    cout << "Introduceti numele autorului:";
    getline(cin, author, '\n');
    try {
        controller.deleteBook(title, author);
        cout << "Carte stearsa cu succes\n";
    }
    catch (RepoException& ex) {
        cout << ex << "\n";
    }
    catch (ValidateException& val) {
        cout << val << "\n";
    }

}

void Console::ui_filter_by_year() {
    int year1, year2;
    cout << "Introduceti primul an:";
    cin >> year1;
    cout << "Introdcuceti al doilea an:";
    cin >> year2;
    auto filtered_books = controller.filter_books_by_year(year1, year2);
    cout << "Carti filtrate:\n";
    Console::print_books(filtered_books);
}

void Console::ui_filter_by_title() {
    string title;
    cout << "Introduceti titlul:";
    cin >> title;
    auto filtered_books = controller.filter_books_by_title(title);
    cout << "Carti filtrate:\n";
    Console::print_books(filtered_books);
}

void Console::ui_find_book() {
    string title, author;
    cin.get();
    cout << "Introduceti titlul cartii:";
    getline(cin, title, '\n');
    cin.get();
    cout << "Introduceti numele autorului:";
    getline(cin, author, '\n');
    try {
        controller.cont_find_book(title, author);
        cout << "Carte gasite\n" ;
    }
    catch (RepoException &ex) {
        cout << ex << "\n";
    }
}

void Console::ui_sort_by_crit() {
    string criteriu;
    cin.get();
    cout << "Alegeti tipul de sortare:(titlu,autor,an + gen):";
    getline(cin, criteriu, '\n');
    if (criteriu == "titlu") {
        auto sorted_books = controller.TitleSort();
        print_books(sorted_books);
    }
    else if (criteriu == "autor") {
        auto sorted_books = controller.AuthorSort();
        print_books(sorted_books);
    }
    else if (criteriu == "an + gen") {
        auto sorted_books = controller.Year_typeSort();
        print_books(sorted_books);
    }
    else {
        cout << "Varianta indisponibila\n";
        ui_sort_by_crit();
    }
}

void Console::ui_random_cart(){
    int nr;
    cout << "Introduceti numarul de carti:";
    cin >> nr;
    controller.random_cart(nr);
}

void Console::ui_add_in_cart(){
    string title, author;
    cin.get();
    cout << "Introduceti titlul cartii:";
    getline(cin, title, '\n');
    cin.get();
    cout << "Introduceti numele autorului:";
    getline(cin, author, '\n');
    try{
        controller.add_in_cart(title,author);
    }
    catch(RepoException &ex){
        cout << ex << "\n";
    }
}

void Console::ui_cartExport() {
    string filename;
    cout << "Dati numele fisierului in care vreti sa salvati cosul de cumparaturi(.csv sau .html): " << endl;
    cin >> filename;
    string referinta = "/home/kali234/CLionProjects/OOP_lab8/shopping_cart/";
    try{
        controller.cartExport(referinta.append(filename));
    }
    catch(RepoException &ex){
        cout << ex <<"\n";
    }
}

void Console::ui_report(){
    map <string,int> map = controller.report();
    for(const auto& type : map){
        cout << "Tip carte:"<< type.first << "    Nr carti:" << type.second << "\n";
    }
}

void Console::ui_undo(){
    try{
        controller.undo();
    }
    catch(RepoException &ex){
        cout << ex;
    }
}

void Console::add_10_books() {
    controller.addBook("Echoes of Eternity", "Sophia Reynolds", "Fantasy", 2019);
    controller.addBook("The Quantum Conundrum", "Benjamin Hayes", "Science Fiction", 2022);
    controller.addBook("Whispers in the Mist", "Olivia Chang", "Mystery", 2018);
    controller.addBook("Beyond the Horizon", "Lucas Fitzgerald", "Adventure", 2020);
    controller.addBook("The Art of Serenity", "Elena Martinez", "Self-Help", 2023);
    controller.addBook("Shadows of the Past", "Jackson Harper", "Thriller", 2017);
    controller.addBook("Songs of Solitude", "Isabella Thompson", "Poetry", 2021);
    controller.addBook("Into the Unknown", "Nathan Patel", "Fantasy", 2016);
    controller.addBook("The Codebreaker's Dilemma", "Emily Johnson", "Mystery", 2024);
    controller.addBook("Journey to Enlightenment", "Aiden Brooks", "Philosophy", 2015);
}

void Console::start_UI() {
    add_10_books();
    string command;
    bool end = false;
    while (!end) {
        print_commands();
        cin >> command;
        if (command == "1")
            ui_add_book();
        else if (command == "2")
            ui_delete_book();
        else if (command == "3")
            ui_modify_book();
        else if (command == "4")
            print_books(controller.getAll());
        else if (command == "5")
            ui_filter_by_year();
        else if (command == "6")
            ui_filter_by_title();
        else if (command == "7")
            ui_find_book();
        else if (command == "8")
            ui_sort_by_crit();
        else if (command == "9")
            ui_random_cart();
        else if (command == "10")
            controller.empty_cart();
        else if (command == "11")
            ui_add_in_cart();
        else if (command == "12")
            ui_cartExport();
        else if(command == "13")
            ui_report();
        else if(command == "14")
            ui_undo();
        else if (command == "0")
            end = true;
        vector <Book> bks = controller.getAll_cart();
        cout << "Numar carti din cosul de cumparaturi:" << bks.size() << "\n";
        print_books(bks);
    }

}