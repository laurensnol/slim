function(slim_enable_coverage)
  message(STATUS "Enabling coverage for target(s) ${ARGN}")

  set(SLIM_COVERAGE_COMPILER_FLAGS "")
  set(SLIM_COVERAGE_LINK_LIBRARIES "")

  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(SLIM_COVERAGE_COMPILER_FLAGS
      "-fprofile-instr-generate"
      "-fcoverage-mapping")
    set(SLIM_COVERAGE_LINK_LIBRARIES  "-fprofile-instr-generate")
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(SLIM_COVERAGE_COMPILER_FLAGS "--coverage")
    set(SLIM_COVERAGE_LINK_LIBRARIES "--coverage")
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "Skipped setting up coverage for MSVC")
    return()
  else()
    message(WARNING "Skipped setting up coverage for unknown compiler ${CMAKE_CXX_COMPILER_ID}")
    return()
  endif()

  foreach(target ${ARGN})
    if(TARGET ${target})
      target_compile_options(${target} PRIVATE ${SLIM_COVERAGE_COMPILER_FLAGS})
      target_link_libraries(${target} PRIVATE ${SLIM_COVERAGE_LINK_LIBRARIES})
    endif()
  endforeach()
endfunction()
