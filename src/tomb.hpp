#ifndef MYTOMB
#define MYTOMB

#include <stdexcept>

/** @brief Generikus Dinamikus tomb osztaly.
 * A Tomb osztaly egy dinamikus tombot reprezental, melynek merete a felhasznalo altal nem korlatozott.
 * 
*/
template <class T> class Tomb {
  /** @brief A tomb dinamikus tomb.
  */
  T *t;
  /** @brief A tomb aktualis merete.
  */
  size_t currentSize;
  /** @brief A tomb aktualis kapacitasa.
  */
  size_t currentCapacity;

public:
  class iterator;
  class const_iterator;

  /** @brief Tomb osztaly konstruktora.
   * A konstruktor letrehoz egy ures tombot, 1 kapacitassal.
  */
  Tomb() : t(new T[1]), currentSize(0), currentCapacity(1) {}

  /** @brief begin iterator.
   * @return Az elso elemre mutato iterator.
   * 
  */
  iterator begin() { return iterator(t, 0); }

  /** @brief end iterator.
   * @return Az utolso elem utan mutato iterator.
   * 
  */
  iterator end() { return iterator(t, currentSize); }

  /** @brief begin const_iterator.
   * @return Az elso elemre mutato const_iterator.
   * 
  */
  const_iterator begin() const { return const_iterator(t, 0); }

  /** @brief end const_iterator.
   * @return Az utolso elem utan mutato const_iterator.
   * 
  */
  const_iterator end() const { return const_iterator(t, currentSize); }

  /** @brief Tomb meretet visszaado fuggveny.
   * @return A tomb merete.
  */
  size_t size() const { return currentSize; }

  /** @brief Tomb kapacitasat visszaado fuggveny.
   * @return A tomb kapacitasa.
  */
  size_t capacity() const { return currentCapacity; }

  /** @brief Tomb at fuggvenye.
   * @param i Az index, melyre az elemet szeretnenk elerni.
   * @return Az i-edik elem.
  */
  T &at(const size_t i) {
    if (i >= currentSize)
      throw std::out_of_range("Array.at(): invalid index");
    return t[i];
  }

  /** @brief Tomb operator[] fuggvenye.
   * @param i Az index, melyre az elemet szeretnenk elerni.
   * @return Az i-edik elem.
  */
  T &operator[](const size_t i) { return at(i); }

  /** @brief Tomb const at fuggvenye.
   * @param i Az index, melyre az elemet szeretnenk elerni.
   * @return const referencia az i-edik elemre.
  */
  const T &at(const size_t i) const {
    if (i >= currentSize)
      throw std::out_of_range("Array.at(): invalid index");
    return t[i];
  }

  /** @brief Tomb const operator[] fuggvenye.
   * @param i Az index, melyre az elemet szeretnenk elerni.
   * @return const referencia az i-edik elemre.
  */
  const T &operator[](const size_t i) const { return at(i); }

  /** @brief Tomb resize fuggvenye.
   * A fuggveny a tomb meretet noveli a megadott ertekkel.
   * @param newSize A novelendo meret.
  */
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

  /** @brief Tomb push_back fuggvenye.
   * A fuggveny a tomb vegere fuz egy elemet.
   * @param value Az ertek, melyet a tomb vegere fuzunk.
  */
  void push_back(T value) {
    if (currentSize == currentCapacity) {
      resize(currentSize * 2);
    }
    t[currentSize++] = value;
  }

  /** @brief Tomb find fuggvenye.
   * A fuggveny megkeresi az elso olyan elemet, mely megegyezik az ertekkel.
   * @param value Az ertek, melyet keresunk.
   * @return Az elso olyan elem indexe, mely megegyezik az ertekkel, ha nincs ilyen, akkor -1.
  */
  int find(const T& value) const {
    for (size_t i = 0; i < currentSize; ++i) {
      if (t[i] == value) {
        return i;
      }
    }
    return -1;
  }

  /** @brief iterator osztaly.
   * Az iterator osztaly a Tomb osztaly iteratora.
   * 
  */
  class iterator {
    /** @brief Az iterator aktualis elemre mutato pointere.
     * 
    */
    T *p;

    /** @brief Az iterator aktualis indexe.
     * 
    */
    size_t idx;

  public:
    /** @brief iterator konstruktora.
     * @param p Az iterator aktualis elemre mutato pointere.
     * @param idx Az iterator aktualis indexe.
    */
    iterator(T *p = nullptr, size_t idx = 0) : p(p), idx(idx) {}

    /** @brief operator* fuggveny.
     * @return Az iterator aktualis elemre mutato referencia.
    */
    T &operator*() { return p[idx]; }

    /** @brief operator++ fuggveny.
     * @return Az iterator az aktualis elem utan mutato referencia.
    */
    iterator &operator++() {
      ++idx;
      return *this;
    }

    /** @brief operator!= fuggveny.
     * @param other A masik iterator.
     * @return Igaz, ha a ket iterator nem egyezik meg, egyebkent hamis.
    */
    bool operator!=(const iterator &other) const { return idx != other.idx; }
  };

  /** @brief const_iterator osztaly.
   * Az const_iterator osztaly a Tomb osztaly const_iteratora.
   * 
  */
  class const_iterator {
    /** @brief Az const_iterator aktualis elemre mutato pointere.
     * 
    */
    const T *p;

    /** @brief Az const_iterator aktualis indexe.
     * 
    */
    size_t idx;

  public:
    /** @brief const_iterator konstruktora.
     * @param p Az const_iterator aktualis elemre mutato pointere.
     * @param idx Az const_iterator aktualis indexe.
    */
    const_iterator(const T *p = nullptr, size_t idx = 0) : p(p), idx(idx) {}

    /** @brief operator* fuggveny.
     * @return Az const_iterator aktualis elemre mutato referencia.
    */
    const T &operator*() const { return p[idx]; }

    /** @brief operator++ fuggveny.
     * @return Az const_iterator az aktualis elem utan mutato referencia.
    */
    const_iterator &operator++() {
      ++idx;
      return *this;
    }

    /** @brief operator!= fuggveny.
     * @param other A masik const_iterator.
     * @return Igaz, ha a ket const_iterator nem egyezik meg, egyebkent hamis.
    */
    bool operator!=(const const_iterator &other) const { return idx != other.idx; }
  };

  /** @brief Tomb destruktora.
   * A destruktor felszabaditja a tombot.
  */
  virtual ~Tomb() {
    delete[] t;
  }
};

#endif
