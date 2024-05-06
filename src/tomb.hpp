#ifndef MYTOMB
#define MYTOMB

#include <stdexcept>

template<class T>
class Tomb {
    T* t; // dynamic array to store elements
    size_t currentSize; // current number of elements
    size_t currentCapacity; // current capacity of the array

public:
    class iterator;
    class const_iterator;

    explicit Tomb(size_t n = 0, const T& value = T()) : t(nullptr), currentSize(0), currentCapacity(0) {
        resize(n, value);
    }

    template <class InputIterator>
    Tomb(InputIterator first, InputIterator last) : t(nullptr), currentSize(0), currentCapacity(0) {
        resize(last - first);
        size_t i = 0;
        for (auto it = first; it != last; ++it, ++i) {
            t[i] = *it;
        }
    }

    iterator begin() {
        return iterator(*this);
    }

    iterator end() {
        return iterator(*this, currentSize);
    }

    const_iterator begin() const {
        return const_iterator(*this);
    }

    const_iterator end() const {
        return const_iterator(*this, currentSize);
    }

    size_t size() const {
        return currentSize;
    }

    size_t capacity() const {
        return currentCapacity;
    }

    T& at(size_t i) {
        if (i >= currentSize) throw std::out_of_range("Array.at(): invalid index");
        return t[i];
    }

    const T& at(size_t i) const {
        if (i >= currentSize) throw std::out_of_range("Array.at(): invalid index");
        return t[i];
    }

    void resize(size_t newSize, const T& value = T()) {
        if (newSize > currentCapacity) {
            size_t newCapacity = newSize * 2; // Double the capacity
            T* newT = new T[newCapacity];
            for (size_t i = 0; i < currentSize; ++i) {
                newT[i] = t[i];
            }
            delete[] t;
            t = newT;
            currentCapacity = newCapacity;
        }
        else if (newSize < currentSize) {
            for (size_t i = newSize; i < currentSize; ++i) {
                t[i].~T(); // Call the destructor for the removed elements
            }
        }
        for (size_t i = currentSize; i < newSize; ++i) {
            new (&t[i]) T(value); // Placement new to construct new elements
        }
        currentSize = newSize;
    }

    class iterator {
        Tomb *p;
        size_t idx;

    public:
        iterator() : p(nullptr), idx(0) {}

        iterator(Tomb& a, size_t ix = 0) : p(&a), idx(ix) {}

        iterator& operator++() {
            if (idx != p->currentSize) ++idx;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        bool operator!=(const iterator& i) const {
            return idx != i.idx;
        }

        bool operator==(const iterator& i) const {
            return !operator!=(i);
        }

        T& operator*() const {
            if (idx != p->currentSize) return p->t[idx];
            else throw std::runtime_error("Invalid dereference");
        }

        T* operator->() const {
            return &operator*();
        }
    };

    class const_iterator : public iterator {
    public:
        const_iterator() {}

        const_iterator(const Tomb& a, size_t ix = 0) : iterator(const_cast<Tomb&>(a), ix) {}

        const T& operator*() const {
            return iterator::operator*();
        }

        const T* operator->() const {
            return &operator*();
        }
    };

    virtual ~Tomb() {
        delete[] t;
    }
};

#endif
