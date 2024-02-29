function(slim_enable_tooling)
  message(STATUS "Enabling tooling for targets ${ARGN}")

  set(SLIM_CLANG_TIDY_PROPERTIES "")
  find_program(CLANG_TIDY_PROGRAM clang-tidy)
  if(CLANG_TIDY_PROGRAM)
    list(APPEND SLIM_CLANG_TIDY_PROPERTIES
      ${CLANG_TIDY_PROGRAM}
      "-p=${CMAKE_CURRENT_BINARY_DIR}"
      "-header-filter=.*"
      "--warnings-as-errors=*")
    message(STATUS "Enabled clang-tidy")
  else()
    message(STATUS "clang-tidy not found")
  endif()

  set(SLIM_CPPCHECK_PROPERTIES "")
  find_program(CPPCHECK_PROGRAM cppcheck)
  if(CPPCHECK_PROGRAM)
    # Suppress "unusedFunction" here to avoid false positives since cppcheck
    # will check every file individually. Truly unused functions will be caught
    # by clang-tidy.
    list(APPEND SLIM_CPPCHECK_PROPERTIES
      ${CPPCHECK_PROGRAM}
      "--quiet"
      "--enable=all"
      "--suppress=missingIncludeSystem"
      "--suppress=unusedFunction"
      "--suppress=unmatchedSuppression"
      "--suppress=checkersReport"
      "--inline-suppr")
    message(STATUS "Enabled cppcheck")
  else()
    message(STATUS "cppcheck not found")
  endif()

  set(SLIM_IWYU_PROPERTIES "")
  find_program(IWYU_PROGRAM include-what-you-use)
  if(IWYU_PROGRAM)
    set(SLIM_IWYU_PROPERTIES "${IWYU_PROGRAM};-Xiwyu;")
    message(STATUS "Enabled include-what-you-use")
  else()
    message(STATUS "include-what-you-use not found")
  endif()

  set(SLIM_CCACHE_PROPERTIES "")
  find_program(CCACHE_PROGRAM ccache)
  if(CCACHE_PROGRAM)
    list(APPEND SLIM_CCACHE_PROPERTIES
      ${CCACHE_PROGRAM})
    message(STATUS "Enabled Ccache")
  else()
    message(STATUS "Ccache not found")
  endif()

  foreach(target ${ARGN})
    if(TARGET ${target})
      set_target_properties(${target} PROPERTIES
        CXX_CLANG_TIDY           "${SLIM_CLANG_TIDY_PROPERTIES}"
        CXX_CPPCHECK             "${SLIM_CPPCHECK_PROPERTIES}"
        CXX_INCLUDE_WHAT_YOU_USE "${SLIM_IWYU_PROPERTIES}"
        CXX_COMPILER_LAUNCHER    "${SLIM_CCACHE_PROPERTIES}")
    endif()
  endforeach()
endfunction()

