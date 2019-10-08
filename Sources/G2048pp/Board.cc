#include <G2048pp/Board.hpp>
#include <effolkronium/random.hpp>
#include <vector>
#include <iostream>

Board::Board(size_t rowSize, size_t colSize)
{
    totScore = 0;
    m_rowSize = rowSize;
    m_colSize = colSize;
    m_board.resize(rowSize * colSize, nullptr);
}

Board::~Board()
{
    if(!m_board.empty()) 
    {
        for(auto item:m_board) 
        {
            if(item!=nullptr)
                delete item;
        }
    }
}

bool Board::AddBlock()
{
    using Random = effolkronium::random_static;
    
    bool isEmptyExist = false;
    std::vector<size_t> idxs;
    for(size_t y_ = 0; y_ < m_rowSize; ++y_)
    {
        for(size_t x_ = 0; x_ < m_colSize; ++x_)
        {
            Block* curBlock = GetBlock(y_, x_);
            if(curBlock == nullptr)
            {
                isEmptyExist = true;
                idxs.push_back(y_*m_colSize+x_);
            }
        }
    }
    if(isEmptyExist)
    {
        size_t idx = Random::get(0lu, idxs.size()-1);
        m_board[idxs[idx]] = new Block;
    }
    return isEmptyExist;
}

void Board::SetState(BlockState state)
{
    m_state = state;
}

bool Board::UpdateBoard()
{
    bool isMoved = false;
    
    if(m_state == BlockState::DOWN)
    {
        for(size_t col = 0; col < m_colSize; col++)
        {
            for(size_t row = 0; row < m_rowSize; row++)
            {
                for(size_t iter = m_rowSize-1 ; iter > row; iter--)
                {
                    Block* curBlock = GetBlock(iter-1, col);
                    Block* nextBlock = GetBlock(iter, col);

                    if(curBlock == nullptr) break;
                    if(nextBlock == nullptr)
                    {
                        isMoved = true;
                        SetBlock(iter, col, curBlock);
                        DelBlock(iter-1, col, false);
                    }
                    else if(nextBlock->GetNum() == curBlock->GetNum())
                    {
                        isMoved = true;
                        nextBlock->DoubleNum();
                        DelBlock(iter-1, col, true);
                    }
                    else break;
                }
            }
        }
    }

    return isMoved;
}

int Board::GetTotalScore() const
{
    return totScore;
}

Block* Board::GetBlock(size_t y, size_t x)
{
    return m_board[m_colSize * y + x];
}

void Board::SetBlock(size_t y, size_t x, Block* block)
{
    m_board[m_colSize * y + x] = block;
}

void Board::DelBlock(size_t y, size_t x, bool delPtr)
{
    if(m_board[m_colSize * y + x] != nullptr)
    {
        if(delPtr) delete m_board[m_colSize * y + x];
        m_board[m_colSize * y + x] = nullptr;
    }
}