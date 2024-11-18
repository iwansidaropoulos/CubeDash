#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player(float size);
    void jump();
    void update();
    void resetPosition();

    const sf::Sprite& getSprite() const;
    bool getIsJumping() const;
    float getVelocityY() const;

    // Hitbox circulaire
    sf::Vector2f getHitboxCenter() const;
    float getHitboxRadius() const;

private:
    sf::Sprite sprite;
    sf::Texture texture;
    float velocityY = 0;
    bool isJumping = false;
    float rotationAngle = 0;
    float hitboxRadius;
};

#endif
