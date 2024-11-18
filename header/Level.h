#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

class Level {
private:
    sf::Texture texture;
    sf::Sprite sprite1;
    sf::Sprite sprite2;
    float scrollSpeed;

    cv::Mat collisionMap;
    std::vector<sf::FloatRect> collisionZones;

    void createCollisions();

public:
    Level();

    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void reset();
    bool checkCollision(const sf::Vector2f& circleCenter, float circleRadius) const;
};

#endif
