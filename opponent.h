#ifndef OPPONENT_H
#define OPPONENT_H

#include "to_unsigned.h"    // for toUZ()
#include "Random.h"         // for Random::Range()
#include <vector>           // for std::vector
#include <algorithm>        // for std::count

using Carray = std::vector<char>;
using Grid = std::vector<Carray>;

namespace Helper
{
    /* Namespace containing all the helper functions to be used in the main function in the Opponent namespace*/

    // Function to return the transpose of a grid
    Grid transpose(const Grid& grid)
    {
        Carray row{' ', ' ', ' '};
        Grid new_grid{row, row, row};

        for (int row{0}; row <= 2; ++row)
        {
            for (int col{0}; col <= 2; ++col)
            {
                new_grid[toUZ(col)][toUZ(row)] = grid[toUZ(row)][toUZ(col)];
            }
        }

        return new_grid;
    }

    // This function returns the number of occurrences of a character 'c' in a character array
    int count(char c, const Carray& arr)
    {
        return static_cast<int>(std::count(arr.begin(),arr.end(), c));
    }

    // This function will replace all occurrences of an element in a vector 
    void replace(Carray& arr, char to_replace, char replace_with)
    {
        for (auto& element : arr)
        {
            if (element == to_replace)
                element = replace_with;
        }
    }
}



namespace Opponent
{

