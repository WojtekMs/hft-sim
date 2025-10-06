set(MODULE_NAME OrderBook)
set(MODULE_LIB_NAME ${MODULE_NAME}Lib)

add_library(
    ${MODULE_LIB_NAME}
    OrderBook.cpp
    OrderBook.hpp
)
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH CMAKE_CURRENT_SOURCE_PARENT_DIR)
target_include_directories(${MODULE_LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_PARENT_DIR})

if(ENABLE_UT)
    set(MODULE_UT_NAME ${MODULE_NAME}Ut)
    add_executable(${MODULE_UT_NAME} OrderBook.ut.cpp)
    target_link_libraries(
        ${MODULE_UT_NAME}
        PRIVATE
            Catch2::Catch2WithMain
            ${MODULE_LIB_NAME}
    )
    catch_discover_tests(${MODULE_UT_NAME})
endif()
