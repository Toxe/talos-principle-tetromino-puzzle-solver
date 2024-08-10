# performance lib
add_library(lib_performance
    cli.cpp
    cli.hpp
    csv.hpp
    summary.cpp
    summary.hpp
)

set_target_properties(lib_performance PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(lib_performance PUBLIC cxx_std_23)
target_compile_options(lib_performance PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
target_link_options(lib_performance PRIVATE ${SANITIZER_LINK_OPTIONS})
target_link_libraries(lib_performance PRIVATE ${SANITIZER_LINK_LIBRARIES} CLI11::CLI11)
target_link_libraries(lib_performance PUBLIC lib_tptps)
target_include_directories(lib_performance INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(lib_performance PROPERTIES FOLDER "Performance Lib")
get_target_property(lib_performance_sources lib_performance SOURCES)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Sources" FILES ${lib_performance_sources})

# performance executable
add_executable(performance main.cpp)
set_target_properties(performance PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(performance PUBLIC cxx_std_23)
target_compile_options(performance PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
target_link_options(performance PRIVATE ${SANITIZER_LINK_OPTIONS})
target_link_libraries(performance PRIVATE ${SANITIZER_LINK_LIBRARIES} lib_performance fmt::fmt)

set_target_properties(performance PROPERTIES FOLDER "Performance")
get_target_property(performance_sources performance SOURCES)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Sources" FILES ${performance_sources})
