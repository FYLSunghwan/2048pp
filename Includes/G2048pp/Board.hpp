#ifndef G2048PP_BOARD_HPP
#define G2048PP_BOARD_HPP

#include <G2048pp/Block.hpp>
#include <G2048pp/Enums.hpp>
#include <vector>

class Board
{
 public:
    Board(int rowSize, int colSize);
    ~Board();
    bool AddBlock(bool isMoved);
    void SetState(const BlockState state);
    bool MoveBlock(const BlockState state);
    bool UpdateBoard();
    int GetTotalScore() const;
    Block* GetBlock(const size_t y, const size_t x);
    void SetBlock(const size_t y, const size_t x, Block* block);
    void DelBlock(const size_t y, const size_t x, bool delPtr = true);

 private:
    Board();
    int totScore;
    std::vector<Block*> m_board;
    int m_rowSize;
    int m_colSize;
    BlockState m_state;
};

#endif