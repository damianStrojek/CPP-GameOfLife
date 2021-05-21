// Damian Strojek GUT 2021, nr studenta : 184407
// Data realizacji projektu : 29.04.2021
#include <iostream>
#include "World.hpp"

int main(){
    system("cls");
    printf("         |        OOP 2021       |\n");
    printf("         | Damian Strojek 184407 |\n");
    printf("         |      Keys to move     |\n");
    printf("         |   w - up   s - down   |\n");
    printf("         |  a - left  d - right  |\n");
    printf("         |  r - special ability  |\n");
    printf("         |  x - save the game    |\n");
    printf("         | - - - - - - - - - - - |\n");
    printf("         |  1 - Start new game   |\n");
    printf("         |  2 - Load last save   |\n");
    printf("         |  2> - quit            |\n");
    printf("         |- - - - - - - - - - - -|\n");
    printf("         | What's your decision? : ");
    int N, M, playerInput;
    std::cin >> N;

    if(N == 1){
        printf("         | New world size : ");
        std::cin >> N >> M;
        // Konstruktor normalnego świata
        World newWorld(N, M);
        // Dopóki znajdujemy się na planszy
        while(newWorld.getGameStatus()){
            system("cls");
            newWorld.drawWorld();
            newWorld.makeTurn();
            // Jednocześnie służy to jako przerwa między narysowaniem kolejne tury
            // oraz zapis i załadowanie świata
            playerInput = getchar();
            if(playerInput == 120){
                newWorld.saveWorld();
                getchar();
                getchar();
            }
        }
        // Koniec gry, pokaz świata
        system("cls");
        newWorld.drawWorld();
    }
    else if(N == 2){
        std::ifstream loadFile;
        loadFile.open("backupWorld.txt", std::ios::in);
        if(!loadFile){
            printf("There is no saved world.\n");
            exit(1);
        }
        int oldTurn, oldCooldown;
        loadFile >> oldTurn >> oldCooldown;
        loadFile >> N >> M;
        // Konstruktor zapisanego świata
        World savedWorld(N, M, loadFile);
        
        savedWorld.setTurn(oldTurn);                // Przywrócenie numeru tury
        savedWorld.setHumanCooldown(oldCooldown);   // Przywrócenie cooldownu specjalnej umiejętności
        
        while(savedWorld.getGameStatus()){
            system("cls");
            savedWorld.drawWorld();
            savedWorld.makeTurn();
            playerInput = getchar();
            if(playerInput == 120){
                savedWorld.saveWorld();
                getchar();
                getchar();
            }
        }
        // Koniec gry, pokaz świata
        system("cls");
        savedWorld.drawWorld();
    }
    else{
        exit(1);
    }

    // Koniec gry
    printf("GAME OVER\n");
    printf("Press any key to exit...");
    getchar();
    return 0;
};