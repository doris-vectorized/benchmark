cmake_minimum_required(VERSION 3.12.0)
project(vec)

add_definitions(-std=c++17)

set(CXX_GCC_FLAGS "${CXX_GCC_FLAGS} -fno-omit-frame-pointer -Wall")

set(CXX_FLAGS_DEBUG "${CXX_GCC_FLAGS} -Werror -Wignored-attributes -ggdb3 -O0 -gdwarf-2 ")
#set(CXX_FLAGS_RELEASE "${CXX_GCC_FLAGS} -O3 -gdwarf-2 -DNDEBUG -fopt-info-vec-optimized -fopt-info-vec-missed")
set(CXX_FLAGS_RELEASE "${CXX_GCC_FLAGS} -O3 -fPIC -gdwarf-2 -DNDEBUG")

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

include_directories("thirdparty/install/include")
include_directories("src/")
#FILE(GLOB COMMON_SOURCE "src/Common/*.cpp")

link_directories("thirdparty/install/lib/")
link_directories("thirdparty/install/lib64/")
link_libraries(fmt pthread dl)

file(GLOB_RECURSE VEC_SOURCE ./src/vec/*.cpp)

#file(GLOB EXCUDE "./src/vec/Functions/intDiv.cpp")
#list(REMOVE_ITEM VEC_SOURCE ${EXCUDE})

add_executable(cow_test test/cow_test.cpp)
target_link_libraries(cow_test gtest)

add_executable(array_test test/podarray_test.cpp ${VEC_SOURCE})
target_link_libraries(array_test gtest pthread dl)

add_executable(exception_test test/exception_test.cpp ${VEC_SOURCE})
target_link_libraries(exception_test boost_stacktrace_addr2line boost_stacktrace_basic boost_exception gtest)

add_executable(column_vector_test test/column_vector_test ${VEC_SOURCE}) 
target_link_libraries(column_vector_test gtest pthread dl)

add_executable(column_string_test test/column_string_test.cpp ${VEC_SOURCE})
target_link_libraries(column_string_test gtest pthread dl)

add_executable(block_test test/block_test.cpp ${VEC_SOURCE})
target_link_libraries(block_test gtest)

add_executable(agg_test test/agg_test.cpp ${VEC_SOURCE})
target_link_libraries(agg_test gtest)

add_executable(decimal_test test/column_decimal_test.cpp ${VEC_SOURCE})
target_link_libraries(decimal_test gtest)

#add_executable(abs_function_test test/abs_function_test.cpp ${VEC_SOURCE})
#target_link_libraries(abs_function_test gtest)

add_executable(column_const_test  test/column_const_test.cpp ${VEC_SOURCE})
target_link_libraries(column_const_test  gtest)


add_executable(comparation_function_test test/comparation_function_test.cpp ${VEC_SOURCE})
target_link_libraries(comparation_function_test  gtest)


add_executable(cast_function_test test/cast_function_test.cpp ${VEC_SOURCE})
target_link_libraries(cast_function_test gtest)

add_executable(binary_arithmetic_test test/binary_arithmetic_test.cpp ${VEC_SOURCE})
target_link_libraries(binary_arithmetic_test gtest)

add_executable(hash_table_test test/hash_table_test.cpp ${VEC_SOURCE})
target_link_libraries(hash_table_test gtest cityhash)

add_executable(permutation_test test/permutation_test.cpp ${VEC_SOURCE})
target_link_libraries(permutation_test gtest)
