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
        m_board[idx] = new Block(BlockState::NONE);
    }
    return isEmptyExist;
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

bool Board::UpdateBoard()
{
    bool isTask = false;
    bool isMoved = false;
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
                        isTask = isMoved = true;
                        SetBlock(ny, nx, curBlock);
                        SetBlock(y_, x_, nullptr);
                    }
                    else if(nextBlock->GetNum() == curBlock->GetNum())
                    {
                        isTask = isMoved = true;
                        *nextBlock += *curBlock;
                        std::cout << nextBlock->GetNum() << std::endl;
                        totScore += nextBlock->GetNum();
                        delete m_board[ny*m_colSize + nx];
                        m_board[ny*m_colSize + nx] = nullptr;
                    }
                    else
                    {
                        curBlock->SetState(BlockState::NONE);
                    }
                }
            }
        }
    } while (isTask);
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