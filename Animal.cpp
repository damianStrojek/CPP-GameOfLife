// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#include "Animal.hpp"
#include "Hogweed.hpp"
#include "Guarana.hpp"
#include "Human.hpp"
#include <typeinfo>

Animal::Animal(World *currentWorld, int strength, int initiative, int posX, int posY, int age, bool newBorn)
: Organism(currentWorld, strength, initiative, posX, posY, age, newBorn){
};

// Sprawdzenie czy organizmy do siebie pasują
bool Animal::doSpeciesMatch(Organism &entity){
    return (this->getName() == entity.getName());
};

void Animal::breed(){
    int *newPosition = pathFindNewUnoccupiedField();
    // Jeżeli nie ma miejsca w którym mógł by się pojawić organizm
    if(newPosition[0] == -1 && newPosition[1] == -1){
        std::cout << "Breeding of " << this->getName() << " failed. No unoccupied field!\n";
        return;
    }
    // Jeżeli znalazło się miejsce
    clone(newPosition[0], newPosition[1]);
    delete newPosition;
};

void Animal::action(){
    int *newPosition = pathFindNewField();
    // Przesunięcie się na inne pole
    if(currentWorld->entitySpace[newPosition[0]][newPosition[1]] == NULL){
        currentWorld->entitySpace[newPosition[0]][newPosition[1]] = this;
        currentWorld->entitySpace[position[0]][position[1]] = NULL;
        position[0] = newPosition[0];
        position[1] = newPosition[1];
    }
    else{
        // Kolizja z innym organizmem
        collision(currentWorld->entitySpace[newPosition[0]][newPosition[1]]);
    }
    delete newPosition;
};

void Animal::collision(Organism *collidingEntity){
    if(doSpeciesMatch(*collidingEntity)){
        if(typeid(*collidingEntity).hash_code() == typeid(Human).hash_code()){
            return;
        }
        // Kolizja z tym samym organizmem
        std::cout << "Colliding entities: [MATCH] " << this->getName() << " (" << position[0] << "," << position[1] << "), ";
        std::cout << collidingEntity->getName() << " (" << collidingEntity->getX() << "," << collidingEntity->getY() << ").\n";
        // Rozmnożenie się
        breed();
        return;
    }
    else{
        // Sprawdzenie czy przypadkiem żółw nie odparł kolizji
        if(collidingEntity->reflected(this)){
            std::cout << "Colliding entities: [REFLECT] " << this->getName() << " (" << position[0] << "," << position[1] << "), ";
            std::cout << collidingEntity->getName() << " (" << collidingEntity->getX() << "," << collidingEntity->getY() << ").\n";
            return;
        }

        // Walka dwóch organizmów
        std::cout << "Colliding entities: [FIGHT] " << this->getName() << " (" << position[0] << "," << position[1] << "), ";
        std::cout << collidingEntity->getName() << " (" << collidingEntity->getX() << "," << collidingEntity->getY() << ").\n";
        // Jeżeli siła jednego zwierzęcia jest wyższa od siły drugiego oraz jeżeli drugim organizmem nie jest HogWeed
        if(strength >= collidingEntity->getStrength() && typeid(*collidingEntity).hash_code() != typeid(Hogweed).hash_code()){
            // Wygrana
            std::cout << "Victory of " << this->getName() << "\n";
            // Jeżeli to była guarana to zwiększamy siłę this organizmu
            if(typeid(*collidingEntity).hash_code() == typeid(Guarana).hash_code()){
                std::cout << this->getName() << " (" << position[0] << "," << position[1] << ") strength increased.\n";
                strength += 3;
            }
            // Usunięcie organizmu z planszy
            currentWorld->entitySpace[position[0]][position[1]] = NULL;
            position[0] = collidingEntity->getX();
            position[1] = collidingEntity->getY();
            currentWorld->entitySpace[position[0]][position[1]] = this;

            currentWorld->entityLookup->remove(collidingEntity);
        }
        else{
            // W przeciwnym wypadku przegrana
            // HogWeed to wilcze jagody, zjedzenie ich pokonuje każdy organizm
            std::cout << "Defeat of " << this->getName() <<".\n";
            currentWorld->entitySpace[position[0]][position[1]] = NULL;
            currentWorld->entityLookup->remove(this);
        }
    }
};

Animal::~Animal(){
};