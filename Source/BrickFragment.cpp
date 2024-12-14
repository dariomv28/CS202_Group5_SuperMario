#include "Headers/BrickFragment.h"

BrickFragment::BrickFragment(const sf::Texture& texture, sf::IntRect textureRect, sf::Vector2f position) {
    // Set the texture and texture rectangle
    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect);

    // Position the fragment with wider spread
    sprite.setPosition(position);

    // Increased spread velocity
    // Horizontal spread: much wider range
    velocity.x = (rand() % 400 - 200) / 50.0f;  // Wider horizontal spread

    // Vertical spread: more dramatic initial upward movement
    velocity.y = -(200.0f + (rand() % 300));  // Upward initial movement

    // Initial rotation with more variation
    rotation = 0.0f;
    rotationSpeed = (rand() % 720 - 360);  // Faster, more dramatic rotation
};

void BrickFragment::update(float dt) {
    // Move the sprite based on velocity
    sprite.move(velocity * dt);

    // Rotate the sprite
    rotation += rotationSpeed * dt;
    sprite.setRotation(rotation);

    // More aggressive gravity simulation
    velocity.y += 800.0f * dt;  // Increased gravity effect

    // Optional: Slow down horizontal movement
    velocity.x *= 0.95f;
};