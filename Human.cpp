// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#include "Human.hpp"

Human::Human(World *currentWorld, int posX, int posY, int age) 
: Animal(currentWorld, 5, 4, posX, posY, age, false){
    
};

void Human::draw(){
    printf("<.>");
};

string Human::getName(){
    return ("Human");
};

void Human::action(){
    // Zwiększenie wieku organizmu o 1 z każdą turą
    age++;
    int playerMove;
    
    // Zdobycie pozycji
    int newPosition[2];
    newPosition[0] = position[0];
    newPosition[1] = position[1];

    printf("Press one of the keys to move: ");
    if(currentWorld->getTurn() == 1){
        playerMove = getchar();
    }
    playerMove = getchar();

    if(playerMove == 97){
        // a - lewo
        if(currentWorld->getHumanCooldown() >= 3){
            // Ruch o 2 pola
            newPosition[0] -= 2;
        }
        else{
            newPosition[0]--;
        }
    }
    else if(playerMove == 100){
        // d - prawo
        if(currentWorld->getHumanCooldown() >= 3){
            // Ruch o 2 pola
            newPosition[0] += 2;
        }
        else{
            newPosition[0]++;
        }
    }
    else if(playerMove == 119){
        // w - góra
        if(currentWorld->getHumanCooldown() >= 3){
            // Ruch o 2 pola
            newPosition[1] -= 2;
        }
        else{
            newPosition[1]--;
        }
    }
    else if(playerMove == 115){
        // s - dół
        if(currentWorld->getHumanCooldown() >= 3){
            // Ruch o 2 pola
            newPosition[1] += 2;
        }
        else{
            newPosition[1]++;
        }
    }
    else if(playerMove == 114){
        // r - szybkość antylopy
        specialAbility();
    }
    printf("\n");
    
    // Sprawdzenie czy można się tak poruszyć
    if((newPosition[0] < 0 || newPosition[1] < 0 ) || (newPosition[0] >= currentWorld->getN()) || (newPosition[1] >= currentWorld->getM())){
        printf("\n[PLAYER] You can't move like this! You lost that turn.\n");
        return;
    }
    
    // Zmiana pozycji gracza
    if(currentWorld->entitySpace[newPosition[0]][newPosition[1]] == NULL){
        currentWorld->entitySpace[newPosition[0]][newPosition[1]] = this;
        currentWorld->entitySpace[position[0]][position[1]] = NULL;
        position[0] = newPosition[0];
        position[1] = newPosition[1];
    }
    else{
        // Jeżeli na tym polu jest jakiś organizm to następuje kolizja
        collision(currentWorld->entitySpace[newPosition[0]][newPosition[1]]);
    }
};
// 7 mod 5 = 2
// Specjalna umiejętność to "szybkość antylopy"
void Human::specialAbility(){
    if(currentWorld->getHumanCooldown() == 0){
        // Specjalna umiejętność gracza pozwala mu na przeskakiwanie dwóch pul zamiast jednego
        // 100% na wykonanie specjalnej umiejętności
        printf("\n[PLAYER] You've got speed on antelope.\n");
        // Countdown ustawiamy na 6 bo tura jest tracona bo użyciu umiejętności
        currentWorld->setHumanCooldown(6);
    }else if(currentWorld->getHumanCooldown() < 3){
        // Tylko 50% szansy na wykonanie umiejętności
        int randomTick = rand() % 2;
        if(randomTick == 1){
            printf("\n[PLAYER] You are lucky! You've got speed of antelope again.\n");
            currentWorld->setHumanCooldown(6);
        }
        else if(randomTick == 0){
            printf("\n[PLAYER] You are not lucky. Ability is on cooldown.\n");
        }
    }
    else{
        printf("\n[PLAYER] Ability is already in use.\n");
    }
};

Organism *Human::clone(int posX, int posY){
    return new Human(currentWorld, posX, posY, 1);
};

Human::~Human(){
    // Zmiana statusu gry, tzw. koniec gry
    currentWorld->setGameStatus();
};