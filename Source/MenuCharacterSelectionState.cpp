#include "Headers/MenuCharacterSelectionState.h"
#include "Headers/MenuWorldState.h"

void MenuCharacterSelectionState::initTextures() {
    if (!marioTexture.loadFromFile("Source/Resources/texture/NPCs_Ending.png"))
        throw("ERROR::CHARACTERSELECTIONSTATE::FAILED TO LOAD MARIO TEXTURE");
    if (!luigiTexture.loadFromFile("Source/Resources/texture/NPCs_Ending.png"))
        throw("ERROR::CHARACTERSELECTIONSTATE::FAILED TO LOAD LUIGI TEXTURE");
}

MenuCharacterSelectionState::~MenuCharacterSelectionState() {
}

void MenuCharacterSelectionState::initFont() {
    if (!font.loadFromFile("Source/Resources/font/Super-Mario-Bros--3.ttf"))
        throw("ERROR::CHARACTERSELECTIONSTATE::FAILED TO LOAD FONT");
}

void MenuCharacterSelectionState::initBackground() {
    // Load background texture
    if (!backgroundTexture.loadFromFile("Source/Resources/texture/selectionBackground2.png"))
        throw("ERROR::MENUCHARACTERSELECTIONSTATE::FAILED TO LOAD BACKGROUND TEXTURE");

    // Setup background sprite
    backgroundSprite.setTexture(backgroundTexture);

    // Get window size
    sf::Vector2u windowSize = this->window->getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();

    // Calculate scale to fit window
    float scaleX = static_cast<float>(windowSize.x) / static_cast<float>(textureSize.x);
    float scaleY = static_cast<float>(windowSize.y) / static_cast<float>(textureSize.y);

    // Apply scale to cover whole window
    backgroundSprite.setScale(scaleX, scaleY);

    // Position at top-left corner
    backgroundSprite.setPosition(0.f, 0.f);

    // Optional: Add a darkening overlay for better visibility of UI elements
    sf::RectangleShape darkenOverlay;
    darkenOverlay.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    darkenOverlay.setFillColor(sf::Color(0, 0, 0, 100)); // Semi-transparent black
    backgroundSprite.setColor(sf::Color(255, 255, 255, 200)); // Slightly dim the background
}

