function(slim_enable_sanitizers)
  message(STATUS "Enabling sanitizers for targets ${ARGN}")

  set(SLIM_SANITIZER_COMPILER_FLAGS "")
  set(SLIM_SANITIZER_LINKER_FLAGS "")

  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(SLIM_SANITIZER_COMPILER_FLAGS
      "-fno-omit-frame-pointer"
      "-fsanitize=address,undefined,leak")
    set(SLIM_SANITIZER_LINKER_FLAGS "-fsanitize=address,undefined,leak")
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(APPLE)
      message(WARNING "Skipped enabling sanitizers\n"
        "GCC does not support sanitizers on MacOS Ventura\n"
        "See: https://github.com/orgs/Homebrew/discussions/3384#discussioncomment-6264292")
    elseif(WIN32)
      message(WARNING "Skipped enabling sanitizers\n"
        "MinGW GCC does not support sanitizers\n"
        "See: https://www.mingw-w64.org/contribute/#thorough-status-report-for-sanitizers-asan-tsan-usan")
    else()
      set(SLIM_SANITIZER_COMPILER_FLAGS
        "-fno-omit-frame-pointer"
        "-fsanitize=address,undefined,leak")
      set(SLIM_SANITIZER_LINKER_FLAGS  "-fsanitize=address,undefined,leak")
    endif()
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(SLIM_SANITIZER_COMPILER_FLAGS  "/fsanitize=address")
  else()
    message(WARNING "Skipped enabling sanitizers for unknown compiler ${CMAKE_CXX_COMPILER_ID}")
  endif()

  foreach(target ${ARGN})
    if(TARGET ${target})
      target_compile_options(${target} PRIVATE ${SLIM_SANITIZER_COMPILER_FLAGS})
      target_link_options(${target} PRIVATE ${SLIM_SANITIZER_LINKER_FLAGS})
    endif()
  endforeach()
endfunction()
