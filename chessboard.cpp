//******************************************************************
// Chessboard program
// This program prints a chessboard pattern that is built up from
// basic strings of white and black characters.
//******************************************************************

#include <iostream>
#include <string>

using namespace std;

void PrintRow(string& row, int times);


const string BLACK = "********";  // Define a line of a black square
const string WHITE = "        ";  // Define a line of a white square

int main ()
{
  string whiteRow;            // A row beginning with a white square
  string blackRow;            // A row beginning with a black square

  // Create a white-black row by concatenating the basic strings
  whiteRow = WHITE + BLACK + WHITE + BLACK +
             WHITE + BLACK + WHITE + BLACK;

  // Create a black-white row by concatenating the basic strings
  blackRow = BLACK + WHITE + BLACK + WHITE +
             BLACK + WHITE + BLACK + WHITE;

  for (int i = 0; i < 4; i++) {
      // Print five white-black rows
      PrintRow(whiteRow, 5);
      // Print five black-white rows
      PrintRow(blackRow, 5);
  }

  return 0;
}

/**
 * Prints X rows of console output to represent the chess board
 * Pre: row is a string of repeated characters, alternating every x character
 * Post: the string is printed to console, with newlines, `times` times
 *
 * @param &string row - The string to print
 * @param int times   - How many times to print the string to cout
*/
void PrintRow(string& row, int times) {
    for (int i = 0; i < 5; i++) {
        cout << row << endl;
    }
}