void MenuCharacterSelectionState::initCharacterCards() {
    sf::Vector2u windowSize = this->window->getSize();
    float cardWidth = 300.f;
    float cardHeight = 400.f;
    float cardSpacing = 100.f;

    // Setup character cards
    CharacterCard marioCard;
    CharacterCard luigiCard;

    // Define text margins and spacing
    const float topMargin = 30.f;
    const float bottomMargin = 30.f;
    const float nameTextSize = 36;
    const float descTextSize = 18;
    const float spriteScale = 3.f;
    const float textPadding = 10.f;

    // Mario Card Base Setup
    marioCard.card.setSize(sf::Vector2f(cardWidth, cardHeight));
    marioCard.card.setFillColor(sf::Color(255, 0, 0, 200));
    marioCard.card.setOutlineThickness(3.f);
    marioCard.card.setOutlineColor(sf::Color::White);

    // Mario Sprite Setup
    marioCard.characterSprite.setTexture(marioTexture);
    marioCard.characterSprite.setTextureRect(sf::IntRect(1, 162, 54, 76));
    marioCard.characterSprite.setScale(spriteScale, spriteScale);

    // Mario Text Setup with word wrapping
    marioCard.nameText.setFont(font);
    marioCard.nameText.setString("MARIO");
    marioCard.nameText.setCharacterSize(nameTextSize);
    marioCard.nameText.setFillColor(sf::Color::White);
    marioCard.nameText.setStyle(sf::Text::Bold);

    // Description text with proper line breaks and smaller size
    marioCard.descriptionText.setFont(font);
    marioCard.descriptionText.setString("DOUBLE JUMP\nHIGHER POWER");
    marioCard.descriptionText.setCharacterSize(descTextSize);
    marioCard.descriptionText.setFillColor(sf::Color::White);
    marioCard.descriptionText.setLineSpacing(1.2f); // Increase line spacing

    // Luigi Card (copy base properties from Mario)
    luigiCard = marioCard;
    luigiCard.card.setFillColor(sf::Color(0, 255, 0, 200));
    luigiCard.characterSprite.setTexture(luigiTexture);
    luigiCard.characterSprite.setTextureRect(sf::IntRect(1, 315, 57, 77));
    luigiCard.nameText.setString("LUIGI");
    luigiCard.descriptionText.setString("JUMP HIGHER\nBETTER LIVES");
    marioCard.descriptionText.setLineSpacing(1.2f); // Increase line spacing


    // Position cards
    float totalWidth = (cardWidth * 2) + cardSpacing;
    float startX = (windowSize.x - totalWidth) / 2;
    float centerY = (windowSize.y - cardHeight) / 2;

    marioCard.card.setPosition(startX, centerY);
    luigiCard.card.setPosition(startX + cardWidth + cardSpacing, centerY);

    // Set initial properties
    marioCard.isSelected = true;
    luigiCard.isSelected = false;
    marioCard.scale = 1.f;
    luigiCard.scale = 1.f;

    // Store original positions
    marioCard.originalPos = marioCard.card.getPosition();
    luigiCard.originalPos = luigiCard.card.getPosition();

    // Add to vector
    characterCards.push_back(marioCard);
    characterCards.push_back(luigiCard);

    // Update text and sprite positions relative to cards
    for (auto& card : characterCards) {
        sf::FloatRect cardBounds = card.card.getGlobalBounds();

        // Position name text at the top with proper margin
        sf::FloatRect nameRect = card.nameText.getGlobalBounds();
        card.nameText.setPosition(
            cardBounds.left + (cardBounds.width - nameRect.width) / 2.f,
            cardBounds.top + topMargin
        );

        // Center character sprite vertically between name and description
        sf::FloatRect spriteRect = card.characterSprite.getGlobalBounds();
        float spriteY = cardBounds.top + (cardBounds.height - spriteRect.height) / 2.f;
        card.characterSprite.setPosition(
            cardBounds.left + (cardBounds.width - spriteRect.width) / 2.f,
            spriteY
        );

        // Position description text at the bottom with proper spacing
        sf::FloatRect descRect = card.descriptionText.getGlobalBounds();
        card.descriptionText.setPosition(
            cardBounds.left + (cardBounds.width - descRect.width) / 2.f,
            cardBounds.top + cardBounds.height - descRect.height - bottomMargin
        );

        // Center align the text
        card.descriptionText.setOrigin(
            descRect.width / 2.f,
            0.f
        );
        card.descriptionText.setPosition(
            cardBounds.left + cardBounds.width / 2.f,
            cardBounds.top + cardBounds.height - descRect.height - bottomMargin
        );
    }
}

void MenuCharacterSelectionState::initUI() {
    sf::Vector2u windowSize = this->window->getSize();

    // Title
    title.setFont(font);
    title.setString("SELECT YOUR CHARACTER");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color::White);
    title.setOutlineThickness(3.f);
    title.setOutlineColor(sf::Color::Black);

    sf::FloatRect titleRect = title.getGlobalBounds();
    title.setPosition(
        (windowSize.x - titleRect.width) / 2,
        50.f
    );

    // Prompt text
    promptText.setFont(font);
    promptText.setString("Press ENTER to confirm selection");
    promptText.setCharacterSize(30);
    promptText.setFillColor(sf::Color::White);
    promptText.setOutlineThickness(2.f);
    promptText.setOutlineColor(sf::Color::Black);

    sf::FloatRect promptRect = promptText.getGlobalBounds();
    promptText.setPosition(
        (windowSize.x - promptRect.width) / 2,
        windowSize.y - 100.f
    );
}

MenuCharacterSelectionState::MenuCharacterSelectionState(StateData* stateData, bool Continue)
    : State(stateData), currentCharacterIndex(0), transitioningOut(false),
    transitionAlpha(0.f), animationTime(0.f),
    cardHoverScale(1.1f), cardNormalScale(1.f)
{
	this->Continue = Continue;
}

MenuCharacterSelectionState::MenuCharacterSelectionState(StateData* stateData)
    : State(stateData), currentCharacterIndex(0), transitioningOut(false),
    transitionAlpha(0.f), animationTime(0.f),
    cardHoverScale(1.1f), cardNormalScale(1.f)
{
    Continue = false;
    initTextures();
    initBackground();
    initFont();
    initCharacterCards();
    initUI();
}

