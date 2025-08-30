# My Custom Vector Implementation

I built this as a learning project to understand how `std::vector` works under the hood. It's a complete implementation of a dynamic array that behaves like the real thing.

## What it does

This is basically my version of `std::vector`. It automatically grows when you add elements, handles memory for you, and works with STL algorithms. I implemented all the core functionality you'd expect:

- Create vectors and fill them with data
- Add and remove elements
- Access elements safely (or unsafely if you want speed)
- Iterate through your data
- Copy and move vectors around efficiently

## How to use it

```cpp
#include "vector.h"

int main() {
    // Create a vector with 5 elements, all set to 42
    Vector<int> numbers(5, 42);

    // Add some more numbers
    numbers.push_back(100);
    numbers.push_back(200);

    // Check what we have
    std::cout << "Size: " << numbers.size() << std::endl;
    std::cout << "First: " << numbers.front() << std::endl;
    std::cout << "Last: " << numbers.back() << std::endl;

    // Print everything
    for (int num : numbers) {
        std::cout << num << " ";
    }

    return 0;
}
```

## Project layout

```
├── include/
│   ├── vector.h      # The interface
│   └── vector.hpp    # All the implementation details
├── test/
│   └── test_vector_gtest.cpp  # 28 tests to make sure it works
├── CMakeLists.txt    # Build configuration
└── setup_gtest.sh    # Script to install Google Test
```

## Building it

### First time setup

You'll need Google Test for the tests. I made a script to set it up:

```bash
./setup_gtest.sh
```

### Building and testing

```bash
mkdir build && cd build
cmake ..
make
./test_vector_gtest
```

If cmake isn't in your PATH (like on macOS), you might need:

```bash
/Applications/CMake.app/Contents/bin/cmake ..
```

## What's implemented

I focused on the core functionality:

**Making vectors:**

- `Vector()` - empty vector
- `Vector(size, value)` - filled with specific values
- Copy and move constructors

**Getting data:**

- `vec[i]` - fast access (no bounds checking)
- `vec.at(i)` - safe access (throws if out of bounds)
- `vec.front()` and `vec.back()` - first and last elements
- `vec.data()` - raw pointer to the data

**Managing size:**

- `vec.size()` - how many elements
- `vec.capacity()` - how much space is allocated
- `vec.empty()` - is it empty?
- `vec.reserve(n)` - allocate space for n elements
- `vec.resize(n)` - change size to n

**Modifying:**

- `vec.push_back(item)` - add to the end
- `vec.pop_back()` - remove from the end
- `vec.clear()` - remove everything

**Iterating:**

- `vec.begin()` and `vec.end()` - for loops and algorithms
- Range-based for loops work: `for (auto& item : vec)`

## How it works internally

I use `malloc`/`free` for raw memory and placement new to construct objects. When you add elements and run out of space, it doubles the capacity (just like the real `std::vector`).

The memory management was the trickiest part - you have to be really careful about when you construct and destroy objects vs when you allocate and free memory.

## Testing

I wrote 28 tests that cover:

- All the constructors
- Element access and bounds checking
- Memory management and resizing
- Adding and removing elements
- Iterators and STL compatibility
- Edge cases and error handling

Run `make test` to see them all pass.

## Requirements

- C++17 (uses some modern features)
- CMake 3.16 or newer
- The setup script will handle Google Test
