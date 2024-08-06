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
