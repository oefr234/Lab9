//
// Created by utilizator2 on 09.05.2024.

#ifndef UNDO_H
#define UNDO_H
#include "domain/domain.h"
#include "repository/repository.h"

class ActiuneUndo {
public:
    virtual void doUndo() = 0;

    virtual ~ActiuneUndo(){};
};

class UndoAdauga : public ActiuneUndo {
    Book addedBook;
    RepoAbstract& repo;
public:
    UndoAdauga(RepoAbstract& Repo,const Book& book):addedBook{book},repo{Repo}{}

    void doUndo() override {
        repo.delete_book(addedBook);
    }
};

class UndoModifica : public ActiuneUndo {
    Book modifiedBook;
    string title,author;
    RepoAbstract& repo;
public:
    UndoModifica(RepoAbstract& Repo,const Book& book,const string title1,const string author1):modifiedBook{book},
                                                                                               title{title1},author{author1},repo{Repo}{}

    void doUndo() override {
        repo.modify_book(modifiedBook,title,author);
    }

};

class UndoSterge : public ActiuneUndo {
    Book deletedBook;
    RepoAbstract& repo;
public:
    UndoSterge(RepoAbstract& Repo,const Book& book):deletedBook{book},repo{Repo}{}

    void doUndo() override {
        repo.add_book(deletedBook);
    }
};


#endif //UNDO_H
