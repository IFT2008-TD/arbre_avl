set(TEST_SOURCES tests_arbre_avl.cpp ${PROJECT_SOURCE_DIR}/arbre_avl.h)

add_executable(
        tests_arbre_avl
        ${TEST_SOURCES}
)

target_include_directories(tests_arbre_avl PRIVATE ${PROJECT_SOURCE_DIR} )

target_link_libraries(
        tests_arbre_avl
        gtest_main
        gtest
        pthread
)

include(GoogleTest)
gtest_discover_tests(tests_arbre_avl)