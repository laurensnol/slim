find_package(Doxygen)
if(Doxygen_FOUND)
  set(DOXYGEN_EXTRACT_ALL YES)
  set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
  set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${CMAKE_CURRENT_SOURCE_DIR}/mainpage.md")

  # doxygen-awesome
  set(DOXYGEN_GENERATE_TREEVIEW NO)
  set(DOXYGEN_DISABLE_INDEX NO)
  set(DOXYGEN_FULL_SIDEBAR NO)
  set(DOXYGEN_HTML_HEADER
    "${CMAKE_CURRENT_SOURCE_DIR}/doxygen-awesome/header.html")
  set(DOXYGEN_HTML_EXTRA_STYLESHEET
    "${CMAKE_CURRENT_SOURCE_DIR}/doxygen-awesome/doxygen-awesome.css")
  set(DOXYGEN_HTML_EXTRA_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/doxygen-awesome/doxygen-awesome-darkmode-toggle.js
    ${CMAKE_CURRENT_SOURCE_DIR}/doxygen-awesome/doxygen-awesome-paragraph-link.js
    ${CMAKE_CURRENT_SOURCE_DIR}/doxygen-awesome/doxygen-awesome-interactive-toc.js)
  set(DOXYGEN_HTML_COLORSTYLE DARK)

  doxygen_add_docs(docs slim
    "${CMAKE_CURRENT_SOURCE_DIR}/mainpage.md"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/include")
else()
  message(WARNING
    "Doxygen not found\n"
    "Documentation cannot be built")
endif()
