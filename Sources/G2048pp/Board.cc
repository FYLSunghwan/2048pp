#include <G2048pp/Board.hpp>

Board::Board(size_t rowSize, size_t colSize)
{
    totScore = 0;
    m_rowSize = rowSize;
    m_colSize = colSize;
    m_board.resize(rowSize * colSize, nullptr);
}

void Board::SetState(BlockState state)
{
    for(size_t y_ = 0; y_ < m_rowSize; ++y_)
    {
        for(size_t x_ = 0; x_ < m_colSize; ++x_)
        {
            Block* curBlock = GetBlock(y_, x_);
            if(curBlock == nullptr)
            {
                continue;
            }
            curBlock->SetState(state);
        }
    }
}

void Board::UpdateBoard()
{
    bool isTask = false;
    int dy[5] = {0, -1, 1, 0, 0};
    int dx[5] = {0, 0, 0, -1, 1};
    do
    {
        isTask = false;
        for(size_t y_ = 0; y_ < m_rowSize; ++y_)
        {
            for(size_t x_ = 0; x_ < m_colSize; ++x_)
            {
                Block* curBlock = GetBlock(y_, x_);
                if(curBlock == nullptr)
                {
                    continue;
                }
                BlockState curState = curBlock->GetState();
                if(curState != BlockState::NONE)
                {
                    int ny = y_ + dy[(int)curState];
                    int nx = x_ + dx[(int)curState];

                    bool condition = ny >= 0
                                  && ny < m_rowSize
                                  && nx >= 0
                                  && nx < m_colSize;
                    if(!condition)
                    {
                        curBlock->SetState(BlockState::NONE);
                        continue;
                    }

                    Block* nextBlock = GetBlock(ny, nx);
                    if(nextBlock == nullptr)
                    {
                        isTask = true;
                        nextBlock = curBlock;
                    }
                    else if(nextBlock->GetNum == curBlock->GetNum)
                    {
                        isTask = true;
                        *nextBlock = *nextBlock + *curBlock;
                        totScore += nextBlock->GetNum;
                        delete curBlock;
                    }
                    else
                    {
                        curBlock->SetState(BlockState::NONE);
                        continue;   
                    }
                    
                }
            }
        }
    } while (isTask);
}

int Board::GetTotalScore() const
{
    return totScore;
}

Block* Board::GetBlock(size_t y, size_t x)
{
    return m_board[m_colSize * y + x];
}