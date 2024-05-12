//
// Created by utilizator2 on 09.05.2024.
//
#include "teste.h"
#include <iostream>
#include <sstream>
#include <cassert>
#include "../repository/repository.h"
#include "../controller/controller.h"

void test_add() {
    BookRepo repo;
    repo.add_book(Book{ "asd","sdd","drama",1999 });
    repo.add_book(Book{ "fs","dsfg","actiune",1939 });
    repo.add_book(Book{ "anme","fds","roman politist",1992 });
    assert(repo.get_all().size() == 3);
    auto all = repo.get_all();
    assert(all[0].get_title() == "asd" && all[0].get_author() == "sdd");
    assert(all[0].get_type() == "drama" && all[0].get_year() == 1999);
    try {
        repo.add_book(Book{ "fs","dsfg","actiune",1939 });
        assert(false);
    }
    catch (RepoException& ex) {
        std::stringstream s;
        s << ex;
        auto mes = s.str();
        assert(mes == "Exista deja cartea fs scrisa de dsfg");
    }
    assert(repo.get_poz(Book{ "Da","Charls","novl",2016 }) == -1);
    assert(repo.get_poz(Book{ "asd","Charls","novl",2016 }) == -1);
    assert(repo.get_poz(Book{ "asd","sdd","novl",2016 }) == 0);

    assert(repo.get_poz(Book{ "ad","sdd","novl",2016 }) == -1);
    repo.modify_book(Book{ "David Copperfield","Charles Dickens","novel",2016 }, "asd", "sdd");
    all = repo.get_all();
    assert(all[0].get_title() == "David Copperfield" && all[0].get_author() == "Charles Dickens");
}

void test_delete() {
    BookRepo repo;
    repo.add_book(Book{ "asd","sdd","drama",1999 });
    repo.add_book(Book{ "fs","dsfg","actiune",1939 });
    repo.add_book(Book{ "anme","fds","roman politist",1992 });
    assert(repo.get_all().size() == 3);
    repo.delete_book(Book{ "anme","fds","roman politist",1992 });
    assert(repo.get_all().size() == 2);
    repo.delete_book(Book{ "fs","dsfg","actiune",1939 });
    assert(repo.get_all().size() == 1);
    try {
        repo.delete_book(Book{ "anme","fds","roman politist",1992 });
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }
    try {
        repo.delete_book(Book{ "asd","fcxv","drama",1999});
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }
}


void test_find() {
    BookRepo repo;
    repo.add_book(Book{ "asd","sdd","drama",1999 });
    repo.add_book(Book{ "fs","dsfg","actiune",1939 });
    auto p = repo.find_book("fs", "dsfg");
    assert(p.get_title() == "fs" && p.get_author() == "dsfg");
    try {
        repo.find_book("sdasd", "safasd");
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }
}

void test_add_book() {
    BookRepo repo;
    Validate valid;
    ShoppingCart cart;
    Library lib{ repo , valid,cart};
    lib.addBook("title1", "author1", "type1", 2000);
    assert(lib.getAll().size() == 1);
    lib.addBook("title2", "author2", "type2", 2001);
    assert(lib.getAll().size() == 2);
    lib.addBook("title3", "author3", "type3", 2002);
    assert(lib.getAll().size() == 3);
}

void test_delete_book() {
    BookRepo repo;
    Validate valid;
    ShoppingCart cart;
    Library lib{ repo , valid,cart};
    lib.addBook("title1", "author1", "type1", 2000);
    lib.addBook("title2", "author2", "type2", 2001);
    lib.addBook("title3", "author3", "type3", 2002);
    lib.deleteBook("title1", "author1");
    assert(lib.getAll().size() == 2);
    lib.deleteBook("title2", "author2");
    assert(lib.getAll().size() == 1);
    lib.deleteBook("title3", "author3");
    assert(lib.getAll().size() == 0);
}

