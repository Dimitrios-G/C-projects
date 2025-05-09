#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIZE 3

char board[SIZE][SIZE];  // Πίνακας για το ταμπλό
char player1_symbol, player2_symbol;  // Σύμβολα παικτών
char player1_name[50], player2_name[50];  // Ονόματα παικτών

// ANSI escape codes για χρώματα
#define LIGHT_RED "\033[38;5;9m"    // Κόκκινο για X
#define LIGHT_YELLOW "\033[38;5;226m" // Κίτρινο για O
#define LIGHT_GREEN "\033[38;5;82m"  // Πράσινο για πίνακα
#define LIGHT_ORANGE "\033[38;5;214m" // Πορτοκαλί για αποτέλεσμα
#define AQUA "\033[38;5;51m"  // Aqua για τίτλο
#define GREEN "\033[32m"      // Πράσινο
#define RESET "\033[0m"  // Επαναφορά χρωμάτων

// Εκτύπωση του ταμπλό
void printBoard()
{
    printf("\n");
    system("cls");  
    printf(AQUA " \n          Τρίλιζα # TicTacToe\n" RESET);  // Εκτύπωση τίτλου με aqua χρώμα και μετά reset
    printf(AQUA " ________________________________________________________________\n\n" RESET);
    printf(GREEN "   1   2   3\n" RESET);  // Αριθμοί στη σειρά
    for (int i = 0; i < SIZE; i++)
    {
        if (i != 0)
        {
            printf(GREEN "  ____________\n" RESET);  // Διαχωριστικά γραμμών για καλύτερη εμφάνιση
        }
        printf(" %d", i + 1);  // Εκτύπωση του αριθμού της σειράς
        for (int j = 0; j < SIZE; j++)
        {
            // Αν είναι X, εκτυπώνεται σε κόκκινο
            if (board[i][j] == 'X')
                printf(LIGHT_RED " %c " RESET GREEN "|" RESET, board[i][j]);
            // Αν είναι O, εκτυπώνεται σε κίτρινο
            else if (board[i][j] == 'O')
                printf(LIGHT_YELLOW " %c " RESET GREEN "|" RESET, board[i][j]);
            else
                printf(" %c " GREEN "|" RESET, board[i][j]);  // Αν είναι κενό, εκτυπώνεται με πράσινο
        }
        printf("\n");
    }
}

// Κίνηση του παίκτη
void playerMove(char symbol, char *player_name)
{
    int row, col;
    while (1) {
        printf("\n\n  %s (%c), επέλεξε τη θέση σου (π.χ. 1 2): ", player_name, symbol);
        if (scanf(" %d %d", &row, &col) != 2) 
		{
            printf(" Λάθος εισαγωγή! Δοκίμασε ξανά με έγκυρους αριθμούς.\n");
            while(getchar() != '\n');  // Καθαρίζει την είσοδο αν γίνει λάθος
            continue;
        }

        row--; col--; // Μετατροπή από 1-based σε 0-based
        if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ') 
		{
            board[row][col] = toupper(symbol); // Τοποθέτηση του συμβόλου του παίκτη
            break;
        } else {
            printf(" Θέση κατειλημμένη! Δοκίμασε άλλη θέση.\n");
        }
    }
}

// Έλεγχος για νίκη
int checkWin(char symbol)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
        {
            return 1; // Νίκη στην οριζόντια γραμμή
        }
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)
        {
            return 1; // Νίκη στην κάθετη στήλη
        }
    }
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
    {
        return 1; // Νίκη στην κύρια διαγώνιο
    }
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
    {
        return 1; // Νίκη στην αντίθετη διαγώνιο
    }
    return 0; // Δεν υπάρχει νίκη
}

// Έλεγχος για ισοπαλία
int checkDraw()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                return 0; // Υπάρχει κενό, η ισοπαλία δεν έχει γίνει ακόμα
            }
        }
    }
    return 1; // Όλα τα τετράγωνα γεμάτα, ισοπαλία
}

