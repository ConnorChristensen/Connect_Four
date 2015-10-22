/****************************************************** 
 ** Program: connect_four.cpp
 ** Author: Connor Christensen
 ** Date: 04/12/2015
 ** Description: Plays connect four with any board or pieces
 ** Input: row, column and peices
 ** Output: the game
 ******************************************************/

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include "./connect_four.h"

using namespace std;

/*
 * Clears screen to prepare for reprinting
 * No input or direct output
 * Lines: 1
*/
void clear_screen() {
    cout << "\e[2J" << "\e[K" << "\e[;H";
}

/*
 * Deletes dynamically alocated array
 * Takes input of array
 * Lines: 3
*/
void delete_table (game *connect) {
    for (int x = 0 ; x < connect->row; x++) {
        delete [] connect->array[x];
    }
    delete [] connect->array;
}

/*
 * Function for clearing X ammount of lines
 * Takes input of number of lines
 * Lines: 3
 */
void clear_line(int number) {
    for (int x = 0; x < number ; x++) {
        cout << "\e[K";
        cout << "\e[1A";
    }
}

/*
 * Produces a countdown timer to let the user know it will clear the screen
 * Takes input for number of ~seconds that the coundown timer will run
 * Lines: 5
 */
void countdown(int number) {
    for (int x = number; x > 0; x--) {
        cout << "\e[31mThe screen will reset in " <<  x << "\e[0m" << endl;
        usleep(550000);
        cout << "\e[K";
        cout << "\e[1A";
    }
    clear_screen();
}

/*
 * Checks isdigit for multi-character c-style strings
 * Takes argument of c-style string - Bool returns false if it is not a valid int
 * Lines: 4
 */
int isnumeric(char temporary[]) {
    bool correct = true;
    for (int y = 0; y < strlen(temporary); y++) {
        if (isdigit(temporary[y]) == false) {
            return false;
        }
    }
    return true;
}
/*
 * Verifies is digit
 * Input of the string it will reprint if not given valid int - Outputs valid int to be captured
 * Lines: ~13
 */
int isnumeric_string(string output) {
    
    int variable;
    bool correct = true;
    char temporary[25];
    
    cout << output;
    cin >> temporary;
    
    do {
        correct = true;
        for (int y = 0; y < strlen(temporary); y++) {
            if (isdigit(temporary[y]) == false) {
                correct = false;
            }
        }
        if (correct == false) {
            cout << "Incorrect, try again: " << endl;
            cout << output;
            cin >> temporary;
        }
        else {
            variable = atoi(temporary);
            correct = true;
        }
    } while (correct == false);
    
    return variable;
}
/*
 * Reprompts user for smaller than number provided
 * Input of the string to reprompt and the number to check is bigger
 * Lines: 10
 */
int loop_number_smaller (string output, int number) {
    bool correct = true;
    int temporary;
    cout << output;
    cin >> temporary;
    do {
        if (temporary >= number) {
            cout << "Incorrect, try again: " << endl;
            cout << output;
            cin >> temporary;
        }
    } while (temporary >= number);
    return temporary;
}
/*
 * Reprompts user for larger than number provided
 * Input of the string to reprompt and the number to check is bigger
 * Lines: 10
 */
int loop_number(string output, int number) {
    bool correct = true;
    int temporary;
    cout << output;
    cin >> temporary;
    do {
        if (temporary <= number) {
            cout << "Incorrect, try again: " << endl;
            cout << output;
            cin >> temporary;
        }
    } while (temporary <= number);
    return temporary;
}
/*
 * Check to see all arguments that need to be are ints
 * Input of argv - Output of verification of int
 * Lines: 5
 */
bool is_valid_arguments(char *info[]) {
    if ((isnumeric(info[2]) and isnumeric(info[4]) and isnumeric(info[6])) == false) {
        cout << "One of your arguments was not a valid number." << endl;
        return false;
    }
    else {
        return true;
    }
}

/* 
 * Check to see r is bigger than 1
 * Input of struct and argv - Output assigning of number to struct
 * Lines: 6
 */
