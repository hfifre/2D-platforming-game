#include "SFML/Graphics.hpp"

void spriteAnimation(
    int const& spriteSheetWidthSize,
    int const& spriteSheetHeightSize,
    int const& unitSize,
    sf::IntRect &rectSourceSprite,
    sf::Sprite &sprite)
{
    if (rectSourceSprite.left == spriteSheetWidthSize-unitSize)
    {
        rectSourceSprite.left = 0;
        if (rectSourceSprite.top == spriteSheetHeightSize-unitSize)
            rectSourceSprite.top = 0;
        else
            rectSourceSprite.top += unitSize;
    }
    else
        rectSourceSprite.left += unitSize;

    sprite.setTextureRect(rectSourceSprite);
}

int main(int argc, char** argv) {
    sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "Demo Game");

    sf::Event event;
    sf::Texture texture;
    texture.loadFromFile("ressources/perso_standing_still.png");

    sf::IntRect rectSourceSprite(0, 0, 240, 240);
    sf::Sprite sprite(texture, rectSourceSprite);
    sf::Clock clock;
    bool alreadyLeft = false;
    bool alreadyRight = false;
    bool alreadyNotMoving = false;

    while (renderWindow.isOpen()) {
        while (renderWindow.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed)
                renderWindow.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if (!alreadyRight)
            {
                rectSourceSprite.left = 0;
                rectSourceSprite.top = 0;
                texture.loadFromFile("ressources/main_character_right.png");
                alreadyRight = true;
                alreadyNotMoving = false;
                alreadyLeft = false;
            }
            if (clock.getElapsedTime().asMilliseconds() > 70.0f)
            {
                spriteAnimation(720, 960, 240, rectSourceSprite, sprite);
                clock.restart();
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if (!alreadyLeft)
            {
                rectSourceSprite.left = 0;
                rectSourceSprite.top = 0;
                texture.loadFromFile("ressources/main_character_left.png");
                alreadyLeft = true;
                alreadyRight = false;
                alreadyNotMoving = false;
            }
            if (clock.getElapsedTime().asMilliseconds() > 70.0f)
            {
                spriteAnimation(720, 960, 240, rectSourceSprite, sprite);
                clock.restart();
            }
        }
        else
        {
            if (!alreadyNotMoving)
            {
                rectSourceSprite.left = 0;
                rectSourceSprite.top = 0;
                texture.loadFromFile("ressources/perso_standing_still.png");
                alreadyNotMoving = true;
                alreadyRight = false;
                alreadyLeft = false;
            }
            if (clock.getElapsedTime().asMilliseconds() > 200.0f)
            {
                spriteAnimation(480, 720, 240, rectSourceSprite, sprite);
                clock.restart();
            }
        }

        renderWindow.clear();
        renderWindow.draw(sprite);
        renderWindow.display();
    }
}