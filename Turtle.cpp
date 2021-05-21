// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#include "Turtle.hpp"

Turtle::Turtle(World* currentWorld, int posX, int posY, int age, bool newBorn)
: Animal(currentWorld, 2, 1, posX, posY, age, newBorn){
    
};

void Turtle::draw(){
    printf("T");
};

string Turtle::getName(){
    return ("Turtle");
};

void Turtle::action(){
    // Zwiększenie wieku organizmu o 1 z każdą turą
    age++;
    // Próba poruszenia się, tylko 25% szansy
    int randomTick = rand() % 100 + 1;
    if(randomTick > 75){
        Animal::action();
    }
};

bool Turtle::reflected(Organism *entity){
    return (entity->getStrength() < 5);
};

Organism *Turtle::clone(int posX, int posY){
    return new Turtle(currentWorld, posX, posY, 1, true);
};

Turtle::~Turtle(){
    
};
