// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#include "Guarana.hpp"

Guarana::Guarana(World *currentWorld, int posX, int posY, int age, bool newBorn)
: Plant(currentWorld, 0, posX, posY, age, newBorn){
};

void Guarana::draw(){
    printf("G");
};

string Guarana::getName(){
    return ("Guarana");
};

Organism *Guarana::clone(int posX, int posY){
    return new Guarana(currentWorld, posX, posY, 1, true);
};

Guarana::~Guarana(){

};