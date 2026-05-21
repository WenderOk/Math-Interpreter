cmake_minimum_required(VERSION 3.23)
project(Interpreter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  UnitTest
  URL "https://raw.githubusercontent.com/WenderOk/UnitTestFramework/refs/heads/main/src/Test.h"
  DOWNLOAD_NO_EXTRACT TRUE
)
FetchContent_MakeAvailable(UnitTest)

# Так как это одиночный файл, создаем интерфейсную библиотеку вручную
add_library(UnitTest INTERFACE)
# Привязываем к ней путь, где лежит скачанный Test.h
target_include_directories(UnitTest INTERFACE ${unittest_SOURCE_DIR})

add_subdirectory(src/modules)
add_subdirectory(src/tests)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE lib)
