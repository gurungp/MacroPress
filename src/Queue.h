#pragma once
#include <iostream>

template <typename T> class Queue {
public:
  Queue(int s) : size(s), arr(new T[s]) {
    // std::cout << "Queue constructor called " << std::endl;
  }
  Queue(const Queue &other) : size(other.size), arr(new T[other.size]) {
    // std::cout << "Copy constructor called " << std::endl;
    for (int i = 0; i < size; i++)
      arr[i] = other.arr[i];
  }

  Queue &operator=(const Queue &other) {
    // std::cout << "Queue copy assignment called" << std::endl;
    if (this == &other) {
      return *this; // handle self assignment
    }

    delete[] arr;

    // Allocate new memory and copy elements
    arr = new T[size];
    size = other.size;
    front = other.front;
    rear = other.rear;
    count = other.count;
    for (int i = 0; i < size; ++i) {
      arr[i] = other.arr[i];
    }
    return *this;
  }
  Queue(Queue &&other)
      : size(other.size), arr(other.arr), front(other.front), rear(other.rear),
        count(other.count) {
    // std::cout << "Move constructor called " << std::endl;
    other.arr = nullptr;
    other.size = other.front = other.rear = other.count = 0;
  }

  T &operator[](int i) { return arr[i]; }

  ~Queue() {
    // std::cout << "Queue destructor called " << std::endl;
    delete[] arr;
  }

  void enqueue(T element) {
    if (arr == nullptr) {
      std::cout << "Queue uninitialized" << std::endl;
      return;
    }

    if (rear == front && count != 0) // front always should be in front if there
                                     // are elements added already
    {
      front = ((front + 1) % size);
    }

    arr[rear % size] = element;
    rear = (rear + 1) % size;

    count++;
    if (count >= size + 1)
      count = size;
  }

  T dequeue() {
    if (isEmpty()) {
      throw std::underflow_error("Queue is empty");
    }

    T element = arr[front];
    front = (front + 1) % size;
    count--;
    if (front == rear && !isEmpty())
      rear = (rear + 1) % size;
    return element;
  }

  bool isEmpty() {
    if (count == 0)
      return true;
    else
      return false;
  }

public:
  T *arr;
  int size;
  int rear = 0;
  int front = 0;
  int count = 0;
};
