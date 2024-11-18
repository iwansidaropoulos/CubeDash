#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Player.h"
#include "Level.h"

class Game {
private:
    sf::RenderWindow window;
    Level level;
    Player player;
    sf::Clock spawnClock;

    // Texte
    sf::Font font;
    sf::Text tryAgainText;
    bool showTryAgainText = false;
    sf::Clock textClock;

public:
    Game();
    void run();

private:
    void handleEvents();
    void update(float deltaTime);
    void updateObstacles(float deltaTime);
    void render();
    void resetGame();
};

#endif
