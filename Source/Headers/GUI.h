#pragma once
#include "stdafx.h"

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

namespace GUI
{
	//Abstract Button class
	class Button
	{
	protected:
		sf::Font* font;
		sf::Text text;

		sf::Vector2f positon;
		float width;
		float height;
		short unsigned buttonState;
	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text = "", unsigned charSize = -1);
		~Button();

		//Getters
		const bool isPressed() const;
		const std::string getText() const;
	
		//Setters
		void setText(const std::string text);

		virtual void render(sf::RenderTarget* target) = 0;
		virtual void update(const sf::Vector2f mousePos) = 0;
	};

	//Classic Button with RectangleShape and Text
	class TextButton: 
		public Button {
	private:

		sf::RectangleShape shape;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;

	public:
		TextButton(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color,
			sf::Color idle_color, sf::Color hover_color,
			sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent);
		~TextButton();

		void render(sf::RenderTarget* target);
		void update(const sf::Vector2f mousePos);
	};

	//Button with Texture and Text
	class TextureButton :
		public Button {
	private:
		sf::Texture idleTexture;
		sf::Texture hoverTexture;

		sf::Sprite sprite;
	public:
		TextureButton(float x, float y, float width, float height,
			std::string idleDirec, std::string hoverDirec);
		~TextureButton();

		void render(sf::RenderTarget* target);
		void update(const sf::Vector2f mousePos);
	};
};