void test_modify_book() {
    BookRepo repo;
    Validate valid;
    ShoppingCart cart;
    Library lib{ repo , valid,cart};
    lib.addBook("title1", "author1", "type1", 2000);
    lib.addBook("title2", "author2", "type2", 2001);
    lib.addBook("title3", "author3", "type3", 2002);
    lib.modifyBook("title1", "author1", "title4", "author4", "type4", 2003);
    assert(lib.getAll()[0].get_title() == "title4");
    assert(lib.getAll()[0].get_author() == "author4");
    assert(lib.getAll()[0].get_type() == "type4");
    assert(lib.getAll()[0].get_year() == 2003);
    lib.modifyBook("title2", "author2", "title5", "author5", "type5", 2004);
    assert(lib.getAll()[1].get_title() == "title5");
    assert(lib.getAll()[1].get_author() == "author5");
    assert(lib.getAll()[1].get_type() == "type5");
    assert(lib.getAll()[1].get_year() == 2004);
}
void test_filter_books_by_title() {
    BookRepo repo;
    Validate valid;
    ShoppingCart cart;
    Library lib{ repo , valid,cart};
    lib.addBook("title1", "author1", "type1", 2000);
    lib.addBook("title2", "author2", "type2", 2001);
    lib.addBook("title3", "author3", "type3", 2002);
    lib.addBook("title1", "author4", "type4", 2003);
    lib.addBook("title2", "author5", "type5", 2004);
    lib.addBook("title3", "author6", "type6", 2005);
    assert(lib.filter_books_by_title("title1").size() == 2);
    assert(lib.filter_books_by_title("title2").size() == 2);
    assert(lib.filter_books_by_title("title3").size() == 2);
    assert(lib.filter_books_by_title("title4").size() == 0);
    assert(lib.filter_books_by_title("title5").size() == 0);
    assert(lib.filter_books_by_title("title6").size() == 0);
}

void test_filter_books_by_year() {
    BookRepo repo;
    Validate valid;
    ShoppingCart cart;
    Library lib{ repo , valid,cart};
    lib.addBook("title1", "author1", "type1", 2000);
    lib.addBook("title2", "author2", "type2", 2001);
    lib.addBook("title3", "author3", "type3", 2002);
    lib.addBook("title4", "author4", "type4", 2003);
    lib.addBook("title5", "author5", "type5", 2004);
    lib.addBook("title6", "author6", "type6", 2005);
    assert(lib.filter_books_by_year(2000, 2001).size() == 2);
    assert(lib.filter_books_by_year(2001, 2002).size() == 2);
    assert(lib.filter_books_by_year(2002, 2003).size() == 2);
    assert(lib.filter_books_by_year(2003, 2004).size() == 2);
    assert(lib.filter_books_by_year(2004, 2005).size() == 2);
    assert(lib.filter_books_by_year(2005, 2006).size() == 1);
}


void teste_domain(){
    Book book = Book{"title1","author1","type1",2024};
    assert(book.get_title() == "title1");
    assert(book.get_author() == "author1");
    assert(book.get_type() == "type1");
    assert(book.get_year() == 2024);
}

void test_sortare() {
    BookRepo repo;
    Validate valid;
    ShoppingCart cart;
    Library library{ repo , valid,cart};
    library.addBook("c", "f", "type1", 2003);
    library.addBook("b", "e", "type2", 2004);
    library.addBook("a", "d", "atype3", 2004);
    auto all = library.TitleSort();

    assert(all[0].get_title() == "a");
    assert(all[1].get_title() == "b");
    assert(all[2].get_title() == "c");
    all = library.AuthorSort();
    assert(all[0].get_author() == "d");
    assert(all[1].get_author() == "e");
    assert(all[2].get_author() == "f");
    all = library.Year_typeSort();
    assert(all[0].get_title() == "c");
    assert(all[1].get_title() == "a");
    assert(all[2].get_title() == "b");
}

void test_cart(){
    BookRepo repo;
    Validate valid;
    ShoppingCart cart;
    Library library{ repo , valid,cart};
    library.addBook("c", "f", "type1", 2003);
    library.addBook("b", "e", "type2", 2004);
    library.addBook("a", "d", "atype3", 2004);
    auto all = library.TitleSort();
    cart.add_in_cart(all[0]);
    assert(cart.getAll_cart().size() == 1);
    cart.add_in_cart(all[1]);
    assert(cart.getAll_cart().size() == 2);
    cart.add_random(all,5);
    assert(cart.getAll_cart().size() == 5);

    cart.empty_cart();
    assert(cart.getAll_cart().size() == 0);
}

void test_validare() {
    Validate valid;
    Book book{ "White Noise","Don DeLillo","fiction",2022 };
    valid.validate(book);
    Book book1{ "","","",-1 };
    try {
        valid.validate(book1);
        //assert(false);
    }
    catch (ValidateException& ex) {
        std::stringstream s;
        s << ex;
        auto mes = s.str();
        assert(mes.find("invalid"));
    }
}

