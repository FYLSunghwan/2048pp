#include <G2048pp/Board.hpp>
#include <effolkronium/random.hpp>
#include <vector>
#include <iostream>

Board::Board(int rowSize, int colSize)
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

bool Board::AddBlock(bool isMoved)
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
    if(isEmptyExist && isMoved)
    {
        size_t idx = Random::get<std::size_t>(0, idxs.size()-1);
        m_board[idxs[idx]] = new Block;
    }
    return isEmptyExist;
}

void Board::SetState(const BlockState state)
{
    m_state = state;
}

bool Board::MoveBlock(const BlockState state)
{
    bool isMoved = false;
    if(m_state == BlockState::DOWN)
    {
        for(int col = 0; col < m_colSize; col++)
        {
            for(int row = m_rowSize-2; row >= 0; row--)
            {
                for(int iter = row ; iter < m_rowSize-1; iter++)
                {
                    Block* curBlock = GetBlock(iter, col);
                    Block* nextBlock = GetBlock(iter+1, col);

                    if(curBlock == nullptr) break;
                    if(nextBlock == nullptr)
                    {
                        isMoved = true;
                        SetBlock(iter+1, col, curBlock);
                        DelBlock(iter, col, false);
                    }
                    else if(nextBlock->GetNum() == curBlock->GetNum())
                    {
                        isMoved = true;
                        nextBlock->DoubleNum();
                        DelBlock(iter, col, true);
                    }
                    else break;
                }
            }
        }
    }

    if(m_state == BlockState::UP)
    {
        for(int col = 0; col < m_colSize; col++)
        {
            for(int row = 1; row < m_rowSize; row++)
            {
                for(int iter = row ; iter > 0; iter--)
                {
                    Block* curBlock = GetBlock(iter, col);
                    Block* nextBlock = GetBlock(iter-1, col);

                    if(curBlock == nullptr) break;
                    if(nextBlock == nullptr)
                    {
                        isMoved = true;
                        SetBlock(iter-1, col, curBlock);
                        DelBlock(iter, col, false);
                    }
                    else if(nextBlock->GetNum() == curBlock->GetNum())
                    {
                        isMoved = true;
                        nextBlock->DoubleNum();
                        DelBlock(iter, col, true);
                    }
                    else break;
                }
            }
        }
    }

    if(m_state == BlockState::RIGHT)
    {
        for(int row = 0; row < m_rowSize; row++)
        {
            for(int col = m_colSize-2; col >= 0; col--)
            {
                for(int iter = col ; iter < m_colSize-1; iter++)
                {
                    Block* curBlock = GetBlock(row, iter);
                    Block* nextBlock = GetBlock(row, iter+1);

                    if(curBlock == nullptr) break;
                    if(nextBlock == nullptr)
                    {
                        isMoved = true;
                        SetBlock(row, iter+1, curBlock);
                        DelBlock(row, iter, false);
                    }
                    else if(nextBlock->GetNum() == curBlock->GetNum())
                    {
                        isMoved = true;
                        nextBlock->DoubleNum();
                        DelBlock(row, iter, true);
                    }
                    else break;
                }
            }
        }
    }

    if(m_state == BlockState::LEFT)
    {
        for(int row = 0; row < m_rowSize; row++)
        {
            for(int col = 1; col < m_colSize; col++)
            {
                for(int iter = col ; iter > 0; iter--)
                {
                    Block* curBlock = GetBlock(row, iter);
                    Block* nextBlock = GetBlock(row, iter-1);

                    if(curBlock == nullptr) break;
                    if(nextBlock == nullptr)
                    {
                        isMoved = true;
                        SetBlock(row, iter-1, curBlock);
                        DelBlock(row, iter, false);
                    }
                    else if(nextBlock->GetNum() == curBlock->GetNum())
                    {
                        isMoved = true;
                        nextBlock->DoubleNum();
                        DelBlock(row, iter, true);
                    }
                    else break;
                }
            }
        }
    }
    return isMoved;
}

bool Board::UpdateBoard()
{
    bool newState = MoveBlock(m_state);
    if(!newState) m_state = BlockState::NONE;
    return newState;
}

int Board::GetTotalScore() const
{
    return totScore;
}

Block* Board::GetBlock(const size_t y, const size_t x)
{
    return m_board[m_colSize * y + x];
}

void Board::SetBlock(const size_t y, const size_t x, Block* block)
{
    m_board[m_colSize * y + x] = block;
}

void Board::DelBlock(const size_t y, const size_t x, bool delPtr)
{
    if(m_board[m_colSize * y + x] != nullptr)
    {
        if(delPtr) delete m_board[m_colSize * y + x];
        m_board[m_colSize * y + x] = nullptr;
    }
}