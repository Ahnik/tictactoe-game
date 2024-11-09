#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <limits>

namespace Input
{
    void ignoreLine()
    {
        // Function to ignore an entire line of input in the input stream until the newline character is encountered
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    bool clearFailedExtraction()
    {
        // Checks whether extraction has failed in the input stream or not.
        // If yes, returns true and clears the input buffer. If no, then returns false.

        if (!std::cin)
        {
            if (std::cin.eof())
                {
                    std::cerr << "EOF detected : Aborting early\n";
                    std::exit(1);       // Shut down the program
                }

            // Now, let's clear the input stream
            std::cin.clear();           // Put us back in normal operation state
            ignoreLine();
            return true;
        }
        return false;
    }

    bool hasUnextractedInput()
    {
        // Checks whether there is unextracted input left after successful extraction
        // If yes, then returns true, else false.
        return !std::cin.eof() && std::cin.peek() != '\n';
    }

    void inputInt(int& var, int min = INT_MIN , int max = INT_MAX)
    {
        // Function takes integer input between min and max(both inclusive) and conducts various input checks.
        while (true)        // Prompts the user for an input until the user enters a valid input
        {
            std::cin >> var;

            if (clearFailedExtraction())
            {
                std::cerr << "The input is invalid. Please try again.\n";
                continue;
            }

            if (hasUnextractedInput())
            {
                std::cerr << "The input is invalid. Please try again.\n";
                ignoreLine();
                continue;
            } 

            if (var < min || var > max)
            {
                std::cerr << "Please enter an input between " << min << " and " << max << ".\n";
                ignoreLine();
                continue;
            }

            // If we have reached here, there were no issues with the input
            break;
        }
    }
}

#endif