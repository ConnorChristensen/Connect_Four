#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include "./connect_four.h"
using namespace std;

int main(int argc, char* argv[]) {
    struct game connect;
    if (argc != 7) {
        cout << "Error: too few arguments." << endl;
        exit(0);
    }
    command_line_game(connect, argv);
    player_prompted(connect);
    return 0;
}
