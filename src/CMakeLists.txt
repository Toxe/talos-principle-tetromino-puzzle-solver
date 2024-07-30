add_library(lib_tptps
    grid/coords.hpp
    grid/grid.hpp
    grid/gridcell.hpp
    solver/board.cpp
    solver/board.hpp
    solver/placement_mask.cpp
    solver/placement_mask.hpp
    solver/solver.cpp
    solver/solver.hpp
    solver/square.hpp
    solver/stats.cpp
    solver/stats.hpp
    solver/tetrominoes.cpp
    solver/tetrominoes.hpp
)

set_target_properties(lib_tptps PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(lib_tptps PUBLIC cxx_std_23)
target_compile_options(lib_tptps PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
target_link_options(lib_tptps PRIVATE ${SANITIZER_LINK_OPTIONS})
target_link_libraries(lib_tptps PRIVATE ${SANITIZER_LINK_LIBRARIES} fmt::fmt)
target_include_directories(lib_tptps INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(lib_tptps PROPERTIES FOLDER "TPTPS")
get_target_property(lib_tptps_sources lib_tptps SOURCES)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Sources" FILES ${lib_tptps_sources})

# main executable
add_executable(tptps main.cpp)
set_target_properties(tptps PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(tptps PUBLIC cxx_std_23)
target_compile_options(tptps PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
target_link_options(tptps PRIVATE ${SANITIZER_LINK_OPTIONS})
target_link_libraries(tptps PRIVATE ${SANITIZER_LINK_LIBRARIES} lib_tptps fmt::fmt)

set_target_properties(tptps PROPERTIES FOLDER "TPTPS")
get_target_property(tptps_sources tptps SOURCES)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Sources" FILES ${tptps_sources})

# performance executable
add_executable(performance performance.cpp)
set_target_properties(performance PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(performance PUBLIC cxx_std_23)
target_compile_options(performance PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
target_link_options(performance PRIVATE ${SANITIZER_LINK_OPTIONS})
target_link_libraries(performance PRIVATE ${SANITIZER_LINK_LIBRARIES} lib_tptps fmt::fmt)

set_target_properties(performance PROPERTIES FOLDER "TPTPS")
get_target_property(performance_sources performance SOURCES)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Sources" FILES ${performance_sources})
