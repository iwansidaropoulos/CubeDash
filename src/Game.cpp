#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Game.h"
#include "constants.h"

Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Cube Dash"), player(50.0f) {
    srand(static_cast<unsigned>(time(0)));
    window.setFramerateLimit(60);

    // Charger la police
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police" << std::endl;
    }
    // Initialiser le texte
    tryAgainText.setFont(font);
    tryAgainText.setString("TRY AGAIN");
    tryAgainText.setCharacterSize(100);
    tryAgainText.setFillColor(sf::Color::Red);
    tryAgainText.setStyle(sf::Text::Bold);
    tryAgainText.setPosition(
        WINDOW_WIDTH / 2 - tryAgainText.getGlobalBounds().width / 2,
        WINDOW_HEIGHT / 2 - tryAgainText.getGlobalBounds().height / 2);
}

void Game::run() {
    sf::Clock deltaClock;
    while (window.isOpen()) {
        float deltaTime = deltaClock.restart().asSeconds();
        handleEvents();
        update(deltaTime);
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            player.jump();
        }
    }
}

void Game::update(float deltaTime) {
    player.update();
    level.update(deltaTime);
    // Vérifier les collisions
    if (level.checkCollision(player.getHitboxCenter(), player.getHitboxRadius())) {
        resetGame();
    }
    // "TRY AGAIN" pendant 1 seconde
    if (showTryAgainText) {
        // Gérer le fondu
        float elapsed = textClock.getElapsedTime().asSeconds();
        if (elapsed >= 1.0f) {
            showTryAgainText = false;
        } else {
            // Calculer l'alpha en fonction du temps
            int alpha = static_cast<int>((1.0f - elapsed) * 255);
            tryAgainText.setFillColor(sf::Color(255, 0, 0, alpha));
        }
    }
}

void Game::render() {
    window.clear();
    level.render(window);
    window.draw(player.getSprite());
    if (showTryAgainText) {
        window.draw(tryAgainText);
    }
    window.display();
}

void Game::resetGame() {
    player.resetPosition();
    level.reset();
    showTryAgainText = true;
    textClock.restart();
}