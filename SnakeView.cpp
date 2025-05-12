#include "SnakeView.h"

SnakeView::SnakeView(SnakeLogic &Snk) :Snake(Snk) {

    if (!head.loadFromFile("../look/head.png")) {
        exit(-1);
    }
    if (!body.loadFromFile("../look/body.png")) {
        exit(-1);
    }
    if (!grass.loadFromFile("../look/grass.png")) {
        exit(-1);
    }
    if (!food1.loadFromFile("../look/food1.png")) {
        exit(-1);
    }
    if (!food2.loadFromFile("../look/food2.png")) {
        exit(-1);
    }
    if (!end.loadFromFile("../look/end.png")) {
        exit(-1);
    }
    if (!dead.loadFromFile("../look/dead.png")) {
        exit(-1);
    }

}

void SnakeView::DrawOnWindow(sf::RenderWindow &win) {

    for (int nrow = 0; nrow < Snake.GetHeight(); nrow++) {
        for (int ncol = 0; ncol < Snake.GetWidth(); ncol++) {

            sf::RectangleShape rectangle(sf::Vector2f(static_cast<float>(win.getSize().x) / static_cast<float>(Snake.GetWidth()), static_cast<float>(win.getSize().y) / static_cast<float>(Snake.GetHeight())));
            rectangle.setPosition(static_cast<float>(ncol * win.getSize().x) / static_cast<float>(Snake.GetWidth()),static_cast<float>(nrow * win.getSize().y) / static_cast<float>(Snake.GetHeight()));

            if (Snake.GetInfoAboutTheField(nrow, ncol) == ' ')
                rectangle.setTexture(&grass);

            if (Snake.GetInfoAboutTheField(nrow, ncol) == 'G') {

                rectangle.setTexture(&head);

                if (Snake.GetCourse() == NORTH) {

                    rectangle.rotate(270);
                    rectangle.move(0, +rectangle.getSize().y);

                } else if (Snake.GetCourse() == SOUTH) {

                    rectangle.rotate(90);
                    rectangle.move(rectangle.getSize().x, 0);

                } else if (Snake.GetCourse() == WEST) {

                    rectangle.rotate(180);
                    rectangle.move(+rectangle.getSize().x, +rectangle.getSize().y);
                }
            }

            if (Snake.GetInfoAboutTheField(nrow, ncol) == 'o')
                rectangle.setTexture(&body);

            if (Snake.GetInfoAboutTheField(nrow, ncol) == '+') {

                if (Snake.GetAppleCount() % 2 == 0) {
                    rectangle.setTexture(&food1);
                }
                if (Snake.GetAppleCount() % 2 == 1) {
                    rectangle.setTexture(&food2);
                }
            }

            if (Snake.GetInfoAboutTheField(nrow, ncol) == 'k')
                rectangle.setTexture(&end);

            if (Snake.GetInfoAboutTheField(nrow, ncol) == 'D') {

                rectangle.setTexture(&dead);

                if (Snake.GetCourse() == NORTH) {

                    rectangle.rotate(270);
                    rectangle.move(0, +rectangle.getSize().y);

                } else if (Snake.GetCourse() == SOUTH) {

                    rectangle.rotate(90);
                    rectangle.move(rectangle.getSize().x, 0);

                } else if (Snake.GetCourse() == WEST) {

                    rectangle.rotate(180);
                    rectangle.move(+rectangle.getSize().x, +rectangle.getSize().y);
                }
            }

            else
                rectangle.setFillColor(sf::Color::White);

            win.draw(rectangle);

        }
    }
}