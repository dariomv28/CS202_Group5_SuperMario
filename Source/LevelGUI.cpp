#include "Headers/LevelGUI.h"



LevelGUI::LevelGUI() {
    
    this->health = 100;
    this->coinsCollected = 0;
    timeCount = 0;
    this->score = 0;
    level = 1;
    
    if (!this->font.loadFromFile("Source/Resources/font/Poppins-Medium.ttf")) {
        throw("ERROR::LEVELGUI::FAILED_TO_LOAD_FONT");
    }

    this->characterName.setFont(font);
    this->characterName.setCharacterSize(40);
    this->characterName.setFillColor(sf::Color::White);
    this->characterName.setPosition(10.f, 10.f);
    this->characterName.setString("Mario");
    
    this->healthBar.setSize(sf::Vector2f(400.f, 20.f));
    this->healthBar.setFillColor(sf::Color::Green);
    this->healthBar.setPosition(10.f, 60.f);

    
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

    this->timer.setFont(this->font);
    this->timer.setCharacterSize(40);
    this->timer.setFillColor(sf::Color::White);
    this->timer.setPosition(900.f, 10.f);
    this->timer.setString("Time: 0");
}

LevelGUI::~LevelGUI() {}

void LevelGUI::setEventMediator(GameEventMediator* eventMediator) {
	this->eventMediator = eventMediator;
}

void LevelGUI::updateInfo() {


    this->healthBar.setSize(sf::Vector2f(400.f * float(health) / 100.f, 20.f));
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
    
    this->coinsLabel.setString("Coins: " + std::to_string(coinsCollected));

}

void LevelGUI::render(sf::RenderTarget* target) {
    target->draw(this->characterName);
    target->draw(this->healthBar);
    target->draw(this->coinsLabel);
    target->draw(this->levelCount);
    target->draw(this->timer);
}

void LevelGUI::updatePosition(const sf::View& view) {
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    
    float xOffset = viewCenter.x - viewSize.x / 2.0f;
    float yOffset = viewCenter.y - viewSize.y / 2.0f;

    this->characterName.setPosition(xOffset + 10.f, yOffset + 10.f);
    this->healthBar.setPosition(xOffset + 10.f, yOffset + 60.f);
    this->coinsLabel.setPosition(xOffset + 420.f, yOffset + 10.f);
    this->levelCount.setPosition(xOffset + 700.f, yOffset + 10.f);
    this->timer.setPosition(xOffset + 900.f, yOffset + 10.f);
}

void LevelGUI::updateTime() {
    sf::Time t = clock.getElapsedTime();
    if (t.asSeconds() >= 1.f) {
        timeCount++;
        clock.restart();
        timer.setString("Time: " + std::to_string(timeCount));
    }
}

void LevelGUI::update(const sf::View& view) {
    updateInfo();
    updatePosition(view);
    updateTime();
}

void LevelGUI::increaseCoins(int numCoins) {
	coinsCollected += numCoins;
	coinsLabel.setString("Coins: " + std::to_string(coinsCollected));
}

void LevelGUI::increaseScore(int numScore) {
	score += numScore;
	scoreLabel.setString("Score: " + std::to_string(score));
}