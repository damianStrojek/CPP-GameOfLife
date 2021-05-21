// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#include "Wolf.hpp"

Wolf::Wolf(World *currentWorld, int posX, int posY, int age, bool newBorn)
: Animal(currentWorld, 9, 5, posX, posY, age, newBorn){
    
};

void Wolf::draw(){
    printf("W");
};

string Wolf::getName(){
    return ("Wolf");
};

Organism *Wolf::clone(int posX, int posY){
    return new Wolf(currentWorld, posX, posY, 1, true);
};

Wolf::~Wolf(){
    
};
