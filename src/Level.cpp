#include <opencv2/opencv.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>

#include "Level.h"
#include "constants.h"

Level::Level() {
    std::string texturePath = "assets/images/level.jpg";
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Erreur : Impossible de charger la texture " << texturePath << std::endl;
    } else {
        // Calculer le facteur de mise à l'échelle pour ajuster la hauteur
        float scaleFactor = static_cast<float>(WINDOW_HEIGHT) / texture.getSize().y;

        // Appliquer la texture aux deux sprites
        sprite1.setTexture(texture);
        sprite2.setTexture(texture);

        // Appliquer la mise à l'échelle pour que la hauteur corresponde à celle de la fenêtre
        sprite1.setScale(scaleFactor, scaleFactor);
        sprite2.setScale(scaleFactor, scaleFactor);

        // Positionner le deuxième sprite à droite du premier
        sprite2.setPosition(texture.getSize().x * scaleFactor, 0);

        // Charger la carte de collision à partir de l'image
        collisionMap = cv::imread("assets/images/level.jpg", cv::IMREAD_GRAYSCALE);

        // Créer les zones de collision
        createCollisions();
    }
}

void Level::createCollisions() {
    // Facteur de mise à l'échelle
    float scaleFactor = static_cast<float>(WINDOW_HEIGHT) / texture.getSize().y;

    // Redimensionner la collisionMap pour réduire sa résolution
    cv::Mat resizedCollisionMap;
    
    // Redimensionner l'image avec OpenCV
    cv::resize(collisionMap, resizedCollisionMap, cv::Size(collisionMap.cols / 4, collisionMap.rows / 4));

    // Parcourir l'image redimensionnée pour détecter les zones blanches
    for (int y = 0; y < resizedCollisionMap.rows; ++y) {
        for (int x = 0; x < resizedCollisionMap.cols; ++x) {
            // Détection des zones blanches dans l'image redimensionnée
            if (resizedCollisionMap.at<uchar>(y, x) > 200) {
                // Créer une zone de collision
                sf::FloatRect collisionZone(
                    static_cast<float>(x) * scaleFactor * 4,
                    static_cast<float>(y) * scaleFactor * 4,
                    scaleFactor * 4,
                    scaleFactor * 4
                );
                collisionZones.push_back(collisionZone);
            }
        }
    }
}

void Level::update(float deltaTime) {
    // Déplacer les deux sprites vers la gauche
    float displacement = SCROLL_SPEED * deltaTime;
    sprite1.move(-displacement, 0);
    sprite2.move(-displacement, 0);

    // Déplacer les zones de collision
    for (auto& collisionZone : collisionZones) {
        collisionZone.left -= displacement;
        // Replacer la zone à droite
        if (collisionZone.left + collisionZone.width < 0) {
            collisionZone.left += sprite1.getGlobalBounds().width;
        }
    }

    // Si un sprite sort de l'écran, le repositionner à droite de l'autre
    if (sprite1.getPosition().x + sprite1.getGlobalBounds().width < 0) {
        sprite1.setPosition(sprite2.getPosition().x + sprite2.getGlobalBounds().width, 0);
    }
    if (sprite2.getPosition().x + sprite2.getGlobalBounds().width < 0) {
        sprite2.setPosition(sprite1.getPosition().x + sprite1.getGlobalBounds().width, 0);
    }
}

void Level::render(sf::RenderWindow& window) {
    // Dessiner les deux sprites
    window.draw(sprite1);
    window.draw(sprite2);
}

bool Level::checkCollision(const sf::Vector2f& circleCenter, float circleRadius) const {
    for (const auto& zone : collisionZones) {
        // Trouver le point le plus proche du cercle sur le rectangle
        float closestX = std::clamp(circleCenter.x, zone.left, zone.left + zone.width);
        float closestY = std::clamp(circleCenter.y, zone.top, zone.top + zone.height);

        // Calculer la distance entre le cercle et ce point
        float distanceX = circleCenter.x - closestX;
        float distanceY = circleCenter.y - closestY;
        float distanceSquared = distanceX * distanceX + distanceY * distanceY;

        // Vérifier si la distance est inférieure au rayon
        if (distanceSquared < (circleRadius * circleRadius)) {
            return true;
        }
    }
    return false;
}

void Level::reset() {
    // Réinitialiser la position des sprites
    sprite1.setPosition(0, 0);
    sprite2.setPosition(sprite1.getGlobalBounds().width, 0);

    // Réinitialiser les zones de collision
    collisionZones.clear();
    createCollisions();
}
