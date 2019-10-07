#ifndef G2048PP_BLOCK_HPP
#define G2048PP_BLOCK_HPP

#include <G2048pp/Enums.hpp>
#include <effolkronium/random.hpp>

class Block
{
 public:
    Block(BlockState state);
    int GetNum() const;
    BlockState GetState() const;
    void SetState(BlockState state);
    void operator+=(const Block& rhs);

 private:
    Block();
    BlockState m_state;
    int m_num;
};

#endif