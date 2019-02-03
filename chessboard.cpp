//******************************************************************
// Chessboard program
//
// Author:  John Hicks
// Course:  CSC 201 D01B
// Date:    2/04/2019
//
// This program prints a chessboard pattern that is built up from
// basic strings of white and black characters. The square size is variable
// as well as the character used to shade black squares. The user is
// prompted for both those values.
//******************************************************************

#include <iostream>
#include <string>

using namespace std;

void PrintRow(string& row, int times);
int PromptForSideLength();
int NumLinesToPrint(int vertLen);
char PromptForBlackSquareChar();
string BuildRowLine(int squareLength, char black, bool startWithWhite);
string StringOfChars(char c, int num);  // Utility

const int CHESS_BOARD_SIDE_LEN = 8;     // The number of squares on any side of the chess board
const int MAX_SQUARE_SIZE = 100;        // Maximum number of characters allowed in forming the horizontal sides of the chess board's squares

int main ()
{
  // In terms of pixels, we want each square share the same number of pixels on each side; however,
  // text characters are taller than they are wide. We need to the ratio of height to width in the terminal
  // to determine how many characters to output to make each square have about the same (similar enough) side length.
  // I've chosen to let the user choose how many characters to print in the horizontal sides of each square
  // and then calculate how many newlines should be used.
  int sqHorizLen = PromptForSideLength();                           // The number of characters to use in printing the squares' horizontal sides
  int sqVertLen  = NumLinesToPrint(sqHorizLen);                     // The number of lines to use in printing the squares' vertical sides
  char useForBlack = PromptForBlackSquareChar();                    // The character to use for making black squares
  string whiteRow = BuildRowLine(sqHorizLen, useForBlack, true);    // A row beginning with a white square
  string blackRow = BuildRowLine(sqHorizLen, useForBlack, false);   // A row beginning with a black square

  cout << "\n\n\n"; // Add margin between prompt messages and board

  // Print two rows of squares on each pass
  for (int i = 0; i < (CHESS_BOARD_SIDE_LEN / 2); i++) {
      PrintRow(whiteRow, sqVertLen);
      PrintRow(blackRow, sqVertLen);
  }

  return 0;
}

/**
 * Prints rows of console output to represent the chess board
 * Pre: row is a string of repeated characters, alternating every x character
 * Post: the string is printed to console, with newlines, `times` times
 *
 * @param &string row - The string to print
 * @param int times   - How many times to print the string to cout
*/
void PrintRow(string& row, int times) {
    for (int i = 0; i < times; i++) {
        cout << row << endl;
    }
}

int PromptForSideLength() {
    int len = 0;
    cout << "Please type the horizontal side length (1 thru " << MAX_SQUARE_SIZE << ") to use for the \nchess board's squares, then press enter:  ";
    cin >> len;
    while(!cin || (len < 1 || len > MAX_SQUARE_SIZE)) {
        if (!cin) {
            cin.clear();
            cin.ignore(100, '\n');
        }
        cout << "\nThat entry is invalid. Enter a number between 1 and " << MAX_SQUARE_SIZE << ": ";
        cin >> len;
        cout << "\n";
    }
    cout << "Using " << len << " as top and bottom side length.\n";
    cout << endl << endl;
    return len;
}

char PromptForBlackSquareChar() {
    char use = '*';
    cout << "Please enter the character to use when shading the board's black \nsquares, then press enter:  ";
    cin >> use;
    while (!cin) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "\nInvalid entry. Enter a single character: ";
        cin >> use;
    }
    cout << "Using \"" << use << "\" as shading for black squares.\n";
    return use;
}

string BuildRowLine(int squareLength, char black, bool startWithWhite) {
    string rowLine = "";      // The string that will be returned
    string wSq = StringOfChars(' ', squareLength);     // One row's worth of a white chess board square
    string bSq = StringOfChars(black, squareLength);   // One row's worth of a black chess board square
    int i = 1;     // Iterator must start at 1 because the mod operation is run against it to do different output for even/odd iterations
    int loopEnd = CHESS_BOARD_SIDE_LEN + 1; // One more than CHESS_BOARD_SIDE_LEN because iterator starts at 1.
    // Iterator is checked even/odd when determining which strings (squares, b vs w) to add; use this fact to set up which color goes first
    if (startWithWhite) {
        i++;
        loopEnd++;
    }
    // Create a black-white or white-black row by concatenating the basic strings
    while(i < loopEnd) {
        if (i % 2 == 0) {
            rowLine += wSq;
        } else {
            rowLine += bSq;
        }
        i++;
    }
    return rowLine;
}

// Returns a string with a repeating character num times
string StringOfChars(char c, int num) {
    string out = "";
    int i = 0;
    while(i < num) {
        out += c;
        i++;
    }
    return out;
}

// Calculates how many vertical lines to print given the number of horizontal characters
int NumLinesToPrint(int vertLen) {
    // In the original program, ratio of the squares' horizontal-side chars to vertical-side newlines is 8:5. Use that.
    float round = 0.0;
    if (vertLen < 4)  // Below 4 characters on top, the ratio did not look right; adjust accordingly.
        round = 0.5;
    int hori = ((5 * vertLen) / 8.0) + round ; // The ratio stated above, solved for height and rounded by a specified amount.
    return hori;
}
