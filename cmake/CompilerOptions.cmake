function(slim_set_compiler_options)
  message(STATUS "Setting compiler options for targets ${ARGN}")

  set(SLIM_COMPILER_FLAGS "")

  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug") 
      set(SLIM_COMPILER_FLAGS 
        "-g" "-O1" "-Werror" "-Wall" "-Wextra" "-Wshadow" "-Wconversion"
        "-Wpedantic" "-Wold-style-cast" "-Wcast-align" "-Wunused"
        "-Woverloaded-virtual" "-Wconversion" "-Wsign-conversion"
        "-Wdouble-promotion" "-Wformat=2" "-Wimplicit-fallthrough")
    else()
      set(SLIM_COMPILER_FLAGS "-O3")
    endif()
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug") 
      set(SLIM_COMPILER_FLAGS
        "-g" "-O1" "-Werror" "-Wall" "-Wextra" "-Wshadow" "-Wconversion"
        "-Wpedantic" "-Wold-style-cast" "-Wcast-align" "-Wunused"
        "-Woverloaded-virtual" "-Wconversion" "-Wdouble-promotion" "-Wformat=2"
        "-Wimplicit-fallthrough" "-Wduplicated-cond" "-Wduplicated-branches"
        "-Wlogical-op" "-Wnull-dereference" "-Wuseless-cast")
    else()
      set(SLIM_COMPILER_FLAGS "-O3")
    endif()
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug") 
      set(SLIM_COMPILER_FLAGS
        "/MDd" "/WX" "/permissive" "/W4" "/w14242" "/w14254" "/w14263" "/w14265"
        "/w14287" "/we4289" "/w14296" "/w14311" "/w14545" "/w14546" "/w14547"
        "/w14549" "/w14555" "/w14619" "/w14619" "/w14640" "/w14826" "/w14905"
        "/w14906" "/w14928" "/wd4996")
    else()
      set(SLIM_COMPILER_FLAGS "/MD")
    endif()
  else()
    message(WARNING "Skipped setting compiler options for unknown compiler ${CMAKE_CXX_COMPILER_ID}")
    return()
  endif()

  foreach(target ${ARGN})
    if(TARGET ${target})
      target_compile_options(${target} PRIVATE ${SLIM_COMPILER_FLAGS})
    endif()
  endforeach()
endfunction()
