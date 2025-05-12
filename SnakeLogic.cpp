#include <iostream>
#include <iomanip>
#include <utility>
#include <cassert>
#include <algorithm>

#include "SnakeLogic.h"

/***************************************************************************
 * Konstruktor zapobiega nadaniu planszy nie dozwolonych wartosci wymiarow *
 * Czysci planszy aby w razie czego nie mialy one nie porzadanych wartosci *
 * Ustawia (pseudo)randomowe kordynaty dla jedzenia                        *
 * Ustawia poziom trudnosci                                                *
 ***************************************************************************/

SnakeLogic::SnakeLogic(std::pair<int, int> BoardDimensions, GameMode Mode) : dimensions(std::move(BoardDimensions)) {

    if (BoardDimensions.first<=1 or BoardDimensions.first>=100 or BoardDimensions.second<=1 or BoardDimensions.second>=100){

        exit(0);
    }

    ClearBoard();
    appleCords={rand()%dimensions.second,rand()%dimensions.first};
    GameStartSet(Mode);

}

void SnakeLogic::GameStartSet(const GameMode &Mode) {

    setCourse = EAST;
    appleCounter = 0;

    snakeCords.emplace_back(dimensions.second / 2, 0);

    length = static_cast<int>(snakeCords.size());
    SnakeOnTheBoard();
    PlaceFood();

    if (Mode == DEBUG) {

        speed = 0;

    }

    if (Mode == EASY) {

        speed = 1;

    }

    if (Mode == NORMAL) {

        speed = 2;

    }

    if (Mode == HARD) {

        speed = 3;

    }

    if (Mode == EXTREME) {

        speed = 4.5;

    }
}

//Funkcja odpowiedzialna za przedstawienie planszy i weza na niej

void SnakeLogic::SnakeOnTheBoard() {

    if (length <= 0) {

        return;
    }

    ClearBoard();

    for (int index = 1; index < static_cast<int>(snakeCords.size() - 1); index++) {

        //Body
        board[snakeCords[index].first][snakeCords[index].second] = 'o';

    }

    //Body end

    if (length > 1) {
        if (snakeCords[snakeCords.size() - 1].first >= 0 and
            snakeCords[snakeCords.size() - 1].first < dimensions.second and
            snakeCords[snakeCords.size() - 1].second >= 0 and
            snakeCords[snakeCords.size() - 1].second < dimensions.first) {

            board[snakeCords[snakeCords.size() - 1].first][snakeCords[snakeCords.size() - 1].second] = 'k';

        }
    }

    if (snakeCords[0].first >= 0 && snakeCords[0].first < dimensions.second && snakeCords[0].second >= 0 &&
        snakeCords[0].second < dimensions.first) {

        //Head
        board[snakeCords[0].first][snakeCords[0].second] = 'G';

    }

    if (GetGameMode() != DEBUG) {

        board[appleCords.first][appleCords.second] = '+';

        if (snakeCords[0].first >= 0 && snakeCords[0].first < dimensions.second && snakeCords[0].second >= 0 &&
            snakeCords[0].second < dimensions.first) {

            board[snakeCords[0].first][snakeCords[0].second] = 'G';
        }
    }

    for (int count = 1; count < length; count++) {
        if (snakeCords[0] == snakeCords[count]) {

            board[snakeCords[0].first][snakeCords[0].second] = 'D';
        }
    }

    if (snakeCords[0].first < 0 or snakeCords[0].first >= dimensions.second or snakeCords[0].second < 0 or
        snakeCords[0].second >= dimensions.first) {
        if (length > 1) {

            board[snakeCords[1].first][snakeCords[1].second] = 'D';
        }
    }
}

Course SnakeLogic::GetCourse() const {

    return setCourse;
}

void SnakeLogic::ClearBoard() {

    for (int row = 0; row < dimensions.second; ++row) {
        for (int column = 0; column < dimensions.first; ++column) {

            board[row][column] = ' ';

        }
    }
}

void SnakeLogic::Display() const {

    std::cout<<"  ";

    for (int column = 0; column < dimensions.first; column++) {

        std::cout << std::setw(3) << column;

    }

    std::cout << std::endl;

    for (int row = 0; row < dimensions.second; row++) {

        std::cout << std::setw(2) << row << " ";

        for (int column = 0; column < dimensions.first; column++) {


            std::cout << "[" << GetInfoAboutTheField(row,column) << "]";

        }

        std::cout << std::endl;

    }

    std::cout<<std::endl;

}

std::pair<int, int> SnakeLogic::GetSnakeHeadPosition() const {

    return std::make_pair(snakeCords[0].first, snakeCords[0].second);
}

GameState SnakeLogic::GetGameState() const {

    if (!CheckIfSnakeIsInTheBoardOrNotOnItself()) {

        return FINISHED_LOSS;
    }

    if (appleCounter == dimensions.first * dimensions.second) {

        return FINISHED_WON;
    }

    return RUNNING;
}