void MenuCharacterSelectionState::updateCardAnimations(const float& dt) {
    animationTime += dt;

    for (size_t i = 0; i < characterCards.size(); i++) {
        auto& card = characterCards[i];
        float targetScale = (i == currentCharacterIndex) ? cardHoverScale : cardNormalScale;
        float scaleSpeed = 5.f;

        // Smooth scale interpolation
        card.scale += (targetScale - card.scale) * scaleSpeed * dt;

        // Apply scale and center the card
        sf::Vector2f scaleDiff = card.card.getSize() * (card.scale - 1.f);
        card.card.setScale(card.scale, card.scale);
        card.card.setPosition(
            card.originalPos.x - scaleDiff.x / 2,
            card.originalPos.y - scaleDiff.y / 2
        );

        // Update character sprite position
        sf::FloatRect cardBounds = card.card.getGlobalBounds();
        sf::FloatRect spriteBounds = card.characterSprite.getGlobalBounds();
        card.characterSprite.setPosition(
            cardBounds.left + (cardBounds.width - spriteBounds.width) / 2,
            cardBounds.top + (cardBounds.height - spriteBounds.height) / 2
        );

        // Add floating animation
        float floatOffset = std::sin(animationTime * 3.f) * 5.f;
        card.characterSprite.move(0, floatOffset);

        // Make selected card pulse
        if (i == currentCharacterIndex) {
            float pulseAlpha = (std::sin(animationTime * 5.f) * 25.f) + 230.f;
            sf::Color cardColor = card.card.getFillColor();
            cardColor.a = static_cast<sf::Uint8>(pulseAlpha);
            card.card.setFillColor(cardColor);
        }
    }
}

void MenuCharacterSelectionState::updateInput() {
    if (transitioningOut) return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->stateData->audio->playbuttonSound();
        currentCharacterIndex = 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->stateData->audio->playbuttonSound();
        currentCharacterIndex = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        this->stateData->audio->playbuttonSound();
        transitioningOut = true;
        if (currentCharacterIndex == 0)
            this->stateData->userData->setNameCharacter("Mario");
        else
            this->stateData->userData->setNameCharacter("Luigi");
    }
}

void MenuCharacterSelectionState::updateTransitionEffect(const float& dt) {
    if (transitioningOut) {
        transitionAlpha += dt * 255.f * 2.f; // Fade out speed
        if (transitionAlpha >= 255.f) {
            this->stateData->userData->createPlayer();
            this->states->push(new MenuWorldState(this->stateData));
            this->endState();
        }
    }
}

void MenuCharacterSelectionState::update(const float& dt, const sf::Event& event) {
    if (Continue)
    {
        this->Continue = false;
		std::ifstream saveFile("SaveGame.txt");
		std::string currentCharacter;
        int currentWorld, currentLevel;
        float view_x, CurrentLeft, CurrentRight;

        saveFile >> currentWorld;
		saveFile >> currentLevel;

        saveFile >> view_x;
        saveFile >> CurrentLeft;
        saveFile >> CurrentRight;
		saveFile >> currentCharacter;
		saveFile.close();

        std::cerr << currentCharacter << std::endl;


		this->stateData->userData->setNameCharacter(currentCharacter);
		this->stateData->userData->UserData::createPlayer();
		this->states->push(new MenuWorldState(this->stateData, 1));
		this->endState();

        return;
    }
    updateMousePosition();
    updateInput();
    updateCardAnimations(dt);
    updateTransitionEffect(dt);
}

void MenuCharacterSelectionState::render(sf::RenderTarget* target) {
    if (!target)
        target = this->window;

    // Draw background
    target->draw(backgroundSprite);

    // Draw UI elements
    target->draw(title);

    // Draw character cards
    for (size_t i = 0; i < characterCards.size(); i++) {
        auto& card = characterCards[i];
        target->draw(card.card);
        target->draw(card.characterSprite);
        target->draw(card.nameText);
        target->draw(card.descriptionText);
    }

    target->draw(promptText);

    // Draw transition overlay
    if (transitioningOut) {
        sf::RectangleShape overlay(sf::Vector2f(window->getSize()));
        overlay.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(transitionAlpha)));
        target->draw(overlay);
    }
}