// Copyright 2021 <Ethan Adams>
#include "./ArrayList.h"

template <class U>
ostream& operator<<(ostream & os, ArrayList<U> a) {
  os << "[";
  for (int i = 0; i < a.getSize(); i++) {
    os << a.getData(i) << " ";
  }
  os << "]";
  return os;
}

template <class T>
ArrayList<T>::ArrayList() {
  size = 0;
  data = new T[size];
}

template <class T>
ArrayList<T>::ArrayList(int size, T val) {
  this->size = size;
  data = new T[size];
  for (int i = 0; i <size; i++) {
    data[i] = val;
  }
}

template <class T>
ArrayList<T>::ArrayList(const ArrayList<T> & copy) {
  setSize(copy.getSize());
  data = new T[size];
  for (int i = 0; i < size; i++) {
    data[i] = copy[i];
  }
}

template <class T>
ArrayList<T>::~ArrayList() {
  delete [] data;
}

template <class T>
void ArrayList<T>::setSize(int size) {
  if (size >= 0) {
    this->size = size;
  } else {
    std::cout << "Incorrect size\n";
    exit(1);
  }
}

template <class T>
int ArrayList<T>::getSize() const {
  return size;
}

template <class T>
T ArrayList<T>::getData(int index) const {
  if (index >= 0 && index < size) {
    return data[index];
  } else {
    std::cout << "Invalid Index\n";
    exit(0);
  }
}

template <class T>
T ArrayList<T>::operator[](int index) const {
  if (index >= 0 && index < size) {
    return data[index];
  } else {
    std::cout << "Invalid Index\n";
    exit(0);
  }
}

template <class T>
T& ArrayList<T>::operator[](int index) {
  return data[index];
}

template <class T>
const ArrayList<T> & ArrayList<T>::operator=(const ArrayList<T> rhs) {
  size = rhs.getSize();
  delete [] data;
  data = new T[size];
  for (int i = 0; i < size; i++) {
    data[i] = rhs[i];
  }
  return *this;
}

template <class T>
void ArrayList<T>::print() const {
  for (int i = 0; i < size; i++) {
    std::cout << data[i] << " ";
  }
  std::cout << "\n";
}

// Start of new functions

template <class T>
bool ArrayList<T>::operator!=(const ArrayList<T> & rhs) const {
  if (size == rhs.getSize()) {
    for (int i = 0; i < size; i++) {
      if (data[i] != rhs.data[i]) {
        return true;
      }
    }
    return false;
  }
  return true;
}

template <class T>
ArrayList<T> ArrayList<T>::operator+(T val) const {
  ArrayList ret(*this);
  for (int i = 0; i < size; i++) {
    ret[i] += val;
  }
  return ret;
  // return *this;
}

template <class T>
ArrayList<T> ArrayList<T>::operator+(const ArrayList<T> & rhs) const {
  if (size != rhs.size)
    return *this;
  ArrayList ret(*this);
  for (int i = 0; i < size; i++) {
    ret[i] += rhs.data[i];
  }
  return ret;
  // return *this;
}

template <class T>
ArrayList<T> & ArrayList<T>::operator--() {
  if (size == 0)
    return *this;
  T *temp = data;
  data = new T[size-1];
  for (int i = 0; i < size-1; i++) {
    data[i] = temp[i];
  }
  delete [] temp;
  --size;
  return *this;
}

template <class T>
ArrayList<T> ArrayList<T>::operator--(int) {
  if (size == 0)
    return *this;
  ArrayList ret(*this);
  T *temp = data;
  data = new T[size-1];
  for (int i = 0; i < size-1; i++) {
    data[i] = temp[i];
  }
  delete [] temp;
  --size;
  return ret;
}

template <class T>
void ArrayList<T>::operator+=(T val) {
  T *temp = data;
  data = new T[size+1];
  for (int i = 0; i < size; i++) {
    data[i] = temp[i];
  }
  data[size] = val;
  ++size;
  delete [] temp;
  return;
}

template <class T>
void ArrayList<T>::operator+=(const ArrayList<T> & rhs) {
  T *temp = data;
  data = new T[size+rhs.size];
  for (int i = 0; i < size; i++) {
    data[i] = temp[i];
  }
  int counter = 0;
  for (int i = size; i < size+rhs.size; i++) {
    data[i] = rhs[counter];
    counter++;
  }
  delete [] temp;
  size += rhs.size;
  return;
}

template <class T>
ArrayList<T> ArrayList<T>::operator*(int val) const {
  ArrayList ret(size * val, 0);
  int counter = 0;
  for (int i = 0; i < size*val; i += size) {
    for (int j = 0; j < size; j++) {
      ret[counter] = data[j];
      ++counter;
    }
  }
  return ret;
  // return *this;
}

template <class T>
ArrayList<T> ArrayList<T>::operator/(int val) const {
  ArrayList ret(size/val, 0);
  for (int i = 0; i < size/val; i++) {
    ret[i] = data[i];
  }
  return ret;
  // return *this;
}
