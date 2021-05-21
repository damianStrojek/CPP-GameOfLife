// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#ifndef Wolf_hpp
#define Wolf_hpp

#include <stdio.h>
#include "Animal.hpp"

class Wolf : public Animal {
    public:
        Wolf(World* currentWorld, int posX, int posY, int age, bool newBorn);
        void draw() override;
        string getName() override;
        Organism* clone(int posX, int posY) override;
        ~Wolf() override;
};

#endif