#include "FULLGAME.h"
#include "SnakeController.h"

//Ruch weza w zaleznosci od tego gdzie kliknieto mysza

void FULLGAME::MouseMoveReact(sf::RenderWindow &win, sf::Event &event) {

    if (event.mouseMove.y >= 0 and event.mouseMove.y < static_cast<signed int>(win.getSize().y / 4)) {

        UpdateTextures(GameMode::EASY);

    } else if (event.mouseMove.y >= static_cast<signed int>(win.getSize().y / 4) and
               event.mouseMove.y < static_cast<signed int>(win.getSize().y / 2)) {

        UpdateTextures(GameMode::NORMAL);

    } else if (event.mouseMove.y >= static_cast<signed int>(2 * win.getSize().y / 4) and
               event.mouseMove.y < static_cast<signed int>(3 * win.getSize().y / 4)) {

        UpdateTextures(GameMode::HARD);

    } else if (event.mouseMove.y >= static_cast<signed int>(3 * win.getSize().y / 4) and
               event.mouseMove.y <= static_cast<signed int>(win.getSize().y)) {

        UpdateTextures(GameMode::EXTREME);

    }
}

//Wyswietlanie menu i interakcja

GameMode FULLGAME::Menu(sf::RenderWindow &win) {

    while (win.isOpen()) {

        SetTexturesPosition(win);
        Choice_EASY.setTexture(&EASY);
        Choice_NORMAL.setTexture(&NORMAL);
        Choice_HARD.setTexture(&HARD);
        Choice_EXTREME.setTexture(&EXTREME);

        sf::Event event{};

        while (win.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {

                win.close();
                exit(10);

            }

            if (event.type == sf::Event::Resized) {

                sf::FloatRect visibleArea(0, 0, static_cast<float>(event.size.width),
                                          static_cast<float>(event.size.height));
                win.setView(sf::View(visibleArea));

            }

            if (SetMode(win, event)) {

                return ModeType;
            }

            if (event.type == sf::Event::MouseMoved) {

                MouseMoveReact(win, event);
            }
        }

        win.clear();
        win.draw(Choice_EASY);
        win.draw(Choice_NORMAL);
        win.draw(Choice_HARD);
        win.draw(Choice_EXTREME);
        win.display();
    }
    return ModeType;
}

// Obsluga calej aplikacji, menu i gra.

void FULLGAME::RunGame(int X, int Y) {

    sf::RenderWindow window(sf::VideoMode(900, 900), "Snake");

    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(30);

    sf::Image logo;

    if (!logo.loadFromFile("../look/head.png")) {

        exit(-1);
    }

    window.setIcon(logo.getSize().x, logo.getSize().y, logo.getPixelsPtr());

    ModeType = Menu(window);
    SnakeLogic Snake({X, Y}, ModeType);
    SnakeView View(Snake);
    SnakeController Game(Snake, View);
    Game.Play(window);

}

FULLGAME::FULLGAME() {

    ModeType=DEBUG;

    if (!EASY.loadFromFile("../look/easy.png")) {
        exit(-1);
    }
    if (!NORMAL.loadFromFile("../look/normal.png")) {
        exit(-1);
    }
    if (!HARD.loadFromFile("../look/hard.png")) {
        exit(-1);
    }
    if (!EXTREME.loadFromFile("../look/extreme.png")) {
        exit(-1);
    }
    if (!EASY_CLICKED.loadFromFile("../look/easy_clicked.png")) {
        exit(-1);
    }
    if (!NORMAL_CLICKED.loadFromFile("../look/normal_clicked.png")) {
        exit(-1);
    }
    if (!HARD_CLICKED.loadFromFile("../look/hard_clicked.png")) {
        exit(-1);
    }
    if (!EXTREME_CLICKED.loadFromFile("../look/extreme_clicked.png")) {
        exit(-1);
    }
}

void FULLGAME::SetTexturesPosition(sf::RenderWindow &win) {

    Choice_EASY.setSize(
            sf::Vector2f(static_cast<float>(win.getSize().x), static_cast<float>(win.getSize().y) / 4));
    Choice_EASY.setPosition(0, 0);

    Choice_NORMAL.setSize(
            sf::Vector2f(static_cast<float>(win.getSize().x), static_cast<float>(win.getSize().y) / 4));
    Choice_NORMAL.setPosition(0, static_cast<float>(win.getSize().y) / 4);

    Choice_HARD.setSize(
            sf::Vector2f(static_cast<float>(win.getSize().x), static_cast<float>(win.getSize().y) / 4));
    Choice_HARD.setPosition(0, static_cast<float>(win.getSize().y) / 2);

    Choice_EXTREME.setSize(
            sf::Vector2f(static_cast<float>(win.getSize().x), static_cast<float>(win.getSize().y) / 4));
    Choice_EXTREME.setPosition(0, static_cast<float>(3 * win.getSize().y) / 4);

}

void FULLGAME::UpdateTextures(GameMode gameMode) {

    Choice_EASY.setTexture(&EASY);
    Choice_NORMAL.setTexture(&NORMAL);
    Choice_HARD.setTexture(&HARD);
    Choice_EXTREME.setTexture(&EXTREME);

    if (gameMode==GameMode::EASY) {

        Choice_EASY.setTexture(&EASY_CLICKED);
    }

    if (gameMode==GameMode::NORMAL) {

        Choice_NORMAL.setTexture(&NORMAL_CLICKED);
    }

    if (gameMode==GameMode::HARD) {

        Choice_HARD.setTexture(&HARD_CLICKED);
    }

    if (gameMode==GameMode::EXTREME) {

        Choice_EXTREME.setTexture(&EXTREME_CLICKED);
    }
}

bool FULLGAME::SetMode(sf::RenderWindow &win, sf::Event &event) {

    if (event.type == sf::Event::MouseButtonPressed) {

        if (event.mouseButton.y >= 0 and event.mouseButton.y < static_cast<signed int>(win.getSize().y / 4)) {

            ModeType = GameMode::EASY;

            return true;

        } else if (event.mouseButton.y >= static_cast<signed int>(win.getSize().y / 4) and
                   event.mouseButton.y < static_cast<signed int>(win.getSize().y / 2)) {

            ModeType = GameMode::NORMAL;

            return true;

        } else if (event.mouseButton.y >= static_cast<signed int>(2 * win.getSize().y / 4) and
                   event.mouseButton.y < static_cast<signed int>(3 * win.getSize().y / 4)) {

            ModeType = GameMode::HARD;

            return true;

        } else if (event.mouseButton.y >= static_cast<signed int>(3 * win.getSize().y / 4) and
                   event.mouseButton.y <= static_cast<signed int>(win.getSize().y)) {

            ModeType = GameMode::EXTREME;

            return true;

        }
    }

    if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::BackSpace) {

        ModeType = GameMode::DEBUG;

        return true;

    }

    return false;
}
