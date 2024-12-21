#include "Headers/MenuCharacterSelectionState.h"
#include "Headers/MenuWorldState.h"

// Initialisation des textures
void MenuCharacterSelectionState::initTextures()
{
    if (!marioTexture.loadFromFile("Source/Resources/texture/NPCs_Ending.png"))
        throw("ERROR::CHARACTERSELECTIONSTATE::FAILED TO LOAD MARIO TEXTURE");
    if (!luigiTexture.loadFromFile("Source/Resources/texture/NPCs_Ending.png"))
        throw("ERROR::CHARACTERSELECTIONSTATE::FAILED TO LOAD LUIGI TEXTURE");
}

void MenuCharacterSelectionState::initBackground()
{

    if (!backgroundTexture.loadFromFile("Source/Resources/texture/selection_character_background.png"))
        throw("ERROR::MENUCHARACTERSELECTIONSTATE::FAILED TO LOAD BACKGROUND TEXTURE");


    backgroundSprite.setTexture(backgroundTexture);


    sf::Vector2u windowSize = this->window->getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();


    float scaleX = static_cast<float>(windowSize.x) / static_cast<float>(textureSize.x);
    float scaleY = static_cast<float>(windowSize.y) / static_cast<float>(textureSize.y);


    backgroundSprite.setScale(scaleX, scaleY);


    backgroundSprite.setPosition(0.f, 0.f);
}


void MenuCharacterSelectionState::initSprites()
{
    characterSprite.setTexture(marioTexture);
    characterSprite.setTextureRect(sf::IntRect(1, 162, 54, 76));
    characterSprite.setScale(2.f, 2.f);


    sf::Vector2u windowSize = this->window->getSize();
    characterSprite.setPosition(
        (windowSize.x / 2.f) - characterSprite.getGlobalBounds().width / 2.f,
        (windowSize.y / 2.f) - characterSprite.getGlobalBounds().height / 2.f
    );
}


void MenuCharacterSelectionState::initFonts()
{
    if (!font.loadFromFile("Source/Resources/font/Super-Mario-Bros--3.ttf"))
        throw("ERROR::CHARACTERSELECTIONSTATE::FAILED TO LOAD FONT");
}


void MenuCharacterSelectionState::initTitle()
{
    title.setFont(font);
    title.setString("Select Your Character");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);

    sf::Vector2u windowSize = this->window->getSize();
    title.setPosition(
        (windowSize.x / 2.f) - (title.getGlobalBounds().width / 2.f),
        50.f
    );
}


void MenuCharacterSelectionState::initSelectionBox()
{
    selectionBox.setSize(sf::Vector2f(200.f, 200.f));
    selectionBox.setFillColor(sf::Color::White);
    selectionBox.setOutlineThickness(5.f);
    selectionBox.setOutlineColor(sf::Color::Black);


    sf::Vector2u windowSize = this->window->getSize();
    selectionBox.setPosition(
        (windowSize.x / 2.f) - (selectionBox.getSize().x / 2.f),
        (windowSize.y / 2.f) - (selectionBox.getSize().y / 2.f)
    );
}


MenuCharacterSelectionState::MenuCharacterSelectionState(StateData* stateData)
    : State(stateData), currentCharacterIndex(0)
{
    initBackground();
    initTextures();
    initSprites();
    initFonts();
    initTitle();
    initSelectionBox();
}


MenuCharacterSelectionState::~MenuCharacterSelectionState()
{
}


void MenuCharacterSelectionState::updateInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        currentCharacterIndex = 1;
        characterSprite.setTexture(luigiTexture);
        characterSprite.setTextureRect(sf::IntRect(1, 315, 57, 77));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        currentCharacterIndex = 0;
        characterSprite.setTexture(marioTexture);
        characterSprite.setTextureRect(sf::IntRect(1, 162, 54, 76));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        if (currentCharacterIndex == 0)
            this->stateData->userData->setNameCharacter("Mario");
        else
            this->stateData->userData->setNameCharacter("Luigi");

        this->stateData->userData->createPlayer();
        this->states->push(new MenuWorldState(this->stateData));
        this->endState();
    }
}


void MenuCharacterSelectionState::update(const float& dt)
{
    updateMousePosition();
    updateInput();
}


void MenuCharacterSelectionState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;


    target->draw(backgroundSprite);
    


    target->draw(selectionBox);
    target->draw(characterSprite);
    target->draw(title);
}


