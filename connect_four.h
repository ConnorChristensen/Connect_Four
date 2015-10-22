using namespace std;

struct game {
    char **array, color, winner;
    int row, col, pieces;
    char p1;
    char p2;
};


void clear_screen();
void delete_table (game *connect);
void clear_line(int number);
void countdown(int number);
int isnumeric(char temporary[]);
int loop_number_smaller (string output, int number);
int loop_number(string output, int number);
bool is_valid_arguments(char *info[]);
void check_r(game *connect, char *info[]);
void check_p(game *connect, char *info[]);
void check_c(game *connect, char *info[]);
void check_p_cap(game *connect, char *info[]);
void set_game_info(game *connect, char *info[]);
void set_color(game *connect);
bool check_vertical(game connect);
bool check_horizontal(game connect);
bool check_diagonal_right(game connect);
bool check_diagonal_left(game connect);
bool check_winner(game connect);
char** create_table(int row, int col);
void fill_array(game *connect);
bool empty_array(game* *connect);
void baseline_print(game *connect);
void print_array(game *connect);
void spot_drop_color(game **connect, char color, int player);
void clear_print(game *connect);
void play_game(game *connect);
void setup(game *connect);
void command_line_game(game &connect, char* argv[]);
void prompt(game *connect);
void player_prompted(game &connect);
int isnumeric_string(string output);
