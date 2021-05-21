// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#include "Hogweed.hpp"
#include "Animal.hpp"

Hogweed::Hogweed(World* currentWorld, int posX, int posY, int age, bool newBorn)
: Plant(currentWorld, 10, posX, posY, age, newBorn){
};

void Hogweed::draw(){
    printf("&");
};

string Hogweed::getName(){
    return ("Hogweed");
};

void Hogweed::action(){
    // Zwiększenie wieku organizmu o 1 z każdą turą
    age++;
    // Barszcz sosnowskiego musi dynamic castować obiekty aby sprawdzić czy dziedziczą one po klasie Zwierzę
    // Jeżeli tak to tylko wtedy barszcz może zabić te organizmy
    int currentPosition[2];
    // Zdobycie aktualnej pozycji
    currentPosition[0] = position[0];
    currentPosition[1] = position[1];
    
    // Trzeba za każdym razem sprawdzić wszystko dookoła
    // Sprawdzenie góry
    if((currentPosition[1] != 0) && (currentWorld->entitySpace[currentPosition[0]][currentPosition[1]-1] != NULL)){
        // Sprawdzenie czy dziedziczy po zwierzęciu
        if(Animal *animalOrganism = dynamic_cast<Animal*>(currentWorld->entitySpace[currentPosition[0]][currentPosition[1]-1])){
            // Jeżeli tak to zabicie tego organizmu
            std::cout << "Hogweed action : " << this->getName() << " (" << position[0] << "," << position[1] << "), " << currentWorld->entitySpace[currentPosition[0]][currentPosition[1]-1]->getName();
            std::cout << " (" << currentWorld->entitySpace[currentPosition[0]][currentPosition[1]-1]->getX() << "," << currentWorld->entitySpace[currentPosition[0]][currentPosition[1]-1]->getY() << ").\n";

            currentWorld->entityLookup->remove(currentWorld->entitySpace[currentPosition[0]][currentPosition[1]-1]);
            currentWorld->entitySpace[currentPosition[0]][currentPosition[1]-1] = NULL;
        }
    }
    // Sprawdzenie prawej
    if((currentPosition[0] != currentWorld->getN() - 1) && (currentWorld->entitySpace[currentPosition[0]+1][currentPosition[1]] != NULL)){
        // Sprawdzenie czy dziedziczy po zwierzęciu
        if(Animal* animalOrganism = dynamic_cast<Animal*>(currentWorld->entitySpace[currentPosition[0]+1][currentPosition[1]])){
            // Jeżeli tak to zabicie tego organizmu
            std::cout << "Hogweed action : " << this->getName() << " (" << position[0] << "," << position[1] << "), " << currentWorld->entitySpace[currentPosition[0]+1][currentPosition[1]]->getName();
            std::cout << " (" << currentWorld->entitySpace[currentPosition[0]+1][currentPosition[1]]->getX() << "," << currentWorld->entitySpace[currentPosition[0]+1][currentPosition[1]]->getY() << ").\n";

            currentWorld->entityLookup->remove(currentWorld->entitySpace[currentPosition[0]+1][currentPosition[1]]);
            currentWorld->entitySpace[currentPosition[0]+1][currentPosition[1]] = NULL;
        }
    }
    // Sprawdzenie dołu
    if((currentPosition[1] != currentWorld->getM() - 1) && (currentWorld->entitySpace[currentPosition[0]][currentPosition[1]+1] != NULL)){
        // Sprawdzenie czy dziedziczy po zwierzęciu
        if(Animal* animalOrganism = dynamic_cast<Animal*>(currentWorld->entitySpace[currentPosition[0]][currentPosition[1]+1])){
            // Jeżeli tak to zabicie tego organizmu
            std::cout << "Hogweed action : " << this->getName() << " (" << position[0] << "," << position[1] << "), " << currentWorld->entitySpace[currentPosition[0]][currentPosition[1]+1]->getName();
            std::cout << " (" << currentWorld->entitySpace[currentPosition[0]][currentPosition[1]+1]->getX() << "," << currentWorld->entitySpace[currentPosition[0]][currentPosition[1]+1]->getY() << ").\n";

            currentWorld->entityLookup->remove(currentWorld->entitySpace[currentPosition[0]][currentPosition[1]+1]);
            currentWorld->entitySpace[currentPosition[0]][currentPosition[1]+1] = NULL;
        }
    }
    // Sprawdzenie lewej
    if((currentPosition[0] != 0) && (currentWorld->entitySpace[currentPosition[0]-1][currentPosition[1]] != NULL)){
        // Sprawdzenie czy dziedziczy po zwierzęciu
        if(Animal* animalOrganism = dynamic_cast<Animal*>(currentWorld->entitySpace[currentPosition[0]-1][currentPosition[1]])){
            // Jeżeli tak to zabicie tego organizmu
            std::cout << "Hogweed action : " << this->getName() << " (" << position[0] << "," << position[1] << "), " << currentWorld->entitySpace[currentPosition[0]-1][currentPosition[1]]->getName();
            std::cout << " (" << currentWorld->entitySpace[currentPosition[0]-1][currentPosition[1]]->getX() << "," << currentWorld->entitySpace[currentPosition[0]-1][currentPosition[1]]->getY() << ").\n";
 
            currentWorld->entityLookup->remove(currentWorld->entitySpace[currentPosition[0]-1][currentPosition[1]]);
            currentWorld->entitySpace[currentPosition[0]-1][currentPosition[1]] = NULL;
        }
    }
    // Rozsiewanie się
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

Organism *Hogweed::clone(int posX, int posY){
    return new Hogweed(currentWorld, posX, posY, 1, true);
};

Hogweed::~Hogweed(){
};