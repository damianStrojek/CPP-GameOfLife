// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#ifndef Grass_hpp
#define Grass_hpp

#include <stdio.h>
#include "Plant.hpp"

class Grass : public Plant {
    public:
        Grass(World* currentWorld, int posX, int posY, int age, bool newBorn);
        void draw() override;
        string getName() override;
        Organism* clone(int posX, int posY) override;
        ~Grass() override;
};

#endif