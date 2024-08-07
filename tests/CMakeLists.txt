if(BUILD_TESTING)
    add_executable(tests
        helpers/tempfile.cpp
        helpers/tempfile.hpp
        lib/grid/coords.cpp
        lib/grid/grid.cpp
        lib/grid/gridcell.cpp
        lib/solver/board.cpp
        lib/solver/placement.cpp
        lib/solver/placement_mask.cpp
        lib/solver/rotation.cpp
        lib/solver/solver.cpp
        lib/solver/square.cpp
        lib/utility/duration.cpp
        lib/utility/factorial.cpp
        lib/utility/statistics.cpp
        performance/cli.cpp
        performance/csv.cpp
    )

    set_target_properties(tests PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(tests PUBLIC cxx_std_23)
    target_compile_options(tests PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
    target_link_options(tests PRIVATE ${SANITIZER_LINK_OPTIONS})
    target_link_libraries(tests PRIVATE ${SANITIZER_LINK_LIBRARIES} lib_tptps lib_performance Catch2::Catch2WithMain)

    set_target_properties(tests PROPERTIES FOLDER "Tests")
    get_target_property(tests_sources tests SOURCES)
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Sources" FILES ${tests_sources})

    add_test(NAME tests COMMAND tests)
endif()
