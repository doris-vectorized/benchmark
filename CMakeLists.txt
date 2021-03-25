cmake_minimum_required(VERSION 3.12.0)
project(vec)

add_definitions(-std=c++17)

set(CXX_GCC_FLAGS "${CXX_GCC_FLAGS} -fno-omit-frame-pointer -Wall")

set(CXX_FLAGS_DEBUG "${CXX_GCC_FLAGS} -Werror -ggdb3 -O0 -gdwarf-2 ")
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
include_directories("libs/libcommon/include")
#include_directories("libs/libpcg-random/include")
include_directories("libs/cityhash102/include")
#FILE(GLOB COMMON_SOURCE "src/Common/*.cpp")

link_directories("thirdparty/install/lib/")
link_directories("thirdparty/install/lib64/")
link_libraries(fmt pthread dl)

add_executable(cow_test test/cow_test.cpp src/vec/Functions/IFunction.cpp src/vec/Functions/FunctionHelpers.cpp)
target_link_libraries(cow_test gtest)

add_executable(array_test test/podarray_test.cpp src/vec/Common/PODArray.cpp src/vec/Columns/IColumn.cpp src/vec/Columns/ColumnVector.cpp src/vec/Common/Exception.cpp src/vec/Common/ErrorCodes.cpp src/vec/Columns/ColumnConst.cpp src/vec/Columns/ColumnNullable.cpp src/vec/common/demangle.cpp src/vec/Columns/ColumnsCommon.cpp)
target_link_libraries(array_test gtest pthread dl)

add_executable(exception_test test/exception_test.cpp src/vec/Common/Exception.cpp src/vec/Common/ErrorCodes.cpp src/vec/Columns/ColumnConst.h src/vec/Columns/ColumnConst.cpp src/vec/Columns/ColumnsCommon.cpp src/vec/common/demangle.cpp src/vec/Columns/IColumn.cpp src/vec/Common/PODArray.cpp src/vec/Columns/ColumnNullable.cpp src/vec/Columns/ColumnVector.cpp)
target_link_libraries(exception_test boost_stacktrace_addr2line boost_stacktrace_basic boost_exception gtest)

add_executable(column_vector_test test/column_vector_test src/vec/Common/PODArray.cpp src/vec/Columns/IColumn.cpp src/vec/Columns/ColumnVector.cpp src/vec/Common/Exception.cpp src/vec/Common/ErrorCodes.cpp src/vec/Columns/ColumnConst.cpp src/vec/Columns/ColumnNullable.cpp src/vec/common/demangle.cpp src/vec/Columns/ColumnsCommon.cpp)
target_link_libraries(column_vector_test gtest pthread dl)

add_executable(block_test test/block_test.cpp src/vec/Core/BlockInfo.cpp src/vec/Common/PODArray.cpp src/vec/Common/ErrorCodes.cpp src/vec/Common/Exception.cpp src/vec/Core/Block.cpp src/vec/Columns/IColumn.cpp src/vec/Core/ColumnWithTypeAndName.cpp src/vec/DataTypes/IDataType.cpp src/vec/DataTypes/NestedUtils.cpp src/vec/Columns/ColumnConst.cpp src/vec/Columns/ColumnNullable.cpp src/vec/common/demangle.cpp src/vec/Columns/ColumnsCommon.cpp src/vec/DataTypes/DataTypesNumber.cpp src/vec/DataTypes/DataTypeNumberBase.cpp src/vec/Columns/ColumnVector.cpp)
target_link_libraries(block_test gtest)

add_executable(agg_test test/agg_test.cpp src/vec/AggregateFunctions/AggregateFunctionSum.cpp src/vec/Core/BlockInfo.cpp src/vec/Common/PODArray.cpp src/vec/Common/ErrorCodes.cpp src/vec/Common/Exception.cpp src/vec/Core/Block.cpp src/vec/Columns/IColumn.cpp src/vec/Core/ColumnWithTypeAndName.cpp src/vec/DataTypes/IDataType.cpp src/vec/DataTypes/NestedUtils.cpp src/vec/Columns/ColumnConst.cpp src/vec/Columns/ColumnNullable.cpp src/vec/common/demangle.cpp src/vec/Columns/ColumnsCommon.cpp src/vec/DataTypes/DataTypesNumber.cpp src/vec/DataTypes/DataTypeNumberBase.cpp src/vec/Columns/ColumnVector.cpp)
target_link_libraries(agg_test gtest)

add_executable(abs_function_test test/abs_function_test.cpp
src/vec/Functions/IFunction.cpp src/vec/Functions/FunctionHelpers.cpp
src/vec/Common/Exception.cpp
        src/vec/DataTypes/IDataType.cpp src/vec/Columns/IColumn.cpp
src/vec/Columns/ColumnNullable.cpp src/vec/Columns/ColumnConst.cpp
        src/vec/Common/ErrorCodes.cpp src/vec/Core/Block.cpp
src/vec/Common/PODArray.cpp src/vec/Core/ColumnWithTypeAndName.cpp
src/vec/DataTypes/IDataType.cpp src/vec/DataTypes/NestedUtils.cpp
src/vec/common/demangle.cpp src/vec/Columns/ColumnsCommon.cpp
src/vec/DataTypes/DataTypesNumber.cpp src/vec/DataTypes/DataTypeNumberBase.cpp
src/vec/Columns/ColumnVector.cpp)
target_link_libraries(abs_function_test gtest)
