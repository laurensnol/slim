# Create a symlink for compile_commands.json to be found by clangd.
if(CMAKE_EXPORT_COMPILE_COMMANDS)
  if(WIN32)
    message(WARNING
      "Skipped creation of symlink for compile_commands.json\n"
      "Please copy compile_commands.json manually for clangd to work as expected")
  else()
    message(STATUS "Creating symlink for compile_commands.json")

    file(CREATE_LINK
      "${CMAKE_BINARY_DIR}/compile_commands.json"
      "${CMAKE_SOURCE_DIR}/build/compile_commands.json"
      SYMBOLIC)
  endif()
endif()

