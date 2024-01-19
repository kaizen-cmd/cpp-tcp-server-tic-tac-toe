#pragma once

#include <iostream>
#include <vector>

namespace boardGames
{
    class TicTacToe
    {
    private:
        std::vector<std::vector<char>> m_board;
        int m_x, m_y, m_turns, m_inprogress;
        bool m_player1Turn;

        bool checkFillValid(int x, int y);

        bool checkWinner(int x, int y);

        void setBoard();


    public:
        TicTacToe();

        void updateBoard(int x, int y, char symbol);

        enum Result
        {
            Player1Win,
            Player2Win,
            Tie,
            Continue
        };

        void displayBoard();

        Result play(int x, int y);
    };
}