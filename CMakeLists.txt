project(SmartNumber)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS  "-O2 -m64 -fsanitize=leak -fsanitize=address -fsanitize=undefined -Wall -Werror")

add_library(SmartNumber SmartNumber.cpp SmartNumber.hpp)