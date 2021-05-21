// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#include "Grass.hpp"

Grass::Grass(World* currentWorld, int posX, int posY, int age, bool newBorn)
: Plant(currentWorld, 0, posX, posY, age, newBorn){
};

void Grass::draw(){
    printf("#");
};

string Grass::getName(){
    return ("Grass");
};

Organism *Grass::clone(int posX, int posY){
    return new Grass(currentWorld, posX, posY, 1, true);
};

Grass::~Grass(){
    
};