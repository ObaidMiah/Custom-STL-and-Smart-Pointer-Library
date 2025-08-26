#ifndef VECTOR_HPP
#define VECTOR_HPP

template<typename T>
void Vector<T>::reallocate(size_t new_capacity) {
    //Allocate new memory 
    T* new_data = nullptr; 

    if(new_capacity > 0)
    {
        new_data = static_cast<T*>(std::malloc(new_capacity * sizeof(T))); 

        if(!new_data)
        {
            throw std::bad_alloc(); 
        }
    }

    //Copy over data
    for(size_t i = 0; i < m_size; ++i)
    {
        new (new_data+i) T(std::move(m_data[i]));
        m_data[i].~T(); 
    }

    //Release old memory 
    std::free(m_data); 
    m_data = new_data; 
    m_capacity = new_capacity; 
}

// Constructors
template<typename T>
Vector<T>::Vector() : m_data(nullptr), m_size(0), m_capacity(0) {}

template<typename T>
Vector<T>::Vector(size_t count, const T& value) : m_data(nullptr), m_size(0), m_capacity(0) {
    if(count > 0)
    {
        reserve(count); 

        for(size_t i = 0; i < count; ++i)
        {
            new (m_data+i) T(value); 
        }

        m_size = count; 
    }
}

template<typename T>
Vector<T>::Vector(const Vector& other) : m_data(nullptr), m_size(0), m_capacity(0) {
    if(other.m_size > 0)
    {
        reserve(other.m_capacity); 

        for(size_t i = 0; i < other.m_size; ++i)
        {
            new (m_data+i) T(other.m_data[i]);
        }

        m_size = other.m_size; 
    }
}

template<typename T>
Vector<T>::Vector(Vector&& other) noexcept 
    : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity) {
    other.m_data = nullptr; 
    other.m_size = 0; 
    other.m_capacity = 0; 
}

// Destructor
template<typename T>
Vector<T>::~Vector() {
    if(m_data != nullptr)
    {
        clear(); 
        std::free(m_data);
    }
}

// Element access
template<typename T>
T& Vector<T>::operator[](size_t index) {
    return m_data[index];
}

template<typename T>
T* Vector<T>::data() noexcept {
    return m_data;
}

// Capacity
template<typename T>
bool Vector<T>::empty() const noexcept {
    return m_size == 0; 
}

template<typename T>
size_t Vector<T>::size() const noexcept {
    return m_size; 
}

template<typename T>
size_t Vector<T>::capacity() const noexcept {
    return m_capacity;
}

template<typename T>
void Vector<T>::reserve(size_t new_capacity) {
    if(new_capacity > 0)
    {
        reallocate(new_capacity); 
    }
}

// Modifiers
template<typename T>
void Vector<T>::push_back(const T& value) {
    if(m_size == m_capacity)
    {
        size_t new_capacity = m_capacity == 0 ? 1 : m_capacity*2; 
        reserve(new_capacity);
    }

    new (m_data + m_size) T(value);
    ++m_size; 
}

template<typename T>
void Vector<T>::push_back(T&& value) {
    if(m_size == m_capacity)
    {
        size_t new_capacity = m_capacity == 0 ? 1 : m_capacity*2; 
        reserve(new_capacity);
    }

    new (m_data + m_size) T(std::move(value));
    ++m_size; 
}

template<typename T>
void Vector<T>::clear() noexcept {
    if(m_size > 0)
    {
        for(size_t i = 0; i < m_size; ++i)
        {
            m_data[i].~T(); 
        }
    }

    m_size = 0; 
}

#endif // VECTOR_HPP