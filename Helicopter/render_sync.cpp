#include "render_sync.h"


std::mutex RenderSync::renderMutex;
bool RenderSync::isLocked = false;