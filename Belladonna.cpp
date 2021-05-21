// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#include "Belladonna.hpp"

Belladonna::Belladonna(World *currentWorld, int posX, int posY, int age, bool newBorn)
: Plant(currentWorld, 99, posX, posY, age, newBorn){
};

void Belladonna::draw(){
    printf("B");
};

string Belladonna::getName(){
    return ("Belladonna");
};

Organism *Belladonna::clone(int posX, int posY){
    return new Belladonna(currentWorld, posX, posY, 1, true);
};

Belladonna::~Belladonna(){
};