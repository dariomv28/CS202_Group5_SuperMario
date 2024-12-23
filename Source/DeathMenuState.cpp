#include "Headers/DeathMenuState.h"
#include "Headers/MainMenuState.h"
#include "Headers/GameState.h"


void DeathMenuState::initVariables() {}


void DeathMenuState::initBackground()
{
    background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    background.setFillColor(sf::Color(0, 0, 0, 150));
    background.setPosition(0.f, 0.f);
}


void DeathMenuState::initTexts()
{
    if (!font.loadFromFile("Source/Resources/font/Super-Mario-Bros--3.ttf")) {
        throw("ERROR::DEATHMENUSTATE::COULD NOT LOAD FONT");
    }


    titleText.setFont(font);
    titleText.setString("Game Over!");
    titleText.setCharacterSize(75);
    titleText.setFillColor(sf::Color::White);
    centerText(titleText, window->getView().getCenter().y - 250);


    questionText.setFont(font);
    questionText.setString("Left click or Press enter to continue");
    questionText.setCharacterSize(30);
    questionText.setFillColor(sf::Color::White);
    centerText(questionText, window->getView().getCenter().y - 100);
}


void DeathMenuState::centerText(sf::Text& text, float y)
{
    text.setPosition(
        window->getView().getCenter().x - text.getGlobalBounds().width / 2,
        y
    );
}

void DeathMenuState::updateBackground() {
    sf::Vector2f viewCenter = window->getView().getCenter();
    sf::Vector2f viewSize = window->getView().getSize();

    background.setPosition(viewCenter.x - viewSize.x / 2.f, viewCenter.y - viewSize.y / 2.f);
}


void DeathMenuState::updateButtonHover(sf::Text& text, sf::Vector2f mousePos)
{
    if (text.getGlobalBounds().contains(mousePos))
        text.setFillColor(sf::Color(200, 200, 200));
    else
        text.setFillColor(sf::Color::White);
}


DeathMenuState::DeathMenuState(StateData* stateData, GameState* gameState)
    : State(stateData), gameState(gameState)
{
    this->initVariables();
    this->initBackground();
    this->initTexts();
}


DeathMenuState::~DeathMenuState() {}


void DeathMenuState::updateGUI()
{
    sf::Vector2f mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

    updateBackground();
    updateButtonHover(questionText, mousePosView);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		this->gameState->endState();
        this->endState();
	}
     
}


void DeathMenuState::update(const float& dt)
{
    updateMousePosition();
    updateGUI();
}


void DeathMenuState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    if (gameState)
        gameState->renderLevelManager(target);

    target->draw(this->background);
    target->draw(this->titleText);
    target->draw(this->questionText);

}
