add_subdirectory(lib)
add_executable(day01-02 day01-02.cpp)
#target_link_libraries(main PUBLIC advent_of_code_2022_lib)

target_link_libraries (day01-02 LINK_PUBLIC Elf_lib)

#target_include_directories(main PUBLIC
#        "${PROJECT_BINARY_DIR}"
#        "${PROJECT_SOURCE_DIR}/lib"
#        )
