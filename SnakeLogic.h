#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <utility>
#include <vector>
#include <string>

enum GameMode {EASY, NORMAL, HARD, DEBUG, EXTREME};
enum GameState {RUNNING, FINISHED_LOSS, FINISHED_WON};
enum TurnDirection {RIGHT, LEFT, STRAIGHT};
enum Course {NORTH, SOUTH, WEST, EAST};

class SnakeLogic {

    std::vector<std::pair<int, int>> snakeCords{};
    float speed{};
    int length{};
    Course setCourse{};
    int appleCounter{};
    std::pair<int, int> appleCords{};

    char board[100][100]{};
    std::pair<int, int> dimensions;

    void ClearBoard();
    void GameStartSet(const GameMode &Mode);

    void SnakeOnTheBoard();

    void PlaceFood();
    [[nodiscard]] bool EatFood() const;
    void TryToGrow();

    void UpdateHead(int newFirstPosition, int newSecondPosition);

public:

    SnakeLogic(std::pair<int, int> BoardDimensions, GameMode Mode);

    [[nodiscard]] GameState GetGameState() const;
    [[nodiscard]] std::pair<int,int> GetSnakeHeadPosition() const;
    [[nodiscard]] bool CheckIfSnakeIsInTheBoardOrNotOnItself() const;
    [[nodiscard]] Course GetCourse() const;
    [[nodiscard]] GameMode GetGameMode() const;
    [[nodiscard]] float GetSpeed() const;
    [[nodiscard]] char GetInfoAboutTheField(int row, int column) const;
    [[nodiscard]] int GetWidth() const;
    [[nodiscard]] int GetHeight() const;
    [[nodiscard]] int GetAppleCount() const;

    void Turn(TurnDirection Direction);

    void Display() const;

};


#endif //SNAKE_SNAKE_H
