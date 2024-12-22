#pragma once
#include "stdafx.h"
#include "AudioSystem.h"
namespace GUI
{
	enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

	//Abstract Button class
	class Button
	{
	protected:
		sf::Font* font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		float width;
		float height;
		short unsigned buttonState;

		bool stickyAllowed;
		AudioSystem* audio;
		bool disable;


	public:
		Button(bool stickyAllowed, float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned charSize,
			sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor);
		~Button();

		//Getters
		const bool isPressed() const;
		const std::string getText() const;
	
		//Setters
		void setText(const std::string text);
		void setDisable(bool disable);
		bool getDisable() { return disable; }

		virtual void render(sf::RenderTarget* target) = 0;
		virtual void update(const sf::Vector2i mousePos) = 0;



		void highlight(bool isHighlighted);
		virtual void setPosition(float x, float y) = 0;
		
	};

	//Classic Button with RectangleShape and Text
	class TextButton: 
		public Button {
	private:

		sf::RectangleShape shape;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

	public:
		TextButton(bool stickyAllowed, float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent);
		~TextButton();

		void setPosition(float x, float y);
		void render(sf::RenderTarget* target);
		void update(const sf::Vector2i mousePos);
		
	};

	//Button with Texture and Text
	class TextureButton :
		public Button {
	private:
		sf::Texture idleTexture;
		sf::Texture hoverTexture;
		sf::Texture activeTexture;

		sf::Sprite sprite;
	public:
		TextureButton(bool stickyAllowed, float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned charSize,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			std::string idleDirec, std::string hoverDirec, std::string activeDirec);
		~TextureButton();
		
		void setPosition(float x, float y);
		void render(sf::RenderTarget* target);
		void update(const sf::Vector2i mousePos);
	};
};

