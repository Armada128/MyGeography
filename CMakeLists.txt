cmake_minimum_required(VERSION 3.16)
project(MyGeography VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 REQUIRED)

file(GLOB_RECURSE MYHEADERS ${CMAKE_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE MYSOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM MYSOURCES ${CMAKE_SOURCE_DIR}/src/main.cpp)

foreach (header IN LISTS MYHEADERS)
    message(${header})
endforeach ()

add_library(MyGeography SHARED ${MYHEADERS} ${MYSOURCES} )
target_link_libraries(MyGeography PUBLIC Eigen3::Eigen)
#target_include_directories(MyGeometry PUBLIC )

add_executable(test ${MYHEADERS} ${MYSOURCES} ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(test PUBLIC Eigen3::Eigen)

message("CMAKE_INSTALL_PREFIX: " ${CMAKE_INSTALL_PREFIX})
message("CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR})
include(GNUInstallDirs)
message("CMAKE_INSTALL_INCLUDEDIR: " ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS MyGeography
        EXPORT MyGeographyTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
        TYPE INCLUDE
        FILES_MATCHING PATTERN "*.h")

install(EXPORT MyGeographyTargets
        FILE MyGeographyTargets.cmake
        DESTINATION lib/cmake/MyGeography)

include(CMakePackageConfigHelpers)
#configure_package_config_file(
#        MyGeometryConfig.cmake.in
#        MyGeometryConfig.cmake
#        INSTALL_DESTINATION lib/cmake/test_message)
#
#
write_basic_package_version_file(
        "MyGeographyConfigVersion.cmake"
        VERSION ${MyGeography_VERSION}
        COMPATIBILITY AnyNewerVersion)

install(FILES "MyGeographyConfig.cmake" "${CMAKE_CURRENT_BINARY_DIR}/MyGeographyConfigVersion.cmake"
        DESTINATION lib/cmake/MyGeography)
