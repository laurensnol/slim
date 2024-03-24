set(IMGUI_SOURCES
  "imgui/imgui.cpp"
  "imgui/imgui_demo.cpp"
  "imgui/imgui_draw.cpp"
  "imgui/imgui_tables.cpp"
  "imgui/imgui_widgets.cpp"
  "imgui/imconfig.h"
  "imgui/imgui.h"
  "imgui/imgui_internal.h"
  "imgui/imstb_rectpack.h"
  "imgui/imstb_textedit.h"
  "imgui/imstb_truetype.h"

  "imgui/backends/imgui_impl_glfw.h"
  "imgui/backends/imgui_impl_opengl3.h"
  "imgui/backends/imgui_impl_glfw.cpp"
  "imgui/backends/imgui_impl_opengl3.cpp")

if(SLIM_PLATFORM_MACOS)
  list(APPEND ${IMGUI_SOURCES}
    "imgui/backends/imgui_impl_osx.h"
    "imgui/backends/imgui_impl_osx.mm")
endif()

add_library(imgui ${IMGUI_SOURCES})
target_include_directories(imgui PRIVATE
  "imgui"
  "${SLIM_THIRDPARTY_DIR}/glfw/include")

if(SLIM_PLATFORM_MACOS)
  target_link_libraries(imgui PRIVATE
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreFoundation")
endif()
