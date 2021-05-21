// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#ifndef Sheep_hpp
#define Sheep_hpp

#include <stdio.h>
#include "Animal.hpp"

class Sheep : public Animal {
    public:
        Sheep(World* currentWorld, int posX, int posY, int age, bool newBorn);
        void draw() override;
        string getName() override;
        Organism* clone(int posX, int posY) override;
        ~Sheep() override;
};

#endif