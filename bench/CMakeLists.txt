cmake_minimum_required(VERSION 3.12.0)
project(doris-bench)

set(CXX_GCC_FLAGS "${CXX_GCC_FLAGS} -fno-omit-frame-pointer -Wall -std=gnu++17 -fno-access-control")
set(CXX_FLAGS_DEBUG "${CXX_GCC_FLAGS} -Wignored-attributes -ggdb3 -O0 -gdwarf-2 -std=gnu++17")
set(CXX_FLAGS_RELEASE "${CXX_GCC_FLAGS} -O3 -fPIC -gdwarf-2 -DNDEBUG -std=gnu++17")

string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
    SET(CMAKE_CXX_FLAGS ${CXX_FLAGS_DEBUG})
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RELEASE")
    SET(CMAKE_CXX_FLAGS ${CXX_FLAGS_RELEASE})
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "ASAN")
    SET(CMAKE_CXX_FLAGS "${CXX_FLAGS_ASAN}")
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "LSAN")
    SET(CMAKE_CXX_FLAGS "${CXX_FLAGS_LSAN}")
else()
    message(FATAL_ERROR "Unknown build type: ${CMAKE_BUILD_TYPE}")
endif()

set(BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../")

add_subdirectory("${BASE_DIR}thirdparty/googletest" "thirdparty/googletest")
add_subdirectory("${BASE_DIR}thirdparty/benchmark" "thirdparty/benchmark")

set(DORIS_HOME "doris" CACHE STRING "doris-home")
file(GLOB_RECURSE DORIS_STATIC_LIB "${DORIS_HOME}/be/build_Release/*.a")
#message(STATUS "found doris lib: ${DORIS_STATIC_LIB}")
message(STATUS "${BENCHMARK_ROOT}")

include_directories(${DORIS_HOME}/gensrc/build/)


set(PREBUILT_THIRDPARTY ${DORIS_HOME}/thirdparty/installed CACHE STRING "doris thirdparty install dir")
include_directories(${PREBUILT_THIRDPARTY}/include)
include_directories(${PREBUILT_THIRDPARTY}/gperftools/include)
include_directories(${PREBUILT_THIRDPARTY}/include/thrift)
include_directories(${PREBUILT_THIRDPARTY}/include/event)


file(GLOB_RECURSE PREBUILT_THIRDPARTY_LIB "${PREBUILT_THIRDPARTY}/lib64/*.a")

set(DORIS_SRC ${DORIS_HOME}/be/src)

include_directories(${DORIS_SRC})
#FILE(GLOB CHILDREN RELATIVE ${DORIS_SRC} ${DORIS_SRC}/*)
#FOREACH(CHILD ${CHILDREN})
    #IF(IS_DIRECTORY ${DORIS_SRC}/${CHILD})
        #include_directories(${DORIS_SRC}/${CHILD})
        #message(STATUS ${DORIS_SRC}/${CHILD})
    #ENDIF()
#ENDFOREACH()

link_libraries(pthread dl)
add_executable(expr_bench src/bench.cpp)
set_target_properties(expr_bench PROPERTIES ENABLE_EXPORTS 1)
target_link_libraries(expr_bench 
    -Xlinker "-("
    ${DORIS_STATIC_LIB} ${PREBUILT_THIRDPARTY_LIB} 
    -Xlinker "-)"
    benchmark)

