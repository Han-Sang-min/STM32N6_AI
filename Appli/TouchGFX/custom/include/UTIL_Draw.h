#ifndef UTIL_DRAW_H
#define UTIL_DRAW_H

#include <stdint.h>

class UTIL_Draw {
    public:
        enum PixelFormat {
            PF_ARGB8888,
            PF_RGB565
        };

        enum DrawColor {
            COLOR_WHITE,
            COLOR_BLACK
        };

        void setPixel(uint32_t Xpos, uint32_t Ypos, DrawColor Color);
        void drawLine(uint32_t Xpos1, uint32_t Ypos1, uint32_t Xpos2, uint32_t Ypos2, DrawColor Color);
        void drawRectangle(uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height, DrawColor Color);
        void setBuffer(uint32_t *buf, uint32_t width, uint32_t height, PixelFormat pf);
        void clearBuffer();
        void unsetBuffer();
        uint32_t getColor(DrawColor color);

    private:
        static inline int32_t ABS(int32_t x);

        uint32_t *buf = nullptr;
        uint32_t width = 0;
        uint32_t height = 0;
        PixelFormat pixelFormat;
};

#endif