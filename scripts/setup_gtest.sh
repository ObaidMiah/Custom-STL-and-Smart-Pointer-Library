#!/bin/bash

# Script to download and build Google Test locally
# This is required for building the Custom STL Vector project

GTEST_VERSION="1.14.0"
GTEST_DIR="googletest-${GTEST_VERSION}"
GTEST_BUILD_DIR="gtest_build"

echo "Setting up Google Test ${GTEST_VERSION} for Custom STL Vector project..."

# Check if already installed
if [ -d "${GTEST_BUILD_DIR}/install" ] && [ -f "${GTEST_BUILD_DIR}/install/lib/libgtest.a" ]; then
    echo "Google Test is already installed and ready to use!"
    echo "You can now run: mkdir build && cd build && cmake .. && make && make test"
    exit 0
fi

# Check if already downloaded
if [ ! -d "${GTEST_DIR}" ]; then
    echo "Downloading Google Test..."
    curl -L "https://github.com/google/googletest/archive/v${GTEST_VERSION}.tar.gz" -o gtest.tar.gz
    
    if [ $? -ne 0 ]; then
        echo "Failed to download Google Test. Trying with wget..."
        wget "https://github.com/google/googletest/archive/v${GTEST_VERSION}.tar.gz" -O gtest.tar.gz
        
        if [ $? -ne 0 ]; then
            echo "Error: Failed to download Google Test"
            exit 1
        fi
    fi
    
    echo "Extracting Google Test..."
    tar -xzf gtest.tar.gz
    rm gtest.tar.gz
fi

# Build Google Test
if [ ! -d "${GTEST_BUILD_DIR}" ]; then
    echo "Building Google Test..."
    mkdir -p "${GTEST_BUILD_DIR}"
    cd "${GTEST_BUILD_DIR}"
    
    # Use the CMake installation we found
    CMAKE_CMD="/Applications/CMake.app/Contents/bin/cmake"
    if [ ! -f "$CMAKE_CMD" ]; then
        # Try to find cmake in PATH
        CMAKE_CMD="cmake"
    fi
    
    echo "Using CMake: $CMAKE_CMD"
    "$CMAKE_CMD" "../${GTEST_DIR}" -DCMAKE_INSTALL_PREFIX="$(pwd)/install"
    if [ $? -ne 0 ]; then
        echo "Error: CMake configuration failed"
        exit 1
    fi
    
    make
    if [ $? -ne 0 ]; then
        echo "Error: Build failed"
        exit 1
    fi
    
    # Install to local directory
    make install
    if [ $? -ne 0 ]; then
        echo "Error: Install failed"
        exit 1
    fi
    
    cd ..
fi

echo ""
echo "✅ Google Test setup complete!"
echo "📁 Libraries installed in: ${GTEST_BUILD_DIR}/install/lib/"
echo "📁 Headers installed in: ${GTEST_BUILD_DIR}/install/include/"
echo ""
echo "🚀 Ready to build! Run these commands:"
echo "   mkdir build && cd build"
echo "   cmake .."
echo "   make && make test"
echo ""
echo "ℹ️  CMake will automatically detect the local Google Test installation."
