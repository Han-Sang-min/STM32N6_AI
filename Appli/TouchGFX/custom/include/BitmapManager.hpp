#ifndef BITMAP_MANAGER_HPP
#define BITMAP_MANAGER_HPP

#include "touchgfx/Bitmap.hpp"

using namespace touchgfx;

class BitmapManager {
public:
    enum BitmapIndex {
        CAMERA1,
        CAMERA2,
        AI
    };

    static void createBitmap(int width, int height, Bitmap::BitmapFormat format, BitmapIndex index);
    static BitmapId getBitmapId(BitmapIndex index);
    static uint8_t *getBitmapAddr(BitmapIndex index);
    static void releaseBitmap(int index);

private:
    const static int NB_BITMAP = 3;
    inline static BitmapId bmpId[3] = {BITMAP_INVALID, BITMAP_INVALID, BITMAP_INVALID};
};

#endif // BITMAP_MANAGER_HPP