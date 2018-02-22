#include <SkBitmap.h>
#include <core/SkCanvas.h>
#include <core/SkTypeface.h>

#ifdef _WIN32

#include <SDL.h>

#else

#include <SDL2/SDL.h>

#endif

struct RGBA {
    Uint32 rmask = 0x00ff0000;
    Uint32 gmask = 0x0000ff00;
    Uint32 bmask = 0x000000ff;
    Uint32 amask = 0xff000000;
};

//Create SkBitmap and draw objects.
SkBitmap draw(int w, int h) {
    SkBitmap bitmap;
    bitmap.setInfo(SkImageInfo::Make(w, h, kBGRA_8888_SkColorType, kOpaque_SkAlphaType));
    bitmap.allocPixels();
    SkCanvas canvas(bitmap);
    SkPaint paint;
    canvas.clear(SK_ColorWHITE);
    paint.setAntiAlias(true);
    paint.setARGB(255, 255, 0, 0);
    canvas.drawCircle(80, 80, 40, paint);
    canvas.drawLine(0, 480, w, 480, paint);
    sk_sp<SkTypeface> font(SkTypeface::MakeFromFile("/usr/share/fonts/truetype/ancient-scripts/Aegean_hint.ttf"));
    paint.setTypeface(font);
    paint.setTextSize(150);
    canvas.drawString("Hello Skia", 300, 300, paint);
    paint.setStyle(SkPaint::kStroke_Style);
    paint.setTextSize(60);
    canvas.drawString("中文测试", 300, 600, paint);
    return bitmap;
}

//Create SDL_Rect with SDL_Surface.
SDL_Rect create_rect(SDL_Surface *surface) {
    SDL_Rect src = {0, 0, surface->w, surface->h};
    return src;
}

int main(int args, char *argv[]) {
    SDL_Window *window;
    SDL_DisplayMode mode = {0};
    SDL_Surface *surface;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SkBitmap bitmap;
    RGBA rgba;
    SDL_Rect rect;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GetDesktopDisplayMode(0, &mode);

    window = SDL_CreateWindow("Hello Skia", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mode.w, mode.h,
                              SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
    if (window == NULL) {
        return -1;
    }

    bitmap = draw(mode.w, mode.h);
    surface = SDL_CreateRGBSurfaceFrom(bitmap.getPixels(), mode.w, mode.h, 32, mode.w * 4, rgba.rmask, rgba.gmask,
                                       rgba.bmask, rgba.amask);
    rect = create_rect(surface);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0x00);
    SDL_RenderClear(renderer);

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);

    SDL_Delay(5000);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}