cmake_minimum_required(VERSION 3.10)

# Project name and version
project(PSSP VERSION 3.0)

# pridedu pagrindines bibliotekas
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")


# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Optional: enable more warnings and optimizations
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# Source files
set(SOURCES
    main.cpp
)

# Header files (optional for IDEs)
set(HEADERS
    mylib.h
    structs.h
)

# Define the executable
add_executable(PSSP ${SOURCES} ${HEADERS})
