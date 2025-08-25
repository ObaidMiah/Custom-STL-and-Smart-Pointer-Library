#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <algorithm>
#include <cstdlib>

template<typename T>
class Vector {
public:
    Vector();                               // Default constructor
    Vector(size_t count, const T& value);   // Constructor with count and value
    Vector(const Vector& other);            // Copy constructor
    Vector(Vector&& other) noexcept;        // Move constructor

    ~Vector();                             // Destructor

    bool empty() const noexcept;           // Check if vector is empty
    size_t size() const noexcept;          // Get number of elements
    size_t capacity() const noexcept;      // Get current capacity
    void reserve(size_t new_capacity);     // Reserve memory for new capacity
    
    void clear() noexcept;                 // Clear vector elements

    private:
    T* m_data;           // Pointer to the dynamically allocated array
    size_t m_size;       // Current number of elements
    size_t m_capacity;   // Current capacity of the vector

    void reallocate(size_t new_capacity); // Reallocate memory
};

// Implementation
#include "vector.hpp"

#endif // VECTOR_H