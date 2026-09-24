#include "MainLoop.h"

int main()
{
    MainLoop mainLoop;

    if (!mainLoop.Initialize()) {
        return 1;
    }

    mainLoop.RunLoop();

    return 0;
}
