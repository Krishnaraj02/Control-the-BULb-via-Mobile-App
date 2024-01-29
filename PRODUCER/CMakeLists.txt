cmake_minimum_required(VERSION 3.20.2)
project(sender VERSION 0.1.0 LANGUAGES C CXX)

add_executable(sender main.cpp)
target_link_libraries(sender -lmosquitto)
target_include_directories(sender PUBLIC /opt/Krishnaraj/Crow/build/asio/asio/include)


