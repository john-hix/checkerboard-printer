//******************************************************************
// Chessboard program
// This program prints a chessboard pattern that is built up from
// basic strings of white and black characters.
//******************************************************************

#include <iostream>
#include <string>

using namespace std;

void PrintRow(string& row, int times);
int PromptForSideLength();


const string BLACK = "********";  // Define a line of a black square
const string WHITE = "        ";  // Define a line of a white square
const int MAX_SQUARE_SIZE = 100;  // Maximum number of characters allowed for each square's side length

int main ()
{
  string whiteRow;            // A row beginning with a white square
  string blackRow;            // A row beginning with a black square
  int squareSideLength = PromptForSideLength();   // The length to use for each of the chess board's squares







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

int PromptForSideLength() {
    int len = 0;
    cout << "Please enter a side length to use for the chess board's squares, then press enter:";
    cin >> len;
    while(!cin || (len < 1 || len > MAX_SQUARE_SIZE)) {
        if (!cin) {
            cin.clear();
            cin.ignore(100, '\n');
        }
        cout << "\nThat entry is invalid. Please try again by entering a number between 1 and " << MAX_SQUARE_SIZE << ": ";
        cin >> len;
    }
    return len;
}

