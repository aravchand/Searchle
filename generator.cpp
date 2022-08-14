#include "generator.h"
#include <iostream>
#include <fstream>
#include <random>
#include <functional>
#include <array>
#include <chrono>
#include <algorithm>
#include <iterator>

using std::vector, std::string, std::cout;

vector<string> words;
vector<string> wordle_list;

void printBoard(vector<vector<char>> board) {
    for(vector<char> row : board) {
        for(char c : row) {
            cout << c;
        }
        cout << '\n';
    }
}

int randNum(int lower_bound, int upper_bound) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(lower_bound, upper_bound);
    return distribution(generator);   
}

bool validBoardPosition(int i, int j) {
    return 0 <= i && i < BOARD_SIZE && 0 <= j && j < BOARD_SIZE;
}

// generates word search board having the words in words hidden in it
vector<vector<char>> generateBoard(vector<string> words) {
    vector<vector<char>> board(BOARD_SIZE, vector<char>(BOARD_SIZE, EMPTY));
    
    vector<std::pair<int, int>> directions = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};    
    
    int pos_i, pos_j, dir_i, dir_j, cur_pos_i, cur_pos_j;
    for(string word : words) {
        while(1) { // with sufficiently large board, this loop will always terminate
            bool bad_position = false;
            
            pos_i = randNum(0, BOARD_SIZE - 1), pos_j = randNum(0, BOARD_SIZE - 1); 
            
            std::tie(dir_i, dir_j) = directions[randNum(0, directions.size() - 1)];
            
            cur_pos_i = pos_i, cur_pos_j = pos_j;
            // check if this position and direction work
            for(char c : word) {
                bool within_board = validBoardPosition(cur_pos_i, cur_pos_j);
                bool valid_board_pos = within_board && (board[cur_pos_i][cur_pos_j] == EMPTY || board[cur_pos_i][cur_pos_j] == c);
                if(!valid_board_pos) {
                    bad_position = true;
                    break;
                }
                cur_pos_i += dir_i; cur_pos_j += dir_j;
            }
            
            if(!bad_position) {
                break;
            }
        }
        
        cur_pos_i = pos_i, cur_pos_j = pos_j;
        
        for(char c : word) {
            board[cur_pos_i][cur_pos_j] = c;
            cur_pos_i += dir_i; cur_pos_j += dir_j;
        }
        
    }

    for(vector<char> &row : board) {
        for(char &c : row) {
            if(c == EMPTY) {
                c = (char) randNum('A', 'Z'); 
            }
        } 
    }

    return board;
}

// helper function to fill the wordle_list
void getWordleList() {
    std::ifstream word_file("wordleList.txt");
    string word;
    while(word_file >> word) {
        for(char &c : word) c = toupper(c);
        wordle_list.push_back(word);
    }
    word_file.close();
}

// generate words vector with num_words random words from wordle_list
void fillWords(int num_words) {
    if(wordle_list.size() == 0) { // if wordle_list is not yet retrieved...
        getWordleList(); // ...retrieve it
    }
    words.clear();
    std::sample(begin(wordle_list), end(wordle_list), std::back_inserter(words), num_words, std::mt19937{std::random_device{}()});
}
