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
    titleText.setString("Game Over!");
    titleText.setCharacterSize(100);
    titleText.setFillColor(sf::Color::White);
    centerText(titleText, window->getView().getCenter().y - 250);


    questionText.setFont(font);
    questionText.setString("Left click or Press enter to continue");
    questionText.setCharacterSize(50);
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


    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        sf::View view = window->getDefaultView();

        // Set the view's position so its top-left corner is at (0, 0)
        sf::Vector2f viewSize = view.getSize();
        view.setCenter(viewSize.x / 2, viewSize.y / 2);

        // Apply the view to the window
        window->setView(view);
		this->gameState->endState();
        this->stateData->userData->resetPlayer(gameState->getWorld());
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

}
