    #pragma
    #ifndef ANIMATIONCOMPONENT_H
    #define ANIMATIONCOMPONENT_H

    #include <SFML/Graphics.hpp>
    #include <map>
    #include <string>

    class AnimationComponent {
    public:
    
        AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
        virtual ~AnimationComponent();

    
        struct Animation {
            sf::Sprite& sprite;
            sf::Texture& textureSheet;
            float animationTimer;
            float timer;
            int width;
            int height;
            std::vector<sf::IntRect> frames;
            int currentFrame;

        
            Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, float animation_timer,
                int startX, int startY, int framesX, int framesY, int width, int height);

       
            void play(const float& dt);
            void reset();
        };

    
        void addAnimation(const std::string& key, float animation_timer, int startX, int startY, int framesX, int framesY, int width, int height);
        void play(const std::string& key, const float& dt);

    private:
        sf::Sprite& sprite;
        sf::Texture& textureSheet;
        std::map<std::string, Animation*> animations;
    };

    #endif
