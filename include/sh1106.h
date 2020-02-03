/**
 * Copyright 2018 Brandon Davidson <brad@oatmail.org>
 * copyright 2018 Manfred Mueller-Spaeth <fms1961@gmail.com> (changes, additions)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR 
 * A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **/

#ifndef SH1106_H
#define SH1106_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "mgos_features.h"
#include "mgos_i2c.h"

#include "common/cs_dbg.h"

#include "mgos_init.h"
#include "mgos_sys_config.h"
#include "mgos_system.h"
#include "mgos_config.h"
#include "mgos_gpio.h"

#include "fonts.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


  typedef enum
  {
    SH1106_COLOR_TRANSPARENT = -1,     //< Transparent (not drawing)
    SH1106_COLOR_BLACK = 0,    //< Black (pixel off)
    SH1106_COLOR_WHITE = 1,    //< White (or blue, yellow, pixel on)
    SH1106_COLOR_INVERT = 2,   //< Invert pixel (XOR)
  } mgos_sh1106_color_t;

  /**
   * @brief Standard Mongoose-OS init hook.
   *
   * @return True if module was enabled and successfully initialized.
   */
  bool mgos_sh1106_init (void);

  /**
   * @brief Access the SSD1306 driver handle that is set up via sysconfig.
   *
   * @return Preconfigured SSD1306 driver handle.
   */
  struct mgos_sh1106 *mgos_sh1106_get_global (void);

  /**
   * @brief Initialize the SSD1306 driver with the given params. Typically clients
   * don't need to do that manually; mgos has a global SSD1306 instance that is created
   * with the params given in system config; use `mgos_sh1106_get_global() to get the
   * global instance
   *
   * @param cfg SSD1306 configuration.
   *
   * @return SSD1306 driver handle, or NULL if setup failed.
   */
  struct mgos_sh1106 *mgos_sh1106_create (const struct mgos_config_sh1106 *cfg);

  /**
   * @brief Power down the display, close I2C connection, and free memory.
   *
   * @param oled SSD1306 driver handle.
   */
  void mgos_sh1106_close (struct mgos_sh1106 *oled);

  /**
   * @brief Get screen width.
   *
   * @param oled SSD1306 driver handle
   *
   * @return Screen width, in pixels.
   */
  uint8_t mgos_sh1106_get_width (struct mgos_sh1106 *oled);

  /**
   * @brief Get screen height
   *
   * @param oled SSD1306 driver handle
   *
   * @return Screen height, in pixels.
   */
  uint8_t mgos_sh1106_get_height (struct mgos_sh1106 *oled);

  /**
   * @brief Clear the screen bitmap.
   *
   * @param oled SSD1306 driver handle.
   */
  void mgos_sh1106_clear (struct mgos_sh1106 *oled);

  /**
   * @brief Refresh the display, sending any dirty regions to the OLED controller for display.
   * Call this after you are finished calling any drawing primitives.
   *
   * @param oled SSD1306 driver handle.
   * @param force Redraw the entire bitmap, not just dirty regions.
   */
  void mgos_sh1106_refresh (struct mgos_sh1106 *oled, bool force);

  /**
   * @brief Draw a single pixel.
   *
   * @param oled SSD1306 driver handle.
   * @param x X coordinate.
   * @param y Y coordinate.
   * @param color Pixel color.
   */
  void mgos_sh1106_draw_pixel (struct mgos_sh1106 *oled, int8_t x, int8_t y,
                                mgos_sh1106_color_t color);

  /**
   * @brief Draw a horizontal line.
   *
   * @param oled SSD1306 driver handle.
   * @param x X coordinate.
   * @param y Y coordinate.
   * @param w Line length.
   * @param color Line color.
   */
  void mgos_sh1106_draw_hline (struct mgos_sh1106 *oled, int8_t x, int8_t y, uint8_t w,
                                mgos_sh1106_color_t color);

  /**
   * @brief Draw a vertical line.
   *
   * @param oled SSD1306 driver handle.
   * @param x X coordinate.
   * @param y Y coordinate.
   * @param h Line length.
   * @param color Line color.
   */
  void mgos_sh1106_draw_vline (struct mgos_sh1106 *oled, int8_t x, int8_t y, uint8_t h,
                                mgos_sh1106_color_t color);

  /**
   * @brief Draw an unfilled rectangle.
   *
   * @param oled SSD1306 driver handle.
   * @param x X coordinate.
   * @param y Y coordinate.
   * @param w Rectangle width.
   * @param h Rectangle height.
   * @param color Line color.
   */
  void mgos_sh1106_draw_rectangle (struct mgos_sh1106 *oled, int8_t x, int8_t y, uint8_t w, uint8_t h,
                                    mgos_sh1106_color_t color);

  /**
   * @brief Draw a filled rectangle.
   *
   * @param oled SSD1306 driver handle.
   * @param x X coordinate.
   * @param y Y coordinate.
   * @param w Rectangle width.
   * @param h Rectangle height.
   * @param color Line and fill color.
   */
  void mgos_sh1106_fill_rectangle (struct mgos_sh1106 *oled, int8_t x, int8_t y, uint8_t w, uint8_t h,
                                    mgos_sh1106_color_t color);

  /**
   * @brief Draw an unfilled circle.
   *
   * @param oled SSD1306 driver handle.
   * @param x0 Center X coordinate .
   * @param y0 Center Y coordinate.
   * @param r Radius.
   * @param color Line color.
   */
  void mgos_sh1106_draw_circle (struct mgos_sh1106 *oled, int8_t x0, int8_t y0, uint8_t r, mgos_sh1106_color_t color);

  /**
   * @brief Draw a filled circle.
   *
   * @param oled SSD1306 driver handle.
   * @param x0 Center X coordinate.
   * @param y0 Center Y coordinate.
   * @param r Radius.
   * @param color Line and fill color.
   */
  void mgos_sh1106_fill_circle (struct mgos_sh1106 *oled, int8_t x0, int8_t y0, uint8_t r, mgos_sh1106_color_t color);

  /**
   * @brief Select active font ID.
   *
   * @param oled SSD1306 driver handle.
   * @param font Font index; see `fonts.h`.
   */
  void mgos_sh1106_select_font (struct mgos_sh1106 *oled, uint8_t font);

  /**
   * @brief Draw a single character using the active font and selected colors.
   *
   * @param oled SSD1306 driver handle.
   * @param x X coordinate.
   * @param y Y coordinate.
   * @param c Character to draw.
   * @param foreground Foreground color.
   * @param background Background color.
   *
   * @return Character width in pixels
   */
  uint8_t mgos_sh1106_draw_char (struct mgos_sh1106 *oled, uint8_t x, uint8_t y, unsigned char c,
                                  mgos_sh1106_color_t foreground, mgos_sh1106_color_t background);

  /**
   * @brief Draw a string using the active font and selected colors.
   *
   * @param oled SSD1306 driver handle.
   * @param x X coordinate.
   * @param y Y coordinate.
   * @param str String to draw.
   * @param foreground Foreground color.
   * @param background Background color.
   *
   * @return String witdth in pixels.
   */
  uint8_t mgos_sh1106_draw_string_color (struct mgos_sh1106 *oled, uint8_t x, uint8_t y, const char *str,
                                          mgos_sh1106_color_t foreground, mgos_sh1106_color_t background);

  /**
   * @brief Draw a string using the active font and default colors (white on transparent)
   *
   * @param oled SSD1306 driver handle.
   * @param x X coordinate.
   * @param y Y coordinate.
   * @param str String to draw.
   *
   * @return String width in pixels.
   */
  uint8_t mgos_sh1106_draw_string (struct mgos_sh1106 *oled, uint8_t x, uint8_t y, const char *str);

  /**
   * @brief Measure on-screen width of string if drawn using active font.
   *
   * @param oled SSD1306 driver handle.
   * @param str String to measure.
   *
   * @return String width in pixels.
   */
  uint8_t mgos_sh1106_measure_string (struct mgos_sh1106 *oled, const char *str);

  /**
   * @brief Get the height of the active font.
   *
   * @param oled SSD1306 driver handle.
   *
   * @return Font height in pixels.
   */
  uint8_t mgos_sh1106_get_font_height (struct mgos_sh1106 *oled);

  /**
   * @brief Get the inter-character font spacing.
   *
   * @param oled SSD1306 driver handle.
   *
   * @return Font inter-character spacing in pixels.
   */
  uint8_t mgos_sh1106_get_font_c (struct mgos_sh1106 *oled);

  /**
   * @brief Invert or restore the display. Inverting the display flips the bitmask -
   * 1 is black (off) and 0 is white (on).
   *
   * @param oled SSD1306 driver handle.
   * @param invert Enable inversion.
   */
  void mgos_sh1106_invert_display (struct mgos_sh1106 *oled, bool invert);

  /**
   * @brief Flip the display render order. May not do exactly what you expect, depending on
   * the display's segment remap configuration.
   *
   * @param oled SSD1306 driver handle.
   * @param horizontal Enable horizontal flipping.
   * @param vertical Enable vertical flipping
   */
  void mgos_sh1106_flip_display (struct mgos_sh1106 *oled, bool horizontal, bool vertical);

  /**
   * @brief Rotates the display with an amount of 180 degrees

   * @param oled SSD1306 driver handle.
   * @param bool alt, if the current way won't work, try the second one
   */
  void mgos_sh1106_rotate_display (struct mgos_sh1106 *oled, bool alt);

  /**
   * @brief Copy pre-rendered bytes directly into the bitmap.
   *
   * @param oled SSD1306 driver handle.
   * @param data Array containing bytes to copy into buffer.
   * @param length Length to copy (unchecked) from source buffer.
   */
  void mgos_sh1106_update_buffer (struct mgos_sh1106 *oled, uint8_t * data, uint16_t length);

  /**
   * @brief Sends a command without parameters to the display
   *
   * @param int command
   */
  void mgos_sh1106_command (struct mgos_sh1106 *oled, uint8_t cmd);

  /**
   * @brief Start the displays functionality
   */
  void mgos_sh1106_start (struct mgos_sh1106 *oled);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SSD1306_H */
