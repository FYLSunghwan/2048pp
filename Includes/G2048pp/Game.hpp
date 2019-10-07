#ifndef G2048PP_GAME_HPP
#define G2048PP_GAME_HPP

#include <G2048pp/Board.hpp>

class Game
{
 public:
    Game() = delete;
    Game(size_t rowSize, size_t colSize);
    void PrintBoard();
    void PlayGame();

 private:
    Board board;
    int score;
};

#endif