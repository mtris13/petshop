cmake_minimum_required(VERSION 3.16)
project(petshop)

# chọn chuẩn C++
set(CMAKE_CXX_STANDARD 17)

# thêm thư mục include/
include_directories(${CMAKE_SOURCE_DIR}/include)

# -----------------------------------------------------
# THAY THẾ GLOB BẰNG DANH SÁCH RÕ RÀNG
# -----------------------------------------------------
set(SOURCES
    src/main.cpp
    src/infra/repositories/AccountRepoFile.cpp
    src/infra/repositories/BillRepoFile.cpp
    src/infra/repositories/BookingRepoFile.cpp
    src/infra/repositories/PetRepoFile.cpp
    src/infra/repositories/ServiceRepoFile.cpp
    
    # >> TỆP BẠN ĐANG BỊ THIẾU LÀ TỆP NÀY <<
    src/infra/repositories/CartRepoFile.cpp 
    # (Hãy đảm bảo tên tệp này chính xác)
)

# tạo executable tên "petshop"
add_executable(petshop ${SOURCES})