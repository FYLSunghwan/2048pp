#include <G2048pp/Block.hpp>

Block::Block()
{
    using Random = effolkronium::random_static;
    m_num = Random::get(1,2);
}

int Block::GetNum() const
{
    return m_num;
}

void Block::DoubleNum()
{
    m_num *= 2;
}