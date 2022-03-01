// Copyright 2021 Ethan Adams
#include "./SuperString.h"

// DO NOT MODIFY START
void SuperString::print() {
    if (size != 0) {
        for (int i = 0; i < size; i++) {
            std::cout << data[i];
        }
        std::cout << "\n";
    } else {
        std::cout << "<EMPTY>\n";
    }
}

char SuperString::get(int index) {
    if (index >= 0 && index < size) {
        return data[index];
    }
    return '\0';
}

int SuperString::length() {
    return size;
}
// DO NOT MODIFY END

// PUT YOUR CODE BELOW!

SuperString::SuperString() {
  size = 0;
  data = new char[size];
}

SuperString::SuperString(std::string str) {
  size = str.length();
  data = new char[size];
  for (int i = 0; i < size; i++) {
    data[i] = str[i];
  }
}

SuperString::SuperString(int size, char val) {
  this->size = size;
  data = new char[size];
  for (int i = 0; i < size; i++) {
    data[i] = val;
  }
}

SuperString::SuperString(const SuperString& copy) {
  this->size = copy.size;
  data = new char[size];
  for (int i = 0; i < size; i++) {
    data[i] = copy.data[i];
  }
}

int SuperString::find(char c, int start) {
  for (int i = start; i < size; i++) {
    if (data[i] == c)
      return i;
  }
  return -1;
}

int SuperString::find(std::string str, int start) {
  int counter = 0;
  for (int i = start; i < size; i++) {
    if (data[i] == str.at(0)) {
      for (int j = 0; j < str.length(); j++) {
        if (data[i+j] == str.at(counter)) {
          counter++;
        } else {
          counter = 0;
        }
      }
      if (counter == str.length()) {
        return i;
      }
    }
  }
  return -1;
}

SuperString SuperString::substr(int start, int numChar) {
  SuperString emptySString;
  if ((start + numChar) > this->size || (start + numChar) < 0 || start < 0)
    return emptySString;
  SuperString sString(numChar, 'A');
  for (int i = start; i < numChar; i++) {
    sString.data[i] = this->data[i];
  }
  return sString;
}

SuperString SuperString::reverse() {
  SuperString rString(this->size, 'a');
  int counter = 0;
  for (int i = this->size-1; i > -1; i--) {
    rString.data[counter] = this->data[i];
    counter++;
  }
  return rString;
}

SuperString SuperString::replace(int start, int numChar, std::string sub) {
  SuperString emptySString;
  if ((start + numChar) > this->size || (start + numChar) < 0 || start < 0)
    return emptySString;
  std::string ret(size, ' ');
  for (int i = 0; i < size; i++) {
    ret[i] = data[i];
  }
  for (int i = 0; i < start; i++) {
    ret[i] = data[i];
  }
  for (int i = start; i < numChar; i++) {
    ret[i] = sub[i];
  }
  int counter = start;
  for (int i = start + numChar; i < size; i++) {
    ret[i] = data[i];
    counter++;
  }
  SuperString retString(ret);
  return retString;
  /*
  OLD FUNCTION
  This implementation was before the project description was updated, and used dynamic management
  Also modified the calling object's data
  int replaceSize = (size - numChar + sub.length());
  char *temp = data;
  data = new char[replaceSize];
  for (int i = 0; i < start; i++) {
    data[i] = temp[i];
  }
  for (int i = start; i < numChar; i++) {
    data[i] = sub[i];
  }
  int counter = start;
  for (int i = start + numChar; i < size; i++) {
    data[i] = temp[i];
    counter++;
  }
  delete [] temp;
  return *this;
  */
}

void SuperString::push_back(char c) {
  char *temp = data;
  data = new char[size+1];
  for (int i = 0; i < size; i++) {
    data[i] = temp[i];
  }
  data[size] = c;
  delete [] temp;
  size++;
  return;
}

void SuperString::append(std::string str) {
  char *temp = data;
  data = new char[size + str.length()];
  for (int i = 0; i < size; i++) {
    data[i] = temp[i];
  }
  int counter = 0;
  for (int i = size; i < (size + str.length()); i++) {
    data[i] = str[counter];
    counter++;
  }
  size = (size + str.length());
  delete [] temp;
  return;
}

void SuperString::append(const SuperString& obj) {
  char *temp = data;
  data = new char[size + obj.size];
  for (int i = 0; i < size; i++) {
    data[i] = temp[i];
  }
  int counter = 0;
  for (int i = size; i < (size + obj.size); i++) {
    data[i] = obj.data[counter];
    counter++;
  }
  size = (size + obj.size);
  delete [] temp;
  return;
}

void SuperString::replace(char find, char rep) {
  for (int i = 0; i < size; i++) {
    if (data[i] == find) {
      data[i] = rep;
    }
  }
  return;
}

// Bonus Methods
// TODO(epadams) finish
void SuperString::removeAll(char c) {
  return;
}

// TODO(epadams) finish
void SuperString::replace(std::string find, std::string rep) {
  return;
}

bool SuperString::isUpper() {
  for (int i = 0; i < size; i++) {
    if (data[i] < 65 || data[i] > 90) {
      return false;
    }
  }
  return true;
}

bool SuperString::isLower() {
  for (int i = 0; i < size; i++) {
    if (data[i] < 97 || data[i] > 122) {
      return false;
    }
  }
  return true;
}

// TODO(epadams) finish
// probably use stringstream/getline and check capitilization that way
bool SuperString::isTitleCase() {
  // for (int i = 0; < size; i++) {
  return true;
}

SuperString::~SuperString() {
  delete [] data;
}
