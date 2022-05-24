# Declare cmake information
cmake_minimum_required(VERSION 2.8.10)

# Setting CMAKE output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

# Copy executable shell script
if ( EXISTS ${CMAKE_SOURCE_DIR}/example.sh )
    message( STATUS "Copy ${CMAKE_SOURCE_DIR}/example.sh to ${CMAKE_CURRENT_BINARY_DIR}/example.sh")
    configure_file(${CMAKE_SOURCE_DIR}/example.sh ${CMAKE_CURRENT_BINARY_DIR}/example.sh COPYONLY)
endif()

# Add subdirecotry
add_subdirectory(case1)
add_subdirectory(case2)