void test_undo_adauga() {
    BookRepo repo;
    Book bookToAdd("Title", "Author", "Type", 2024);
    repo.add_book(bookToAdd);

    UndoAdauga undoAdauga(repo, bookToAdd);
    undoAdauga.doUndo();

    assert(repo.get_all().size() == 0);
}

void test_undo_modifica() {
    BookRepo repo;
    Book originalBook{"Title", "Author", "Type", 2024};
    repo.add_book(originalBook);

    string newTitle = "New Title";
    string newAuthor = "New Author";
    Book modified_book{newTitle,newAuthor,"Type",2024};

    repo.modify_book(modified_book,"Title","Author");

    UndoModifica undoModifica{repo, originalBook, newTitle, newAuthor};

    undoModifica.doUndo();

    assert(repo.get_all().size() == 1);
    assert(repo.get_all()[0].get_title() == "Title");
    assert(repo.get_all()[0].get_author() == "Author");
}

void test_undo_sterge() {
    BookRepo repo;
    Book bookToDelete{"Title", "Author", "Type", 2024};

    UndoSterge undoSterge{repo, bookToDelete};

    undoSterge.doUndo();
    assert(repo.get_all().size() == 1);
    assert(repo.get_all()[0].get_title() == "Title");
    assert(repo.get_all()[0].get_author() == "Author");
}

void run_newrepo_tests() {
/*
    {
        RepoLab repo;
        Book book{"Title", "Author", "Type", 2024};
        try {
            repo.add_book(book);
        }
        catch(RepoException){
            assert(true);
        }
        assert(repo.get_all().size() == 1);
    }

    {
        RepoLab repo;
        Book book{"Title", "Author", "Type", 2024};
        repo.add_book(book);
        const Book& foundBook = repo.find_book("Title", "Author");
        assert(foundBook.get_title() == "Title");
        assert(foundBook.get_author() == "Author");
    }

    {
        RepoLab repo;
        Book book{"Title", "Author", "Type", 2024};
        repo.add_book(book);
        repo.delete_book(book);
        assert(repo.get_all().empty());
    }

    {
        RepoLab repo;
        Book originalBook{"Title", "Author", "Type", 2024};
        repo.add_book(originalBook);
        Book newBook{"New Title", "New Author", "New Type", 2025};
        repo.modify_book(newBook, "Title", "Author");
        const Book& modifiedBook = repo.find_book("New Title", "New Author");
        assert(modifiedBook.get_title() == "New Title");
        assert(modifiedBook.get_author() == "New Author");
    }
*/
}

void test_ShoppingCart() {
    ShoppingCart cart;

    Book book1{ "Title1", "Author1", "Type1", 2000 };
    Book book2{ "Title2", "Author2", "Type2", 2001 };
    cart.add_in_cart(book1);
    cart.add_in_cart(book2);
    assert(cart.getAll_cart().size() == 2);
    cart.empty_cart();
    assert(cart.getAll_cart().empty());

    // Test add_in_cart
    Book bookToAdd{ "Title3", "Author3", "Type3", 2002 };
    cart.add_in_cart(bookToAdd);
    assert(cart.getAll_cart().size() == 1);
    auto all = cart.getAll_cart();
    //assert(cart.getAll_cart()[0] == bookToAdd);

    // Test add_random
    std::vector<Book> booksToAdd{
            Book{ "Title4", "Author4", "Type4", 2003 },
            Book{ "Title5", "Author5", "Type5", 2004 },
            Book{ "Title6", "Author6", "Type6", 2005 }
    };
    cart.add_random(booksToAdd, 2);
    assert(cart.getAll_cart().size() == 2);
    //assert(cart.getAll_cart()[0] == bookToAdd); // Previous book should still be there
    //assert(cart.getAll_cart()[1] != cart.getAll_cart()[2]); // Random books should not be the same
}

void teste_validare(){
    test_validare();
}

void teste_repo() {
    test_undo_adauga();
    test_undo_sterge();
    test_undo_modifica();
    run_newrepo_tests();
    test_add();
    test_delete();
    test_find();
}

void teste_controller() {
    test_ShoppingCart();
    test_cart();
    test_filter_books_by_year();
    test_filter_books_by_title();
    test_modify_book();
    test_delete_book();
    test_add_book();
    test_sortare();
}