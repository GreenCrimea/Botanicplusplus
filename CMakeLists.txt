cmake_minimum_required(VERSION 3.0.0)
project(cpp_library_test VERSION 0.1.0)


INCLUDE_DIRECTORIES(
    /home/gc/vcpkg/installed/x64-linux/include/cryptopp 
    /home/gc/vcpkg/installed/x64-linux/include/crow 
    /home/gc/vcpkg/installed/x64-linux/include/boost 
    )

LINK_DIRECTORIES(
    /home/gc/vcpkg/installed/x64-linux/lib
)


add_executable(botanic main.cpp)


TARGET_LINK_LIBRARIES(botanic
    cryptopp 
    
    
)