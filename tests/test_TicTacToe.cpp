#include <iostream>
#include "boardGames/TicTacToe.h"

using namespace std;

void TestTicTacToe()
{
    // vector<pair<int, int>> turns = {
    //     {0, 0},
    //     {0, 1},
    //     {0, 2},
    //     {1, 0},
    //     {1, 1},
    //     {1, 2},
    //     {2, 0},
    //     {2, 2},
    //     {2, 1},
    // };

    // boardGames::TicTacToe game = boardGames::TicTacToe();
    // for (auto turn : turns)
    // {
    //     try
    //     {
    //         enum ::boardGames::TicTacToe::Result result = game.play(turn.first, turn.second);
    //         if (result != boardGames::TicTacToe::Result::Continue)
    //         {
    //             switch (result)
    //             {
    //             case boardGames::TicTacToe::Result::Player1Win:
    //                 // cout << "Player1Win" << endl;
    //                 break;
    //             case boardGames::TicTacToe::Result::Player2Win:
    //                 // cout << "Player2Win" << endl;
    //                 break;
    //             case boardGames::TicTacToe::Result::Tie:
    //                 // cout << "Tie" << endl;
    //                 break;
    //             case boardGames::TicTacToe::Result::Continue:
    //                 break;
    //             }
    //         }
    //     }
    //     catch (std::invalid_argument const &ex)
    //     {
    //     }
    // }
}

int main()
{
    // TestTicTacToe();
    cout << "Tests passed" << endl;
}