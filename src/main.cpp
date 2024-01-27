#include <tyra>
#include "LogoDemo.hpp"

int main() {
  Tyra::Engine engine;
  LogoDemo::LogoDemo game(&engine);
  engine.run(&game);
  SleepThread();
  return 0;
}
