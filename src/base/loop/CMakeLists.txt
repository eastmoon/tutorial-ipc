# Declare cmake information
cmake_minimum_required(VERSION 2.8.10)
project(example)

# Setting CMAKE output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

# Copy executable shell script
if ( EXISTS ${CMAKE_SOURCE_DIR}/example.sh )
    message( STATUS "Copy ${CMAKE_SOURCE_DIR}/example.sh to ${CMAKE_CURRENT_BINARY_DIR}/example.sh")
    configure_file(${CMAKE_SOURCE_DIR}/example.sh ${CMAKE_CURRENT_BINARY_DIR}/example.sh COPYONLY)
endif()

# Add library & classes
file(
    GLOB
    includes_library
    "classes/*.cpp"
    "classes/*.h"
)

# Add source code in project
add_executable(
    example
    main.cpp
    ${includes_library}
)

# Add thread package
find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
  set_property(TARGET example PROPERTY COMPILE_OPTIONS "-pthread")
  set_property(TARGET example PROPERTY INTERFACE_COMPILE_OPTIONS "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(example "${CMAKE_THREAD_LIBS_INIT}")
endif()
