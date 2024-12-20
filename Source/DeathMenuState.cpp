#include "Headers/DeathMenuState.h"
#include "Headers/MainMenuState.h"
#include "Headers/GameState.h"


void DeathMenuState::initVariables() {}


void DeathMenuState::initBackground()
{
    background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    background.setFillColor(sf::Color::Black);
    background.setPosition(0.f, 0.f);
}


void DeathMenuState::initTexts()
{
    if (!font.loadFromFile("Source/Resources/font/Super-Mario-Bros--3.ttf")) {
        throw("ERROR::DEATHMENUSTATE::COULD NOT LOAD FONT");
    }


    titleText.setFont(font);
    titleText.setString("Game Over");
    titleText.setCharacterSize(100);
    titleText.setFillColor(sf::Color::White);
    centerText(titleText, window->getView().getCenter().y - 250);


    questionText.setFont(font);
    questionText.setString("Play Again?");
    questionText.setCharacterSize(50);
    questionText.setFillColor(sf::Color::White);
    centerText(questionText, window->getView().getCenter().y - 100);


    yesButtonText.setFont(font);
    yesButtonText.setString("Yes");
    yesButtonText.setCharacterSize(60);
    yesButtonText.setFillColor(sf::Color::White);
    centerText(yesButtonText, window->getView().getCenter().y + 50);


    noButtonText.setFont(font);
    noButtonText.setString("No");
    noButtonText.setCharacterSize(60);
    noButtonText.setFillColor(sf::Color::White);
    centerText(noButtonText, window->getView().getCenter().y + 150);
}


void DeathMenuState::centerText(sf::Text& text, float y)
{
    text.setPosition(
        window->getView().getCenter().x - text.getGlobalBounds().width / 2,
        y
    );
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


    updateButtonHover(yesButtonText, mousePosView);
    updateButtonHover(noButtonText, mousePosView);


    if (yesButtonText.getGlobalBounds().contains(mousePosView) &&
        sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        
        //this->stateData->audio->init();

        gameState->setPlayerHealth(gameState->getHealthStart());
        gameState->loadLevel(
            gameState->getPlayer(),
            gameState->getWorld(),
            gameState->getLevel()
        );
        
        this->endState();
    }


    if (noButtonText.getGlobalBounds().contains(mousePosView) &&
        sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        window->setView(window->getDefaultView());

        this->stateData->audio->playMusic();
        this->states->push(new MainMenuState(this->stateData));
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

    target->draw(this->background);
    target->draw(this->titleText);
    target->draw(this->questionText);
    target->draw(this->yesButtonText);
    target->draw(this->noButtonText);
}
