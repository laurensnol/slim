find_package(Doxygen)
if(Doxygen_FOUND)
  set(DOXYGEN_EXTRACT_ALL YES)
  set(DOXYGEN_BUILTIN_STL_SUPPORT YES)

  doxygen_add_docs(docs slim
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/include")
else()
  message(WARNING
    "Doxygen not found\n"
    "Documentation cannot be built")
endif()