void check_r(game *connect, char *info[]) {
    for (int x = 1; x < 7; x += 2) {
        if (!strcmp(info[x], "-r")) {
            if (atoi(info[x+1]) <= 0) {
                connect->row = loop_number("You cannot have rows smaller than 2. Try again: ", 1);
            }
            else {
                connect->row = atoi(info[x+1]);
            }
        }
    }
}
/*
 * Check to see p is bigger than 1
 * Input of struct and argv - Output assigning of number to struct
 * Lines: 6
 */
void check_p(game *connect, char *info[]) {
    for (int x = 1; x < 7; x += 2) {
        if (!strcmp(info[x], "-p")) {
            if (atoi(info[x+1]) < 2) {
                connect->pieces = loop_number("You cannot connect any less than 2 pieces. Try again: ", 1);
            }
            else {
                connect->pieces = atoi(info[x+1]);
            }
        }
    }
}
/*
 * Check to see c is bigger than 1
 * Input of struct and argv - Output assigning of number to struct
 * Lines: 6
 */
void check_c(game *connect, char *info[]) {
    for (int x = 1; x < 7; x += 2) {
        if (!strcmp(info[x], "-c")) {
            if (atoi(info[x+1]) <= 0) {
                connect->col = loop_number("You cannot have columns smaller than 2. Try again: ", 1);
            }
            else {
                connect->col = atoi(info[x+1]);
            }
        }
    }
}
/*
 * Check to see p is smaller than r and c
 * Input of struct and argv - Output assigning of number to struct
 * Lines: 7
 */
void check_p_cap(game *connect, char *info[]) {
    for (int x = 1; x < 7; x += 2) {
        if ((connect->pieces > connect->col) and (connect->pieces > connect->row)) {
            int larger;
            if (connect->col > connect->row) {
                larger = connect->col;
            }
            else if (connect->col == connect->row) {
                larger = connect->row;
            }
            else {
                larger = connect->row;
            }
            connect->pieces = loop_number_smaller("You cannot connect more pieces than both the rows and columns. Try again: ", (larger+1));
        }
    }
}
/*
 * Launches the verification and assigning proccess
 * Input of struct and argv
 * Lines: 5
 */
void set_game_info(game *connect, char *info[]) {
    if (is_valid_arguments(info) == true) {
        check_c(connect, info);
        check_r(connect, info);
        check_p(connect, info);
        check_p_cap(connect, info);
    }
    else {
        exit(0);
    }
}
/*
 * Decides which player will be which color
 * Input of struct - Output of assigning 'r' and 'y' char to struct players
 * Lines: 10
 */
void set_color(game &connect) {
    cout << "What color would you like to be Player 1? (r/y): ";
    cin >> connect.p1;
    
    if (connect.p1 == 'r') {
        cout << "P2, you will be " << "\033[0;40;33myellow\033[0m" << "." << endl;
        connect.p2 = 'y';
        cout << "Please wait while the screen clears" << endl;
        countdown(9);
    }
    else {
        cout << "P2, you will be " << "\033[0;31mred.\033[0m"<< endl;
        connect.p2 = 'r';
        cout << "Please wait while the screen clears" << endl;
        countdown(9);
    }
}

/*
 * Checks for vertical wins
 * Input of struct - Output of Bool confirmation
 * Lines: 10
 */
bool check_vertical(game connect) {
    int counter = 0;
    char space_holder = ' ';
    
    for (int x = 0; x < connect.col; x++) {
        counter = 1;
        for (int y = 0; y < (connect.row - 1); y++) {
            if ((connect.array[y][x] == 'r') or (connect.array[y][x] == 'y')) {
                space_holder = connect.array[y][x];
            }
            else {
                continue;
            }
            if (connect.array[y+1][x] == space_holder) {
                counter += 1;
                if (counter == connect.pieces) {
                    return true;
                }
            }
            else {counter = 1;}
        }
    }
    return false;
}
/*
 * Checks for horizontal wins
 * Input of struct - Output of bool value
 * Lines: 10
 */
