// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#include "Fox.hpp"

Fox::Fox(World* currentWorld, int posX, int posY, int age, bool newBorn)
: Animal(currentWorld, 3, 7, posX, posY, age, newBorn){
    
};

void Fox::draw(){
    printf("F");
};

string Fox::getName(){
    return ("Fox");
};

void Fox::action(){
    // Zwiększenie wieku organizmu o 1 z każdą turą
    age++;
    // Lis nigdy nie ruszy się na pozycję zajętą przez silniejszy organizm niż on sam
    int *newPosition = pathFindNewField();
    
    if(currentWorld->entitySpace[newPosition[0]][newPosition[1]] == NULL){
        currentWorld->entitySpace[newPosition[0]][newPosition[1]] = this;
        currentWorld->entitySpace[position[0]][position[1]] = NULL;
        position[0] = newPosition[0];
        position[1] = newPosition[1];
    }
    else{
        // Rusz się tylko wtedy gdy jesteś w stanie pokonać organizm, który jest na tym polu
        if(currentWorld->entitySpace[newPosition[0]][newPosition[1]]->getStrength() <= getStrength()){
            collision(currentWorld->entitySpace[newPosition[0]][newPosition[1]]);
        }else{
            // Nie przejście na nową pozycję
            std::cout << "Colliding entities: [REFUSE] " << this->getName() << " (" << position[0] << "," << position[1] << "), ";
            std::cout << currentWorld->entitySpace[newPosition[0]][newPosition[1]]->getName() << "(" << currentWorld->entitySpace[newPosition[0]][newPosition[1]]->getX() << "," << currentWorld->entitySpace[newPosition[0]][newPosition[1]]->getY() << ").\n";
       }
    }
    delete newPosition;
};

Organism* Fox::clone(int posX, int posY){
    return new Fox(currentWorld, posX, posY, 1, true);
};

Fox::~Fox(){
    
};
