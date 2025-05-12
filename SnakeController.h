#ifndef SNAKE_SNAKECONTROLLER_H
#define SNAKE_SNAKECONTROLLER_H


#include "SnakeLogic.h"
#include "SnakeView.h"

class SnakeController {

    SnakeLogic &Snake;
    SnakeView &View;
    bool AfterGame;
    bool hasTurned;
    sf::Clock clock;

    void SnakeUpdate();
    void GameActionsDependingOnGameState(sf::Event &event);
    void MoveDependingOnAction(sf::Event &event);
    void ResetClockIfKeysReleased(sf::Event &event);
    void ResetGameIfRIsClicked(sf::Event &event);
    void SaveTop10(const std::string &filename);

public:

    SnakeController(SnakeLogic &Snk, SnakeView &Vw);
    void Play(sf::RenderWindow &win);

};


#endif //SNAKE_SNAKECONTROLLER_H
