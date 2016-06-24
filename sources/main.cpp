#include <SdlContext.hh>
#include "menu.hh"
#include "Core.hpp"
#include "RandomMapGenerator.hpp"
#include "menuexception.hh"
#include <assert.h>

int main()
{
  gdl::SdlContext context;
  Menu::ReturnCode code;

  if (!context.start(1920, 1080, "Bomberman", SDL_INIT_VIDEO, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN)) {
    throw "pas de chance";
  }

  try
  {
    Menu menu(context);
    menu.initialize();
    while ((code = menu.updateCode()) == Menu::CONTINUECODE) {
      menu.draw();
    }

  }
  catch (const TextureNotFound &)
  {
    std::cerr << "Impossible to load some textures, exiting..." << std::endl;
    return -1;
  }

  return 0;
}
