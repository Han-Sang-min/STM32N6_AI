// ModelTypes.hpp
#ifndef CUSTOM_TYPES_HPP
#define CUSTOM_TYPES_HPP

#include <touchgfx/Bitmap.hpp>

typedef struct {
    uint32_t needsRefresh = false;
    touchgfx::BitmapId curr_id;
} CameraData;

typedef struct {
    uint16_t nb_rois = 0;
    uint16_t ready = false;
} AI_Info;

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
} AI_Result;

#endif // CUSTOM_TYPES_HPP
