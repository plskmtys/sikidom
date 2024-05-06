#ifndef SIKIDOM_MYTOMB_HPP
#define SIKIDOM_MYTOMB_HPP

#include <cstddef>
#include <stdexcept>

template<class T>
class Tomb {
    T* t;
    size_t currentSize;
    size_t currentCapacity;

public:
    class iterator;
    class const_iterator;

    explicit Tomb();

    explicit Tomb(const T& value, size_t n = 0); 
    
    iterator begin();

    iterator end();

    const_iterator cbegin() const;

    const_iterator cend() const;

    size_t size() const;

    size_t capacity() const;

    T& at(const size_t i);

    T& operator[](const size_t i) { return at(i); }

    const T& at(const size_t i) const;

    const T& operator[](const size_t i) const { return at(i); } 

    void resize(size_t newSize, const T& value = T());

    void add(const T& element);

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
            else throw std::runtime_error("Érvénytelen dereferálás");
        }

        T* operator->() const { return &operator*(); }
    };

    class const_iterator : public iterator {
    public:
        const_iterator() {}

        const_iterator(const Tomb& a, size_t ix = 0) : iterator(const_cast<Tomb&>(a), ix) {}

        const T& operator*() const { return iterator::operator*(); }

        const T* operator->() const { return &operator*(); }
    };

    virtual ~Tomb() { delete[] t; }
};

#endif