bool check_horizontal(game connect) {
    int counter = 0;
    char space_holder = ' ';
    
    for (int y = 0; y < (connect.row); y++) {
        counter = 1;
        for (int x = 0; x < (connect.col); x++) {
            if ((connect.array[y][x] == 'r') or (connect.array[y][x] == 'y')) {
                space_holder = connect.array[y][x];
            }
            else {
                continue;
            }
            if (connect.array[y][x+1] == space_holder) {
                counter += 1;
                if (counter == connect.pieces) {
                    return true;
                }
            }
            else {
                counter = 1;
            }
        }
    }
    return false;
}
/*
 * Chekcs for diagonal right wins
 * Input of struct - Output of bool value
 * Lines: 10
 */
bool check_diagonal_right(game connect) {
    int counter;
    
    for (int y = 0; y < (connect.row-(connect.pieces-1)); y++) {
        for (int x = 0; x < (connect.col-(connect.pieces-1)); x++) {
            counter = 1;
            for (int z = 0; z < (connect.pieces-1); z++) {
                if (connect.array[y+z][x+z] != ' ') {
                    if (connect.array[y+z][x+z] == connect.array[y+(z+1)][x+(z+1)]) {
                        counter += 1;
                        if (counter == connect.pieces) {
                            return true;
                        }
                    }
                }
                else {
                    counter = 1;
                }
            }
        }
    }
    return false;
}
/*
 * Checks for diagonal left wins
 * Input of struct - Output of bool value
 * Lines: 10
 */
bool check_diagonal_left(game connect) {
    int counter;
    
    for (int y = (connect.row-1); y > (connect.pieces-2); y--) {
        for (int x = 0; x < (connect.col-(connect.pieces-1)); x++) {
            counter = 1;
            for (int z = 0; z < (connect.pieces-1); z++) {
                if (connect.array[y-z][x+z] != ' ') {
                    if (connect.array[y-z][x+z] == connect.array[y-(z+1)][x+(z+1)]) {
                        counter += 1;
                        if (counter == connect.pieces) {
                            return true;
                        }
                    }
                }
                else {
                    counter = 1;
                }
            }
        }
    }
    return false;
}

/*
 * Checks for sum of wins
 * Input of struct - Output of bool value
 * Lines: 4
 */
bool check_winner(game connect){
    if (check_horizontal(connect)) {
        return true;
    }
    else if (check_vertical(connect)) {
        return true;
    }
    else if (check_diagonal_right(connect)) {
        return true;
    }
    else if (check_diagonal_left(connect)) {
        return true;
    }
    return false;
}

/*
 * Creates space for table
 * Input of rows and columns - Output of allocated memory
 * Lines:
 */
char** create_table(int row, int col) {
    char **array;
    array = new char *[row];
    for (int x = 0; x < row; x++) {
        array[x] = new char[col];
    }
    return array;
}
/*
 * Fills the array with empty space
 * Input of struct - Output of empty array
 * Lines:
 */
void fill_array(game &connect) {
    for (int y = 0; y < connect.row; y++) {
        for (int x = 0; x < connect.col; x++) {
            connect.array[y][x] = ' ';
        }
    }
}
/*
 * Checks to see if array is full or not
 * Input of struct - Output of bool value
 * Lines: 3
 */
bool empty_array(game* &connect) {
    for (int y = 0; y < connect->col; y++) {
        if (connect->array[0][y] == ' ') {
            return true;
        }
    }
    return false;
}

/*
 * Part of print function
 * Input of struct - Ouptut of lines inbetween array
 * Lines:
 */
void baseline_print(game *connect) {
    cout << "+";
    for (int y = 0; y < (connect->col - 1); y++) {
        cout << "--";
    }
    cout << "-+" << endl;
}
/*
 * Prints the array
 * Input of struct - Output of printed array
 * Lines: 9
 */
void print_array(game *connect) {
    baseline_print(connect);
    for (int y = 0; y < connect->row; y++) {
        for (int x = 0; x < connect->col; x++) {
            if (connect->array[y][x] == 'r') {
                cout << "|" << "\033[1;41m" << connect->array[y][x] << "\033[0m";
            }
            else if (connect->array[y][x] == 'y') {
                cout << "|" << "\033[1;43m" << connect->array[y][x] << "\033[0m";
            }
            else {
                cout << "|" << connect->array[y][x];
            }
            
        }
        cout << "|" << endl;
        baseline_print(connect);
    }
    cout << endl;
}
/*
 * Function for assigning chars to spaces on the board selected by the player (artifical gravity)
 * Input of struct, what color type and what player - Output of updated array
 * Lines: ~11
 */
