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
//
// NOTE to instructor: comments inside main point out three structural
// improvements made.
//******************************************************************

#include <iostream>
#include <string>

using namespace std;

// Function declarations
void PrintRow(string& row, int times);
int PromptForSquareWidth();
int CalcSquareHeightInLines(int vertLen);
char PromptForBlackSquareChar();
string BuildRowLine(int squareLength, char black, bool startWithWhite);
string StringOfChars(char c, int num);  // Utility

// Symbolic constants
const int CHESS_BOARD_SIDE_LEN = 8;     // The number of squares on any side of the chess board
const int MAX_SQUARE_SIZE = 100;        // Maximum number of characters allowed in forming the horizontal sides of the chess board's squares

int main () {
  int sqWidth = PromptForSquareWidth();                          // The number of characters to use in printing the squares' horizontal sides, i.e. width
  int sqHeight  = CalcSquareHeightInLines(sqWidth);              // The number of lines to use in printing the squares' vertical sides, i.e. height
  char useForBlack = PromptForBlackSquareChar();                 // The character to use for making black squares

  // BuildRowLine could have been used as a structural improvement even if the project scope had not included doing variable square sizes
  string whiteRow = BuildRowLine(sqWidth, useForBlack, true);    // A row beginning with a white square
  string blackRow = BuildRowLine(sqWidth, useForBlack, false);   // A row beginning with a black square

  cout << "\n\n\n"; // Add margin between prompt messages and board

  // Major structural improvement: loop when printing lines.
  // Print two rows of squares on each pass
  for (int i = 0; i < (CHESS_BOARD_SIDE_LEN / 2); i++) {
      PrintRow(whiteRow, sqHeight); // Structural improvement: use a function with a loop in it to print board rows. See func def.
      PrintRow(blackRow, sqHeight);
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

/**
 * Prompts user for how many characters wide to make each square in the board
 *
 * Pre: None
 * Post: Prompts have been printed to the screen; if user entry fails validation 15 times,
 *  default value of 5 is returned. User always informed of value used.
*/
int PromptForSquareWidth() {
    int defaultLen = 5;             // Default square side length
    int len = 0;                    // Variable to return as square width if user input goes well
    int dataEntryAttempts = 0;      // Number of times the user has attempted to enter a width value
    int maxDataEntryAttempts = 15;  // Maximum number of times to try to read user input before using default width value

    cout << "Please type the width, in characters, to use for the \nchess board's squares, then press enter (1 thru " << MAX_SQUARE_SIZE << "):  ";
    cin >> len;

    while(!cin || (len < 1 || len > MAX_SQUARE_SIZE)) {     // cin in fail state or input out of range
        if (!cin) {
            cin.clear();
            cin.ignore(100, '\n');
        }
        if (dataEntryAttempts == maxDataEntryAttempts) {    // Too many attempts
            cout << "Too many failed attempts. Using " << defaultLen << " as top and bottom side length.\n\n\n";
            return defaultLen;
        }
        cout << "\nThat entry is invalid. Enter a number between 1 and " << MAX_SQUARE_SIZE << ": ";
        cin >> len;
        cout << "\n";
        dataEntryAttempts++;
    }
    cout << "Using " << len << " as top and bottom side length.\n\n\n";
    return len;
}
/**
 * Prompts user for which character to use when shading black squares
 *
 * Pre: cin is not in fail state
 * Post: At least one prompt has been output to console; default value of '*' used if data entry fails 15 times.
*/

char PromptForBlackSquareChar() {
    char defaultChar = '*';
    char use = defaultChar;
    int dataEntryAttempts = 0;      // Number of times the user has attempted to enter a value
    int maxDataEntryAttempts = 15;  // Maximum number of times to try to read user input before using default value
    cout << "Please enter the character to use when shading the board's black \nsquares, then press enter:  ";
    cin >> use;
    while (!cin) {
        cin.clear();
        cin.ignore(100, '\n');
        if (dataEntryAttempts == maxDataEntryAttempts) {
            cout << "Too many failed attempts. Using " << defaultChar  << " for shading.\n\n\n";
            return defaultChar;
        }
        cout << "\nInvalid entry or other input failure. Enter a single character: ";
        cin >> use;
        dataEntryAttempts++;
    }
    cout << "Using \"" << use << "\" as shading for black squares.\n";
    return use;
}

/**
 * Builds a string to use as one line of console output when printing chess board rows
 *
 * Pre:  squareLength is greater than zero and less than MAX_SQUARE_SIZE
 * Post: Returned string is constructed with as many alternations (squares) as the value of CHESS_BOARD_SIDE_LEN
 * @param int squareLength    - How wide to make each square, in characters. Number is not validated in this function.
 * @param char black          - Which character to use for shading black squares
 * @param bool startWithWhite - Set to true to use whitespace in the first part of the string,
 *  ultimately for use in a row starting with a white square.
*/

string BuildRowLine(int squareLength, char black, bool startWithWhite) {
    string rowLine = "";                                // The string that will be returned
    string wSq = StringOfChars(' ', squareLength);      // One row's worth of a white chess board square
    string bSq = StringOfChars(black, squareLength);    // One row's worth of a black chess board square
    int i = 1;                                          // Iterator must start at 1 because the modulus operator
                                                        //   is used on it to check if an iteration is even or odd
    int loopEnd = CHESS_BOARD_SIDE_LEN + 1;             // One more than CHESS_BOARD_SIDE_LEN because iterator starts at 1.

    // Iterator is checked even/odd when determining which strings (squares, b vs w) to add; use this fact to set up which color goes first
    if (startWithWhite) {
        i++;
        loopEnd++;
    }
    // Create a black-white or white-black row by concatenating the basic strings
    while(i < loopEnd) {
        if (i % 2 == 0) {       // Even iterations add white output to the string
            rowLine += wSq;
        } else {                // Odd iterations add white output to the string
            rowLine += bSq;
        }
        i++;
    }
    return rowLine;
}

/**
 * Returns a string with a repeating character a specified number of times
 *
 * Pre: num is positive or zero
 * @param char c  - The character to use in the string
 * @param int num - How long to make the string
*/
string StringOfChars(char c, int num) {
    string out = "";
    int i = 0;
    while(i < num) {
        out += c;
        i++;
    }
    return out;
}

/**
 * Calculates the squares' height (how many vertical lines to print) given the number of horizontal characters
 * that make up the squares' width. The calculation is based on the 8:5 ratio between width-wise chars to
 * height-wise newlines given in the original program. Below 4 characters wide, the output looks best if the
 * number of lines printed is rounded up, so that is what this function does in such cases.
 *
 * Pre: width is between 0 and MAX_SQUARE_LENGTH
 * @param int width - How wide each square shall be, in characters
 * @return int - The number of vertical lines to print, truncated if width is >= 4, rounded up if not.
*/
int CalcSquareHeightInLines(int width) {
    float round = 0.0;
    if (width < 4)  // Below 4 characters wide, rounding up the number of lines looks best.
        round = 0.5;
    return ((5 * width) / 8.0) + round ; // The ratio stated above, solved for height and rounded by the amount specified above
}
