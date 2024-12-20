#ifndef LAVA_H
#define LAVA_H

#include "PowerUpObject.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class Lava : public PowerUpObject {
private:
    int currentFrame;
    float animationTimer;
    float animationSpeed;
    bool isAnimatingForward;

    std::map<std::string, sf::IntRect> spritesSheet;

    void initSpritesSheet();

public:

    Lava(sf::Vector2f position, sf::Vector2f size, std::string name);
    virtual ~Lava();


    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget* target);
    virtual void reactToCollison();
};

#endif 