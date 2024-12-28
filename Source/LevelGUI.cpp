#include "Headers/LevelGUI.h"

LevelGUI::LevelGUI() {
    
    this->health = 3;
    this->coinsCollected = 0;
    timeCount = 0;
    this->score = 0;
    level = 1;
    
    if (!this->font.loadFromFile("Source/Resources/font/pixel-nes.otf")) {
        throw("ERROR::LEVELGUI::FAILED_TO_LOAD_FONT");
    }

    if (!this->heartTexture.loadFromFile("Source/Resources/texture/heart.png")) {
        throw("ERROR::LEVELGUI::FAILED_TO_LOAD_HEART_TEXTURE");
    }
    this->heartSprite.setTexture(this->heartTexture);
    this->heartSprite.setScale(0.03f, 0.03f); 
    this->heartSprite.setPosition(10.f, 10.f); 

    this->livesText.setFont(this->font);
    this->livesText.setCharacterSize(30);
    this->livesText.setFillColor(sf::Color::White);
    this->livesText.setPosition(60.f, 10.f); 
    this->livesText.setString("x" + std::to_string(this->health));


    this->characterName.setFont(font);
    this->characterName.setCharacterSize(30);
    this->characterName.setFillColor(sf::Color::White);
    this->characterName.setPosition(10.f, 10.f);
    this->characterName.setString("Mario");
    
    /*this->healthBar.setSize(sf::Vector2f(400.f, 20.f));
    this->healthBar.setFillColor(sf::Color::Green);
    this->healthBar.setPosition(10.f, 60.f);
    this->healthBarBorder.setSize(sf::Vector2f(healthBar.getSize().x + 4.f, healthBar.getSize().y + 4.f));
    this->healthBarBorder.setFillColor(sf::Color::Transparent);
    this->healthBarBorder.setOutlineColor(sf::Color::Red);
    this->healthBarBorder.setOutlineThickness(2.f);*/
    
    this->coinsLabel.setFont(this->font);
    this->coinsLabel.setCharacterSize(30);
    this->coinsLabel.setFillColor(sf::Color::White);
    this->coinsLabel.setPosition(420.f, 10.f);
    this->coinsLabel.setString("Coins: 0");

    this->levelCount.setFont(this->font);
    this->levelCount.setCharacterSize(30);
    this->levelCount.setFillColor(sf::Color::White);
    this->levelCount.setPosition(700.f, 10.f);
    this->levelCount.setString("Level: 1");

    this->timer.setFont(this->font);
    this->timer.setCharacterSize(30);
    this->timer.setFillColor(sf::Color::White);
    this->timer.setPosition(900.f, 10.f);
    this->timer.setString("Time: 0");

    this->scoreLabel.setFont(font);
    this->scoreLabel.setCharacterSize(30);
    this->scoreLabel.setFillColor(sf::Color::White);
    this->scoreLabel.setPosition(1200.f, 10.f);
    this->scoreLabel.setString("Score: 0");
}

LevelGUI::~LevelGUI() {}

void LevelGUI::setEventMediator(GameEventMediator* eventMediator) {
	this->eventMediator = eventMediator;
}

void LevelGUI::updateInfo() {

    /*this->healthBar.setSize(sf::Vector2f(400.f * float(health) / 100.f, 20.f));
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
    this->scoreLabel.setString("Score: " + std::to_string(score));*/
}

void LevelGUI::render(sf::RenderTarget* target) {
    target->draw(this->characterName);
    //target->draw(this->healthBar);
    //target->draw(this->healthBarBorder);
    target->draw(this->coinsLabel);
    target->draw(this->levelCount);
    target->draw(this->timer);
    target->draw(this->scoreLabel);
    target->draw(this->heartSprite);
    target->draw(this->livesText);
}

