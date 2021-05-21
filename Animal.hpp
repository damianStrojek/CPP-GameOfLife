// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#ifndef Animal_hpp
#define Animal_hpp

#include <iostream>
#include <string>
#include "Organism.hpp"

using std::string;

// Zwierzęta dziedziczą po klasie Organizm
class Animal : public Organism {
    public:
        Animal(World *currentWorld, int strength, int initiative, int pos_x, int pos_y, int age, bool newborn);
        bool doSpeciesMatch(Organism &entity);
        void breed();
        string getName() override = 0;         // Każde zwierzę ma inną nazwę
        void draw() override = 0;                   // Każde zwierzę jest inaczej oznaczane
        void action() override;                     // Każde zwierzę inaczej się zachowuje
        virtual void collision(Organism *collidingEntity);
        ~Animal();
};

#endif