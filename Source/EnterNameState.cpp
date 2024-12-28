#include "Headers/EnterNameState.h"
#include "Headers/MenuCharacterSelectionState.h"

// Constructors/Destructors
EnterNameState::EnterNameState(StateData* stateData)
    : State(stateData)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initText();
    this->initInputBox();
    this->initButtons();
    this->initDecorations();
}

EnterNameState::~EnterNameState() {
    delete this->confirmButton;
    delete this->cancelButton;
}

// Initializer functions
void EnterNameState::initVariables() {
    this->animationTime = 0.f;
    this->userInput = "";
}

void EnterNameState::initBackground() {
    this->backgroundColor = sf::Color(25, 25, 112, 255); // Dark blue background
}

void EnterNameState::initFonts() {
    if (!this->font.loadFromFile("Source/Resources/font/American Captain.ttf")) {
        throw("ERROR::ENTERNAMESTATE::FAILED_TO_LOAD_FONT");
    }
}

void EnterNameState::initText() {
    // Title text
    this->promptText.setFont(this->font);
    this->promptText.setString("Enter your name:");
    this->promptText.setCharacterSize(36);
    this->promptText.setFillColor(sf::Color::White);
    this->promptText.setOutlineColor(sf::Color(0, 0, 0, 150));
    this->promptText.setOutlineThickness(3.f);
    this->promptText.setPosition(
        this->window->getSize().x / 2.f - this->promptText.getGlobalBounds().width / 2.f,
        80.f
    );

    // Input text
    this->inputText.setFont(this->font);
    this->inputText.setString("");
    this->inputText.setCharacterSize(30);
    this->inputText.setFillColor(sf::Color::White);
    this->inputText.setPosition(
        this->window->getSize().x / 2.f - 140.f,
        165.f
    );
}

void EnterNameState::initInputBox() {
    this->inputBox.setSize(sf::Vector2f(300.f, 50.f));
    this->inputBox.setFillColor(sf::Color(50, 50, 50, 230));
    this->inputBox.setOutlineColor(sf::Color(255, 216, 0));
    this->inputBox.setOutlineThickness(3.f);
    this->inputBox.setPosition(
        this->window->getSize().x / 2.f - 150.f,
        150.f
    );
}

void EnterNameState::initButtons() {
    float buttonWidth = 150.f;
    float buttonHeight = 60.f;
    float buttonY = 250.f;

    this->confirmButton = new GUI::TextButton(
        false,
        this->window->getSize().x / 2.f - buttonWidth - 20.f,
        buttonY,
        buttonWidth,
        buttonHeight,
        &this->font,
        "Let's-a Go!",
        28,
        sf::Color::White,
        sf::Color(40, 175, 40),
        sf::Color(30, 140, 30),
        sf::Color(70, 70, 70, 200),
        sf::Color(150, 150, 150, 255),
        sf::Color(20, 20, 20, 200)
    );

    this->cancelButton = new GUI::TextButton(
        false,
        this->window->getSize().x / 2.f + 20.f,
        buttonY,
        buttonWidth,
        buttonHeight,
        &this->font,
        "Cancel",
        28,
        sf::Color::White,
        sf::Color(175, 40, 40),
        sf::Color(140, 30, 30),
        sf::Color(70, 70, 70, 200),
        sf::Color(150, 150, 150, 255),
        sf::Color(20, 20, 20, 200)
    );
}

void EnterNameState::initDecorations() {
    this->coinShape.setRadius(15.f);
    this->coinShape.setPointCount(8);
    this->coinShape.setFillColor(sf::Color(255, 216, 0));
    this->coinShape.setOutlineColor(sf::Color(204, 172, 0));
    this->coinShape.setOutlineThickness(2.f);

    this->coinShape2 = this->coinShape;
}

// Update functions
void EnterNameState::updateInput(const sf::Event& event) {
    static bool isKeyPressed = false;
    if (event.type == sf::Event::TextEntered && !isKeyPressed) {
        if (event.text.unicode == 8) { // Backspace
            if (!this->userInput.empty()) {
                this->userInput.pop_back();
            }
        }
        else if (event.text.unicode >= 32 && event.text.unicode <= 126) { // Printable characters
            if (event.text.unicode != 32 && this->userInput.size() < 20) { // Limit input to 20 characters
                this->userInput += static_cast<char>(event.text.unicode);
            }
        }
        this->inputText.setString(this->userInput + "_");

        // Center the text
        sf::FloatRect textBounds = this->inputText.getLocalBounds();
        this->inputText.setOrigin(
            textBounds.left + textBounds.width / 2.0f,
            textBounds.top + textBounds.height / 2.0f
        );
        this->inputText.setPosition(this->window->getSize().x / 2.0f, 180.f); // Center on screen

        isKeyPressed = true;
    }
    if (event.type == sf::Event::KeyReleased) {
        isKeyPressed = false;
    }
}


void EnterNameState::updateButtons() {
    this->confirmButton->update(this->mousePosWindow);
    this->cancelButton->update(this->mousePosWindow);

    if (this->confirmButton->isPressed() && !this->userInput.empty()) {
        this->stateData->userData->setName(this->userInput);
        this->states->push(new MenuCharacterSelectionState(this->stateData));
    }

    if (this->cancelButton->isPressed()) {
        this->endState();
    }
}

void EnterNameState::updateAnimation(const float& dt) {
    this->animationTime += dt;

    float coinBob = std::sin(this->animationTime * 3.f) * 5.f;
    float coinBob2 = std::sin(this->animationTime * 3.f + 1.f) * 5.f;

    this->coinShape.setPosition(50.f, 150.f + coinBob);
    this->coinShape2.setPosition(this->window->getSize().x - 80.f, 150.f + coinBob2);
}

void EnterNameState::endState() {
    this->quit = true;
}

void EnterNameState::update(const float& dt, const sf::Event& event) {
	this->updateMousePosition();
    this->updateInput(event);
    this->updateButtons();
    this->updateAnimation(dt);
}

void EnterNameState::render(sf::RenderTarget* target) {
    if (!target)
        target = this->window;

    target->clear(this->backgroundColor);

    target->draw(this->coinShape);
    target->draw(this->coinShape2);
    target->draw(this->promptText);
    target->draw(this->inputBox);
    target->draw(this->inputText);

    this->confirmButton->render(target);
    this->cancelButton->render(target);
}