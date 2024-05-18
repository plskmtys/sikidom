#ifndef MYTOMB
#define MYTOMB

#include <stdexcept>

/** @brief Generikus Dinamikus tömb osztály.
 * A Tomb osztály egy dinamikus tömböt reprezentál, melynek mérete a felhasználó által nem korlátozott.
 * 
*/
template <class T> class Tomb {
  /** @brief A dinamikusan foglalt tömb elejére mutató pointer.
  */
  T *t;
  /** @brief A tömb aktuális mérete.
  */
  size_t currentSize;
  /** @brief A tömb aktuális kapacitása.
  */
  size_t currentCapacity;

public:
  class iterator;
  class const_iterator;

  /** @brief Tomb osztály konstruktora.
   * A konstruktor létrehoz egy üres tömböt, 1 kapacitással.
  */
  Tomb() : t(new T[1]), currentSize(0), currentCapacity(1) {}

  /** @brief begin iterator.
   * @return Az első elemre mutató iterator.
   * 
  */
  iterator begin() { return iterator(t, 0); }

  /** @brief end iterator.
   * @return Az utolsó elem után mutató iterator.
   * 
  */
  iterator end() { return iterator(t, currentSize); }

  /** @brief begin const_iterator.
   * @return Az első elemre mutató const_iterator.
   * 
  */
  const_iterator begin() const { return const_iterator(t, 0); }

  /** @brief end const_iterator.
   * @return Az utolsó elem után mutató const_iterator.
   * 
  */
  const_iterator end() const { return const_iterator(t, currentSize); }

  /** @brief Tomb méretét visszaado függvény.
   * @return A tömb mérete.
  */
  size_t size() const { return currentSize; }

  /** @brief Tomb kapacitásat visszaado függvény.
   * @return A tömb kapacitása.
  */
  size_t capacity() const { return currentCapacity; }

  /** @brief Tomb at függvénye.
   * @param i Az index, ahol lévő az elemet szeretnénk elérni.
   * @return Az i-edik elem.
  */
  T &at(const size_t i) {
    if (i >= currentSize)
      throw std::out_of_range("Array.at(): invalid index");
    return t[i];
  }

  /** @brief Tomb operator[] függvénye.
   * @param i Az index, ahol lévő elemet szeretnénk elérni.
   * @return Az i-edik elem.
  */
  T &operator[](const size_t i) { return at(i); }

  /** @brief Tomb const at függvénye.
   * @param i Az index, ahol lévő elemet szeretnénk elérni.
   * @return const referencia az i-edik elemre.
  */
  const T &at(const size_t i) const {
    if (i >= currentSize)
      throw std::out_of_range("Array.at(): invalid index");
    return t[i];
  }

  /** @brief Tomb const operator[] függvénye.
   * @param i Az index, ahol lévő elemet szeretnénk elérni.
   * @return const referencia az i-edik elemre.
  */
  const T &operator[](const size_t i) const { return at(i); }

  /** @brief Tomb resize függvénye.
   * A függvény a tömb méretét növeli a megadott értékkel.
   * @param newSize A novelendo meret.
  */
  void resize(size_t newSize) {
    if (newSize > currentCapacity) {
      T* newT = new T[newSize * 2];
      for (size_t i = 0; i < currentSize; ++i) {
        newT[i] = t[i];
      }
      delete[] t;
      t = newT;
      currentCapacity = newSize * 2;
    }
  }

  /** @brief Tomb push_back függvénye.
   * A függvény a tömb végére fűz egy elemet.
   * @param value Az érték, melyet a tömb végére fűzünk.
  */
  void push_back(T value) {
    if (currentSize == currentCapacity) {
      resize(currentSize * 2);
    }
    t[currentSize++] = value;
  }

  /** @brief Tomb find függvénye.
   * A függvény megkeresi az első olyan elemet, mely megegyezik az értékkel.
   * @param value Az érték, melyet keresünk.
   * @return Az első olyan elem indexe, mely megegyezik az értékkel, ha nincs ilyen, akkor -1.
  */
  int find(const T& value) const {
    for (size_t i = 0; i < currentSize; ++i) {
      if (t[i] == value) {
        return i;
      }
    }
    return -1;
  }

  /** @brief iterator osztály.
   * Az iterator osztály a Tomb osztály iteratora.
   * 
  */
  class iterator {
    /** @brief Az iterator aktuális elemre mutató pointere.
     * 
    */
    T *p;

    /** @brief Az iterator aktuális indexe.
     * 
    */
    size_t idx;

  public:
    /** @brief iterator konstruktora.
     * @param p Az iterator aktuális elemre mutató pointere.
     * @param idx Az iterator aktuális indexe.
    */
    iterator(T *p = nullptr, size_t idx = 0) : p(p), idx(idx) {}

    /** @brief operator* függvény.
     * @return Az iterator aktuális elemre mutató referencia.
    */
    T &operator*() { return p[idx]; }

    /** @brief operator++ függvény.
     * @return Az iterator az aktuális elem után mutató referencia.
    */
    iterator &operator++() {
      ++idx;
      return *this;
    }

    /** @brief operator!= függvény.
     * @param other A másik iterator.
     * @return Igaz, ha a két iterator nem egyezik meg, egyébként hamis.
    */
    bool operator!=(const iterator &other) const { return idx != other.idx; }
  };

  /** @brief const_iterator osztály.
   * Az const_iterator osztály a Tomb osztály const_iteratora.
   * 
  */
  class const_iterator {
    /** @brief Az const_iterator aktuális elemre mutató pointere.
     * 
    */
    const T *p;

    /** @brief Az const_iterator aktuális indexe.
     * 
    */
    size_t idx;

  public:
    /** @brief const_iterator konstruktora.
     * @param p Az const_iterator aktuális elemre mutató pointere.
     * @param idx Az const_iterator aktuális indexe.
    */
    const_iterator(const T *p = nullptr, size_t idx = 0) : p(p), idx(idx) {}

    /** @brief operator* függvény.
     * @return Az const_iterator aktuális elemre mutató referencia.
    */
    const T &operator*() const { return p[idx]; }

    /** @brief operator++ függvény.
     * @return Az const_iterator az aktuális elem után mutató referencia.
    */
    const_iterator &operator++() {
      ++idx;
      return *this;
    }

    /** @brief operator!= függvény.
     * @param other A másik const_iterator.
     * @return Igaz, ha a ket const_iterator nem egyezik meg, egyébként hamis.
    */
    bool operator!=(const const_iterator &other) const { return idx != other.idx; }
  };

  /** @brief Tomb destruktora.
   * A destruktor felszabadítja a tömbot.
  */
  virtual ~Tomb() {
    delete[] t;
  }
};

#endif
