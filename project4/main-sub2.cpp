// Copyright 2021 Ethan Adams
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using std::vector;
using std::cout;
using std::string;

void readPuzzle(vector<vector<char>> &puzzle, string filename);
void readWords(vector<string> &words, string filename);
void printPuzzle(const vector<vector<char>> &puzzle);
void printWords(const vector<string> &words);
void printLocation(string word, const vector<int> &start,
                   const vector<int> &end, bool found);
bool findWord(const vector<vector<char>> & puzzle, string word,
              vector<int> &start, vector<int> &end);
bool checkNorth(const vector<vector<char>> & puzzle, string word,
    vector<int> &start, vector<int> &end, int i, int j);
bool checkNorthEast(const vector<vector<char>> & puzzle, string word,
    vector<int> &start, vector<int> &end, int i, int j);
bool checkEast(const vector<vector<char>> & puzzle, string word,
    vector<int> &start, vector<int> &end, int i, int j);
bool checkSouthEast(const vector<vector<char>> & puzzle, string word,
    vector<int> &start, vector<int> &end, int i, int j);
bool checkSouth(const vector<vector<char>> & puzzle, string word,
    vector<int> &start, vector<int> &end, int i, int j);
bool checkSouthWest(const vector<vector<char>> & puzzle, string word,
    vector<int> &start, vector<int> &end, int i, int j);
bool checkWest(const vector<vector<char>> & puzzle, string word,
    vector<int> &start, vector<int> &end, int i, int j);
bool checkNorthWest(const vector<vector<char>> & puzzle,
    string word, vector<int> &start, vector<int> &end, int i, int j);


int main(int argc, char **argv) {
  string puzzleFileName;
  string wordsFileName;
  vector<vector<char>> puzzle;
  vector<string> words;
  if (argc != 3) {
    cout << "Usage: ./sub2 puzzle.txt words.txt\n";
    exit(0);
  }
  puzzleFileName = argv[1];
  wordsFileName = argv[2];
  readPuzzle(puzzle, puzzleFileName);
  readWords(words, wordsFileName);
  printPuzzle(puzzle);
  printWords(words);

  for (auto word : words) {
    vector<int> start;
    vector<int> end;
    bool found;
    found = findWord(puzzle, word, start, end);
    printLocation(word, start, end, found);
    end.clear();
    start.clear();
  }
  return 0;
}

void readPuzzle(vector<vector<char>> &puzzle, string filename) {
  std::ifstream in(filename);
  if (in.is_open()) {
    // 3
    for (int i = 0; i < 3; i++) {
      vector<char> row;
      string line;
      std::getline(in, line);
      std::stringstream ss(line);
      // 4
      for (int j = 0; j < 4; j++) {
        string value;
        std::getline(ss, value, ' ');
        // offending line
        row.push_back(value[0]);
      }
      puzzle.push_back(row);
    }
  }
  string line;
  in.close();
  return;
}

void readWords(vector<string> &words, string filename) {
  std::ifstream in(filename);
  if (in.is_open()) {
    string line;
    while (getline(in, line)) {
      words.push_back(line);
    }
  } else {
    std::cout << "File could not be opened\n";
  }
  return;
}

void printPuzzle(const vector<vector<char>> &puzzle) {
  for (int i = 0; i < puzzle.size(); i++) {
    for (int j = 0; j < puzzle[i].size(); j++) {
      cout << puzzle[i][j] << " ";
    }
    cout << "\n";
  }
  return;
}

void printWords(const vector<string> &words) {
  for (int i = 0; i < words.size(); i++) {
    cout << words[i] << "\n";
  }
  return;
}

void printLocation(string word, const vector<int> &start,
                   const vector<int> &end, bool found) {
  cout << "Word " << word << " found at (" << start[0] << ", " << start[1] <<
    ") -> (" << end[0] << ", " << end[1] << ")\n";
  return;
}

bool findWord(const vector<vector<char>> & puzzle, string word,
              vector<int> &start, vector<int> &end) {
  bool found = false;
  for (int i = 0; i < puzzle.size(); i++) {
    for (int j = 0; j < puzzle[i].size(); j++) {
      if (puzzle[i][j] == word[0]) {
        found = checkNorth(puzzle, word, start, end, i, j);
        if (found == true)
          return found;
        found = checkNorthEast(puzzle, word, start, end, i, j);
        if (found == true)
          return found;
        found = checkEast(puzzle, word, start, end, i, j);
        if (found == true)
          return found;
        found = checkSouthEast(puzzle, word, start, end, i, j);
        if (found == true)
          return found;
        found = checkSouth(puzzle, word, start, end, i, j);
        if (found == true)
          return found;
        found = checkSouthWest(puzzle, word, start, end, i, j);
        if (found == true)
          return found;
        found = checkWest(puzzle, word, start, end, i, j);
        if (found == true)
          return found;
        found = checkNorthWest(puzzle, word, start, end, i, j);
        if (found == true)
          return found;
      }
    }
  }
  return false;
}

