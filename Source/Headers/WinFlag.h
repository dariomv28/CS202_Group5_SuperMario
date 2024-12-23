#pragma once
#include "Block.h"
class WinFlag :
    public Block
{
   
private:
    enum class FlagState {
        IDLE,
        SLIDING,
        COMPLETED
    };

    FlagState animationState;
    bool isAnimating;
    float flagPosition;
    float animationTimer;
    sf::Vector2f originalPosition;
    sf::Vector2f targetPosition;
    sf::Texture flagTexture;

    std::map<FlagState, std::vector<sf::IntRect>> spritesSheet;

    static constexpr float SLIDE_DURATION = 1.0f;  // Time for flag to slide down
    static constexpr float ANIMATION_FRAME_DURATION = 0.1f;  // Time between animation frames
    int currentFrame = 0;

    sf::Sprite poleSprite;
    sf::Sprite sphereSprite;

public:
	WinFlag(sf::Vector2f position, sf::Vector2f size, std::string name);
	~WinFlag();

	void initSpritesSheet();
	void update(const float& dt);
	void reactToCollison(int collidedSide);
	void render(sf::RenderTarget* target);
};

