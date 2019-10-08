#ifndef G2048PP_GAME_HPP
#define G2048PP_GAME_HPP

#include <G2048pp/Board.hpp>

class Game
{
 public:
    Game() = delete;
    Game(int rowSize, int colSize)
    :board(rowSize, colSize),
     score(0),
     m_rowSize(rowSize),
     m_colSize(colSize) 
    {
       // Do Nothing
    };
    void PrintBoard();
    void PlayGame();

 private:
    Board board;
    int score;
    int m_rowSize;
    int m_colSize;
};

#endif