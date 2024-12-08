# libme

## Overview
An experimental collection of algorithms and data structures inspired by the C++ STL. Designed exclusively for learning and experimentation, not suitable for production environments.

`libme` is a modern C++23 header-only library that implements some STL-like algorithms and data structures. It leverages C++23 modules for better compilation times and cleaner inclusion semantics.

## Project Structure

```
libme/
├── CMakeLists.txt          # Main build configuration
├── src/                    # Source directory
│   ├── algo/              # Algorithm implementations
│   ├── ds/                # Data structure implementations
│   └── it/                # Iterator implementations
├── examples/              # Usage examples
│   └── basic_usage.cpp    # Basic usage demonstration
├── tests/                 # Unit tests
│   └── ds/               # Data structure tests
└── README.md             # This file
```

### Directory Purposes

- `src/`: Contains all library implementation
  - `algo/`: Houses algorithm implementations (sorting, searching, etc.)
  - `ds/`: Contains data structure implementations (circular_buffer, etc.)
  - `it/`: Implements custom iterators used by the library
- `examples/`: Demonstrates practical usage of the library components
- `tests/`: Contains unit tests using Catch2 framework

## Requirements

- C++23 compliant compiler with modules support (GCC 14 or later recommended)
- CMake 3.28 or later
- Catch2 (automatically fetched during build)

### GCC 14 installation on Ubuntu
#### Add Ubuntu Toolchain repository
```sudo add-apt-repository ppa:ubuntu-toolchain-r/test```

#### Update package list
```sudo apt update```

#### Install GCC 14
```sudo apt install gcc-14 g++-14```

## Building

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Running Tests

From the build directory:
```bash
ctest
```

## Running Examples

After building, from the build directory:
```bash
./examples/basic_usage
```

## Usage

To use the library in your project:

```cpp
import me.ds.circular_buffer;  // Import specific module

int main() {
    me::ds::circular_buffer<int, 5> buffer;
    buffer.push(42);
    // ... use the buffer
}
```

## CMake Integration

To use `libme` in your CMake project:

```cmake
add_subdirectory(path/to/libme)
target_link_libraries(your_target PRIVATE libme)
```

## Design Philosophy

This library prioritizes:
- Learning and experimentation over performance
- Modern C++ features and practices
- Clear implementation over optimization
- Educational value over production readiness

## Contributing

Feel free to:
- Open issues for bugs or enhancement ideas
- Submit pull requests with improvements
- Use the code for learning purposes
- Provide feedback on implementations

## License

[Add your chosen license here]

## Disclaimer

This library is intended for educational and experimental purposes only. It should not be used in production environments.