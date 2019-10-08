#include <G2048pp/Game.hpp>
#include <effolkronium/random.hpp>
#include <iostream>
#include <cstdlib>
#include <term.h>
#include <termios.h>
#include <unistd.h>

char getch(void)  
{  
  char ch;  
  struct termios buf;  
  struct termios save;  
  
   tcgetattr(0, &save);  
   buf = save;  
   buf.c_lflag &= ~(ICANON|ECHO);  
   buf.c_cc[VMIN] = 1;  
   buf.c_cc[VTIME] = 0;  
   tcsetattr(0, TCSAFLUSH, &buf);  
   ch = getchar();  
   tcsetattr(0, TCSAFLUSH, &save);  
   return ch;  
}  

void Game::PrintBoard()
{
    system("clear");
    std::cout << "PRESS P TO EXIT\n";
    std::cout << "-------------------------------------\n";
    for(size_t y_ = 0; y_ < m_rowSize; ++y_)
    {
        for(size_t x_ = 0; x_ < m_colSize; ++x_)
        {
            Block* curBlock = board.GetBlock(y_, x_);
            if(curBlock == nullptr) printf("   . ");
            else printf("%4d ", curBlock->GetNum());
        }
        std::cout << std::endl;
    }
    std::cout << "-------------------------------------" << std::endl;
}

void Game::PlayGame()
{
    std::cout << "WELCOME TO 2048pp" << std::endl;
    std::cout << "PRESS ANY KEY" << std::endl;
    getch();

    board.AddBlock();
    Game::PrintBoard();
    while(true)
    {
        char inp = getch();
        if(inp == 'q') break;

        BlockState state;
        if(inp == 'w') state = BlockState::UP;
        else if(inp == 's') state = BlockState::DOWN;
        else if(inp == 'a') state = BlockState::LEFT;
        else if(inp == 'd') state = BlockState::RIGHT;
        else state = BlockState::NONE;

        if(state == BlockState::NONE) continue;

        board.SetState(state);
        board.UpdateBoard();
        score = board.GetTotalScore();

        if(!board.AddBlock()) break;
        Game::PrintBoard();
    }
}