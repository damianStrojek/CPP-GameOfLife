// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#include "Sheep.hpp"

Sheep::Sheep(World* currentWorld, int posX, int posY, int age, bool newBorn)
: Animal(currentWorld, 4, 4, posX, posY, age, newBorn){
    
};

void Sheep::draw(){
    printf("S");
};

string Sheep::getName(){
    return ("Sheep");
};

Organism *Sheep::clone(int posX, int posY){
    return new Sheep(currentWorld, posX, posY, 1, true);
};

Sheep::~Sheep(){
    
};
