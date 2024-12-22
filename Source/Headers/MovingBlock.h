#include "SolidBlock.h"

class MovingBlock : public SolidBlock {
private:
    float moveSpeed;
    sf::Vector2f initialPosition;
    float moveDistance;
    int currentDirection; // 0: right, 1: down, 2: left, 3: up

    void updateMovement(const float& dt);

public:
    MovingBlock();
    MovingBlock(sf::Vector2f position, sf::Vector2f size, std::string name, float moveSpeed = 100.f, float moveDistance = 100.f);
    virtual ~MovingBlock();

    virtual void update(const float& dt) override;
    virtual void render(sf::RenderTarget* target) override;
};