// Λήψη του ονόματος του παίκτη
void getPlayerName(char *name, int size, int playerNumber) 
{
    while (1) {
        printf(" Εισάγετε όνομα Παίκτη %d: ", playerNumber);
        if (fgets(name, size, stdin) != NULL) 
		{
            name[strcspn(name, "\n")] = 0; // Αφαίρεση του newline
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
                break; // Όνομα χωρίς αριθμούς
            } else
			{
                printf(" Το όνομα δεν πρέπει να περιέχει αριθμούς. Προσπάθησε ξανά.\n");
            }
        } else 
		{
            // Σε περίπτωση σφάλματος εισαγωγής
            exit(EXIT_FAILURE);
        }
    }
}

// Λογική του παιχνιδιού
void playGame()
{
    getPlayerName(player1_name, sizeof(player1_name), 1);
    getPlayerName(player2_name, sizeof(player2_name), 2);

    while (1)
    {
        char symbol_input[3]; // Εισαγωγή συμβόλου
        printf(" %s, διάλεξε σύμβολο (X ή O): ", player1_name);
        if (fgets(symbol_input, sizeof(symbol_input), stdin) != NULL)
		 {
            if (strlen(symbol_input) == 2) 
			{ //  όταν ο χρήστης εισάγει το σύμβολο για τον παίκτη, η είσοδος που διαβάζουμε περιλαμβάνει δύο χαρακτήρες:
                char entered_symbol = toupper(symbol_input[0]);
                if (entered_symbol == 'X' || entered_symbol == 'O') 
				{
                    player1_symbol = entered_symbol;
                    player2_symbol = (player1_symbol == 'X') ? 'O' : 'X';
                    break;
                } else 
				{                	
                    printf(" Λάθος σύμβολο, διάλεξε X ή O.\n");
                }
            } else 
			{
                printf(" Λάθος είσοδος συμβόλου.\n");
            }
        } else
		{
            // Σε περίπτωση σφάλματος εισαγωγής
            exit(EXIT_FAILURE);
        }
    }

    // Καθαρισμός του πίνακα
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = ' ';  // Αρχικοποίηση του ταμπλό με κενά
        }
    }

    printBoard();  // Εκτύπωση του ταμπλό

    while (1)
    {
        playerMove(player1_symbol, player1_name);  // Κίνηση Παίκτη 1
        printBoard();  // Εκτύπωση ταμπλό μετά την κίνηση του Παίκτη 1
        if (checkWin(player1_symbol))  // Έλεγχος για νίκη Παίκτη 1
        {
            printf("\n " LIGHT_GREEN "%s νίκησε! :)" RESET "," LIGHT_ORANGE " %s έχασε :(" RESET "\n\n", player1_name, player2_name);
            break;
        }
        if (checkDraw())  // Έλεγχος για ισοπαλία
        {
            printf(" Ισοπαλία!\n");
            break;
        }

        playerMove(player2_symbol, player2_name);  // Κίνηση Παίκτη 2
        printBoard();  // Εκτύπωση ταμπλό μετά την κίνηση του Παίκτη 2
        if (checkWin(player2_symbol))  // Έλεγχος για νίκη Παίκτη 2
        {
            printf("\n " LIGHT_GREEN "%s νίκησε! :)" RESET "," LIGHT_ORANGE " %s έχασε :(" RESET "\n\n", player2_name, player1_name);
            break;
        }
        if (checkDraw())  // Έλεγχος για ισοπαλία
        {
            printf("Ισοπαλία!\n");
            break;
        }
    }
}

// Κύρια συνάρτηση
int main()
{
    system("CHCP 1253 >nul");  // Ρυθμίζει την κωδικοποίηση για ελληνικά
    printf(AQUA " \n          Τρίλιζα # TicTacToe\n" RESET);  // Τίτλος με χρώμα Aqua και μετά επαναφορά των χρωμάτων( με το RESET)
    printf(AQUA "________________________________________________________________\n\n" RESET);

    playGame();  // Εκκίνηση του παιχνιδιού

    system("PAUSE");  
    return 0;
}

