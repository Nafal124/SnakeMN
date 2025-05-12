#ifndef SNAKE_FULLGAME_H
#define SNAKE_FULLGAME_H

#include <SFML/Graphics.hpp>
#include "SnakeLogic.h"

class FULLGAME {

    sf::Texture EASY;
    sf::Texture NORMAL;
    sf::Texture HARD;
    sf::Texture EXTREME;
    sf::Texture EASY_CLICKED;
    sf::Texture NORMAL_CLICKED;
    sf::Texture HARD_CLICKED;
    sf::Texture EXTREME_CLICKED;

    sf::RectangleShape Choice_EASY;
    sf::RectangleShape Choice_NORMAL;
    sf::RectangleShape Choice_HARD;
    sf::RectangleShape Choice_EXTREME;

    GameMode ModeType;

    GameMode Menu(sf::RenderWindow &win);
    void SetTexturesPosition(sf::RenderWindow &win);
    void UpdateTextures(GameMode gameMode);
    void MouseMoveReact(sf::RenderWindow &win, sf::Event &event);
    bool SetMode(sf::RenderWindow &win, sf::Event &event);

public:

    FULLGAME();
    void RunGame(int X, int Y);

};


#endif //SNAKE_FULLGAME_H
