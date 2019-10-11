#include <G2048pp/Game.hpp>
#include <effolkronium/random.hpp>
#include <iostream>
#include <cstdlib>

#ifdef _WIN32
#include <conio.h>
void Game::ClearScreen()
{
    system("cls");
}

#else
#include <term.h>  
#include <termios.h>  
#include <unistd.h> 

void Game::ClearScreen()
{
    system("clear");
}

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
#endif

void Game::PrintBoard()
{
    system("cls");
    std::cout << "PRESS Q TO EXIT\n";
    std::cout << "-------------------------------------\n";
    for(int y_ = 0; y_ < m_rowSize; ++y_)
    {
        for(int x_ = 0; x_ < m_colSize; ++x_)
        {
            Block* curBlock = board.GetBlock(y_, x_);
            if(curBlock == nullptr) printf("   . ");
            else printf("%4d ", curBlock->GetNum());
        }
        std::cout << std::endl;
    }
    std::cout << "-------------------------------------" << std::endl;
}

char Game::GetKey()
{
    return getch();
}

void Game::MenuScreen()
{
    std::cout << "WELCOME TO 2048pp" << std::endl;
    std::cout << "PRESS ANY KEY" << std::endl;
    Game::GetKey();
}

void Game::PlayGame()
{
    Game::MenuScreen();

    board.AddBlock(true);
    Game::PrintBoard();
    while(true)
    {
        char inp = Game::GetKey();
        if(inp == 'q') break;

        BlockState state;
        if(inp == 'w') state = BlockState::UP;
        else if(inp == 's') state = BlockState::DOWN;
        else if(inp == 'a') state = BlockState::LEFT;
        else if(inp == 'd') state = BlockState::RIGHT;
        else state = BlockState::NONE;

        if(state == BlockState::NONE) continue;

        board.SetState(state);
        bool isMoved = board.UpdateBoard();
        score = board.GetTotalScore();

        bool isFull = !board.AddBlock(isMoved);
        if(isFull) break;
        Game::PrintBoard();
    }
}