#include <G2048pp/Block.hpp>

Block::Block(BlockState state)
{
    using Random = effolkronium::random_static;

    m_state = state;
    m_num = Random::get(1,2);
}

int Block::GetNum() const
{
    return m_num;
}

BlockState Block::GetState() const 
{
    return m_state;
}

void Block::SetState(BlockState state)
{
    m_state = state;
}

Block& Block::operator+(const Block& rhs)
{
    m_num += rhs.GetNum();
    m_state = rhs.GetState();
}