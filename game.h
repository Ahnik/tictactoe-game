#ifndef GAME_H
#define GAME_H

#include "opponent.h"
#include "input.h"
#include "to_unsigned.h"        // for toUZ()
#include <iostream>
#include <vector>               // for std::vector
#include <algorithm>            // for std::count
#include <string>               // for std::string

using Carray = std::vector<char>;
using Grid = std::vector<Carray>;     // We'll represent the grid using a vector of character vectors


namespace Initiate
{
    // Namespace containing all the functions that will be called before the game starts
    void intro()
    {
        // Function to display the introduction at the starting of every game
        const std::string first_line(30, '~');  // This is the first line that will be printed at the start of each game
        std::cout << first_line << '\n';
        std::cout << "Welcome to a game of TicTacToe.\n";
        std::cout << "X = Player\n";
        std::cout << "O = Computer\n";
        std::cout << "Good luck!\n";
    }

    int turn()
    {
        // Function to take input from the user on whether they will start the game first or the computer will start the game first
        std::cout << "Would you like to go first or second? Answer using 1 or 2 : ";
        int choice{};   // Variable storing the integer representing the choice made by the player

        Input::inputInt(choice, 1, 2);     // The input by the user is stored in the variable choice

        if (choice == 2)            // Choice can either be 1 or -1 so that they can be easily interconverted by multiplying with -1
            choice = -1;

        return choice;
    }

    Grid initializeGrid()
    {
        // Function to initiate an empty grid
     Carray row{' ',' ',' '};
        
        return Grid{row, row, row};
    }
}





class Game
{
public:
    Game()          // The constructor
        : m_grid{Initiate::initializeGrid()}
    {
    }

    // Function prompts the user to enter the row and column number to mark the corresponding the square on the grid
    // This function is called when it is the player's turn
    void player();

    // Function is called to invoke the non-player opponent to mark a square on the grid using the steps given in "opponent.h"
    // This function is called when it the computer's turn
    void computer();        /* TODO */

    // Checks whether the game is won by either the player or the opponent or not
    bool isWon() const;     /* TODO*/

    // Checks whether the game is in a draw state or not
    bool isDraw() const;    /* TODO */

    // Displays the grid
    void display() const;   /* TODO */


private:
    Grid m_grid{};

    void setRow(const Carray& row, int rowNo)
    {
        // Sets an entire row in the grid to a given character array
        m_grid[toUZ(rowNo - 1)] = row;
    }

    void setSquare(char mark, int row, int col)
    {
        // Sets a square in the grid to a given character
        m_grid[toUZ(row - 1)][toUZ(col - 1)] = mark; 
    }

    void setGrid(const Grid& grid)
    {
        // Sets the entire grid to the argument entered 
        m_grid = grid;
    }

    Grid getGrid() const { return m_grid;}
};





// Here are all the public member function definitions
inline void Game::player()
{
    int row{};
    int col{};

    while(true)
    {
        std::cout << "Enter the row : \n";
        Input::inputInt(row, 1, 3);
   
        std::cout << "Enter the column : \n";
        Input::inputInt(col, 1, 3);

        if (getGrid()[toUZ(row - 1)][toUZ(col - 1)] == ' ')
            break;

        std::cout << "That square is already marked. Please try again.\n";
    }

    Game::setSquare('X', row, col);
}

inline void Game::computer()
{
    setGrid(Opponent::opponentMove(getGrid()));
}

inline bool Game::isWon() const
{
    // If any one of the rows consists of all 'X' or all 'O', the game is won
    for  (const auto& row : getGrid())
    {
        if (row == Carray{'O','O','O'} || row == Carray{'X','X','X'})
            return true;
    }

    // If any one of the columns consists of all 'X' or all 'O', the game is won
    for (int col{0}; col <= 2; ++col)
    {
        if (
            (getGrid()[0][toUZ(col)] == getGrid()[1][toUZ(col)]) &&
            (getGrid()[0][toUZ(col)] == getGrid()[2][toUZ(col)]) &&
            (getGrid()[0][toUZ(col)] != ' ')
            )   
            return true;
    }

    // If any of the diagonals consists of all 'X' or all 'O', the game is won
    if (
        (getGrid()[0][0] == getGrid()[1][1]) &&
        (getGrid()[0][0] == getGrid()[2][2]) &&
        (getGrid()[0][0] != ' ')
        )   
        return true;

    if (
        (getGrid()[0][2] == getGrid()[1][1]) && 
        (getGrid()[1][1] == getGrid()[2][0]) &&
        (getGrid()[0][2] != ' ')
        )
        return true;

    // If we have reached here, then the grid doesn't satisfy any of the conditions.
    // Thus, the game is still not won.
    return false;
}



inline bool Game::isDraw() const
{
    // To check the game state to determine whether the game is a draw or not.
    // This function is only called if isWon == false.
    int count{0};   // Variable containing the number of ' ' in the grid

    for (const auto& row : getGrid())
    {
        count += static_cast<int>(std::count(row.begin(), row.end(), ' '));
    }

    return (count == 0);
}


inline void Game::display() const
{
    const std::string line(11, '_');    // The line to be displayed after every row is printed

    int count{0};                       // Variable to keep track of how many rows have been printed

    for (const auto& row : getGrid())
    {
        std::cout << ' ' << row[0] << " | " << row[1] << " | " << row[2] << '\n';
        ++count;

        if (count < 3)
            std::cout << line << '\n';
    }

    std::cout << '\n';
}

#endif