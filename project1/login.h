// Author: Ethan Adams
// Email: epadams@email.sc.edu
// Section #: 001
// Copyright 2021 Ethan Adams
// Modified from template code @coleca24 GitHub
#ifndef LOGIN_H_
#define LOGIN_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using std::string;

const int COLS = 4;
const int ROWS = 5;

void printUsers(const string data[ROWS][COLS]);
bool readUsers(string fh, string data[ROWS][COLS]);
char displayOptions();
bool validateOption(char option);
void executeOption(char option, string data[ROWS][COLS], string);
int searchForUser(string name, const string data[ROWS][COLS]);

int findAllUsers(string title, const string data[ROWS][COLS]);
bool deleteUser(string name, string data[ROWS][COLS], string fh);
string generatePassword();
string generateEmail(string name);
int checkEmpty(const string data[ROWS][COLS]);
void addUser(int index, string name, string title,
             string data[ROWS][COLS], string fh);

bool readUsers(string fh, string data[ROWS][COLS]) {
  std::ifstream in(fh);
  bool bool1 = false;
  if (in.is_open()) {
    bool1 = true;
    /* first for loop goes through a line, uses stringstream to hold the line
     * then the second loop uses stringstream as the input,
     * and breaks it apart into the correct index for the array
     */ 
    for (int i = 0; i < ROWS; i++) {
      string line;
      std::getline(in, line);
      std::stringstream ss(line);
      for (int j = 0; j < COLS; j++) {
        string value;
        std::getline(ss, value, ',');
        data[i][j] = value;
      }
    }
  } else {
    std::cout << "File does not exist or did not open\n";
    bool1 = false;
  }
  in.close();
  return bool1;
}

void printUsers(const string data[ROWS][COLS]) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      std::cout << data[i][j] << "\t";
    }
    std::cout << std::endl;
  }
}

bool validateOption(char option) {
  // if (strchr("EePpSsFfAaDd", option) != null)
  if (option == 'E' || option == 'e' ||
      option == 'P' || option == 'p' ||
      option == 'S' || option == 's' ||
      option == 'F' || option == 'f' ||
      option == 'A' || option == 'a' ||
      option == 'D' || option == 'd')
    return true;
  else
    return false;
}

char displayOptions() {
  std::cout << "\nPlease choose one of the following options:\n" <<
    "P(or p): Print data\n" <<
    "S(or s): Search data by name\n" <<
    "F(or f): Find all in data with a certain job title\n" <<
    "A(or a): Add a new user\n" <<
    "D(or d): Delete an existing user\n" <<
    "E(or e): End session\n";
  char input;
  bool bool1 = false;
  while (bool1 == false) {
    std::cin >> input;
    if (validateOption(input)) {
      bool1 = true;
    } else {
     std::cout << "Your input was not valid. Try again\n";
    }
  }
  return input;
}

void executeOption(char option, string data[ROWS][COLS], string fn) {
  if (option == 'P' || option == 'p') {
    printUsers(data);
  } else {
      if (option == 'S' || option == 's') {
        string first, last, full;
        std::cout << "Please enter a first name: ";
        std::cin >> first;
        std::cout << "Please enter a last name: ";
        std::cin >> last;
        full = first + " " + last;
        int index = searchForUser(full, data);
        if (index != -1)
          std::cout << "User found at index " << index << "\n";
        else
          std::cout << "User was not found." << "\n";
        for (int i = 0; i < COLS; i++) {
          if (index == -1)
            break;
          std::cout << data[index][i] << ", ";
        }
  } else {
      if (option == 'F' || option =='f') {
        string jobTitle;
        std::cout << "Please enter a job title to search for: \n";
        std::cin >> jobTitle;
        int jT = findAllUsers(jobTitle, data);
  }   else {
        if (option == 'A' || option == 'a') {
          string first, last, full, jTitle;
          int avail = checkEmpty(data);
          std::cout << "Please enter a first name: ";
          std::cin >> first;
          std::cout << "Please enter a last name: ";
          std::cin >> last;
          full = first + " " + last;
          std::cout << "Enter Job Title: ";
          std::cin >> jTitle;
          addUser(avail, full, jTitle, data, fn);
  }     else {
          if (option == 'D' || option == 'd') {
            bool myB;
            string first, last, full;
            std::cout << "Please enter a first name: ";
            std::cin >> first;
            std::cout << "Please enter a last name: ";
            std::cin >> last;
            full = first + " " + last;
            myB = deleteUser(full, data, fn);
          }
        }
      }
    }
  }
}

int searchForUser(string name, const string data[ROWS][COLS]) {
  for (int i = 0; i < ROWS; i++) {
    if (data[i][0] == name)
      return i;
  }
  return -1;
}

int findAllUsers(string title, const string data[ROWS][COLS]) {
  int numOfUsers = 0;
  for (int i = 0; i < ROWS; i++) {
    if (data[i][3] == title) {
      numOfUsers++;
    }
  }
  if (numOfUsers != 0) {
    printf("There were %i users with job title %s\n",
        numOfUsers, title.c_str());
  } else if (numOfUsers == 0) {
    printf("No users w/ job title: %s\n", title.c_str());
    return 0;
  }
  return numOfUsers;
}

bool deleteUser(string name, string data[ROWS][COLS], string fh) {
  bool tracker = false;
  for (int i = 0; i < ROWS; i++) {
    if (data[i][0] == name) {
      tracker = true;
      for (int j = 0; j < COLS; j++) {
        data[i][j] = "NULL";
      }
    }
  }
  if (tracker == 1) {
    printf("User %s deleted.\n", name.c_str());
  } else if (tracker == 0) {
    printf("User not found\n");
  }
  // Overwriting file
  std::ofstream out(fh);
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS - 1; j++) {
      out << data[i][j] << ",";
    }

    out << data[i][3] << "\n";
  }
  out.close();
  return tracker;
}

string generatePassword() {
  string pass;
  std::stringstream ss;
  srand(time(NULL));
  char num = rand() % 10 + 48;
  char upper = rand() % 26 + 65;
  ss << num << upper;
  for (int i = 0; i < 6; i++) {
    char character = rand() % 26 + 97;
    ss << character;
  }
  ss >> pass;
  std::cout << "Generating password...\n" << "Password: " << pass << "\n";
  return pass;
}

string generateEmail(string name) {
  string first, last, email;
  std::stringstream ss(name);
  std::getline(ss, first, ' ');
  std::getline(ss, last);
  email = first + last + "@email.com";
  std::cout << "Generating email...\n" << "Email: " << email << "\n";
  return email;
}

int checkEmpty(const string data[ROWS][COLS]) {
  int tracker = -1;
  for (int i = 0; i < ROWS; i++) {
    if (data[i][0] == "NULL") {
      tracker = i;
      break;
    }
  }
  return tracker;
}

void addUser(int index, string name, string title,
             string data[ROWS][COLS], string fh) {
  if (index == -1) {
    std::cout << "Database full (max 5 users)\n";
    return;
  }
  data[index][0] = name;
  data[index][1] = generateEmail(name);
  data[index][2] = generatePassword();
  data[index][3] = title;
  // Overwriting file
  std::ofstream out(fh);
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS - 1; j++) {
      out << data[i][j] << ",";
    }
    out << data[i][3] << "\n";
  }
  out.close();
}
#endif  // LOGIN_H_
