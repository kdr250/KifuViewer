#include "application/Application.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
#include <emscripten/val.h>
#endif

Application application;

int main()
{
    if (!application.Initialize()) {
        return 1;
    }

    application.RunLoop();

    return 0;
}

#ifdef __EMSCRIPTEN__
void ProcessUploadedFile(std::string fileName)
{
    application.ProcessUploadedFile(fileName);
}

EMSCRIPTEN_BINDINGS(my_module)
{
    emscripten::function("processUploadedFile", &ProcessUploadedFile);
}
#endif
