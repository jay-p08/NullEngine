cmake_minimum_required(VERSION 3.10)
project(NullEngine VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. 패키지 찾기
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# 2. 소스 파일 및 헤더 설정
file(GLOB_RECURSE SOURCES "src/*.cpp")
include_directories(include src)

add_executable(${PROJECT_NAME} ${SOURCES})

# 3. 라이브러리 링크 (실제 연결)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    glfw 
    glad::glad 
    spdlog::spdlog
    glm::glm
)