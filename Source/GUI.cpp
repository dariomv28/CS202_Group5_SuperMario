#include "Headers/GUI.h"

namespace GUI
{
	Button::Button(float x, float y, float width, float height,
		sf::Font* font, std::string text, unsigned charSize)
	{
		this->width = width;
		this->height = height;
		this->buttonState = BTN_IDLE;	
		this->font = font;
		this->text.setFont(*this->font);
		this->text.setString(text);
		this->text.setFillColor(sf::Color::White);
		this->text.setCharacterSize(charSize);
		this->text.setPosition(
			x + (width / 2.f) - this->text.getGlobalBounds().width / 2.f,
			y + (height / 2.f) - this->text.getGlobalBounds().height / 2.f
		);
	}

	Button::~Button()
	{
	}

	const bool Button::isPressed() const
	{
		if (this->buttonState == BTN_ACTIVE)
			return true;

		return false;
	}

	const std::string Button::getText() const
	{
		return this->text.getString();
	}

	void Button::setText(const std::string text)
	{
		this->text.setString(text);
	}

	TextButton::TextButton(float x, float y, float width, float height,
		sf::Font* font, std::string text, unsigned character_size,
		sf::Color text_idle_color, sf::Color text_hover_color,
		sf::Color idle_color, sf::Color hover_color,
		sf::Color outline_idle_color, sf::Color outline_hover_color)
		: Button(x, y, width, height, font, text, character_size)
	{
		this->shape.setPosition({x,y});
		this->shape.setSize(sf::Vector2f(width, height));
		this->shape.setFillColor(idle_color);
		this->shape.setOutlineThickness(1.f);
		this->shape.setOutlineColor(outline_idle_color);

		this->textIdleColor = text_idle_color;
		this->textHoverColor = text_hover_color;
		this->textActiveColor = sf::Color::White;

		this->idleColor = idle_color;
		this->hoverColor = hover_color;

		this->outlineIdleColor = outline_idle_color;
		this->outlineHoverColor = outline_hover_color;
	}

	TextButton::~TextButton()
	{
	}

	void TextButton::update(const sf::Vector2f mousePos)
	{
		/* Update the booleans for hover and pressed */

		//Idle
		this->buttonState = BTN_IDLE;

		//Hover
		if (this->shape.getGlobalBounds().contains(mousePos))
		{
			this->buttonState = BTN_HOVER;

			//Pressed
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->buttonState = BTN_ACTIVE;
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

	void TextButton::render(sf::RenderTarget* target)
	{
		target->draw(this->shape);
		target->draw(this->text);
	}

	TextureButton::TextureButton(float x, float y, float width, float height,
		std::string idleDirec, std::string hoverDirec) :
		Button(x, y, width, height, nullptr, "")
	{
		this->idleTexture.loadFromFile(idleDirec);
		this->hoverTexture.loadFromFile(hoverDirec);
		this->sprite.setTexture(this->idleTexture);
		this->sprite.setPosition(x, y);
		this->sprite.setScale(width / this->sprite.getGlobalBounds().width, height / this->sprite.getGlobalBounds().height);

	}

	TextureButton::~TextureButton()
	{
	}

	void TextureButton::update(const sf::Vector2f mousePos)
	{
		/* Update the booleans for hover and pressed */

		//Idle
		this->buttonState = BTN_IDLE;

		//Hover
		if (this->sprite.getGlobalBounds().contains(mousePos))
		{
			this->buttonState = BTN_HOVER;

			//Pressed
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->buttonState = BTN_ACTIVE;
			}
		}

		switch (this->buttonState)
		{
		case BTN_IDLE:
			this->sprite.setTexture(this->idleTexture);
			break;
		case BTN_HOVER:
			this->sprite.setTexture(this->hoverTexture);
			break;
		case BTN_ACTIVE:
			break;
		default:
			break;
		}
	}

	void TextureButton::render(sf::RenderTarget* target)
	{
		target->draw(this->sprite);
		target->draw(this->text);
	}
}