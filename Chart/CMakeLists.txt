cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
#название моего проекта
project(Qt)
#создание библиотеки
add_library(mpl STATIC src/Mpl.cpp)
#подключение ЗАГОЛОВКА Matplotlib и ЗАГОЛОВКОВ sfml
target_include_directories(mpl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/library ${SFML_INCLUDE_DIR})
#Выполняемый файл
add_executable(${PROJECT_NAME} cxx/main.cpp)
#линковка проекта и статической библиотеки + библиотек SFML
target_link_libraries(Qt PRIVATE mpl sfml-window sfml-system sfml-graphics)