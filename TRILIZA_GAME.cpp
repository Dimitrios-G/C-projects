#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIZE 3

char board[SIZE][SIZE];  // ������� ��� �� ������
char player1_symbol, player2_symbol;  // ������� �������
char player1_name[50], player2_name[50];  // ������� �������

// ANSI escape codes ��� �������
#define LIGHT_RED "\033[38;5;9m"    // ������� ��� X
#define LIGHT_YELLOW "\033[38;5;226m" // ������� ��� O
#define LIGHT_GREEN "\033[38;5;82m"  // ������� ��� ������
#define LIGHT_ORANGE "\033[38;5;214m" // ��������� ��� ����������
#define AQUA "\033[38;5;51m"  // Aqua ��� �����
#define GREEN "\033[32m"      // �������
#define RESET "\033[0m"  // ��������� ��������

// �������� ��� ������
void printBoard()
{
    printf("\n");
    system("cls");  
    printf(AQUA " \n          ������� # TicTacToe\n" RESET);  // �������� ������ �� aqua ����� ��� ���� reset
    printf(AQUA " ________________________________________________________________\n\n" RESET);
    printf(GREEN "   1   2   3\n" RESET);  // ������� ��� �����
    for (int i = 0; i < SIZE; i++)
    {
        if (i != 0)
        {
            printf(GREEN "  ____________\n" RESET);  // ������������ ������� ��� �������� ��������
        }
        printf(" %d", i + 1);  // �������� ��� ������� ��� ������
        for (int j = 0; j < SIZE; j++)
        {
            // �� ����� X, ����������� �� �������
            if (board[i][j] == 'X')
                printf(LIGHT_RED " %c " RESET GREEN "|" RESET, board[i][j]);
            // �� ����� O, ����������� �� �������
            else if (board[i][j] == 'O')
                printf(LIGHT_YELLOW " %c " RESET GREEN "|" RESET, board[i][j]);
            else
                printf(" %c " GREEN "|" RESET, board[i][j]);  // �� ����� ����, ����������� �� �������
        }
        printf("\n");
    }
}

// ������ ��� ������
void playerMove(char symbol, char *player_name)
{
    int row, col;
    while (1) {
        printf("\n\n  %s (%c), ������� �� ���� ��� (�.�. 1 2): ", player_name, symbol);
        if (scanf(" %d %d", &row, &col) != 2) 
		{
            printf(" ����� ��������! �������� ���� �� �������� ��������.\n");
            while(getchar() != '\n');  // ��������� ��� ������ �� ����� �����
            continue;
        }

        row--; col--; // ��������� ��� 1-based �� 0-based
        if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ') 
		{
            board[row][col] = toupper(symbol); // ���������� ��� �������� ��� ������
            break;
        } else {
            printf(" ���� ������������! �������� ���� ����.\n");
        }
    }
}

// ������� ��� ����
int checkWin(char symbol)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
        {
            return 1; // ���� ���� ��������� ������
        }
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)
        {
            return 1; // ���� ���� ������ �����
        }
    }
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
    {
        return 1; // ���� ���� ����� ��������
    }
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
    {
        return 1; // ���� ���� �������� ��������
    }
    return 0; // ��� ������� ����
}

// ������� ��� ��������
int checkDraw()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                return 0; // ������� ����, � �������� ��� ���� ����� �����
            }
        }
    }
    return 1; // ��� �� ��������� ������, ��������
}

// ���� ��� �������� ��� ������
void getPlayerName(char *name, int size, int playerNumber) 
{
    while (1) {
        printf(" �������� ����� ������ %d: ", playerNumber);
        if (fgets(name, size, stdin) != NULL) 
		{
            name[strcspn(name, "\n")] = 0; // �������� ��� newline
            int hasDigit = 0;
            for (int i = 0; name[i] != '\0'; i++) 
			{
                if (isdigit(name[i])) 
				{
                    hasDigit = 1;
                    break;
                }
            }
            if (!hasDigit && name[0] != '\0') 
			{
                break; // ����� ����� ��������
            } else
			{
                printf(" �� ����� ��� ������ �� �������� ��������. ���������� ����.\n");
            }
        } else 
		{
            // �� ��������� ��������� ���������
            exit(EXIT_FAILURE);
        }
    }
}

// ������ ��� ����������
void playGame()
{
    getPlayerName(player1_name, sizeof(player1_name), 1);
    getPlayerName(player2_name, sizeof(player2_name), 2);

    while (1)
    {
        char symbol_input[3]; // �������� ��������
        printf(" %s, ������� ������� (X � O): ", player1_name);
        if (fgets(symbol_input, sizeof(symbol_input), stdin) != NULL)
		 {
            if (strlen(symbol_input) == 2) 
			{ //  ���� � ������� ������� �� ������� ��� ��� ������, � ������� ��� ���������� ������������ ��� ����������:
                char entered_symbol = toupper(symbol_input[0]);
                if (entered_symbol == 'X' || entered_symbol == 'O') 
				{
                    player1_symbol = entered_symbol;
                    player2_symbol = (player1_symbol == 'X') ? 'O' : 'X';
                    break;
                } else 
				{                	
                    printf(" ����� �������, ������� X � O.\n");
                }
            } else 
			{
                printf(" ����� ������� ��������.\n");
            }
        } else
		{
            // �� ��������� ��������� ���������
            exit(EXIT_FAILURE);
        }
    }

    // ���������� ��� ������
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = ' ';  // ������������ ��� ������ �� ����
        }
    }

    printBoard();  // �������� ��� ������

    while (1)
    {
        playerMove(player1_symbol, player1_name);  // ������ ������ 1
        printBoard();  // �������� ������ ���� ��� ������ ��� ������ 1
        if (checkWin(player1_symbol))  // ������� ��� ���� ������ 1
        {
            printf("\n " LIGHT_GREEN "%s ������! :)" RESET "," LIGHT_ORANGE " %s ����� :(" RESET "\n\n", player1_name, player2_name);
            break;
        }
        if (checkDraw())  // ������� ��� ��������
        {
            printf(" ��������!\n");
            break;
        }

        playerMove(player2_symbol, player2_name);  // ������ ������ 2
        printBoard();  // �������� ������ ���� ��� ������ ��� ������ 2
        if (checkWin(player2_symbol))  // ������� ��� ���� ������ 2
        {
            printf("\n " LIGHT_GREEN "%s ������! :)" RESET "," LIGHT_ORANGE " %s ����� :(" RESET "\n\n", player2_name, player1_name);
            break;
        }
        if (checkDraw())  // ������� ��� ��������
        {
            printf("��������!\n");
            break;
        }
    }
}

// ����� ���������
int main()
{
    system("CHCP 1253 >nul");  // �������� ��� ������������ ��� ��������
    printf(AQUA " \n          ������� # TicTacToe\n" RESET);  // ������ �� ����� Aqua ��� ���� ��������� ��� ��������( �� �� RESET)
    printf(AQUA "________________________________________________________________\n\n" RESET);

    playGame();  // �������� ��� ����������

    system("PAUSE");  
    return 0;
}

