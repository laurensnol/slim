#include "core/application.h"

int main()
{  
  slim::Application& app = slim::Application::getInstance();
  app.start();

  return 0;
}