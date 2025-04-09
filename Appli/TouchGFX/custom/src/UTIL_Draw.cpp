#include "UTIL_Draw.h"

void UTIL_Draw::setPixel(uint32_t Xpos, uint32_t Ypos, DrawColor Color)
{
  uint32_t index;
  uint32_t formatted_color;

  index = Ypos * width + Xpos;
  formatted_color = getColor(Color);

  if (pixelFormat == PF_ARGB8888) {
    ((uint32_t*)buf)[index] = formatted_color;
  } else if (pixelFormat == PF_RGB565) {
    ((uint16_t*)buf)[index] = formatted_color;
  }
}

void UTIL_Draw::drawLine(uint32_t Xpos1, uint32_t Ypos1, uint32_t Xpos2, uint32_t Ypos2, DrawColor Color)
{
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
  curpixel = 0;
  int32_t x_diff, y_diff;

  x_diff = Xpos2 - Xpos1;
  y_diff = Ypos2 - Ypos1;

  deltax = ABS(x_diff);         /* The absolute difference between the x's */
  deltay = ABS(y_diff);         /* The absolute difference between the y's */
  x = Xpos1;                       /* Start x off at the first pixel */
  y = Ypos1;                       /* Start y off at the first pixel */

  if (Xpos2 >= Xpos1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }

  if (Ypos2 >= Ypos1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }

  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    numadd = deltay;
    numpixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    numadd = deltax;
    numpixels = deltay;         /* There are more y-values than x-values */
  }

  for (curpixel = 0; curpixel <= numpixels; curpixel++)
  {
    setPixel(x, y, Color);   /* Draw the current pixel */
    num += numadd;                            /* Increase the numerator by the top of the fraction */
    if (num >= den)                           /* Check if numerator >= denominator */
    {
      num -= den;                             /* Calculate the new numerator value */
      x += xinc1;                             /* Change the x as appropriate */
      y += yinc1;                             /* Change the y as appropriate */
    }
    x += xinc2;                               /* Change the x as appropriate */
    y += yinc2;                               /* Change the y as appropriate */
  }
}

void UTIL_Draw::drawRectangle(uint32_t Xpos, uint32_t Ypos, uint32_t RectWidth, uint32_t RectHeight, DrawColor Color)
{
  if (Xpos >= width)
    return ;
    //Xpos = width - 1;
  if (Ypos >= height)
    return ;
    //Ypos = height - 1;
  if (Xpos + RectWidth >= width)
    RectWidth = width - Xpos - 1;
  if (Ypos + RectHeight >= height)
    RectHeight = height - Ypos - 1;

  /* Draw horizontal lines */
  drawLine(Xpos, Ypos, Xpos + RectWidth - 1, Ypos, Color);
  drawLine(Xpos, Ypos + RectHeight - 1, Xpos + RectWidth - 1, Ypos + RectHeight - 1, Color);
  
  /* Draw vertical lines */
  drawLine(Xpos, Ypos, Xpos, Ypos + RectHeight - 1, Color);
  drawLine(Xpos + RectWidth - 1, Ypos, Xpos + RectWidth - 1, Ypos + RectHeight - 1, Color);
}

void UTIL_Draw::setBuffer(uint32_t *buf, uint32_t width, uint32_t height, PixelFormat pf)
{
  this->buf = buf;
  this->width = width;
  this->height = height;
  this->pixelFormat = pf;
}

void UTIL_Draw::clearBuffer()
{
  uint32_t size = width * height;
  if (pixelFormat == PF_ARGB8888) {
      uint32_t *p = (uint32_t*)buf;
      for (uint32_t i = 0; i < size; i++) {
          p[i] = 0;
      }
  } else if (pixelFormat == PF_RGB565) {
      uint16_t *p = (uint16_t*)buf;
      for (uint32_t i = 0; i < size; i++) {
          p[i] = 0;
      }
  }
}

void UTIL_Draw::unsetBuffer()
{
  buf = nullptr;
  width = 0;
  height = 0;
}

uint32_t UTIL_Draw::getColor(DrawColor color)
{
  uint32_t argb;
  switch(color) {
    case COLOR_WHITE:
      if (pixelFormat == PF_ARGB8888)
        argb = 0xFFFFFFFF;
      else if(pixelFormat == PF_RGB565)
        argb = 0xFFFF;
      break;
    case COLOR_BLACK:
      if (pixelFormat == PF_ARGB8888)
        argb = 0xFF000000;
      else if(pixelFormat == PF_RGB565)
        argb = 0x0000;
      break;
  }
  return argb;
}

inline int32_t UTIL_Draw::ABS(int32_t x)
{
  return x > 0 ? x : -x;
}
