#include "Headers/ChatUI.h"

ChatUI::ChatUI(ChatComponent* chatComponent, sf::RenderWindow* window)
    : chatComponent(chatComponent), window(window)
{
    // Initialize UI elements
    // Chat Box
    chatBoxRect.setSize(sf::Vector2f(800.f, 400.f));
    chatBoxRect.setFillColor(sf::Color(0, 0, 0, 128));
    chatBoxRect.setOutlineColor(sf::Color(255, 255, 255, 128));
    chatBoxRect.setOutlineThickness(2.f);

    // Chat Input Field
    chatInputRect.setSize(sf::Vector2f(700.f, 70.f));
    chatInputRect.setFillColor(sf::Color(255, 255, 255, 200));
    chatInputRect.setOutlineColor(sf::Color(128, 128, 128, 128));
    chatInputRect.setOutlineThickness(2.f);

    // Chat Text Display
    chatText.setFont(font);
    chatText.setCharacterSize(22);
    chatText.setFillColor(sf::Color::White);
    chatText.setString("");

	// User Input Text
    userInputText.setFont(font);
    userInputText.setCharacterSize(22);
    userInputText.setFillColor(sf::Color::Black); // Contrast with input box background
    userInputText.setString("");

    // Load font
    if (!font.loadFromFile("Source/Resources/font/pixel-nes.otf"))
    {
        throw("ERROR::LEVELGUI::FAILED_TO_LOAD_FONT");
    }

	// Title Text
    titleText.setFont(font);
    titleText.setCharacterSize(28); // Slightly larger than chat text
    titleText.setFillColor(sf::Color::White);
    titleText.setString("CHATBOT SYSTEM");
    titleText.setStyle(sf::Text::Bold);
}

std::string ChatUI::wrapText(const std::string& text, const sf::Font& font, unsigned int fontSize, float maxWidth) {
    std::string wrappedText = "";
    std::string line = "";
    std::string word = "";

    sf::Text sfText;
    sfText.setFont(font);
    sfText.setCharacterSize(fontSize);

    for (char c : text) {
        if (c == ' ' || c == '\n') {
            sfText.setString(line + word); // Check line + next word
            if (sfText.getLocalBounds().width > maxWidth) {
                wrappedText += line + '\n'; // Break the line
                line = word + ' ';          // Start a new line
            }
            else {
                line += word + ' ';         // Append word to the line
            }
            word = "";
        }
        else {
            word += c; // Build word
        }
    }

    // Add the last word
    if (!word.empty()) {
        sfText.setString(line + word);
        if (sfText.getLocalBounds().width > maxWidth) {
            wrappedText += line + '\n' + word;
        }
        else {
            wrappedText += line + word;
        }
    }

    return wrappedText;
}

void ChatUI::updatePosition(const sf::View& view) {
	// Update chat box position
	chatBoxRect.setPosition(view.getCenter().x - view.getSize().x / 2.f + 400.f, view.getCenter().y + view.getSize().y / 2.f - 700.f - 50.f);
	chatInputRect.setPosition(chatBoxRect.getPosition().x + 50.f, chatBoxRect.getPosition().y + 300.f);
    userInputText.setPosition(chatInputRect.getPosition().x + 10.f, chatInputRect.getPosition().y + 10.f);
	chatText.setPosition(chatBoxRect.getPosition().x + 50.f, chatBoxRect.getPosition().y + 50.f);

    titleText.setPosition(
        chatBoxRect.getPosition().x + 250.f,   // Keep title aligned with chat box
        chatBoxRect.getPosition().y + 10.f  // Positioned slightly above the chat box
    );
}

void ChatUI::update(const sf::View& view)
{
    updatePosition(view);

    // Check for alphanumeric key presses
    for (int key = sf::Keyboard::A; key <= sf::Keyboard::Z; ++key) {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key))) {
            static sf::Clock keyTimer;
            if (keyTimer.getElapsedTime().asMilliseconds() > 150)
            {
                keyTimer.restart();
                userInput += static_cast<char>(key - sf::Keyboard::A + 'a');
            }
        }
    }
    for (int key = sf::Keyboard::Num0; key <= sf::Keyboard::Num9; ++key) {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key))) {
            static sf::Clock keyTimer;
            if (keyTimer.getElapsedTime().asMilliseconds() > 150)
            {
                keyTimer.restart();
                userInput += static_cast<char>(key - sf::Keyboard::Num0 + '0');
            }
        }
    }

    // Handle backspace
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !userInput.isEmpty()) {
        static sf::Clock keyTimer;
        if (keyTimer.getElapsedTime().asMilliseconds() > 150)
        {
            keyTimer.restart();
            userInput.erase(userInput.getSize() - 1, 1);
        }
    }

	// Handle space
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		static sf::Clock keyTimer;
		if (keyTimer.getElapsedTime().asMilliseconds() > 200)
		{
			keyTimer.restart();
			userInput += ' ';
		}
	}

    // Update the displayed user input text
    userInputText.setString(userInput);
    
	// Update the chat text display
    float maxWidth = 700.f; // Max width of chatBoxRect or chatInputRect
    std::string wrappedText = wrapText(response, font, 22, maxWidth);
    chatText.setString(wrappedText);

    // Handle message sending
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !userInput.isEmpty()) {
        sendChatMessage();
        userInput.clear(); // Clear input field after sending
        userInputText.setString(userInput); // Update the display
    }

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
		userInput.clear();
		userInputText.setString(userInput);

		response.clear();
		chatText.setString(response);
	}
}


void ChatUI::render(sf::RenderTarget* target)
{
    target->draw(chatBoxRect);
    target->draw(chatInputRect);
    target->draw(chatText);
    target->draw(userInputText);
    target->draw(titleText);
}

void ChatUI::sendChatMessage()
{
    if (!userInput.isEmpty())
    {
        // Send the input string to the chat system
        chatComponent->sendMessage(userInput.toAnsiString());
	    response = chatComponent->getResponse();

		// Update the chat text with the response
		chatText.setString(userInput + "\n" + response);

        // Clear the input after sending
        userInput.clear();
        chatText.setString(""); // Reset displayed input
    }
}