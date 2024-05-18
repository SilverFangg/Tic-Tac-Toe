#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Board {
private:
    vector<vector<char>> board;

public:
    void generateBoard(int n) {
        board.resize(n, vector<char>(n, '-'));
    }

    void printBoard() const {
        for (const auto& row : board) {
            for (const auto& cell : row) {
                cout << cell << " |";
            }
            cout << endl;
        }
    }

    bool isCellEmpty(int row, int col) const {
        return board[row][col] == '-';
    }

    void makeMove(int row, int col, char symbol) {
        board[row][col] = symbol;
    }

    char getCell(int row, int col) const {
        return board[row][col];
    }

    int getSize() const {
        return board.size();
    }
};

class Game {
private:
    string user1_id;
    string user2_id;
    Board currBoard;
    vector<pair<int, int>> player1_moves, player2_moves;
    unordered_map<int, int> zeroes_in_rows, zeroes_in_cols;
    int zeroes_in_diagonal1 = 0, zeroes_in_diagonal2 = 0;
    unordered_map<int, int> crosses_in_rows, crosses_in_cols;
    int crosses_in_diagonal1 = 0, crosses_in_diagonal2 = 0;
    int winner = -1;
    int size;

    bool checkWinner(int row, int col, char symbol) {
        int required = size;
        if (symbol == '0') {
            if (zeroes_in_rows[row] == required || zeroes_in_cols[col] == required ||
                (row == col && zeroes_in_diagonal1 == required) ||
                (row + col == size - 1 && zeroes_in_diagonal2 == required)) {
                return true;
            }
        } else {
            if (crosses_in_rows[row] == required || crosses_in_cols[col] == required ||
                (row == col && crosses_in_diagonal1 == required) ||
                (row + col == size - 1 && crosses_in_diagonal2 == required)) {
                return true;
            }
        }
        return false;
    }

public:
    Game(string user1_id, string user2_id, int size) 
        : user1_id(user1_id), user2_id(user2_id), size(size), winner(-1) {
        currBoard.generateBoard(size);
    }

    void play() {
        int currPlayer = 1;
        int count_of_moves = 0;
        while (count_of_moves < size * size && winner == -1) {
            cout << "Player " << currPlayer << " move: ";
            int currRow, currCol;
            cin >> currRow >> currCol;

            while (!currBoard.isCellEmpty(currRow, currCol)) {
                cout << "Invalid Move. Try again." << endl;
                cout << "Player " << currPlayer << " move: ";
                cin >> currRow >> currCol;
            }

            char symbol = (currPlayer == 1) ? '0' : 'x';
            currBoard.makeMove(currRow, currCol, symbol);

            if (currPlayer == 1) {
                player1_moves.emplace_back(currRow, currCol);
                zeroes_in_cols[currCol]++;
                zeroes_in_rows[currRow]++;
                if (currRow == currCol) zeroes_in_diagonal1++;
                if (currRow + currCol == size - 1) zeroes_in_diagonal2++;
            } else {
                player2_moves.emplace_back(currRow, currCol);
                crosses_in_cols[currCol]++;
                crosses_in_rows[currRow]++;
                if (currRow == currCol) crosses_in_diagonal1++;
                if (currRow + currCol == size - 1) crosses_in_diagonal2++;
            }

            currBoard.printBoard();

            if (checkWinner(currRow, currCol, symbol)) {
                winner = currPlayer;
            }

            currPlayer = (currPlayer == 1) ? 2 : 1;
            count_of_moves++;
        }

        if (winner == -1) {
            cout << "Game is drawn" << endl;
        } else {
            cout << "Winner of the game is: Player " << winner << endl;
        }
    }
};

class User {
private:
    string user_id;
    string user_name;
    int total_wins = 0;
    int total_losses = 0;
    int total_draws = 0;
    vector<Game> past_games;

public:
    // Add getters, setters, and other methods to manage user statistics and games.
};

int main() {
    Game game("user1", "user2", 3);
    game.play();
    return 0;
}
