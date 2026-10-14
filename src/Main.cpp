#include "MainLoop.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
#include <emscripten/val.h>
#endif

#include "application/FileManager.h"

#ifdef __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(my_module)
{
    emscripten::function("processUploadedFile", &FileManager::ProcessUploadedFile);
}
#endif

int main()
{
    MainLoop mainLoop;

    if (!mainLoop.Initialize()) {
        return 1;
    }

    mainLoop.RunLoop();

    return 0;
}