void LevelGUI::updatePosition(const sf::View& view) {
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    
    float xOffset = viewCenter.x - viewSize.x / 2.0f;
    float yOffset = viewCenter.y - viewSize.y / 2.0f;

    float sectionWidth = viewSize.x / 5.0f;  
    float centerYOffset = 20.f;  
    float horizontalSpacing = 50.f;  


    /*this->characterName.setPosition(xOffset + 10.f, yOffset + 10.f);
    this->healthBar.setPosition(xOffset + 10.f, yOffset + 60.f);
    this->coinsLabel.setPosition(xOffset + 420.f, yOffset + 10.f);
    this->levelCount.setPosition(xOffset + 700.f, yOffset + 10.f);
    this->timer.setPosition(xOffset + 900.f, yOffset + 10.f);
    this->scoreLabel.setPosition(xOffset + 1200.f, yOffset + 10.f);*/

    this->characterName.setPosition(xOffset + sectionWidth * 0.5f - characterName.getLocalBounds().width / 2.0f - horizontalSpacing,
        yOffset + centerYOffset);  

    //this->heartSprite.setPosition(xOffset + sectionWidth * 0.5f - characterName.getLocalBounds().width / 2.0f,
        //yOffset + centerYOffset + healthBarYOffset);
    this->heartSprite.setPosition(
        this->characterName.getPosition().x + this->characterName.getLocalBounds().width + 10.f, // Cách một khoảng 10.f
        this->characterName.getPosition().y
    );

    //this->healthBarBorder.setPosition((xOffset + sectionWidth * 0.5f - characterName.getLocalBounds().width / 2.0f) - 2.f,
        //(yOffset + centerYOffset + healthBarYOffset) - 2.f);
    //this->livesText.setPosition(
        //this->heartSprite.getPosition().x + this->heartSprite.getGlobalBounds().width + 10.f, 
        //this->heartSprite.getPosition().y
    //);
    this->livesText.setPosition(
        this->heartSprite.getPosition().x + this->heartSprite.getGlobalBounds().width + 5.f, // Cách một khoảng 5.f
        this->heartSprite.getPosition().y
    );
    this->coinsLabel.setPosition(xOffset + sectionWidth * 1.5f - coinsLabel.getLocalBounds().width / 2.0f,
        yOffset + centerYOffset);

    this->levelCount.setPosition(xOffset + sectionWidth * 2.5f - levelCount.getLocalBounds().width / 2.0f,
        yOffset + centerYOffset);

    this->timer.setPosition(xOffset + sectionWidth * 3.5f - timer.getLocalBounds().width / 2.0f,
        yOffset + centerYOffset);

    this->scoreLabel.setPosition(xOffset + sectionWidth * 4.5f - scoreLabel.getLocalBounds().width / 2.0f,
        yOffset + centerYOffset);
}

void LevelGUI::updateTime() {
    sf::Time t = clock.getElapsedTime();
    if (t.asSeconds() >= 1.f) {
        timeCount++;
        clock.restart();
        timer.setString("Time: " + std::to_string(timeCount));
    }
}

void LevelGUI::updateFinalScore(const sf::View& view) {
	score += std::min(0, (999 - timeCount)*5);
    score += coinsCollected * 100;
    update(view);
	//scoreLabel.setString("Score: " + std::to_string(score));
}

void LevelGUI::update(const sf::View& view) {
    //updateInfo();
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

void LevelGUI::updateHealth(int playerHealth) {
    if (playerHealth < 0) return;
   /* health = playerHealth;
    this->healthBar.setSize(sf::Vector2f(400.f * float(health) / 100.f, 20.f));
    if (health > 50) {
        this->healthBar.setFillColor(sf::Color::Green);

    }
    else if (health > 20) {
        this->healthBar.setFillColor(sf::Color::Yellow);

    }
    else {

        this->healthBar.setFillColor(sf::Color::Red);

    }*/

    health = playerHealth;
    this->livesText.setString("x" + std::to_string(health));
}

int LevelGUI::getScore() const {
	return score;
}

int LevelGUI::getCoins() const {
	return coinsCollected;
}