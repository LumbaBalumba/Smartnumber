project(SmartMath)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O2 -m64 -fsanitize=leak -fsanitize=address -fsanitize=undefined -Wall -Werror")

add_library(SmartMath SmartMath.cpp SmartMath.hpp SmartNumber.cpp BigInteger.cpp)
add_executable(test SmartMath.cpp SmartMath.hpp main.cpp SmartNumber.cpp BigInteger.cpp)