# performance executable
add_executable(performance main.cpp)
set_target_properties(performance PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(performance PUBLIC cxx_std_23)
target_compile_options(performance PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
target_link_options(performance PRIVATE ${SANITIZER_LINK_OPTIONS})
target_link_libraries(performance PRIVATE ${SANITIZER_LINK_LIBRARIES} lib_tptps fmt::fmt)

set_target_properties(performance PROPERTIES FOLDER "Performance")
get_target_property(performance_sources performance SOURCES)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "Sources" FILES ${performance_sources})
