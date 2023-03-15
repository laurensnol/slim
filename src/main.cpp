#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

int main()
{
  GLFWwindow *window;

  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  #if SLIM_PLATFORM_MACOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif

  window = glfwCreateWindow(1080, 720, "slim", NULL, NULL);
  
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  int version = gladLoadGL(glfwGetProcAddress);
  if (version == 0)
  {
    spdlog::critical("Failed to initialize OpenGL context");
    return -1;
  }

  spdlog::info("Loaded OpenGL {}.{}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

  while (!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
