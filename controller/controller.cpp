//
// Created by utilizator2 on 09.05.2024.
//

//
// Created by onofr on 04/04/2024.
//

#include "controller.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>



void Library::addBook(string book_title, string book_author, string book_type, int year) {
    auto book = Book{ book_title,book_author, book_type,year };
    valid.validate(book);
    repo.add_book(book);
    undoAct.push_back(std::make_unique<UndoAdauga>(repo,book));
}

void Library::deleteBook(string title,string author) {
    auto book = Book{ title,author,"asd",1979 };
    valid.validate(book);
    repo.delete_book(book);
    undoAct.push_back(std::make_unique<UndoSterge>(repo,book));
}

void Library::modifyBook(string title1, string author1, string title2, string author2, string type2, int year2) {
    auto initial_book = repo.find_book(title1,author1);
    auto book = Book{ title2,author2,type2,year2 };
    valid.validate(book);
    repo.modify_book(book, title1, author1);
    undoAct.push_back(std::make_unique<UndoModifica>(repo,initial_book,title2,author2));
}

vector<Book> Library::filter_books_by_title(string title) {
    const vector<Book> &books = getAll();
    vector <Book> filtrated_books;
    std::copy_if(books.begin(), books.end(), back_inserter(filtrated_books), [title](const Book &o) {
        return o.get_title() == title;
    });

    return filtrated_books;}

vector<Book> Library::filter_books_by_year(int year1,int year2) {
    vector<Book> books = getAll();
    vector <Book> filtrated_books;
    copy_if(books.begin(), books.end(), back_inserter(filtrated_books), [year1,year2](const Book &o) {
        return (o.get_year() >= year1) && (o.get_year() <= year2);
    });

    return filtrated_books;}

bool Library::cont_find_book(string title, string author) {
    repo.find_book(title, author);

    return true;
}

const vector<Book> Library::getAll_cart(){
    return cart.getAll_cart();
}

void Library::add_in_cart(string title,string author){
    Book book = repo.find_book(title,author);
    cart.add_in_cart(book);
}

void Library::empty_cart(){
    cart.empty_cart();
}

void Library::random_cart(int nr) {
    vector <Book> books = getAll();
    cart.add_random(books,nr);
}

vector<Book> Library::TitleSort() {
    vector<Book> books{getAll()};
    sort(books.begin(),books.end(), compTitle);
    return (books);
}

vector<Book> Library::AuthorSort() {
    vector<Book> books{getAll()};
    sort(books.begin(),books.end(), compAuthor);
    return (books);
}

vector<Book> Library::Year_typeSort() {
    vector<Book> books{getAll()};
    sort(books.begin(),books.end(), compYearType);
    return (books);
}

map<string,int> Library::report(){
    map<string,int> map;
    auto all = getAll();
    for(const auto& book : all){
        map[book.get_type()]++;
    }
    return map;
}

void Library::cartExport(const string &filename) {
    if (filename.find(".csv") == std::string::npos && filename.find(".html") == std::string::npos) {
        throw RepoException("Fisierul nu este valid!");
    } else {
        ofstream fout(filename);
        if (filename.find(".html") != std::string::npos) {
            fout << "<html>";
            fout << "<style> table, th, td {border:1px solid black} body{background-color: #E6E6FA;} </style>";
            fout << "<body>";
            fout << "<h1> WISHLIST </h1>";
            fout << "<table><tr><th>Titlu</th> <th>Autor</th> <th>Tip</th> <th>An</th></tr>";
            for (auto &o: getAll_cart()) {
                fout << "<tr><td>" << o.get_title() << "<td>" << o.get_author() << "</td><td>" << o.get_type()
                     << "</td><td>" << o.get_year() << "</td></tr>";
            }
            fout << "</table></body>";
            fout << "<html>";
        } else {
            for (auto &o: getAll_cart()) {
                fout << "<tr><td>" << o.get_title() << "<td>" << o.get_author() << "</td><td>" << o.get_type()
                     << "</td><td>" << o.get_year() << "</td></tr>";
            }
        }
        fout.close();
    }
}

void Library::undo(){
    if(undoAct.empty())
        throw RepoException("Nu se mai poate face undo!\n");
    undoAct.back()->doUndo();
    undoAct.pop_back();
}
