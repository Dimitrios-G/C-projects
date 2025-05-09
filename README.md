ic Tac Toe Game in C
This is a simple two-player Tic Tac Toe game implemented in the C programming language. Players take turns marking spaces on a 3x3 grid with their chosen symbol ('X' or 'O'), attempting to get three in a row (horizontally, vertically, or diagonally).

Features
Two-player gameplay.
Clear and colorful display of the game board using ANSI escape codes.
Input validation to ensure players enter valid row and column numbers.
Checks for winning conditions after each move.
Detects draw games when the board is full and no player has won.
Prompts players to enter their names.
Allows the first player to choose their symbol ('X' or 'O').
Handles incorrect input gracefully, prompting the player to try again.
How to Compile and Run
Save the code: Save the provided C code as a .c file (e.g., tictactoe.c).
Compile: Open a terminal or command prompt and use a C compiler (like GCC) to compile the code:
Bash

gcc tictactoe.c -o tictactoe
Run: Execute the compiled program:
Bash

./tictactoe
(On Windows, you might need to run tictactoe.exe).
How to Play
The game will first ask Player 1 and Player 2 to enter their names.
Player 1 will then be prompted to choose their symbol ('X' or 'O'). Player 2's symbol will be the other option.
The 3x3 game board will be displayed, with numbers indicating the rows (1-3) and columns (1-3).
Players take turns entering their desired move by specifying the row and column number (e.g., "1 2" for the top-middle cell).
The board will be updated after each valid move.
The game continues until one player gets three of their symbols in a row, column, or diagonal, or until all the cells are filled (resulting in a draw).
The winner (if any) will be announced.
ANSI Escape Codes for Colors
This game uses ANSI escape codes to add colors to the output in the terminal. This enhances the visual experience, making it easier to distinguish between players' symbols and the board.

Light Red: Used for 'X'.
Light Yellow: Used for 'O'.
