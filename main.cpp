#include <iostream>
#include "repository/repository.h"
#include "domain/validare.h"
#include "ui/consola.h"
#include "teste/teste.h"

int main() {
    teste_repo();
    teste_controller();
    teste_validare();
    teste_domain();
    BookRepo repo;
    Validate valid;
    ShoppingCart cart;
    Library controller{ repo , valid,cart};
    Console ui{ controller };
    ui.start_UI();
    return 0;
}
