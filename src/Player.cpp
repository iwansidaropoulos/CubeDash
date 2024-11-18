#include <iostream>
#include <cmath>
#include <filesystem>

#include "Player.h"
#include "constants.h"

Player::Player(float size) {
    const std::string texturePath = "assets/images/player_sprite.png";
    
    // Charger la texture
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Erreur : Impossible de charger la texture " << texturePath << std::endl;
        std::cout << "Répertoire courant : " << std::filesystem::current_path() << std::endl;
    } else {
        sprite.setTexture(texture);
    }

    // Redimensionner le sprit
    float scaleFactor = CUBE_SIZE / sprite.getLocalBounds().width;
    sprite.setScale(scaleFactor, scaleFactor);

    // Positionner le sprite
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(LEFT_SPACE, WINDOW_HEIGHT);

    hitboxRadius = (sprite.getGlobalBounds().width / 2);
}

void Player::jump() {
    if (!isJumping) {
        velocityY = JUMP_STRENGTH;
        isJumping = true;
    }
}

void Player::update() {
    // Appliquer la gravité
    velocityY += GRAVITY;
    sprite.move(0, velocityY);

    // Arrêter le saut quand on touche le sol
    if (sprite.getPosition().y >= WINDOW_HEIGHT - sprite.getGlobalBounds().height/2) {
        sprite.setPosition(sprite.getPosition().x, WINDOW_HEIGHT - sprite.getGlobalBounds().height/2);
        isJumping = false;
        velocityY = 0;
        rotationAngle -= fmod(rotationAngle, 90);
    }

    // Gérer la rotation pendant le saut
    if (isJumping) {
        rotationAngle += 3.5f;
    }
    rotationAngle = fmod(rotationAngle,360);
    sprite.setRotation(rotationAngle);
}

void Player::resetPosition() {
    // Réinitialiser la position du joueur
    sprite.setPosition(LEFT_SPACE, WINDOW_HEIGHT);
}

sf::Vector2f Player::getHitboxCenter() const {
    return sprite.getPosition();
}

float Player::getHitboxRadius() const {
    return hitboxRadius;
}

const sf::Sprite& Player::getSprite() const {
    return sprite;
}