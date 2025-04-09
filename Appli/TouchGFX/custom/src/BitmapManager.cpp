#include "BitmapManager.hpp"

using namespace touchgfx;

void BitmapManager::createBitmap(int width, int height, Bitmap::BitmapFormat format, BitmapIndex index)
{
    bmpId[index] = Bitmap::dynamicBitmapCreate(width, height, format);
}

BitmapId BitmapManager::getBitmapId(BitmapIndex index)
{
    return bmpId[index];
}

uint8_t *BitmapManager::getBitmapAddr(BitmapIndex index)
{
    BitmapId id;

    id = bmpId[index];
    return (uint8_t*)Bitmap::dynamicBitmapGetAddress(id);
}

void BitmapManager::releaseBitmap(int index)
{
    if (bmpId[index] != BITMAP_INVALID) {
        Bitmap::dynamicBitmapDelete(bmpId[index]);
        bmpId[index] = BITMAP_INVALID;
    }
}
