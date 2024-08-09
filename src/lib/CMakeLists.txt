add_library(lib_tptps
    grid/coords.hpp
    grid/grid.hpp
    grid/gridcell.hpp
    solver/board.cpp
    solver/board.hpp
    solver/placement.cpp
    solver/placement.hpp
    solver/placement_mask.cpp
    solver/placement_mask.hpp
    solver/rotation.cpp
    solver/rotation.hpp
    solver/solver.cpp
    solver/solver.hpp
    solver/square.cpp
    solver/square.hpp
    solver/tetrominoes.hpp
    utility/duration.cpp
    utility/duration.hpp
    utility/factorial.cpp
    utility/factorial.hpp
    utility/statistics.hpp
    utility/str.cpp
    utility/str.hpp
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
