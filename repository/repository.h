//
// Created by utilizator2 on 09.05.2024.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "../domain/domain.h"
#include <unordered_map>
#include <random>
#include <iostream>
#include <vector>
#include <ostream>
#include <string>

using std::vector;
using std::ostream;

class RepoAbstract {
public:
    RepoAbstract() = default;

    RepoAbstract(const RepoAbstract& book) = delete;

    //Salveaza o carte in lista de carti
    virtual void add_book(const Book& book) = 0;

    //Sterge o carte din lista de carti
    virtual void delete_book(const Book& book) = 0;

    //Modifica o carte din lista de carti
    virtual void modify_book(const Book& book, string title, string author) = 0;

    //Cauta o carte in lista de carti
    virtual const Book& find_book(string title,string author) const = 0;

    //Returneaza lista de carti
    virtual const vector<Book>& get_all() const noexcept = 0;

    virtual int get_poz(const Book& book) = 0;
};

class BookRepo : public RepoAbstract {
    vector<Book> books;

    bool exist(const Book& book) const;

public:
    BookRepo() = default;

    BookRepo(const BookRepo& book) = delete;

    //Salveaza o carte in lista de carti
    void add_book(const Book& book) override;

    //Sterge o carte din lista de carti
    void delete_book(const Book& book) override;

    //Modifica o carte din lista de carti
    void modify_book(const Book& book, string title, string author) override;

    //Cauta o carte in lista de carti
    const Book& find_book(string title,string author) const override;

    //Returneaza lista de carti
    const vector<Book>& get_all() const noexcept override;

    int get_poz(const Book& book) override;
};

class RepoLab : public RepoAbstract {
private:
    std::unordered_map<int,Book> books;
    double prob;

    void random() const;

    bool exist(const Book& book) const;

public:
    RepoLab() {
        std::mt19937 num(123);
        std::uniform_real_distribution<double> dis(0.0, 1.0);
        prob = dis(num);
    };

    RepoLab(const RepoLab& book) = delete;

    void set_prob(double p);

    //Salveaza o carte in lista de carti
    void add_book(const Book& book) override;

    //Sterge o carte din lista de carti
    void delete_book(const Book& book) override;

    //Modifica o carte din lista de carti
    void modify_book(const Book& book, string title, string author) override;

    //Cauta o carte in lista de carti
    const Book& find_book(string title,string author) const override;

    //Returneaza lista de carti
    const vector<Book>& get_all() const noexcept override;

    int get_poz(const Book& book) override;

};

class RepoException {
    string message;
public:
    RepoException(string mes) :message{ mes } {}
    friend ostream& operator<<(ostream& out, const RepoException& except);
};

ostream& operator<<(ostream& out, const RepoException& except);

#endif //REPOSITORY_H
