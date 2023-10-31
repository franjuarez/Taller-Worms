#include "game_world.h"
#include <iostream>

int main(){
    GameWorld game;
    game.update();
    game.moveWormLeft();
    for(int i = 0; i < 100; i++){
        game.update();    
    }
    game.moveWormRight();
    for(int i = 0; i < 100; i++){
        game.update();    
    }
    game.moveWormRight();
    for(int i = 0; i < 100; i++){
        game.update();    
    }
    game.moveWormRight();
    for(int i = 0; i < 100; i++){
        game.update();    
    }
    game.moveWormRight();
    for(int i = 0; i < 100; i++){
        game.update();    
    }
    std::cout << "Termina3" << std::endl;
    return 0;
}