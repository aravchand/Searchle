#include <vector>
#include <string>

#pragma once

// constants
const int BOARD_SIZE = 7;
const char EMPTY = '_';

extern std::vector<std::string> words;
extern std::vector<std::string> wordle_list;

void fillWords(int num_words);
int randNum(int lower_bound, int upper_bound);
bool validBoardPosition(int i, int j);
void printBoard(std::vector<std::vector<char>> board);
std::vector<std::vector<char>> generateBoard(std::vector<std::string> words);
