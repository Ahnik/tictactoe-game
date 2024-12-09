/* This is the main file of the program */
#include "game.h"
#include "input.h"
#include <string>

// This function drives the entire game
void play()
{
    // This variable is just for design printing.
    const std::string aesthetic_line(11, '~');

    // First the functions under the namespace Initiate are run
    Initiate::intro();

    // Input from the player on who will go first
    int turn{Initiate::turn()};

    // The class instance of the class Game is constructed.
    Game game_state{};

    // Printing the grid at the beginning of the game
    std::cout << '\n';
    game_state.display();

    // The game is not end until the player either wins or loses or the game ends up in a draw
    while (!(game_state.isWon() || game_state.isDraw()))
    {
        std::cout << aesthetic_line << '\n';

        if (turn == -1)
        {
            std::cout << "Computer's turn.\n";
            game_state.computer();
        }

        else
        {
            std::cout << "Player's turn.\n";
            game_state.player();
        }

        game_state.display();
        turn *= -1;
    }

    // If we have reached here, the game must have been in a win state or a draw state.
    if (game_state.isWon())
    {
        if (turn == -1)
            std::cout << "Congratulations! You won.\n";
        else
            std::cout << "You lost. Better luck next time.\n";
    }

    else
        std::cout << "Game drawn.\n";
}

// The driver code
int main()
{
    // The player can keep playing the game again and again if they wish to
    while(true)
    {
        play();

        // This variable is to determine whether the player wants to play the game again or not.
        int again{};    

        std::cout << "Would you like to play the game again? (1 = Yes, 0 = No) : ";
        Input::inputInt(again, 0, 1);

        if (again == 0)
            break;
    }

    return 0;
}