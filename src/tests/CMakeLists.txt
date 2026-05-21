project(tests)

add_executable(${PROJECT_NAME}
  #lexerTests.cpp
  #tokenTests.cpp
  parserTests.cpp
)

set(CMAKE_CXX_STANDARD 20)

target_link_libraries(${PROJECT_NAME} PUBLIC
  lib
  UnitTest
)
