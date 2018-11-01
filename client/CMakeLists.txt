cmake_minimum_required (VERSION 3.4)

# The project
project (client)

set(CMAKE_BUILD_TYPE RelWithDebInfo)

# The version number.
set (client_VERSION_MAJOR 1)
set (client_VERSION_MINOR 0)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

# Use static libs
set (OPENSSL_USE_STATIC_LIBS TRUE)

set (CMAKE_INCLUDE_CURRENT_DIR ON)

# Cpp files
set(SOURCE_FILES client.cpp)

include_directories(../include)

# Libs
set(LIBRARY_FILES OpenSSL::Crypto OpenSSL::SSL Threads::Threads)

# Compile the target
add_executable (${PROJECT_NAME} ${SOURCE_FILES})

# Link the libs
target_link_libraries(${PROJECT_NAME} ${LIBRARY_FILES})