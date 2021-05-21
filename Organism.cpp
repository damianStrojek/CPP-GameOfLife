// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#include "Organism.hpp"

Organism::Organism(World* currentWorld, int strength, int initiative, int posX, int posY, int age, bool newBorn) 
: currentWorld(currentWorld), strength(strength), initiative(initiative), age(age), newBorn(newBorn){
    // Zmiana pozycji organizmu
    this->position[0] = posX;
    this->position[1] = posY;
    
    // Jeżeli pozycja nie jest zdefiniowana to zwracamy return
    if(posX == -1 && posY == -1) return;
    
    currentWorld->entitySpace[posX][posY] = this;
    // Dodajemy ten organizm do Lookup'u
    currentWorld->entityLookup->add(this);
};

// Funkcja zajmująca się znajdowaniem nowego miejsca do poruszenia się dla organizmu
int *Organism::pathFindNewField(){
    // Stworzenie dwóch pozycji, w które poruszy się organizm
    int *returnPosition = new int[2];
    returnPosition[0] = position[0];
    returnPosition[1] = position[1];

    int field;
    bool invalidMove;
    do{
        // Losowanie pozycji na którą się poruszy organizm
        field = rand() % 4;
        invalidMove = false;
        switch(field){
            case 0:     // Góra
                if(returnPosition[1] == 0){
                    invalidMove = true;
                }
                else returnPosition[1]--;
                break;
            case 1:     // Prawo
                if(returnPosition[0] == currentWorld->getN()-1){
                    invalidMove = true;
                }
                else returnPosition[0]++;
                break;
            case 2:     // Dół
                if(returnPosition[1] == currentWorld->getM()-1){
                    invalidMove = true;
                }
                else returnPosition[1]++;
                break;
            case 3:     // Lewo
                if(returnPosition[0] == 0){
                    invalidMove = true;
                }
                else returnPosition[0]--;
        }
    }while(invalidMove);
    return returnPosition;
};

// Funkcja zajmująca się znalezieniem nowej pozycji, która nie jest zajęta przez inny organizm
int *Organism::pathFindNewUnoccupiedField(){
    // Stworzenie dwóch pozycji, w które poruszy się organizm
    int *returnPosition = new int[2];
    returnPosition[0] = position[0];
    returnPosition[1] = position[1];

    // Góra
    if((returnPosition[1] != 0) && (currentWorld->entitySpace[returnPosition[0]][returnPosition[1]-1] == NULL)){
        returnPosition[1]--;
        return returnPosition;
    }
    // Prawo
    else if((returnPosition[0] != currentWorld->getN() - 1) && (currentWorld->entitySpace[returnPosition[0]+1][returnPosition[1]] == NULL)){
        returnPosition[0]++;
        return returnPosition;
    }
    // Dół
    else if((returnPosition[1] != currentWorld->getM() - 1) && (currentWorld->entitySpace[returnPosition[0]][returnPosition[1]+1] == NULL)){
        returnPosition[1]++;
        return returnPosition;
    }
    // Lewo
    else if((returnPosition[0] != 0) && (currentWorld->entitySpace[returnPosition[0]-1][returnPosition[1]] == NULL)){
        returnPosition[0]--;
        return returnPosition;
    }

    // Jeżeli nie ma żadnego miejsca dookoła organizmu, które nie jest zajęte to zwracamy -1
    returnPosition[0] = -1;
    returnPosition[1] = -1;
    return returnPosition;
};

int Organism::getStrength(){
    return strength;
};

int Organism::getInitiative(){
    return initiative;
};

void Organism::setX(int x){
    position[0] = x;
};

int Organism::getX(){
    return position[0];
};

void Organism::setY(int y){
    position[1] = y;
};

int Organism::getY(){
    return position[1];
};

int Organism::getAge(){
    return age;
};

bool Organism::getNewBorn(){
    return newBorn;
};

// Boolean tylko dla Żółwia, który może odbijać "ataki" w jego stronę
bool Organism::reflected(Organism *entity){
    return false;
};

Organism::~Organism(){

};