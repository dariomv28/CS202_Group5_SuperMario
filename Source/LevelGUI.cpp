#include "Headers/LevelGUI.h"



LevelGUI::LevelGUI() {
    
    this->health = 100;
    this->coinsCollected = 0;

    
    if (!this->font.loadFromFile("Source/Resources/font/Poppins-Medium.ttf")) {
        throw("ERROR::LEVELGUI::FAILED_TO_LOAD_FONT");
    }

    
    this->healthBar.setSize(sf::Vector2f(400.f, 20.f));
    this->healthBar.setFillColor(sf::Color::Green);
    this->healthBar.setPosition(10.f, 10.f);

    
    this->coinsLabel.setFont(this->font);
    this->coinsLabel.setCharacterSize(40);
    this->coinsLabel.setFillColor(sf::Color::White);
    this->coinsLabel.setPosition(420.f, 10.f);
    this->coinsLabel.setString("Coins: 0");

    this->levelCount.setFont(this->font);
    this->levelCount.setCharacterSize(40);
    this->levelCount.setFillColor(sf::Color::White);
    this->levelCount.setPosition(700.f, 10.f);
    this->levelCount.setString("Level: 1");
}

LevelGUI::~LevelGUI() {}

void LevelGUI::updateInfo(int playerHealth, int coins) {
    this->health = playerHealth;
    this->coinsCollected = coins;
    
    this->healthBar.setSize(sf::Vector2f(400.f * float(playerHealth) / 100.f, 20.f));
    //this->healthBar.setSize(sf::Vector2f(static_cast<float>(health) * 4.f, 20.f));
    if (health > 50) {
        this->healthBar.setFillColor(sf::Color::Green);
        
    }
    else if (health > 20) {
        this->healthBar.setFillColor(sf::Color::Yellow);
        
    }
    else {

        this->healthBar.setFillColor(sf::Color::Red);
        
    }
    
    this->coinsLabel.setString("Coins: " + std::to_string(coins));
}

void LevelGUI::render(sf::RenderTarget* target) {
    target->draw(this->healthBar);
    target->draw(this->coinsLabel);
    target->draw(this->levelCount);
}

void LevelGUI::updatePosition(const sf::View& view) {
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    
    float xOffset = viewCenter.x - viewSize.x / 2.0f;
    float yOffset = viewCenter.y - viewSize.y / 2.0f;

    
    this->healthBar.setPosition(xOffset + 10.f, yOffset + 10.f);
    this->coinsLabel.setPosition(xOffset + 420.f, yOffset + 10.f);
    this->levelCount.setPosition(xOffset + 700.f, yOffset + 10.f);
}