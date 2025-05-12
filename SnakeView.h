#ifndef SNAKE_SNAKEVIEW_H
#define SNAKE_SNAKEVIEW_H

#include <SFML/Graphics.hpp>

#include "SnakeLogic.h"

class SnakeView {

    SnakeLogic &Snake;

    sf::Texture head;
    sf::Texture body;
    sf::Texture grass;
    sf::Texture food1;
    sf::Texture food2;
    sf::Texture end;
    sf::Texture dead;

public:

    explicit SnakeView(SnakeLogic &Snk);
    void DrawOnWindow(sf::RenderWindow &win);

};


#endif //SNAKE_SNAKEVIEW_H