    // The following function will play the most optimal move for the opponent
    Grid opponentMove(Grid grid)
    {
        /*
        The algorithm followed by the opponent goes like this :
        1. First the opponent looks if there is any winning move or not.
           i.e. if there is any row, column or diagonal with two 'O' and one ' ' and then marks the empty square to 'O'.
        2. Then it looks if the player has any winning move that can be blocked.
           i.e. if there is any row, column or diagonal with two 'X' and one ' ' and then marks the empty square to 'O'.
        3. Now, the opponent looks for any row or column of the form {'O',' ',' '} or {' ',' ','O'} and if found, it converts them
           to {'O',' ','O'}.
        4. If none of the above satisfies, the opponent marks any vacant corner square.
        5. If even that is not possible, the opponent marks any random vacant square.
        */

        // If the computer goes second in the game, in the first turn, the computer will mark the centre square unless it is already
        // marked.
        if (
            (Helper::count('X', grid[0]) + Helper::count('X', grid[1]) + Helper::count('X', grid[2]) == 1) &&
            (grid[1][1] == ' ')
        )
        {
            grid[1][1] = 'O';
            return grid;
        }      

        // We will check if the opponent has any winning move.
        // We will check the rows
        for (auto& row : grid)
        {
            // If a row contains 2 'O' and one vacant space
            if (Helper::count('O',row) == 2 && Helper::count(' ',row) == 1)
            {
                row = {'O','O','O'};
                return grid;
            }
        }

        // Next, we will check the columns

        // Here is the transpose of our grid

        Grid transposedGrid{Helper::transpose(grid)};
        for (auto& row : transposedGrid)
        {
            // If a column contains 2 'O' and one vacant space
            if (Helper::count('O',row) == 2 && Helper::count(' ',row) == 1)
            {
                row = {'O','O','O'};
                return Helper::transpose(transposedGrid);
            }
        }

        // Next, we will check the diagonals
        // We need to test this part thoroughly before running
        if (
            (grid[0][0] == ' ') && (grid[1][1] == grid[2][2]) && (grid[1][1] == 'O')
            )
        {
            grid[0][0] = 'O';
            return grid;
        }

        if (
            (grid[1][1] == ' ') && (grid[0][0] == grid[2][2]) && (grid[0][0] == 'O')
            )
        {
            grid[1][1] = 'O';
            return grid;
        }

        if (
            (grid[2][2] == ' ') && (grid[0][0] == grid[1][1]) && (grid[0][0] == 'O')
            )
        {
            grid[2][2] = 'O';
            return grid;
        }

        if (
            (grid[0][2] == ' ') && (grid[1][1] == grid[2][0]) && (grid[1][1] == 'O')
            )
        {
            grid[0][2] = 'O';
            return grid;
        }

        if (
            (grid[1][1] == ' ') && (grid[0][2] == grid[2][0]) && (grid[0][2] == 'O')
            )
        {
            grid[1][1] = 'O';
            return grid;
        }

        if (
            (grid[2][0] == ' ') && (grid[1][1] == grid[0][2]) && (grid[1][1] == 'O')
            )
        {
            grid[2][0] = 'O';
            return grid;
        }


        // If we have reached here, that means there are no winning moves.
        // Now, we will check if the player has any winning moves that we can block.
        // We will check if there is any row, column or diagonal with with two 'X' and one vacant space.
        // We will first check the rows if there are two 'X' and one vacant space.
        for (auto& row : grid)
        {
            // If a row contains two 'X' and one vacant space
            if (Helper::count('X',row) == 2 && Helper::count(' ',row) == 1)
            {
                Helper::replace(row, ' ','O');
                return grid;
            }
        }

        // Now, we will check if any column contains two 'X' and one vacant space
        for (auto& row : transposedGrid)
        {
            // If a column contains two 'X' and one vacant space
            if (Helper::count('X',row) == 2 && Helper::count(' ',row) == 1)
            {
                Helper::replace(row, ' ','O');
                return Helper::transpose(transposedGrid);
            }
        }

        // Now, we will check if any diagonal contains two 'X' and one vacant space
        if (
            (grid[0][0] == ' ') && (grid[1][1] == grid[2][2]) && (grid[1][1] == 'X')
            )
        {
            grid[0][0] = 'O';
            return grid;
        }

        if (
            (grid[1][1] == ' ') && (grid[0][0] == grid[2][2]) && (grid[0][0] == 'X')
            )
        {
            grid[1][1] = 'O';
            return grid;
        }

        if (
            (grid[2][2] == ' ') && (grid[0][0] == grid[1][1]) && (grid[0][0] == 'X')
            )
        {
            grid[2][2] = 'O';
            return grid;
        }

        if (
            (grid[0][2] == ' ') && (grid[1][1] == grid[2][0]) && (grid[1][1] == 'X')
            )
        {
            grid[0][2] = 'O';
            return grid;
        }

        if (
            (grid[1][1] == ' ') && (grid[0][2] == grid[2][0]) && (grid[0][2] == 'X')
            )
        {
            grid[1][1] = 'O';
            return grid;
        }

        if (
            (grid[2][0] == ' ') && (grid[1][1] == grid[0][2]) && (grid[1][1] == 'X')
            )
        {
            grid[2][0] = 'O';
            return grid;
        }

        // If we have reached here, there is no winning moves for either the opponent or the player.
        // Now, the opponent will look if there is any row, column or diagonal of form {'O',' ',' '} or {' ',' ','O'}
        // and turn them into {'O',' ','O'}.

        // We'll first check the rows.
        for (auto& row : grid)
        {
            if (row == Carray {'O',' ',' '} || row == Carray {' ',' ','O'})
            {
                row = {'O',' ','O'};
                return grid;
            }
        }

        // Now, we will check the columns.
        for (auto& row : transposedGrid)
        {
            if (row == Carray {'O',' ',' '} || row == Carray {' ',' ','O'})
            {
                row = {'O',' ','O'};
                return Helper::transpose(transposedGrid);
            }
        }

        // Now, we will check the diagonals.
        if (
            (grid[0][0] == 'O' && (grid[1][1] == grid[2][2]) && (grid[1][1] == ' ')) || 
            (grid[2][2] == 'O' && (grid[1][1] == grid[0][0]) && (grid[1][1] == ' '))
            )
        {
            grid[0][0] = 'O';
            grid[2][2] = 'O';
            return grid;
        }

        if (
            (grid[0][2] == 'O' && (grid[1][1] == grid[2][0]) && (grid[1][1] == ' ')) || 
            (grid[2][0] == 'O' && (grid[1][1] == grid[0][2]) && (grid[1][1] == ' '))
            )
        {
            grid[0][2] = 'O';
            grid[2][0] = 'O';
            return grid;
        }


        // If we have reached here, then the opponent will mark any vacant corner square.
        if (grid[0][0] == ' ')
        {
            grid[0][0] = 'O';
            return grid;
        }

        if (grid[2][2] == ' ')
        {
            grid[2][2] = 'O';
            return grid;
        }

        if (grid[0][2] == ' ')
        {
            grid[0][2] = 'O';
            return grid;
        }

        if (grid[2][0] == ' ')
        {
            grid[2][0] = 'O';
            return grid;
        }

        // If the above is still not possible, the opponent will mark any random vacant square.
        while (true)
        {
            int row{Random::Range(0, 2)};
            int col{Random::Range(0, 2)};

            if (grid[toUZ(row)][toUZ(col)] == ' ')
            {
                grid[toUZ(row)][toUZ(col)] = 'O';
                return grid;
            }
        }
    }
}
        
#endif