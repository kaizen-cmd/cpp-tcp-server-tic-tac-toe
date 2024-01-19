#include <iostream>
#include <vector>
#include "boardGames/TicTacToe.h"

boardGames::TicTacToe::TicTacToe() : m_x(-1), m_y(-1), m_player1Turn(true), m_turns(0), m_inprogress(1)
{
    setBoard();
}

bool boardGames::TicTacToe::checkFillValid(int x, int y)
{
    if (m_board[x][y] != '_')
        return false;
    return true;
}

bool boardGames::TicTacToe::checkWinner(int x, int y)
{
    char symbToCheck = m_board[x][y];

    bool r = true, c = true, d1 = true, d2 = true;

    for (int i = 0; i < 3; ++i)
    {
        if (m_board[x][i] != symbToCheck)
        {
            r = false;
        }
        if (m_board[i][y] != symbToCheck)
        {
            c = false;
        }
    }

    int tx = 0, ty = 0;
    while (tx < 3 && ty < 3)
    {
        if (m_board[tx][ty] != symbToCheck)
        {
            d1 = false;
            break;
        }
        tx++;
        ty++;
    }

    tx = 0, ty = 2;
    while (tx >= 0 && ty >= 0)
    {
        if (m_board[tx][ty] != symbToCheck)
        {
            d2 = false;
            break;
        }
        tx++;
        ty--;
    }

    return r || c || d1 || d2;
}

void boardGames::TicTacToe::setBoard()
{
    m_board.resize(3, std::vector<char>(3));
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            m_board[i][j] = '_';
        }
    }
}

boardGames::TicTacToe::Result boardGames::TicTacToe::play(int x, int y)
{
    if (!m_inprogress)
        throw std::invalid_argument("Game has already finished");
    if (checkFillValid(x, y))
    {
        if (m_player1Turn)
            m_board[x][y] = 'X';
        else
            m_board[x][y] = 'O';
        if (checkWinner(x, y))
        {
            m_inprogress = 0;
            if (m_player1Turn)
                return Player1Win;
            return Player2Win;
        }
        if (m_turns >= 8)
        {
            m_inprogress = 1;
            return Tie;
        }
        m_player1Turn = !m_player1Turn;
        m_turns++;
        return Continue;
    }
    else
    {
        throw std::invalid_argument("Already filled");
    }
}

void boardGames::TicTacToe::updateBoard(int x, int y, char symbol)
{
    if (m_board[x][y] == '_')
    {
        m_board[x][y] = symbol;
    }
}

void boardGames::TicTacToe::displayBoard()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            std::cout << m_board[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}