void spot_drop_color(game* &connect, char color, int player) {
    int spot;
    do {
        cin.ignore();
        cout << "\e[K" << "Player " << player << " choose your space: ";
        cin >> spot;
        if ((connect->array[0][spot-1] != ' ') or (spot > connect->col)) {
            cout << "\e[K" << "That is not a valid column, try again: " << endl;
            countdown(3);
            print_array(connect);
        }
        else {
            for (int x = (connect->row-1); x >= 0; x--) {
                if (connect->array[x][spot-1] == ' ') {
                    if (color == 'r') {
                        connect->array[x][spot-1] = 'r';
                        return;
                    }
                    else if (color == 'y') {
                        connect->array[x][spot-1] = 'y';
                        return;
                    }
                }
            }
        }
    } while (connect->array[0][spot-1] != ' ');
}

/*
 * Moves cursor to origin and reprints after delay
 * Takes input of struct for the nested print array function
 * Lines: 4
 */
void clear_print(game *connect) {
    cout << "\r" << "\e[;H";
    print_array(connect);
}

/*
 * Calls players turns and checks for full screen
 * Input of struct - Output of quiting game
 * Lines: 7
 */
void play_game(game *connect) {
    spot_drop_color(connect, connect->p1, 1);
    clear_print(connect);
    spot_drop_color(connect, connect->p2, 2);
    clear_print(connect);
    if (!(empty_array(connect))) {
        cout << "Cats Game: No winner" << endl;
        exit(0);
    }
}
/*
 * Set color, allocates space for array, fills the array with empty space
 * Input of struct - Output of created space
 * Lines: 3
 */
void setup(game &connect) {
    set_color(connect);
    connect.array = create_table(connect.row, connect.col);
    fill_array(connect);
}
/*
 * The play function from the command line
 * Input of struct and argv - Output of completed game
 * Lines: 9
 */
void command_line_game(game &connect, char* argv[]) {
    set_game_info(&connect, argv);
    setup(connect);
    clear_screen();
    print_array(&connect);
    do {
        play_game(&connect);
    }while (!check_winner(connect));
    delete_table(&connect);
    cout << "\e[K" << "You won!" << endl;
}

/*
 * Function for prompting the user after they have verified they want to play again
 * Input of struct - Output of assigned variables
 * Lines: 6
 */
void prompt(game &connect) {
    bool loop;
    do {
        loop = false;
        connect.row = isnumeric_string("Enter the number of rows: ");
        if (connect.row < 2) {
            cout << "Rows are too small. Try again: " << endl;
            loop = true;
            continue;
        }
        connect.col = isnumeric_string("Enter the number of columns: ");
        if (connect.col < 2) {
            cout << "Columns are too small. Try again: " << endl;
            loop = true;
            continue;
        }
        connect.pieces = isnumeric_string("Enter the number of pieces: ");
        if ((connect.pieces > connect.row) and (connect.pieces > connect.col)) {
            cout << "The pieces have to be smaller than the rows and columns. Try again: " << endl;
            loop = true;
            continue;
        }
    }while (loop == true);
}
/*
 * The entire function for the play function not started from the command line
 * Input of struct - Output of played game
 * Lines: ~10
 */
void player_prompted(game &connect) {
    for (;;) {
        int play_again;
        cout << "Would you like to play again?(0/1) ";
        cin >> play_again;
        if (play_again == 0) {
            cout << "Thank you for playing!" << endl;
            countdown(9);
            clear_screen();
            exit(0);
        }
        prompt(connect);
        setup(connect);
        clear_screen();
        print_array(&connect);
        do {
            play_game(&connect);
        }while (!check_winner(connect));
        delete_table(&connect);
        cout << "\e[K" << "You won!" << endl;
    }
}
