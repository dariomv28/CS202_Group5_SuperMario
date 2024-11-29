#include "Headers/LevelGUI.h"



LevelGUI::LevelGUI() {
    // Initialize variables
    this->health = 100;
    this->coinsCollected = 0;

    // Load font
    if (!this->font.loadFromFile("Source/Resources/font/Super - Mario - Bros--3.ttf")) {
        throw("ERROR::LEVELGUI::FAILED_TO_LOAD_FONT");
    }

    // Initialize health bar
    this->healthBar.setSize(sf::Vector2f(200.f, 20.f));
    this->healthBar.setFillColor(sf::Color::Green);
    this->healthBar.setPosition(10.f, 10.f);

    // Initialize coins label
    this->coinsLabel.setFont(this->font);
    this->coinsLabel.setCharacterSize(20);
    this->coinsLabel.setFillColor(sf::Color::White);
    this->coinsLabel.setPosition(10.f, 40.f);
    this->coinsLabel.setString("Coins: 0");
}

LevelGUI::~LevelGUI() {}

void LevelGUI::updateInfo(int playerHealth, int coins) {
    this->health = playerHealth;
    this->coinsCollected = coins;

    // Update health bar
    this->healthBar.setSize(sf::Vector2f(static_cast<float>(health) * 2.f, 20.f));
    if (health > 50) {
        this->healthBar.setFillColor(sf::Color::Green);
    }
    else if (health > 20) {
        this->healthBar.setFillColor(sf::Color::Yellow);
    }
    else {
        this->healthBar.setFillColor(sf::Color::Red);
    }

    // Update coins label
    this->coinsLabel.setString("Coins: " + std::to_string(coins));
}

void LevelGUI::render(sf::RenderTarget* target) {
    target->draw(this->healthBar);
    target->draw(this->coinsLabel);
}