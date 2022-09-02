#include "image_viewer.h"

#include "config.h"
#include "def.h"
#include "resourceManager.h"
#include "screen.h"
#include "sdlutils.h"
#include "text_viewer.h"

#define VIEWER_MARGIN 1

ImageViewer::ImageViewer(std::string filename)
    : filename_(std::move(filename))
{
    init();
}

void ImageViewer::init()
{
    image_ = SDLSurfaceUniquePtr { SDL_utils::loadImageToFit(
        filename_, screen.w, screen.h) };
    ok_ = (image_ != nullptr);
    if (!ok_) return;
}

void ImageViewer::onResize()
{
    image_ = nullptr;
    init();
}

void ImageViewer::render(const bool focused) const
{
    SDL_utils::applyPpuScaledSurface(0, 0, image_.get(), screen.surface);
}

// Key press management
const bool ImageViewer::keyPress(const SDL_Event &event)
{
    CWindow::keyPress(event);
    const auto &c = config();
    const auto sym = event.key.keysym.sym;
    if (sym == c.key_system || sym == c.key_parent) {
        m_retVal = -1;
        return true;
    }
    else if (sym == c.key_down || sym == c.key_right) {
        m_retVal = 2;
        return true;
    }
    else if (sym == c.key_up || sym == c.key_left) {
        m_retVal = 1;
        return true;
    }
    return false;
}
