#ifndef CHATUI_H
#define CHATUI_H

#include "ChatComponent.h"

class ChatUI {
public:
    ChatUI(ChatComponent* chatComponent, sf::RenderWindow* window);

    void updatePosition(const sf::View& view);
    void update(const sf::View& view);
    void render(sf::RenderTarget* target);
    void sendChatMessage();
    std::string wrapText(const std::string& text, const sf::Font& font, unsigned int fontSize, float maxWidth);
private:
    ChatComponent* chatComponent;
    sf::RenderWindow* window;

    sf::RectangleShape chatBoxRect;
    sf::RectangleShape chatInputRect;
    sf::Text chatText;
	sf::Text titleText; 
    sf::Text userInputText;
    sf::Font font;

    sf::String userInput;
    sf::String response;
};

#endif // CHATUI_H