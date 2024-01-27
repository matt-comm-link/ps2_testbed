#include "LogoDemo.hpp"


namespace LogoDemo {

using namespace Tyra;

LogoDemo::LogoDemo(Tyra::Engine* t_engine) 
{
     engine = t_engine; 
}
LogoDemo::~LogoDemo() 
{
    engine->renderer.getTextureRepository().freeBySprite(sprite);
    engine->renderer.getTextureRepository().freeByMesh(mesh.get());
}

void LogoDemo::init() 
{ 
    TYRA_LOG("Hello!"); 
    engine->renderer.setClearScreenColor(Color(255.0F, 0.0F, 208.0F));
    
    sPipe.setRenderer(&engine->renderer.core);

    camPosition = Vec4(0.0f, 0.0f, -10.0f);
    camLookAt.unit();

    loadSprite();
    loadTexture();
    loadMesh();
}

void LogoDemo::loop() 
{
    TYRA_LOG("LoopFFS");

    if(engine->pad.getClicked().Cross)
        DisplaySprite = !DisplaySprite;
    mesh->rotation.rotateY(0.01f); 

    auto& renderer = engine->renderer;
    if(DisplaySprite){
        renderer.beginFrame();
        renderer.renderer2D.render(sprite);
    }
    else
    {
        renderer.beginFrame(CameraInfo3D(&camPosition, &camLookAt));
        renderer.renderer3D.usePipeline(sPipe);
        renderer.renderer2D.render(sprite);
        sPipe.render(mesh.get(), sPOptions);

    }
    renderer.endFrame();

}

void LogoDemo::loadTexture()
{
    auto& renderer = engine->renderer;

    auto& TextureRepository = renderer.getTextureRepository();

    auto filepath = FileUtils::fromCwd("fiprofile.png");
    auto* texture = TextureRepository.add(filepath);

    texture->addLink(sprite.id);

    TYRA_LOG("Texture Loaded");
}

void LogoDemo::loadSprite()
{
    const auto& screensettings = engine->renderer.core.getSettings();
    sprite.mode - SpriteMode::MODE_STRETCH;

    sprite.size = Vec2(256.0f, 256.0f);

    sprite.position = Vec2(screensettings.getWidth() * 0.5f - sprite.size.x * 0.5f, screensettings.getHeight() * 0.5f - sprite.size.y * 0.5f);
    
    TYRA_LOG("Sprite Created");

}

void LogoDemo::loadMesh()
{
    ObjLoaderOptions options;
    options.scale = 2.0f;
    options.flipUVs = true;
    auto data = ObjLoader::load(FileUtils::fromCwd("3dShip.obj"), options);
    mesh = std::make_unique<StaticMesh>(data.get());
    
    sPOptions.frustumCulling = Tyra::PipelineFrustumCulling_None;
    TYRA_LOG("Mesh Loaded");

}

}  
