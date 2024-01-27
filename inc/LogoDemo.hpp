#pragma once
#include <tyra>
#include <memory.h>

namespace LogoDemo {
using namespace Tyra;

class LogoDemo : public Tyra::Game {
 public:
  LogoDemo(Tyra::Engine* engine);
  ~LogoDemo();

  void init();
  void loop();

 private:
  void loadTexture();
  void loadSprite();
  void loadMesh();

  bool DisplaySprite;
  
  Tyra::StaticPipeline sPipe;
  Tyra::StaPipOptions sPOptions;
  std::unique_ptr<Tyra::StaticMesh> mesh;

  Tyra::Pad* pad;
  Tyra::Engine* engine;
  Tyra::Sprite sprite;

  Vec4 camPosition;
  Vec4 camLookAt;
};

}  // namespace Racer
