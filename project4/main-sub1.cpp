// Copyright 2021 Ethan Adams
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

using std::vector;
using std::cout;
using std::string;

void readData(vector<string> &data, string filename);
void printData(const vector<string> &data);
vector<int> findMinHamming(const vector<string> & data, string test);
void printMinDistance(const vector<string> &data, string word,
                      const vector<int> min);

int main(int argc, char **argv) {
  string filename;
  vector<string> data;
  if (argc != 2) {
    cout << "Usage: ./sub1 data.txt\n";
    exit(0);
  }
  filename = argv[1];
  readData(data, filename);
  printData(data);
  for (auto line : data) {
    vector<int> ret;
    ret = findMinHamming(data, line);
    printMinDistance(data, line, ret);
  }
  return 0;
}

void readData(vector<string> &data, string filename) {
  std::ifstream in(filename);
  if (in.is_open()) {
    string line;
    while (getline(in, line)) {
      data.push_back(line);
    }
  } else {
    std::cout << "File could not be opened\n";
  }
  return;
}

void printData(const vector<string> &data) {
  for (auto i : data) {
    cout << i << "\n";
  }
  return;
}

vector<int> findMinHamming(const vector<string> & data, string test) {
  vector<int> ret;
  int min = 0;
  int minIndex = 0;
  for (int i = 0; i < data.size(); i++) {
    int distance = 0;
    int lesser = 0;
    if (data[i].length() < test.length()) {
      lesser = data[i].length();
    } else {
      lesser = test.length();
    }
    for (int j = 0; j < lesser; j++) {
      if (data[i][j] != test[j]) {
        ++distance;
      }
    }
    distance += (std::max(data[i].length(), test.length()) -
      std::min(data[i].length(), test.length()));
    if (distance != 0) {
      if (min == 0)
        min = distance;
      if (distance < min) {
        min = distance;
        minIndex = i;
      }
    }
  }

  ret.push_back(minIndex);
  ret.push_back(min);
  return ret;
}

void printMinDistance(const vector<string> &data, string word,
                      const vector<int> min) {
  std::cout << "The minimum hamming distance for " << word << " is " << min[1]
    << " (matching word: " << data[min[0]] << ")\n";
  return;
}
