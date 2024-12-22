#include "Headers/GUI.h"

bool globalMousePressed = false;
bool globalMouseReleased = true;


namespace GUI
{
	Button::Button(bool stickyAllowed, float x, float y, float width, float height,
		sf::Font* font, std::string text, unsigned charSize,
		sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor)
	{
		this->disable = false;
		this->stickyAllowed = stickyAllowed;
		this->width = width;
		this->height = height;
		this->buttonState = BTN_IDLE;	
		this->font = font;
		this->textIdleColor = textIdleColor;
		this->textHoverColor = textHoverColor;
		this->textActiveColor = textActiveColor;

		this->text.setFont(*this->font);
		this->text.setString(text);
		this->text.setFillColor(sf::Color::White);
		this->text.setCharacterSize(charSize);
		this->text.setPosition(
			x + (width / 2.f) - this->text.getGlobalBounds().width / 2.f,
			y + (height / 2.f) - this->text.getGlobalBounds().height / 2.f
		);

		this->buttonState = BTN_IDLE;
		audio = AudioSystem::getInstance();
	}

	Button::~Button()
	{
	}

	const bool Button::isPressed() const
	{
		if (this->disable)
			return false;
		if (this->buttonState == BTN_ACTIVE) {
			audio->playbuttonSound();
			return true;
		}

		return false;
	}

	void Button::setDisable(bool disable)
	{
		this->disable = disable;
	}

	const std::string Button::getText() const
	{
		return this->text.getString();
	}

	void Button::setText(const std::string text)
	{
		this->text.setString(text);
	}

	void Button::highlight(bool isHighlighted) {
		if (isHighlighted)
		{
			this->text.setFillColor(sf::Color::Blue); 
		}
	}



	TextButton::TextButton(bool stickyAllowed, float x, float y, float width, float height,
		sf::Font* font, std::string text, unsigned character_size,
		sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
		sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
		sf::Color outline_idle_color, sf::Color outline_hover_color)
		: Button(stickyAllowed, x, y, width, height, font, text, character_size,
			text_idle_color, text_hover_color, text_active_color)
	{
		this->shape.setPosition({x,y});
		this->shape.setSize(sf::Vector2f(width, height));
		this->shape.setFillColor(idle_color);
		this->shape.setOutlineThickness(1.f);
		this->shape.setOutlineColor(outline_idle_color);

		this->idleColor = idle_color;
		this->hoverColor = hover_color;
		this->activeColor = active_color;

		this->outlineIdleColor = outline_idle_color;
		this->outlineHoverColor = outline_hover_color;
		this->outlineActiveColor = sf::Color::Transparent;
	}

	TextButton::~TextButton()
	{
	}

	void TextButton::update(const sf::Vector2i mousePos)
	{
		/* Update the booleans for hover and pressed */

		//Idle
		this->buttonState = BTN_IDLE;

		// Check if the mouse is hovering over the button
		if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
		{
			this->buttonState = BTN_HOVER;

			// Handle activation logic
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				// Activate only if the global mouse has been released since the last click
				if (!globalMousePressed && globalMouseReleased)
				{
					this->buttonState = BTN_ACTIVE;
					globalMousePressed = true;  // Mark the mouse as pressed globally
					globalMouseReleased = false; // Mouse is no longer released
				}
			}
			else
			{
				// Mark global mouse as released when no button is pressed
				globalMouseReleased = true;
				globalMousePressed = false;
			}
		}

		switch (this->buttonState)
		{
		case BTN_IDLE:
			this->shape.setFillColor(this->idleColor);
			this->text.setFillColor(this->textIdleColor);
			this->shape.setOutlineColor(this->outlineIdleColor);
			break;
		case BTN_HOVER:
			this->shape.setFillColor(this->hoverColor);
			this->text.setFillColor(this->textHoverColor);
			this->shape.setOutlineColor(this->outlineHoverColor);
			break;
		case BTN_ACTIVE:
			this->shape.setFillColor(this->hoverColor);
			this->text.setFillColor(this->textActiveColor);
			this->shape.setOutlineColor(this->outlineHoverColor);
			break;
		default:
			this->shape.setFillColor(sf::Color::White);
			this->text.setFillColor(sf::Color::Black);
			this->shape.setOutlineColor(sf::Color::Black);
			break;
		}
	}

	void TextButton::setPosition(float x, float y)
	{
		this->shape.setPosition(x, y);
		this->text.setPosition(
			x + (this->shape.getSize().x / 2.f) - this->text.getGlobalBounds().width / 2.f,
			y + (this->shape.getSize().y / 2.f) - this->text.getGlobalBounds().height / 2.f
		);
	}

	void TextButton::render(sf::RenderTarget* target)
	{
		target->draw(this->shape);
		target->draw(this->text);
	}

	TextureButton::TextureButton(bool stickyAllowed, float x, float y, float width, float height,
		sf::Font* font, std::string text, unsigned charSize,
		sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
		std::string idleDirec, std::string hoverDirec, std::string activeDirec) :
		Button(stickyAllowed, x, y, width, height, font, text, charSize,
			text_idle_color, text_hover_color, text_active_color)
	{
		this->idleTexture.loadFromFile(idleDirec);
		this->hoverTexture.loadFromFile(hoverDirec);
		this->activeTexture.loadFromFile(activeDirec);

		this->sprite.setTexture(this->idleTexture);
		this->sprite.setPosition(x, y);
		this->sprite.setScale(width / this->sprite.getGlobalBounds().width, height / this->sprite.getGlobalBounds().height);
	}

	TextureButton::~TextureButton()
	{
	}

	void TextureButton::update(const sf::Vector2i mousePos)
	{
		/* Update the booleans for hover and pressed */

		//If the button is disabled, set it grey
		if (this->disable)
		{
			this->sprite.setColor(sf::Color(100, 100, 100, 255));
			this->text.setFillColor(sf::Color(100, 100, 100, 255));
			return;
		}

		//Idle
		this->buttonState = BTN_IDLE;
		//Check if the users have unpressed

		if (this->sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
		{
			this->buttonState = BTN_HOVER;

			// Handle activation logic
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				// Activate only if the global mouse has been released since the last click
				if (!globalMousePressed && globalMouseReleased)
				{
					this->buttonState = BTN_ACTIVE;
					globalMousePressed = true;  // Mark the mouse as pressed globally
					globalMouseReleased = false; // Mouse is no longer released
				}
			}
			else
			{
				// Mark global mouse as released when no button is pressed
				globalMouseReleased = true;
				globalMousePressed = false;
			}
		}


		//Set the texture
		switch (this->buttonState)
		{
		case BTN_IDLE:
			this->sprite.setTexture(this->idleTexture);
			this->text.setFillColor(this->textIdleColor);
			break;
		case BTN_HOVER:
			this->sprite.setTexture(this->hoverTexture);
			this->text.setFillColor(this->textHoverColor);
			break;
		case BTN_ACTIVE:
			this->sprite.setTexture(this->activeTexture);
			this->text.setFillColor(this->textActiveColor);
			break;
		default:
			break;
		}
	}

	void TextureButton::setPosition(float x, float y)
	{
		this->sprite.setPosition(x, y);
		this->text.setPosition(
			x + (this->sprite.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
			y + (this->sprite.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
		);
	}

	void TextureButton::render(sf::RenderTarget* target)
	{
		target->draw(this->sprite);
		target->draw(this->text);
	}
}