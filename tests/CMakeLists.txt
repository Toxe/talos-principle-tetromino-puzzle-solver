if(BUILD_TESTING)
    add_executable(tests
        grid_coords.cpp
        grid_grid.cpp
        grid_gridcell.cpp
        solver_board.cpp
        solver_placement_mask.cpp
        solver_rotation.cpp
        solver_solver.cpp
        solver_square.cpp
        utility_duration.cpp
        utility_factorial.cpp
        utility_statistics.cpp
    )

    set_target_properties(tests PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(tests PUBLIC cxx_std_23)
    target_compile_options(tests PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
    target_link_options(tests PRIVATE ${SANITIZER_LINK_OPTIONS})
    target_link_libraries(tests PRIVATE ${SANITIZER_LINK_LIBRARIES} lib_tptps Catch2::Catch2WithMain)

    set_target_properties(tests PROPERTIES FOLDER "TPTPS")
    get_target_property(tests_sources tests SOURCES)
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Sources" FILES ${tests_sources})

    add_test(NAME tests COMMAND tests)
endif()
