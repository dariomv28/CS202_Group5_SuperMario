#include "Headers/EnterNameState.h"
#include "Headers/MenuCharacterSelectionState.h"
EnterNameState::EnterNameState(StateData* stateData)
    : State(stateData) {
    this->initFonts();
    this->initText();
    this->initInputBox();
    this->initButtons();
}

EnterNameState::~EnterNameState() {
    delete this->confirmButton;
    delete this->cancelButton;
}

void EnterNameState::initFonts() {
    if (!this->font.loadFromFile("Source/Resources/font/American Captain.ttf")) {
        throw("ERROR::ENTERNAMESTATE::FAILED_TO_LOAD_FONT");
    }
}

void EnterNameState::initText() {
    this->promptText.setFont(this->font);
    this->promptText.setString("Enter your name:");
    this->promptText.setCharacterSize(24);
    this->promptText.setFillColor(sf::Color::White);
    this->promptText.setPosition(100.f, 100.f);

    this->inputText.setFont(this->font);
    this->inputText.setString("_");
    this->inputText.setCharacterSize(24);
    this->inputText.setFillColor(sf::Color::White);
    this->inputText.setPosition(100.f, 150.f);
}

void EnterNameState::initInputBox() {
    this->inputBox.setSize(sf::Vector2f(300.f, 50.f));
    this->inputBox.setFillColor(sf::Color(50, 50, 50, 200));
    this->inputBox.setOutlineColor(sf::Color::White);
    this->inputBox.setOutlineThickness(2.f);
    this->inputBox.setPosition(90.f, 140.f);
}

void EnterNameState::initButtons() {
    this->confirmButton = new GUI::TextButton(false, 100.f, 250.f, 100.f, 50.f, &this->font, "Confirm", 24,
        sf::Color::White, sf::Color::Green, sf::Color::Blue,
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
    this->cancelButton = new GUI::TextButton(false, 250.f, 250.f, 100.f, 50.f, &this->font, "Cancel", 24,
        sf::Color::White, sf::Color::Red, sf::Color::Blue,
        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

void EnterNameState::updateInput(const sf::Event& event) {
    static bool isKeyPressed = false;

    if (event.type == sf::Event::TextEntered && !isKeyPressed) {
        if (event.text.unicode == 8) { // Backspace
            if (!this->userInput.empty()) {
                this->userInput.pop_back();
            }
        }
        else if (event.text.unicode >= 32 && event.text.unicode <= 126) { // Printable characters
            if (this->userInput.size() < 20) { // Limit input to 20 characters
                this->userInput += static_cast<char>(event.text.unicode);
            }
        }
        this->inputText.setString(this->userInput + "_");
        isKeyPressed = true;
    }

    if (event.type == sf::Event::KeyReleased) {
        isKeyPressed = false;
    }
}

void EnterNameState::updateGUI() {
    this->confirmButton->update(this->mousePosWindow);
    this->cancelButton->update(this->mousePosWindow);

    if (this->confirmButton->isPressed()) {
        if (!this->userInput.empty()) { // Only proceed if a name is entered
            this->stateData->userData->setName(this->userInput);
            this->states->push(new MenuCharacterSelectionState(this->stateData));
        }
    }

    if (this->cancelButton->isPressed()) {
        this->quit = true; // Exit without saving
    }
}

void EnterNameState::update(const float& dt, const sf::Event& event) {
    this->updateMousePosition();
    this->updateInput(event);
    this->updateGUI();
}

void EnterNameState::render(sf::RenderTarget* target) {
    if (!target)
        target = this->window;

    target->draw(this->promptText);
    target->draw(this->inputBox);
    target->draw(this->inputText);

    this->confirmButton->render(target);
    this->cancelButton->render(target);
}

