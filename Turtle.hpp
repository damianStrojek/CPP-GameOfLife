// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#ifndef Turtle_hpp
#define Turtle_hpp

#include <stdio.h>
#include "Animal.hpp"

class Turtle : public Animal {
    public:
        Turtle(World* currentWorld, int posX, int posY, int age, bool newBorn);
        void draw() override;
        void action() override;
        string getName() override;
        bool reflected(Organism *entity) override;
        Organism *clone(int posX, int posY) override;
        ~Turtle() override;
};

#endif