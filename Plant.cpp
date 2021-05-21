// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#include "Plant.hpp"

Plant::Plant(World *currentWorld, int strength, int posX, int posY, int age, bool newBorn)
: Organism(currentWorld, strength, 0, posX, posY, age, newBorn){
};

void Plant::action(){
    // Zwiększenie wieku organizmu o 1 z każdą turą
    // Z wyjątkiem mlecza, który wykonuje rozsiewanie 3 razy
    if(this->getName().compare("Dandelion")){
        age++;
    }
    // Próba rozmnożenia się każdej rośliny, szansa to 15%
    int randomTick = rand() % 100 + 1;
    if(randomTick > 85){
        std::cout << "Sewing " << this->getName() << " (" << position[0] << "," << position[1] << ").\n";
        // Znalezienie nowego nie zajętego miejsca w pobliżu
        int *newPosition = pathFindNewUnoccupiedField();
        // Jeżeli nie ma takiego miejsca to powrót i nie udane rozmnożenie się
        if(newPosition[0] == -1 && newPosition[1] == -1){
            printf("Sewing failed - no unoccupied field!\n");
            delete newPosition;
            return;
        }
        else{
            // Jeżeli jest takie miejsce to rozmnożenie się w tej pozycji
            clone(newPosition[0], newPosition[1]);
        }
    }
};

Plant::~Plant(){

};