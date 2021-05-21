// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#ifndef Dandelion_hpp
#define Dandelion_hpp

#include <stdio.h>
#include "Plant.hpp"

class Dandelion : public Plant {
    public:
        Dandelion(World* currentWorld, int posX, int posY, int age, bool newBorn);
        void draw() override;
        void action() override;
        string getName() override;
        Organism* clone(int posX, int posY) override;
        ~Dandelion() override;
};

#endif