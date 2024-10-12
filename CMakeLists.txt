cmake_minimum_required(VERSION 3.8.0)
project(linux_timer VERSION 0.1.0 LANGUAGES C CXX)

# 빌드 타입 설정 (Debug, Release 등)
set(CMAKE_BUILD_TYPE Debug)

# 소스 파일 목록 명시
add_executable(linux_timer src/main.cc)

# 외부 라이브러리 연결 (필요한 경우)
find_package(Boost REQUIRED COMPONENTS system)
target_link_libraries(linux_timer Boost::system)

# # 테스트 활성화 및 테스트 케이스 추가 (필요한 경우)
# enable_testing()
# include(GoogleTest)
# add_executable(linux_timer_tests tests/test_main.cc)
# target_link_libraries(linux_timer_tests linux_timer GTest)
# add_test(NameOfTest linux_timer_tests)

# CPack 설정
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR "DEB")  # 또는 "RPM", "ZIP" 등
include(CPack)