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
    game.jumpForwardWorm();
    for(int i = 0; i < 100; i++){
        game.update();    
    }
    game.jumpForwardWorm();
    for(int i = 0; i < 100; i++){
        game.update();    
    }
    game.jumpForwardWorm();
    for(int i = 0; i < 100; i++){
        game.update();    
    }
    game.wormLaunchRocket(45.0f, LEFT, 10);
    for(int i = 0; i < 100; i++){
        game.update();    
    }
    game.wormLaunchRocket(90.0f, RIGHT, 90);
    
    std::cout << "Termina3" << std::endl;
    return 0;
}