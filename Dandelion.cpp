// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#include "Dandelion.hpp"

Dandelion::Dandelion(World* currentWorld, int posX, int posY, int age, bool newBorn)
: Plant(currentWorld, 0, posX, posY, age, newBorn){
    
};

void Dandelion::draw(){
    printf("D");
};

string Dandelion::getName(){
    return ("Dandelion");
};

void Dandelion::action(){
    // Zwiększenie wieku organizmu
    age++;
    // Wykonuje trzy próby rozmnożenia się
    Plant::action();
    Plant::action();
    Plant::action();
};

Organism *Dandelion::clone(int posX, int posY){
    return new Dandelion(currentWorld, posX, posY, 1, true);
};

Dandelion::~Dandelion(){
    
};