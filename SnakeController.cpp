#include <iostream>
#include <fstream>
#include <sstream>
#include "SnakeController.h"

SnakeController::SnakeController(SnakeLogic &Snk, SnakeView &Vw) : Snake(Snk), View(Vw) {

    AfterGame=false;
    hasTurned = false;

}

void SnakeController::SnakeUpdate() {

    Snake.Turn(STRAIGHT);
}

//Zaleznie od przycisnietego przycisku i kursu glowy weza waz skreca w odpowiednia strone

void SnakeController::MoveDependingOnAction(sf::Event &event) {

    if (event.key.code == sf::Keyboard::Right or event.key.code == sf::Keyboard::D) {

        if (Snake.GetCourse() == NORTH and !hasTurned) {

            Snake.Turn(RIGHT);
            hasTurned = true;
        }

        if (Snake.GetCourse() == SOUTH and !hasTurned) {

            Snake.Turn(LEFT);
            hasTurned = true;
        }

        if (Snake.GetCourse() == EAST and !hasTurned) {

            Snake.Turn(STRAIGHT);
            hasTurned = true;
        }

        if (Snake.GetCourse() == WEST and !hasTurned) {}

    }

    if (event.key.code == sf::Keyboard::Left or event.key.code == sf::Keyboard::A) {

        if (Snake.GetCourse() == NORTH and !hasTurned) {

            Snake.Turn(LEFT);
            hasTurned = true;
        }

        if (Snake.GetCourse() == SOUTH and !hasTurned) {

            Snake.Turn(RIGHT);
            hasTurned = true;
        }

        if (Snake.GetCourse() == EAST and !hasTurned) {}

        if (Snake.GetCourse() == WEST and !hasTurned) {

            Snake.Turn(STRAIGHT);
            hasTurned = true;
        }
    }

    if (event.key.code == sf::Keyboard::Down or event.key.code == sf::Keyboard::S) {

        if (Snake.GetCourse() == NORTH and !hasTurned) {}

        if (Snake.GetCourse() == SOUTH and !hasTurned) {

            Snake.Turn(STRAIGHT);
            hasTurned = true;
        }

        if (Snake.GetCourse() == EAST and !hasTurned) {

            Snake.Turn(RIGHT);
            hasTurned = true;
        }

        if (Snake.GetCourse() == WEST and !hasTurned) {

            Snake.Turn(LEFT);
            hasTurned = true;
        }
    }

    if (event.key.code == sf::Keyboard::Up or event.key.code == sf::Keyboard::W) {

        if (Snake.GetCourse() == NORTH and !hasTurned) {

            Snake.Turn(STRAIGHT);
            hasTurned = true;
        }

        if (Snake.GetCourse() == SOUTH and !hasTurned) {}

        if (Snake.GetCourse() == EAST and !hasTurned) {

            Snake.Turn(LEFT);
            hasTurned = true;
        }

        if (Snake.GetCourse() == WEST and !hasTurned) {

            Snake.Turn(RIGHT);
            hasTurned = true;
        }
    }
}

void SnakeController::ResetClockIfKeysReleased(sf::Event &event) {

    if (event.key.code == sf::Keyboard::Up or event.key.code == sf::Keyboard::Down or
         event.key.code == sf::Keyboard::Left or event.key.code == sf::Keyboard::Right or
         event.key.code == sf::Keyboard::W or event.key.code == sf::Keyboard::S or
         event.key.code == sf::Keyboard::A or event.key.code == sf::Keyboard::D) {

        hasTurned = false;
        clock.restart();
    }
}

void SnakeController::ResetGameIfRIsClicked(sf::Event &event) {

    if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::R) {

        SnakeLogic SnakeNew({Snake.GetWidth(), Snake.GetHeight()}, Snake.GetGameMode());
        Snake = SnakeNew;
        AfterGame=false;
    }
}

void SnakeController::GameActionsDependingOnGameState(sf::Event &event){

    if (Snake.GetGameState() == RUNNING) {

        if (event.type == sf::Event::KeyPressed) {

            MoveDependingOnAction(event);
        }

        if (event.type == sf::Event::KeyReleased) {

            ResetClockIfKeysReleased(event);
        }
    }

    if (Snake.GetGameState() == FINISHED_WON) {

        if (!AfterGame) {

            std::cout << "You Won! Click R to restart Game!" << std::endl;
            SaveTop10("../top10/top10.txt");
            AfterGame = true;
        }

        ResetGameIfRIsClicked(event);
    }

    if (Snake.GetGameState() == FINISHED_LOSS) {

        if (!AfterGame) {

            std::cout << "You Lost! Click R to restart Game!" << std::endl;
            SaveTop10("../top10/top10.txt");
            AfterGame = true;
        }

        ResetGameIfRIsClicked(event);
    }
}

//Odpowiada za przebieg gry

void SnakeController::Play(sf::RenderWindow &window) {

    sf::View view(sf::FloatRect(0, 0, Snake.GetWidth() * 40.f, Snake.GetHeight() * 40.f));
    window.setView(view);

    while (window.isOpen()) {

        if (Snake.GetGameMode() != DEBUG and
            clock.getElapsedTime() >= sf::milliseconds(static_cast<int>(1250 / Snake.GetSpeed()))) {

            SnakeUpdate();

            clock.restart();
        }

        sf::Event event{};

        while (window.pollEvent(event)) {

            GameActionsDependingOnGameState(event);

            if (event.type == sf::Event::Closed) {

                window.close();
                exit(10);
            }

            if (event.type == sf::Event::Resized) {
                view.setSize(Snake.GetWidth() * 40.f, Snake.GetHeight() * 40.f);
                window.setView(view);
            }
        }

        window.clear();
        View.DrawOnWindow(window);
        window.display();
    }
}

void SnakeController::SaveTop10(const std::string &filename) {

    std::fstream file(filename, std::ios::in);
    std::vector<int> Scores;

    if (!file.is_open()) {
        exit(100);
    }

    int score;
    while (file >> score) {
        Scores.push_back(score);
    }
    file.close();

    score = Snake.GetAppleCount();
    Scores.push_back(score);

    std::sort(Scores.begin(), Scores.end(), std::greater<int>());

    auto last = std::unique(Scores.begin(), Scores.end());
    Scores.erase(last, Scores.end());

    while (Scores.size() > 10) {

        Scores.erase(Scores.end()-1);
    }

    std::ofstream outFile(filename, std::ios::out | std::ios::trunc);

    if (!outFile.is_open()) {

        exit(100);
    }

    for (int Score : Scores) {

        outFile << Score << '\n';
    }

    outFile.close();
}


