#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Arduino_ST7789_Fast.h>  // Biblioteca para la pantalla ST7789

// Definir pines de la pantalla ST7789
#define TFT_DC    7  // Pin Data/Command
#define TFT_RST   8  // Pin Reset
#define BUTTON    3  // Pin Botón (no utilizado en este ejemplo)

// Crear el objeto de la pantalla
#define SCR_WD 240
#define SCR_HT 240
Arduino_ST7789 lcd = Arduino_ST7789(TFT_DC, TFT_RST);

// Definir la paleta de colores y variables de configuración
uint16_t palette[16];
uint16_t line[SCR_WD];
uint16_t bgColor      = RGBto565(160,160,160);
uint16_t bgShadow     = RGBto565(100,100,100);
uint16_t lineColor    = RGBto565(150,40,150);
uint16_t lineShadow   = RGBto565(90,20,90);

#define LINE_Y_START  20
#define LINE_X_START1 30
#define LINE_X_START2 6

#define BALL_WIDTH  64
#define BALL_HEIGHT 64
#define BALL_SCR_WIDTH  240
#define BALL_SCR_HEIGHT 180

#define SPACE 20

#define SHADOW_OFFSET 20

// Datos de la bola Amiga (comprimidos para el ejemplo, necesitas el array completo para la animación real)
#include "ball.h"

// Función para dibujar la bola
void drawBall(int x, int y) {
  for (int j = 0; j < BALL_HEIGHT; j++) {
    uint8_t* img = (uint8_t*)ball + 16*2 + 6 + j*BALL_WIDTH/2 + BALL_WIDTH/2;
    int yy = y + j;
    
    // Determinar si se debe dibujar una línea
    if (yy == LINE_Y_START || (yy - LINE_Y_START) % SPACE == 0) {
      for (int i = 0; i < LINE_X_START1; i++) line[i] = line[SCR_WD - 1 - i] = bgColor;
      for (int i = 0; i <= SCR_WD - LINE_X_START1 * 2; i++) line[i + LINE_X_START1] = lineColor;
    } else {
      for (int i = 0; i < SCR_WD; i++) line[i] = bgColor;
      if (yy > LINE_Y_START) {
        for (int i = 0; i < 10; i++) line[LINE_X_START1 + i*SPACE] = lineColor;
      }
    }
    
    // Dibujar los píxeles de la bola
    for (int i = BALL_WIDTH - 2; i >= 0; i -= 2) {
      uint8_t v = pgm_read_byte(--img);
      if (v >> 4) {
        line[x + i + 0] = palette[v >> 4];
        if (SHADOW_OFFSET > 0) {
          int shadowPos = x + i + 0 + SHADOW_OFFSET;
          if (shadowPos < SCR_WD) {
            if (line[shadowPos] == bgColor) line[shadowPos] = bgShadow;
            else if (line[shadowPos] == lineColor) line[shadowPos] = lineShadow;
          }
        }
      }
      if (v & 0xF) {
        line[x + i + 1] =
