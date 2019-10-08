#ifndef G2048PP_BLOCK_HPP
#define G2048PP_BLOCK_HPP

#include <G2048pp/Enums.hpp>
#include <effolkronium/random.hpp>

class Block
{
 public:
    Block();
    int GetNum() const;
    void DoubleNum();
 private:
    int m_num;
};

#endif