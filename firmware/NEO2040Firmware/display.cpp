#include "display.h"
#include "addr.h"
#include <PicoDVI.h>

// #define DEBUG_DISPLAY

// Pico HDMI for Olimex Neo6502
static const struct dvi_serialiser_cfg dvi_cfg = {
    .pio = DVI_DEFAULT_PIO_INST,
    .sm_tmds = {0, 1, 2},
    .pins_tmds = {14, 18, 16},
    .pins_clk = 12,
    .invert_diffpairs = true};
DVIGFX8 display(DVI_RES_320x240p60, true, dvi_cfg);

typedef struct
{
  uint8_t width;
  uint8_t height;
  uint8_t x; // For xpos > 255: flags bit 0 = 1
  uint8_t y;
  uint8_t flags; // Bit 0: X > 255 | Bit 1: Visibility
  uint8_t color;
  union
  {
    uint16_t address;
    struct
    {
      uint8_t address_high;
      uint8_t address_low;
    };
  };
} TSprite, *TSpritePtr;

typedef struct
{
  uint8_t count;
  uint16_t address;
  uint8_t *flags;
  uint8_t *xpos;
  uint8_t *ypos;
  uint8_t *color;
  uint8_t *width;
  uint8_t *height;
  uint8_t *data_lo;
  uint8_t *data_hi;
} TSpriteDataBlock, *TSpriteDataBlockPtr;

struct
{
  uint16_t x;       // X position in pixel
  uint16_t y;       // Y position in pixel
  uint8_t offset_y; // Top offset in pixel
  uint8_t offset_x; // Left offset in pixel

  uint8_t textbuffer[LINES * LINECHARS];
  uint8_t currentColor;
  uint8_t currentXpos; // X position in character
  uint8_t currentYpos; // Y position in character

  uint32_t needsRefresh; // If > 0: Screen will be updated.
  TSprite sprites[32];
  TSpriteDataBlock sdb;
} screendata;

uint8_t buffer[] = {12, 15, 67};

inline __attribute__((always_inline))
uint16_t
getSpriteOffset(TContextPtr ctx, uint8_t index)
{
  return ((screendata.sdb.data_hi[index] << 8) | screendata.sdb.data_lo[index]);
}

inline __attribute__((always_inline))
uint8_t *
getSpriteDataPtr(TContextPtr ctx, uint8_t index)
{
  return ctx->memory + getSpriteOffset(ctx, index);
}