bool SnakeLogic::CheckIfSnakeIsInTheBoardOrNotOnItself() const {

    if (snakeCords[0].first < 0 or snakeCords[0].first >= dimensions.second or snakeCords[0].second < 0 or
        snakeCords[0].second >= dimensions.first) {

        return false;

    }

    for (int count=1;count<length;count++) {
        if (snakeCords[0]==snakeCords[count]) {

            return false;
        }
    }

    return true;

}

//Funkcja odpowiedzialna za skrecanie weza na podstawie kierunku obranego przez glowe

void SnakeLogic::Turn(TurnDirection Direction) {

    if (GetGameState() != RUNNING) {

        return;
    }

    for (int index = static_cast<int>(snakeCords.size()) - 1; index > 0; --index) {

        snakeCords[index] = snakeCords[index - 1];
    }

    switch (GetCourse()) {
        case EAST:
            if (Direction == STRAIGHT) {

                UpdateHead(snakeCords[0].first, ++snakeCords[0].second);
            } else if (Direction == LEFT) {

                UpdateHead(--snakeCords[0].first, snakeCords[0].second);
                setCourse = NORTH;
            } else if (Direction == RIGHT) {

                UpdateHead(++snakeCords[0].first, snakeCords[0].second);
                setCourse = SOUTH;
            }
            break;

        case WEST:
            if (Direction == STRAIGHT) {

                UpdateHead(snakeCords[0].first, --snakeCords[0].second);
            } else if (Direction == LEFT) {

                UpdateHead(++snakeCords[0].first, snakeCords[0].second);
                setCourse = SOUTH;
            } else if (Direction == RIGHT) {

                UpdateHead(--snakeCords[0].first, snakeCords[0].second);
                setCourse = NORTH;
            }
            break;

        case NORTH:
            if (Direction == STRAIGHT) {

                UpdateHead(--snakeCords[0].first, snakeCords[0].second);
            } else if (Direction == LEFT) {

                UpdateHead(snakeCords[0].first, --snakeCords[0].second);
                setCourse = WEST;
            } else if (Direction == RIGHT) {

                UpdateHead(snakeCords[0].first, ++snakeCords[0].second);
                setCourse = EAST;
            }
            break;

        case SOUTH:
            if (Direction == STRAIGHT) {

                UpdateHead(++snakeCords[0].first, snakeCords[0].second);
            } else if (Direction == LEFT) {

                UpdateHead(snakeCords[0].first, ++snakeCords[0].second);
                setCourse = EAST;
            } else if (Direction == RIGHT) {

                UpdateHead(snakeCords[0].first, --snakeCords[0].second);
                setCourse = WEST;
            }
            break;
    }
    TryToGrow();
    SnakeOnTheBoard();
}


void SnakeLogic::UpdateHead(int newFirstPosition, int newSecondPosition) {

    if (length == 1) {

        snakeCords[0].first = newFirstPosition;
        snakeCords[0].second = newSecondPosition;
    }
    else {

        snakeCords[0] = snakeCords[1];
        snakeCords[0].first = newFirstPosition;
        snakeCords[0].second = newSecondPosition;
    }
}

float SnakeLogic::GetSpeed() const {

    return speed;

}

char SnakeLogic::GetInfoAboutTheField(int row, int column) const {

    if (row < 0 or row >= dimensions.second or column < 0 or
        column >= dimensions.first) {

        return '!';

    }

    return board[row][column];

}

//Ustawia jedzenie na planszy

void SnakeLogic::PlaceFood() {

    if (GetGameMode()==DEBUG) {

        return;
    }

    if (GetGameState()!=RUNNING) {

        return;
    }

    int row,column;

    do {

        row = rand() % dimensions.second;
        column = rand() % dimensions.first;

    } while (GetInfoAboutTheField(row, column)!=' ');

    appleCords={row,column};
    board[row][column]='+';

}

//Czy zjedzone?

bool SnakeLogic::EatFood() const {

    if (CheckIfSnakeIsInTheBoardOrNotOnItself() and GetSnakeHeadPosition()==appleCords) {

        return true;
    }

    return false;
}

/**************************************************************************************
 *                                                                                    *
 * Jesli EatFood() to waz rosnie o 1 i zwieksza appleCounter (ilosc punktow)          *
 * Po zjedzeniu dokladany jest nastepny czlon weza ktory dostaje wspolrzedne -1 i -1  *
 * aby po wykonaniu nastepnego ruchu ten czlon pojawil sie za wezem                   *
 *                                                                                    *
 **************************************************************************************/

void SnakeLogic::TryToGrow() {

    if (GetGameMode() == DEBUG) {

        return;
    }

    if (EatFood()) {

        ++appleCounter;
        snakeCords.emplace_back(-1, -1);
        ++length;

        PlaceFood();

    }
}

GameMode SnakeLogic::GetGameMode() const {

    if (GetSpeed()==1) {

        return EASY;
    }

    if (GetSpeed()==2) {

        return NORMAL;
    }

    if (GetSpeed()==3) {

        return HARD;
    }

    if (GetSpeed()==4.5) {

        return EXTREME;
    }

    return DEBUG;
}

int SnakeLogic::GetWidth() const {

    return dimensions.first;
}

int SnakeLogic::GetHeight() const {

    return dimensions.second;
}

int SnakeLogic::GetAppleCount() const {
    return appleCounter;
}
