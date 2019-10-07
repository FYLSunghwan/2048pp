#ifndef G2048PP_BOARD_HPP
#define G2048PP_BOARD_HPP

#include <G2048pp/Block.hpp>
#include <G2048pp/Enums.hpp>
#include <vector>

class Board
{
 public:
    Board(size_t rowSize, size_t colSize);
    ~Board();
    bool AddBlock();
    void SetState(BlockState state);
    bool UpdateBoard();
    int GetTotalScore() const;
    Block* GetBlock(size_t y, size_t x);
    void SetBlock(size_t y, size_t x, Block* block);

 private:
    Board();
    int totScore;
    std::vector<Block*> m_board;
    size_t m_rowSize;
    size_t m_colSize;
};

#endif