inline __attribute__((always_inline))
uint16_t
convertColor565(uint8_t r, uint8_t g, uint8_t b)
{
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

inline __attribute__((always_inline)) void setColor(uint8_t vColor)
{
  screendata.currentColor = vColor;
  display.setTextColor(vColor);
}

void initDisplay(TContextPtr ctx)
{

  if (!display.begin())
  {
#ifdef DEBUG_DISPLAY
    Serial.println("ERROR: not enough RAM available");
#endif
    for (;;)
      ;
  }
  screendata.offset_x = 1;
  screendata.offset_y = 1;

  display.setColor(0, convertColor565(0, 0, 0));         // Black
  display.setColor(1, convertColor565(128, 0, 0));       // Maroon
  display.setColor(2, convertColor565(0, 128, 0));       // Green
  display.setColor(3, convertColor565(128, 128, 0));     // Olive
  display.setColor(4, convertColor565(0, 0, 128));       // Navy
  display.setColor(5, convertColor565(128, 0, 128));     // Purple
  display.setColor(6, convertColor565(0, 128, 128));     // Teal
  display.setColor(7, convertColor565(192, 192, 192));   // Silver
  display.setColor(8, convertColor565(128, 128, 128));   // Grey
  display.setColor(9, convertColor565(255, 0, 0));       // Red
  display.setColor(10, convertColor565(0, 255, 0));      // Lime
  display.setColor(11, convertColor565(255, 255, 0));    // Yellow
  display.setColor(12, convertColor565(0, 0, 255));      // Blue
  display.setColor(13, convertColor565(255, 0, 255));    // Fuchsia
  display.setColor(14, convertColor565(0, 255, 255));    // Aqua
  display.setColor(15, convertColor565(255, 255, 255));  // White
  display.setColor(16, convertColor565(0, 0, 0));        // Grey0
  display.setColor(17, convertColor565(0, 0, 95));       // NavyBlue
  display.setColor(18, convertColor565(0, 0, 135));      // DarkBlue
  display.setColor(19, convertColor565(0, 0, 175));      // Blue3
  display.setColor(20, convertColor565(0, 0, 215));      // Blue2
  display.setColor(21, convertColor565(0, 0, 255));      // Blue1
  display.setColor(22, convertColor565(0, 95, 0));       // DarkGreen
  display.setColor(23, convertColor565(0, 95, 95));      // DeepSkyBlue4
  display.setColor(24, convertColor565(0, 95, 135));     // DeepSkyBlue4
  display.setColor(25, convertColor565(0, 95, 175));     // DeepSkyBlue4
  display.setColor(26, convertColor565(0, 95, 215));     // DodgerBlue3
  display.setColor(27, convertColor565(0, 95, 255));     // DodgerBlue2
  display.setColor(28, convertColor565(0, 135, 0));      // Green4
  display.setColor(29, convertColor565(0, 135, 95));     // SpringGreen4
  display.setColor(30, convertColor565(0, 135, 135));    // Turquoise4
  display.setColor(31, convertColor565(0, 135, 175));    // DeepSkyBlue3
  display.setColor(32, convertColor565(0, 135, 215));    // DeepSkyBlue3
  display.setColor(33, convertColor565(0, 135, 255));    // DodgerBlue1
  display.setColor(34, convertColor565(0, 175, 0));      // Green3
  display.setColor(35, convertColor565(0, 175, 95));     // SpringGreen3
  display.setColor(36, convertColor565(0, 175, 135));    // DarkCyan
  display.setColor(37, convertColor565(0, 175, 175));    // LightSeaGreen
  display.setColor(38, convertColor565(0, 175, 215));    // DeepSkyBlue2
  display.setColor(39, convertColor565(0, 175, 255));    // DeepSkyBlue1
  display.setColor(40, convertColor565(0, 215, 0));      // Green3
  display.setColor(41, convertColor565(0, 215, 95));     // SpringGreen3
  display.setColor(42, convertColor565(0, 215, 135));    // SpringGreen2
  display.setColor(43, convertColor565(0, 215, 175));    // Cyan3
  display.setColor(44, convertColor565(0, 215, 215));    // DarkTurquoise
  display.setColor(45, convertColor565(0, 215, 255));    // Turquoise2
  display.setColor(46, convertColor565(0, 255, 0));      // Green1
  display.setColor(47, convertColor565(0, 255, 95));     // SpringGreen2
  display.setColor(48, convertColor565(0, 255, 135));    // SpringGreen1
  display.setColor(49, convertColor565(0, 255, 175));    // MediumSpringGreen
  display.setColor(50, convertColor565(0, 255, 215));    // Cyan2
  display.setColor(51, convertColor565(0, 255, 255));    // Cyan1
  display.setColor(52, convertColor565(95, 0, 0));       // DarkRed
  display.setColor(53, convertColor565(95, 0, 95));      // DeepPink4
  display.setColor(54, convertColor565(95, 0, 135));     // Purple4
  display.setColor(55, convertColor565(95, 0, 175));     // Purple4
  display.setColor(56, convertColor565(95, 0, 215));     // Purple3
  display.setColor(57, convertColor565(95, 0, 255));     // BlueViolet
  display.setColor(58, convertColor565(95, 95, 0));      // Orange4
  display.setColor(59, convertColor565(95, 95, 95));     // Grey37
  display.setColor(60, convertColor565(95, 95, 135));    // MediumPurple4
  display.setColor(61, convertColor565(95, 95, 175));    // SlateBlue3
  display.setColor(62, convertColor565(95, 95, 215));    // SlateBlue3
  display.setColor(63, convertColor565(95, 95, 255));    // RoyalBlue1
  display.setColor(64, convertColor565(95, 135, 0));     // Chartreuse4
  display.setColor(65, convertColor565(95, 135, 95));    // DarkSeaGreen4
  display.setColor(66, convertColor565(95, 135, 135));   // PaleTurquoise4
  display.setColor(67, convertColor565(95, 135, 175));   // SteelBlue
  display.setColor(68, convertColor565(95, 135, 215));   // SteelBlue3
  display.setColor(69, convertColor565(95, 135, 255));   // CornflowerBlue
  display.setColor(70, convertColor565(95, 175, 0));     // Chartreuse3
  display.setColor(71, convertColor565(95, 175, 95));    // DarkSeaGreen4
  display.setColor(72, convertColor565(95, 175, 135));   // CadetBlue
  display.setColor(73, convertColor565(95, 175, 175));   // CadetBlue
  display.setColor(74, convertColor565(95, 175, 215));   // SkyBlue3
  display.setColor(75, convertColor565(95, 175, 255));   // SteelBlue1
  display.setColor(76, convertColor565(95, 215, 0));     // Chartreuse3
  display.setColor(77, convertColor565(95, 215, 95));    // PaleGreen3
  display.setColor(78, convertColor565(95, 215, 135));   // SeaGreen3
  display.setColor(79, convertColor565(95, 215, 175));   // Aquamarine3
  display.setColor(80, convertColor565(95, 215, 215));   // MediumTurquoise
  display.setColor(81, convertColor565(95, 215, 255));   // SteelBlue1
  display.setColor(82, convertColor565(95, 255, 0));     // Chartreuse2
  display.setColor(83, convertColor565(95, 255, 95));    // SeaGreen2
  display.setColor(84, convertColor565(95, 255, 135));   // SeaGreen1
  display.setColor(85, convertColor565(95, 255, 175));   // SeaGreen1
  display.setColor(86, convertColor565(95, 255, 215));   // Aquamarine1
  display.setColor(87, convertColor565(95, 255, 255));   // DarkSlateGray2
  display.setColor(88, convertColor565(135, 0, 0));      // DarkRed
  display.setColor(89, convertColor565(135, 0, 95));     // DeepPink4
  display.setColor(90, convertColor565(135, 0, 135));    // DarkMagenta
  display.setColor(91, convertColor565(135, 0, 175));    // DarkMagenta
  display.setColor(92, convertColor565(135, 0, 215));    // DarkViolet
  display.setColor(93, convertColor565(135, 0, 255));    // Purple
  display.setColor(94, convertColor565(135, 95, 0));     // Orange4
  display.setColor(95, convertColor565(135, 95, 95));    // LightPink4
  display.setColor(96, convertColor565(135, 95, 135));   // Plum4
  display.setColor(97, convertColor565(135, 95, 175));   // MediumPurple3
  display.setColor(98, convertColor565(135, 95, 215));   // MediumPurple3
  display.setColor(99, convertColor565(135, 95, 255));   // SlateBlue1
  display.setColor(100, convertColor565(135, 135, 0));   // Yellow4
  display.setColor(101, convertColor565(135, 135, 95));  // Wheat4
  display.setColor(102, convertColor565(135, 135, 135)); // Grey53
  display.setColor(103, convertColor565(135, 135, 175)); // LightSlateGrey
  display.setColor(104, convertColor565(135, 135, 215)); // MediumPurple
  display.setColor(105, convertColor565(135, 135, 255)); // LightSlateBlue
  display.setColor(106, convertColor565(135, 175, 0));   // Yellow4
  display.setColor(107, convertColor565(135, 175, 95));  // DarkOliveGreen3
  display.setColor(108, convertColor565(135, 175, 135)); // DarkSeaGreen
  display.setColor(109, convertColor565(135, 175, 175)); // LightSkyBlue3
  display.setColor(110, convertColor565(135, 175, 215)); // LightSkyBlue3
  display.setColor(111, convertColor565(135, 175, 255)); // SkyBlue2
  display.setColor(112, convertColor565(135, 215, 0));   // Chartreuse2
  display.setColor(113, convertColor565(135, 215, 95));  // DarkOliveGreen3
  display.setColor(114, convertColor565(135, 215, 135)); // PaleGreen3
  display.setColor(115, convertColor565(135, 215, 175)); // DarkSeaGreen3
  display.setColor(116, convertColor565(135, 215, 215)); // DarkSlateGray3
  display.setColor(117, convertColor565(135, 215, 255)); // SkyBlue1
  display.setColor(118, convertColor565(135, 255, 0));   // Chartreuse1
  display.setColor(119, convertColor565(135, 255, 95));  // LightGreen
  display.setColor(120, convertColor565(135, 255, 135)); // LightGreen
  display.setColor(121, convertColor565(135, 255, 175)); // PaleGreen1
  display.setColor(122, convertColor565(135, 255, 215)); // Aquamarine1
  display.setColor(123, convertColor565(135, 255, 255)); // DarkSlateGray1
  display.setColor(124, convertColor565(175, 0, 0));     // Red3
  display.setColor(125, convertColor565(175, 0, 95));    // DeepPink4
  display.setColor(126, convertColor565(175, 0, 135));   // MediumVioletRed
  display.setColor(127, convertColor565(175, 0, 175));   // Magenta3
  display.setColor(128, convertColor565(175, 0, 215));   // DarkViolet
  display.setColor(129, convertColor565(175, 0, 255));   // Purple
  display.setColor(130, convertColor565(175, 95, 0));    // DarkOrange3
  display.setColor(131, convertColor565(175, 95, 95));   // IndianRed
  display.setColor(132, convertColor565(175, 95, 135));  // HotPink3
  display.setColor(133, convertColor565(175, 95, 175));  // MediumOrchid3
  display.setColor(134, convertColor565(175, 95, 215));  // MediumOrchid
  display.setColor(135, convertColor565(175, 95, 255));  // MediumPurple2
  display.setColor(136, convertColor565(175, 135, 0));   // DarkGoldenrod
  display.setColor(137, convertColor565(175, 135, 95));  // LightSalmon3
  display.setColor(138, convertColor565(175, 135, 135)); // RosyBrown
  display.setColor(139, convertColor565(175, 135, 175)); // Grey63
  display.setColor(140, convertColor565(175, 135, 215)); // MediumPurple2
  display.setColor(141, convertColor565(175, 135, 255)); // MediumPurple1
  display.setColor(142, convertColor565(175, 175, 0));   // Gold3
  display.setColor(143, convertColor565(175, 175, 95));  // DarkKhaki
  display.setColor(144, convertColor565(175, 175, 135)); // NavajoWhite3
  display.setColor(145, convertColor565(175, 175, 175)); // Grey69
  display.setColor(146, convertColor565(175, 175, 215)); // LightSteelBlue3
  display.setColor(147, convertColor565(175, 175, 255)); // LightSteelBlue
  display.setColor(148, convertColor565(175, 215, 0));   // Yellow3
  display.setColor(149, convertColor565(175, 215, 95));  // DarkOliveGreen3
  display.setColor(150, convertColor565(175, 215, 135)); // DarkSeaGreen3
  display.setColor(151, convertColor565(175, 215, 175)); // DarkSeaGreen2
  display.setColor(152, convertColor565(175, 215, 215)); // LightCyan3
  display.setColor(153, convertColor565(175, 215, 255)); // LightSkyBlue1
  display.setColor(154, convertColor565(175, 255, 0));   // GreenYellow
  display.setColor(155, convertColor565(175, 255, 95));  // DarkOliveGreen2
  display.setColor(156, convertColor565(175, 255, 135)); // PaleGreen1
  display.setColor(157, convertColor565(175, 255, 175)); // DarkSeaGreen2
  display.setColor(158, convertColor565(175, 255, 215)); // DarkSeaGreen1
  display.setColor(159, convertColor565(175, 255, 255)); // PaleTurquoise1
  display.setColor(160, convertColor565(215, 0, 0));     // Red3
  display.setColor(161, convertColor565(215, 0, 95));    // DeepPink3
  display.setColor(162, convertColor565(215, 0, 135));   // DeepPink3
  display.setColor(163, convertColor565(215, 0, 175));   // Magenta3
  display.setColor(164, convertColor565(215, 0, 215));   // Magenta3
  display.setColor(165, convertColor565(215, 0, 255));   // Magenta2
  display.setColor(166, convertColor565(215, 95, 0));    // DarkOrange3
  display.setColor(167, convertColor565(215, 95, 95));   // IndianRed
  display.setColor(168, convertColor565(215, 95, 135));  // HotPink3
  display.setColor(169, convertColor565(215, 95, 175));  // HotPink2
  display.setColor(170, convertColor565(215, 95, 215));  // Orchid
  display.setColor(171, convertColor565(215, 95, 255));  // MediumOrchid1
  display.setColor(172, convertColor565(215, 135, 0));   // Orange3
  display.setColor(173, convertColor565(215, 135, 95));  // LightSalmon3
  display.setColor(174, convertColor565(215, 135, 135)); // LightPink3
  display.setColor(175, convertColor565(215, 135, 175)); // Pink3
  display.setColor(176, convertColor565(215, 135, 215)); // Plum3
  display.setColor(177, convertColor565(215, 135, 255)); // Violet
  display.setColor(178, convertColor565(215, 175, 0));   // Gold3
  display.setColor(179, convertColor565(215, 175, 95));  // LightGoldenrod3
  display.setColor(180, convertColor565(215, 175, 135)); // Tan
  display.setColor(181, convertColor565(215, 175, 175)); // MistyRose3
  display.setColor(182, convertColor565(215, 175, 215)); // Thistle3
  display.setColor(183, convertColor565(215, 175, 255)); // Plum2
  display.setColor(184, convertColor565(215, 215, 0));   // Yellow3
  display.setColor(185, convertColor565(215, 215, 95));  // Khaki3
  display.setColor(186, convertColor565(215, 215, 135)); // LightGoldenrod2
  display.setColor(187, convertColor565(215, 215, 175)); // LightYellow3
  display.setColor(188, convertColor565(215, 215, 215)); // Grey84
  display.setColor(189, convertColor565(215, 215, 255)); // LightSteelBlue1
  display.setColor(190, convertColor565(215, 255, 0));   // Yellow2
  display.setColor(191, convertColor565(215, 255, 95));  // DarkOliveGreen1
  display.setColor(192, convertColor565(215, 255, 135)); // DarkOliveGreen1
  display.setColor(193, convertColor565(215, 255, 175)); // DarkSeaGreen1
  display.setColor(194, convertColor565(215, 255, 215)); // Honeydew2
  display.setColor(195, convertColor565(215, 255, 255)); // LightCyan1
  display.setColor(196, convertColor565(255, 0, 0));     // Red1
  display.setColor(197, convertColor565(255, 0, 95));    // DeepPink2
  display.setColor(198, convertColor565(255, 0, 135));   // DeepPink1
  display.setColor(199, convertColor565(255, 0, 175));   // DeepPink1
  display.setColor(200, convertColor565(255, 0, 215));   // Magenta2
  display.setColor(201, convertColor565(255, 0, 255));   // Magenta1
  display.setColor(202, convertColor565(255, 95, 0));    // OrangeRed1
  display.setColor(203, convertColor565(255, 95, 95));   // IndianRed1
  display.setColor(204, convertColor565(255, 95, 135));  // IndianRed1
  display.setColor(205, convertColor565(255, 95, 175));  // HotPink
  display.setColor(206, convertColor565(255, 95, 215));  // HotPink
  display.setColor(207, convertColor565(255, 95, 255));  // MediumOrchid1
  display.setColor(208, convertColor565(255, 135, 0));   // DarkOrange
  display.setColor(209, convertColor565(255, 135, 95));  // Salmon1
  display.setColor(210, convertColor565(255, 135, 135)); // LightCoral
  display.setColor(211, convertColor565(255, 135, 175)); // PaleVioletRed1
  display.setColor(212, convertColor565(255, 135, 215)); // Orchid2
  display.setColor(213, convertColor565(255, 135, 255)); // Orchid1
  display.setColor(214, convertColor565(255, 175, 0));   // Orange1
  display.setColor(215, convertColor565(255, 175, 95));  // SandyBrown
  display.setColor(216, convertColor565(255, 175, 135)); // LightSalmon1
  display.setColor(217, convertColor565(255, 175, 175)); // LightPink1
  display.setColor(218, convertColor565(255, 175, 215)); // Pink1
  display.setColor(219, convertColor565(255, 175, 255)); // Plum1
  display.setColor(220, convertColor565(255, 215, 0));   // Gold1
  display.setColor(221, convertColor565(255, 215, 95));  // LightGoldenrod2
  display.setColor(222, convertColor565(255, 215, 135)); // LightGoldenrod2
  display.setColor(223, convertColor565(255, 215, 175)); // NavajoWhite1
  display.setColor(224, convertColor565(255, 215, 215)); // MistyRose1
  display.setColor(225, convertColor565(255, 215, 255)); // Thistle1
  display.setColor(226, convertColor565(255, 255, 0));   // Yellow1
  display.setColor(227, convertColor565(255, 255, 95));  // LightGoldenrod1
  display.setColor(228, convertColor565(255, 255, 135)); // Khaki1
  display.setColor(229, convertColor565(255, 255, 175)); // Wheat1
  display.setColor(230, convertColor565(255, 255, 215)); // Cornsilk1
  display.setColor(231, convertColor565(255, 255, 255)); // Grey100
  display.setColor(232, convertColor565(8, 8, 8));       // Grey3
  display.setColor(233, convertColor565(18, 18, 18));    // Grey7
  display.setColor(234, convertColor565(28, 28, 28));    // Grey11
  display.setColor(235, convertColor565(38, 38, 38));    // Grey15
  display.setColor(236, convertColor565(48, 48, 48));    // Grey19
  display.setColor(237, convertColor565(58, 58, 58));    // Grey23
  display.setColor(238, convertColor565(68, 68, 68));    // Grey27
  display.setColor(239, convertColor565(78, 78, 78));    // Grey30
  display.setColor(240, convertColor565(88, 88, 88));    // Grey35
  display.setColor(241, convertColor565(98, 98, 98));    // Grey39
  display.setColor(242, convertColor565(108, 108, 108)); // Grey42
  display.setColor(243, convertColor565(118, 118, 118)); // Grey46
  display.setColor(244, convertColor565(128, 128, 128)); // Grey50
  display.setColor(245, convertColor565(138, 138, 138)); // Grey54
  display.setColor(246, convertColor565(148, 148, 148)); // Grey58
  display.setColor(247, convertColor565(158, 158, 158)); // Grey62
  display.setColor(248, convertColor565(168, 168, 168)); // Grey66
  display.setColor(249, convertColor565(178, 178, 178)); // Grey70
  display.setColor(250, convertColor565(188, 188, 188)); // Grey74
  display.setColor(251, convertColor565(198, 198, 198)); // Grey78
  display.setColor(252, convertColor565(208, 208, 208)); // Grey82
  display.setColor(253, convertColor565(218, 218, 218)); // Grey85
  display.setColor(254, convertColor565(228, 228, 228)); // Grey89
  display.setColor(255, convertColor565(238, 238, 238)); // Grey93

  // Clear back framebuffer
  display.fillScreen(0);
  display.setFont();       // Use default font
  display.setCursor(0, 0); // Initial cursor position
  display.setTextSize(1);  // Default size
  display.setTextWrap(false);
  display.swap(false, true); // Duplicate same palette into front & back buffers
  screendata.needsRefresh = 1;
  display.setCursor(1, 0);
  setColor(255);
};

void setCursor(TContextPtr ctx, uint8_t x, uint8_t y)
{
  uint8_t ox(screendata.currentXpos);
  uint8_t oy(screendata.currentYpos);

  screendata.currentXpos = x;
  screendata.currentYpos = y;

  if (x >= LINECHARS && (ctx->reg.DISCR & AUTO_WRAP_FLAG))
  {
    screendata.currentXpos = (x % LINECHARS);
    screendata.currentYpos += (x / LINECHARS);
  };

  screendata.x = screendata.currentXpos * FONT_CHAR_WIDTH + screendata.offset_x;
  screendata.y = screendata.currentYpos * FONT_CHAR_HEIGHT + screendata.offset_y;

  display.setCursor(screendata.x, screendata.y);
  if (ctx->reg.DISCR && SHOW_CURSOR_FLAG)
  {
    // If there is a change and we show the cursor,
    // we need to refresh the screen.
    screendata.needsRefresh++;
  }
}

void setCursorX(TContextPtr ctx, uint8_t x)
{
  setCursor(ctx, x, screendata.currentYpos);
}

void setCursorY(TContextPtr ctx, uint8_t y)
{
  setCursor(ctx, screendata.currentXpos, y);
}

void getCursorX(TContextPtr ctx)
{
  ctx->reg.DIS00 = screendata.currentXpos;
}

void getCursorY(TContextPtr ctx)
{
  ctx->reg.DIS00 = screendata.currentYpos;
}

void updateDisplay()
{
  if (screendata.needsRefresh)
  {
    display.swap(true, false);
  };
  screendata.needsRefresh = 0;
}

void writeChar(TContextPtr ctx, uint8_t c)
{
  // Cursor position is off screen, do nothing
  if (screendata.currentXpos >= LINECHARS || screendata.currentYpos >= LINES)
    return;

  display.write(c);
  screendata.needsRefresh++;
  // Check, if we need to adjust the cursor
  // automatically
  if (ctx->reg.DISCR && ADJUST_CURSOR_FLAG)
  {
    setCursor(ctx, screendata.currentXpos + 1, screendata.currentYpos);
  }
}

const TSpritePtr getSprite(const TContextPtr ctx)
{
  return screendata.sprites + (ctx->reg.DIS00 & 0x1f);
}

void executeCommand(TContextPtr ctx)
{

  switch (ctx->reg.DISCMD)
  {
  case CMD_NOP:
    break;
  case CMD_SET_CURSOR_X:
    setCursorX(ctx, ctx->reg.DIS00);
    break;
  case CMD_SET_CURSOR_Y:
    setCursorY(ctx, ctx->reg.DIS00);
    break;
  case CMD_WRITE_CHAR:
    writeChar(ctx, ctx->reg.DIS00);
    screendata.needsRefresh++;
    break;
  case CMD_SET_FG_COLOR:
    setColor(ctx->reg.DIS00);
    break;
  case CMD_GET_CURSOR_X:
    getCursorX(ctx);
    break;
  case CMD_GET_CURSOR_Y:
    getCursorY(ctx);
    break;

  case CMD_SET_SDB:
  {
    screendata.sdb.address = ((ctx->reg.DIS01 << 8) | ctx->reg.DIS00);
    screendata.sdb.count = ctx->reg.DIS02;
    screendata.sdb.flags = ctx->memory + screendata.sdb.address;
    screendata.sdb.xpos = screendata.sdb.flags + screendata.sdb.count;
    screendata.sdb.ypos = screendata.sdb.xpos + screendata.sdb.count;
    screendata.sdb.color = screendata.sdb.ypos + screendata.sdb.count;
    screendata.sdb.width = screendata.sdb.color + screendata.sdb.count;
    screendata.sdb.height = screendata.sdb.width + screendata.sdb.count;
    screendata.sdb.data_lo = screendata.sdb.height + screendata.sdb.count;
    screendata.sdb.data_hi = screendata.sdb.data_lo + screendata.sdb.count;

    Serial.printf(
        "Sprite initalisation: Address %04x | Count %02d | width %02d | height %02d\n",
        screendata.sdb.address,
        screendata.sdb.count,
        screendata.sdb.width[0],
        screendata.sdb.height[0]);

    uint16_t offset = getSpriteOffset(ctx, 0);
  };
  break;
  }
  ctx->reg.DISCR &= 0x7f; // Clear IRQ flag. Leave the rest
}

uint8_t HEXVALUES[] = "0123456789ABCDEF";

inline __attribute__((always_inline))
void writeHexByte(TContextPtr ctx, uint8_t c) {
  writeChar(ctx, HEXVALUES[c & 0xff]);
  writeChar(ctx, HEXVALUES[(c >> 8) & 0xff]);
}

inline __attribute__((always_inline))
uint8_t getSpriteXPos(uint8_t index) {
  return screendata.sdb.xpos[index];
}

inline __attribute__((always_inline))
uint8_t getSpriteYPos(uint8_t index) {
  return screendata.sdb.ypos[index];
}

inline __attribute__((always_inline))
uint8_t getSpriteWidth(uint8_t index) {
  return screendata.sdb.width[index];
}

inline __attribute__((always_inline))
uint8_t getSpriteHeight(uint8_t index) {
  return screendata.sdb.height[index];
}

inline __attribute__((always_inline))
uint8_t getSpriteColor(uint8_t index) {
  return screendata.sdb.color[index];
}

void drawSprites(TContextPtr ctx)
{
  uint8_t x(screendata.currentXpos), y(screendata.currentYpos), c(screendata.currentColor);
  setCursor(ctx, 5, 18);
  writeHexByte(ctx, ctx->reg.DISCR);
  display.fillScreen(GREEN);
  if (ctx->reg.DISCR & 0x40)
  {
    writeChar(ctx, ' ');
    writeHexByte(ctx, screendata.sdb.count);    
    for (uint8_t i = 0; i < screendata.sdb.count; i++)
    {
      if (screendata.sdb.flags[i] & 0x80)
      {
        display.drawBitmap(
            getSpriteXPos(i),
            getSpriteYPos(i),
            getSpriteDataPtr(ctx, i),
            getSpriteWidth(i),
            getSpriteHeight(i),
            getSpriteColor(i));
      };
    };
    screendata.needsRefresh++;
  }
  else
  {
    writeChar(ctx, 'N');
    writeChar(ctx, ' ');
    writeHexByte(ctx, screendata.sdb.xpos[0]);
  };
  setCursor(ctx, x, y);
}

boolean memReadDisplayRegister(TContextPtr ctx)
{
  if (ctx->address < REG_DIS_START || ctx->address > REG_DIS_END)
    return false;
  ctx->data = ctx->reg.displayRegister[ctx->address - REG_DIS_START];
  return true;
}

boolean memWriteDisplayRegister(TContextPtr ctx)
{
  if (ctx->address < REG_DIS_START || ctx->address > REG_DIS_END)
    return false;

#ifdef DEBUG_DISPLAY
  Serial.printf("Display write: [%04X] := %02X\n", ctx->address, ctx->data);
#endif

  // If the IRQ flag is set, we do not change anything, but
  // still the write request is handled.
  if (ctx->reg.DISCR & 0x80)
  {
#ifdef DEBUG_DISPLAY
    Serial.println("IRQ Flag for display set. Register stay unchanged.");
#endif
    return true;
  }

  ctx->reg.displayRegister[ctx->address - REG_DIS_START] = ctx->data;

  // Check for IRQ Flag
  if (ctx->reg.DISCR & 0x80)
  {

// If the IRQ flag is set, we know that it was set through this write
// instruction. This means, we are requested to execute the
// prepared command.
#ifdef DEBUG_DISPLAY
    Serial.printf("IRQ Flag for display set. Executing command. %02x\n", ctx->reg.DISCMD);
#endif
    executeCommand(ctx); // Execute command and clear irq flag
  }
  return true;
}

void animateAlien(TContextPtr ctx)
{
  uint8_t color = screendata.sdb.color[0];
  ctx->reg.DISCR |= 0x40;
  screendata.sdb.flags[0] |= 0x80;
  screendata.sdb.color[0] = BLACK;
  drawSprites(ctx);
  screendata.sdb.color[0] = color;
  screendata.sdb.xpos[0]++;
  screendata.needsRefresh++;
}
