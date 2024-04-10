#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

#define ROW 5

void print(char (&game_map)[ROW][ROW]) {
    for (int i = 0; i != ROW; ++i) {
        for (int j = 0; j != ROW; ++j) {
            std::cout << game_map[i][j];
        }
        std::cout << std::endl;
    }
}

// 0 Ongoing
// 1 Win
// 2 Lose
// 3 Draw
int checkWin(char (&game_map)[ROW][ROW]) {
    // Horizontal win
    if (game_map[0][0] == 'X' && game_map[0][2] == 'X' && game_map[0][4] == 'X') {
        return 1;
    } else if (game_map[2][0] == 'X' && game_map[2][2] == 'X' && game_map[2][4] == 'X') {
        return 1;
    } else if (game_map[4][0] == 'X' && game_map[4][2] == 'X' && game_map[4][4] == 'X') {
        return 1;
    }

    // Horizontal loss
    if (game_map[0][0] == 'O' && game_map[0][2] == 'O' && game_map[0][4] == 'O') {
        return 2;
    } else if (game_map[2][0] == 'O' && game_map[2][2] == 'O' && game_map[2][4] == 'O') {
        return 2;
    } else if (game_map[4][0] == 'O' && game_map[4][2] == 'O' && game_map[4][4] == 'O') {
        return 2;
    }

    // Vertical win
    if (game_map[0][0] == 'X' && game_map[2][0] == 'X' && game_map[4][0] == 'X') {
        return 1;
    } else if (game_map[0][2] == 'X' && game_map[2][2] == 'X' && game_map[4][2] == 'X') {
        return 1;
    } else if (game_map[0][4] == 'X' && game_map[2][4] == 'X' && game_map[4][4] == 'X') {
        return 1;
    }

    // Vertical loss 
    if (game_map[0][0] == 'O' && game_map[2][0] == 'O' && game_map[4][0] == 'O') {
        return 2;
    } else if (game_map[0][2] == 'O' && game_map[2][2] == 'O' && game_map[4][2] == 'O') {
        return 2;
    } else if (game_map[0][4] == 'O' && game_map[2][4] == 'O' && game_map[4][4] == 'O') {
        return 2;
    }

    // Diagonal win
    if (game_map[0][0] == 'X' && game_map[2][2] == 'X' && game_map[4][4] == 'X') {
        return 1;
    } else if (game_map[0][4] == 'X' && game_map[2][2] == 'X' && game_map[4][0] == 'X') {
        return 1;
    }

    // Diagonal loss
    if (game_map[0][0] == 'O' && game_map[2][2] == 'O' && game_map[4][4] == 'O') {
        return 2;
    } else if (game_map[0][4] == 'O' && game_map[2][2] == 'O' && game_map[4][0] == 'O') {
        return 2;
    }

    int cnt = 0;
    for (int i = 0; i != ROW - 1;i+=2) {
        for (int j = 0; j != ROW - 1; j+= 2) {
            if (game_map[i][j] == ' ') {
                break;
            } else {
                ++cnt;
            }
        }
    }
    if (cnt == 9)
        return 3;

    return 0;
}

bool checkInput(int val1, int val2, std::vector<std::pair<int,int>> &possible_moves) {
    
    for (int i = 0; i != possible_moves.size(); ++i) {
        if (possible_moves[i].first == val1 && possible_moves[i].second == val2) {
            return true;
        }
    }
    return false;
}

void player2Input(char (&game_map)[ROW][ROW], std::vector<std::pair<int,int>> &possible_moves) {
    int index_x, index_y, rand_x, rand_y;
    while (true) {
        index_x = std::rand() % possible_moves.size() - 1;
        index_y = std::rand() % possible_moves.size() - 1;
        rand_x = possible_moves[index_x].first;
        rand_y = possible_moves[index_y].second;
        if (checkInput(rand_x, rand_y, possible_moves)) {
            game_map[rand_x][rand_y] = 'O';
            break;
        }       
    }
    std::pair<int, int> pair_to_remove = {rand_x, rand_y};
    std::cout << "Move Chosen: [" << rand_x << "," << rand_y << "]" << std::endl;
    possible_moves.erase(std::remove_if(possible_moves.begin(), possible_moves.end(), [&](const std::pair<int,int>& elem) { return elem == pair_to_remove; }), possible_moves.end());
}

void print_vec(std::vector<std::pair<int,int>> &vec) {
    std::cout << "Possible Moves: ";
    for (auto it = vec.cbegin(); it != vec.cend(); ++it) {
        std::cout << "[" << it->first << "," << it->second << "] ";
    }
    std::cout << std::endl;
}

int main() {
    int win, val1, val2;
    std::vector<std::pair<int,int>> possible_moves = {{0,0},{0,2},{0,4},{2,0},{2,2},{2,4},{4,0},{4,2},{4,4}};

    char game_map[ROW][ROW] = {
        {' ','|',' ','|',' '},
        {'-','+','-','+','-'},
        {' ','|',' ','|',' '},
        {'-','+','-','+','-'},
        {' ','|',' ','|',' '}
    };

    print(game_map);
    do {
        std::cout << "***************" << std::endl;
        std::cout << "  User 1 Turn  " << std::endl;
        std::cout << "***************" << std::endl;
        std::cout << "Place your X (es: 0 2): ";
        if (!(std::cin >> val1 >> val2)) {
            std::cout << "Error: You can only input numbers..." << std::endl;
            std::cin.clear();
            std::cin.ignore(1000,'\n');
        } 
        if (checkInput(val1, val2, possible_moves)) {
            game_map[val1][val2] = 'X';
            std::pair<int, int> pair_to_remove = {val1,val2};
            possible_moves.erase(std::remove_if(possible_moves.begin(), possible_moves.end(), [&](const std::pair<int,int>& elem) { return elem == pair_to_remove; }), possible_moves.end());
        } else {
            std::cout << "Error: You can only input valid numbers..." << std::endl;
        }
        print_vec(possible_moves);
        std::cout << "Move Chosen: [" << val1 << "," << val2 << "]" << std::endl;
        print(game_map);
        win = checkWin(game_map);
        if (win == 1 || win == 2 || win == 3) {
            break;
        }
        std::cout << "***************" << std::endl;
        std::cout << "  User 2 Turn  " << std::endl;
        std::cout << "***************" << std::endl;
        print_vec(possible_moves);
        player2Input(game_map, possible_moves);
        print(game_map);
        win = checkWin(game_map);
        if (win == 1 || win == 2 || win == 3) {
            break;
        }
    } while (val1 != -1 || val2 != -1);
    switch (win) {
    case 1:
        std::cout << "You won" << std::endl;
        break;
    case 2:
        std::cout << "You lose" << std::endl;
        break;
    case 3:
        std::cout << "Draw" << std::endl;
        break;
    }
    return 0;
}
