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

    float tileSide = 40.f;

    for (int nrow = 0; nrow < Snake.GetHeight(); nrow++) {
        for (int ncol = 0; ncol < Snake.GetWidth(); ncol++) {

            sf::RectangleShape rectangle(sf::Vector2f(tileSide, tileSide));
            rectangle.setPosition(ncol*tileSide, nrow*tileSide);

            rectangle.setOrigin(tileSide/2.f, tileSide/2.f);
            rectangle.move(tileSide/2.f, tileSide/2.f);

            char info=Snake.GetInfoAboutTheField(nrow, ncol);

            if (info == ' ')
                rectangle.setTexture(&grass);

            if (info == 'o')
                rectangle.setTexture(&body);

            if (info == '+') {

                rectangle.setTexture(Snake.GetAppleCount()%2==0 ? &food1 : &food2);
            }

            if (info == 'k')
                rectangle.setTexture(&end);


            if (info == 'G' || info == 'D') {

                rectangle.setTexture(info=='G' ? &head : &dead);

                if (Snake.GetCourse() == NORTH) {

                    rectangle.setRotation(270);

                } 
                else if (Snake.GetCourse() == SOUTH) {

                    rectangle.setRotation(90);

                } 
                else if (Snake.GetCourse() == WEST) {

                    rectangle.setRotation(180);
                }
                else if (Snake.GetCourse() == EAST) {

                    rectangle.setRotation(0);

                }
            }

            else rectangle.setFillColor(sf::Color::White);

            win.draw(rectangle);

        }
    }
}