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

    T& operator[](size_t index);           // Access element at index 
    T* data() noexcept;                    // Access data pointer
    T& at(size_t index);                   // Access element at index
    T& front();                            // Access first element
    T& back();                             // Access last element
    
    void push_back(const T& value);        // Add element to end (copy)
    void push_back(T&& value);             // Add element to end (move)
    void pop_back();                       // Remove last element

    bool empty() const noexcept;           // Check if vector is empty
    size_t size() const noexcept;          // Get number of elements
    size_t capacity() const noexcept;      // Get current capacity
    void reserve(size_t new_capacity);     // Reserve memory for new capacity
    void clear() noexcept;                 // Clear vector elements
    void resize(size_t new_size);          // Resize vector to new size

    T* begin() noexcept;                   // Get iterator to first element
    T* end() noexcept;                     // Get iterator to end
    const T* cbegin() const noexcept;      // Get const iterator to first element
    const T* cend() const noexcept;        // Get const iterator to end

    bool operator==(const Vector& other) const; // Check if vectors are equal
    bool operator!=(const Vector& other) const; // Check if vectors are not equal

    Vector& operator=(const Vector& other);       // Copy assignment
    Vector& operator=(Vector&& other) noexcept;   // Move assignment
    
    private:
    T* m_data;           // Pointer to the dynamically allocated array
    size_t m_size;       // Current number of elements
    size_t m_capacity;   // Current capacity of the vector

    void reallocate(size_t new_capacity); // Reallocate memory
};

// Implementation
#include "vector.hpp"

#endif // VECTOR_H