// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#include "Antelope.hpp"

Antelope::Antelope(World *currentWorld, int posX, int posY, int age, bool newBorn)
: Animal(currentWorld, 4, 4, posX, posY, age, newBorn){

};

int *Antelope::pathFindNewField(){
    int *returnPosition = new int[2];

    returnPosition[0] = position[0];
    returnPosition[1] = position[1];

    int field;
    bool invalidMove;
    do {
        field = rand() % 8;
        // Aby sprawdzić czy może się ruszyć w tą stronę
        invalidMove = false;
        switch (field) {
            case 0: // Góra
                if(returnPosition[1] == 0)
                    invalidMove = true;
                else returnPosition[1]--;
                break;
            case 1: // Prawo
                if(returnPosition[0] == currentWorld->getN() - 1)
                    invalidMove = true;
                else returnPosition[0]++;
                break;
            case 2: // Dół
                if(returnPosition[1] == currentWorld->getM() - 1)
                    invalidMove = true;
                else returnPosition[1]++;
                break;
            case 3: // Lewo
                if(returnPosition[0] == 0)
                    invalidMove = true;
                else returnPosition[0]--;
                break;
            case 4: // Góra + 2
                if(returnPosition[1] <= 1)
                    invalidMove = true;
                else returnPosition[1] -= 2;
                break;
            case 5: // Prawo + 2
                if(returnPosition[0] >= currentWorld->getN() - 2)
                    invalidMove = true;
                else returnPosition[0] += 2;
                break;
            case 6: // Dół + 2
                if(returnPosition[1] >= currentWorld->getM() - 2)
                    invalidMove = true;
                else returnPosition[1] += 2;
                break;
            case 7: // Lewo + 2
                if(returnPosition[0] <= 1)
                    invalidMove = true;
                else returnPosition[0] -= 2;
                break;
        }
    }while(invalidMove);

    return returnPosition;
};

void Antelope::draw(){
    printf("A");
};

string Antelope::getName(){
    return ("Antelope");
};

void Antelope::collision(Organism *collidingEntity){
    // Próba ucieczki
    int randomTick = rand() % 2;
    // 50% szansy na ucieczkę
    if((randomTick > 0) && !(doSpeciesMatch(*collidingEntity)) && (collidingEntity->getStrength() > strength)){
        // Ucieczka
        std::cout << "Colliding entities: [ESCAPE] " << this->getName() << " (" << position[0] << "," << position[1] << "), ";
        std::cout << collidingEntity->getName() << " (" << collidingEntity->getX() << "," << collidingEntity->getY() << ").\n";
        // Znalezienie miejsca do ucieczki
        int *newPosition = pathFindNewUnoccupiedField();
        if((newPosition[0] != -1) && (newPosition[1] != -1)){
            currentWorld->entitySpace[newPosition[0]][newPosition[1]] = this;
            currentWorld->entitySpace[position[0]][position[1]] = NULL;
            position[0] = newPosition[0];
            position[1] = newPosition[1];
        }
    }
    else{
        Animal::collision(collidingEntity);
    }
};

Organism *Antelope::clone(int posX, int posY){
    return new Antelope(currentWorld, posX, posY, 1, true);
};

Antelope::~Antelope(){

};