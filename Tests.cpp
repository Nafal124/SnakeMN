#include <cassert>

#include "Tests.h"
#include "SnakeLogic.h"

void Tests::TurnTestAndGameState() {

    int x = 10;
    int y = 10;

    SnakeLogic Snake({x, y}, DEBUG);
    assert(Snake.GetSnakeHeadPosition().first==x/2 and Snake.GetSnakeHeadPosition().second==0);
    Snake.Turn(STRAIGHT);
    assert(Snake.GetSnakeHeadPosition().first==x/2 and Snake.GetSnakeHeadPosition().second==1);
    Snake.Turn(STRAIGHT);
    assert(Snake.GetSnakeHeadPosition().first==x/2 and Snake.GetSnakeHeadPosition().second==2);
    Snake.Turn(STRAIGHT);
    assert(Snake.GetSnakeHeadPosition().first==x/2 and Snake.GetSnakeHeadPosition().second==3);
    Snake.Turn(STRAIGHT);
    assert(Snake.GetSnakeHeadPosition().first==x/2 and Snake.GetSnakeHeadPosition().second==4);
    Snake.Turn(STRAIGHT);
    assert(Snake.GetSnakeHeadPosition().first==x/2 and Snake.GetSnakeHeadPosition().second==5);
    Snake.Turn(STRAIGHT);
    assert(Snake.GetSnakeHeadPosition().first==x/2 and Snake.GetSnakeHeadPosition().second==6);
    Snake.Turn(STRAIGHT);
    assert(Snake.GetSnakeHeadPosition().first==x/2 and Snake.GetSnakeHeadPosition().second==7);
    Snake.Turn(LEFT);
    assert(Snake.GetSnakeHeadPosition().first==x/2-1 and Snake.GetSnakeHeadPosition().second==7);
    Snake.Turn(RIGHT);
    assert(Snake.GetSnakeHeadPosition().first==x/2-1 and Snake.GetSnakeHeadPosition().second==8);
    Snake.Turn(STRAIGHT);
    assert(Snake.GetSnakeHeadPosition().first==x/2-1 and Snake.GetSnakeHeadPosition().second==9);
    assert(Snake.GetGameState()==RUNNING);
    Snake.Turn(STRAIGHT);
    assert(!Snake.CheckIfSnakeIsInTheBoardOrNotOnItself());
    assert(Snake.GetGameState()==FINISHED_LOSS);

}

Tests::Tests() {

    TurnTestAndGameState();

}
