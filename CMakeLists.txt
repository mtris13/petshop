cmake_minimum_required(VERSION 3.16)
project(petshop)

# chọn chuẩn C++
set(CMAKE_CXX_STANDARD 17)

# thêm thư mục include/
include_directories(${CMAKE_SOURCE_DIR}/include)

# lấy toàn bộ .cpp trong src/
file(GLOB_RECURSE SOURCES "src/*.cpp")

# tạo executable tên "petshop"
add_executable(petshop ${SOURCES})
