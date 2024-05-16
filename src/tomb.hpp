#ifndef MYTOMB
#define MYTOMB

#include <stdexcept>
#include <type_traits>

template <class T> class Tomb {
  T *t;                   // dynamic array to store elements
  size_t currentSize;     // current number of elements
  size_t currentCapacity; // current capacity of the array

public:
  class iterator;
  class const_iterator;

  Tomb() : t(new T[1]), currentSize(0), currentCapacity(1) {}

  iterator begin() { return iterator(t, 0); }
  iterator end() { return iterator(t, currentSize); }

  const_iterator begin() const { return const_iterator(t, 0); }
  const_iterator end() const { return const_iterator(t, currentSize); }

  size_t size() const { return currentSize; }

  size_t capacity() const { return currentCapacity; }

  T &at(const size_t i) {
    if (i >= currentSize)
      throw std::out_of_range("Array.at(): invalid index");
    return t[i];
  }

  T &operator[](const size_t i) { return at(i); }

  const T &at(const size_t i) const {
    if (i >= currentSize)
      throw std::out_of_range("Array.at(): invalid index");
    return t[i];
  }

  const T &operator[](const size_t i) const { return at(i); }

  void resize(size_t newSize) {
    if (newSize > currentCapacity) {
      T* newT = new T[newSize * 2];
      for (size_t i = 0; i < currentSize; ++i) {
        newT[i] = t[i];  // Copy the pointers
      }
      delete[] t;
      t = newT;
      currentCapacity = newSize * 2;
    }
  }

  void push_back(T value) {
    if (currentSize == currentCapacity) {
      resize(currentSize * 2);
    }
    t[currentSize++] = value;
  }

  int find(const T& value) const {
    for (size_t i = 0; i < currentSize; ++i) {
      if (t[i] == value) {
        return i;
      }
    }
    return -1;
}

  class iterator {
    T *p;
    size_t idx;

  public:
    iterator(T *p = nullptr, size_t idx = 0) : p(p), idx(idx) {}

    T &operator*() { return p[idx]; }

    iterator &operator++() {
      ++idx;
      return *this;
    }

    bool operator!=(const iterator &other) const { return idx != other.idx; }
  };

  class const_iterator {
    const T *p;
    size_t idx;

  public:
    const_iterator(const T *p = nullptr, size_t idx = 0) : p(p), idx(idx) {}

    const T &operator*() const { return p[idx]; }

    const_iterator &operator++() {
      ++idx;
      return *this;
    }

    bool operator!=(const const_iterator &other) const { return idx != other.idx; }
  };

  virtual ~Tomb() {
    //for (size_t i = 0; i < currentSize; ++i) {
    //  delete t[i];
    //}
    delete[] t;
  }
};

#endif