bool checkNorth(const vector<vector<char>> & puzzle, string word,
    vector<int> &start, vector<int> &end, int i, int j) {
  // k moves along i
  int k = 0;
  int l = 1;
  for (k = i - 1; k < i + word.size() - 1; k--) {
    if (k < 0) {
      return false;
    }
    if (puzzle[k][j] != word[l]) {
      return false;
    }
    ++l;
  }
  start.push_back(i);
  start.push_back(j);
  end.push_back(k);
  end.push_back(j);
  return false;
}


bool checkNorthEast(const vector<vector<char>> & puzzle, string word,
    vector<int> &start, vector<int> &end, int i, int j) {
  // k moves along i, m moves along j
  int k = 0;
  int l = 1;
  int m = 0;
  for (k = i - 1; k < i + word.size() - 1; k--) {
    for (m = j + 1; m < j + word.size() - 1; m++) {
      if (k < 0 || m >= puzzle[0].size()) {
        return false;
      }
      if (puzzle[k][m] != word[l]) {
        return false;
      }
      ++l;
    }
  }
  start.push_back(i);
  start.push_back(j);
  end.push_back(k);
  end.push_back(m);
  return false;
}

bool checkEast(const vector<vector<char>> & puzzle, string word,
    vector<int> &start, vector<int> &end, int i, int j) {
  // k moves along j
  int k = 0;
  int l = 1;
  for (k = j + 1; k < j + word.size() - 1; k++) {
    if (k >= puzzle[0].size()) {
      return false;
    }
    if (puzzle[i][k] != word[l]) {
      return false;
    }
    ++l;
  }
  start.push_back(i);
  start.push_back(j);
  end.push_back(i);
  end.push_back(k);
  return true;
}

bool checkSouthEast(const vector<vector<char>> & puzzle, string word,
    vector<int> &start, vector<int> &end, int i, int j) {
  // k moves along i, m moves along j
  int k = 0;
  int l = 1;
  int m = 0;
  for (k = i + 1; k < i + word.size() - 1; k++) {
    for (m = j + 1; m < j + word.size() - 1; m++) {
      if (k >= puzzle.size() || m >= puzzle[0].size()) {
        return false;
      }
      if (puzzle[k][m] != word[l]) {
        return false;
      }
      ++l;
    }
  }
  start.push_back(i);
  start.push_back(j);
  end.push_back(k);
  end.push_back(m);
  return true;
}

bool checkSouth(const vector<vector<char>> & puzzle, string word,
    vector<int> &start, vector<int> &end, int i, int j) {
  // k moves along i
  int k = 0;
  int l = 1;
  for (k = i + 1; k < i + word.size() - 1; k++) {
    if (k >= puzzle.size()) {
      return false;
    }
    if (puzzle[k][j] != word[l]) {
      return false;
    }
    ++l;
  }
  start.push_back(i);
  start.push_back(j);
  end.push_back(k);
  end.push_back(j);
  return false;
}


bool checkSouthWest(const vector<vector<char>> & puzzle, string word,
    vector<int> &start, vector<int> &end, int i, int j) {
  // k moves along i, m moves along j
  int k = 0;
  int l = 1;
  int m = 0;
  for (k = i + 1; k < i + word.size() - 1; k++) {
    for (m = j - 1; m < j + word.size() - 1; m--) {
      if (k >= puzzle.size() || m < 0) {
        return false;
      }
      if (puzzle[k][m] != word[l]) {
        return false;
      }
      ++l;
    }
  }
  start.push_back(i);
  start.push_back(j);
  end.push_back(k);
  end.push_back(m);
  return true;
}

bool checkWest(const vector<vector<char>> & puzzle, string word,
    vector<int> &start, vector<int> &end, int i, int j) {
  // k moves along j
  int k = 0;
  int l = 1;
  for (k = j - 1; k < j + word.size() - 1; k--) {
    if (k < 0) {
      return false;
    }
    if (puzzle[i][k] != word[l]) {
      return false;
    }
    ++l;
  }
  start.push_back(i);
  start.push_back(j);
  end.push_back(i);
  end.push_back(k);
  return false;
}

bool checkNorthWest(const vector<vector<char>> & puzzle, string word,
    vector<int> &start, vector<int> &end, int i, int j) {
  // k moves along i, m moves along j
  int k = 0;
  int l = 1;
  int m = 0;
  for (k = i - 1; k < i + word.size() - 1; k--) {
    for (m = j - 1; m < j + word.size() - 1; m--) {
      if (k < 0 || m < 0) {
        return false;
      }
      if (puzzle[k][m] != word[l]) {
        return false;
      }
      ++l;
    }
  }
  start.push_back(i);
  start.push_back(j);
  end.push_back(k);
  end.push_back(m);
  return true;
}
