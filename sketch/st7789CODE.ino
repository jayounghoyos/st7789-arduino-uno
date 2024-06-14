#include <Fast_ST7789.h>
#include <SPI.h>

// Definir pines de la pantalla ST7789
#define TFT_CS     10  // Chip select (puede no ser usado)
#define TFT_RST    8   // Reset
#define TFT_DC     9   // Data/Command

// Crear el objeto de la pantalla
Fast_ST7789 tft = Fast_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(9600);  // Iniciar comunicación serial para depuración
  Serial.println("Iniciando demostración gráfica...");

  tft.init(240, 240);  // Inicializa la pantalla con la resolución 240x240
  tft.setRotation(0);  // Ajusta la rotación si es necesario

  // Llenar la pantalla con negro para empezar
  tft.fillScreen(ST77XX_BLACK);
  delay(500);

  // Demostración gráfica
  mostrarGraficos();
}

void loop() {
  // El loop está vacío ya que estamos mostrando elementos estáticos en setup()
}

// Función para mostrar una serie de gráficos impresionantes
void mostrarGraficos() {
  // Rellenar la pantalla con colores cambiantes
  llenarPantallaColores();

  // Mostrar un cubo rotando en 3D
  mostrarCubo3D();
  
  // Dibujar una esfera con gradiente
  mostrarEsferaConGradiente();
}

// Función para llenar la pantalla con colores cambiantes
void llenarPantallaColores() {
  tft.fillScreen(ST77XX_RED);
  delay(500);
  tft.fillScreen(ST77XX_GREEN);
  delay(500);
  tft.fillScreen(ST77XX_BLUE);
  delay(500);
  tft.fillScreen(ST77XX_WHITE);
  delay(500);
  tft.fillScreen(ST77XX_BLACK);
  delay(500);
}

// Función para mostrar un cubo 3D rotando
void mostrarCubo3D() {
  int size = 60;  // Tamaño del cubo
  int offset = 70;  // Desplazamiento desde el centro
  float angle = 0;  // Ángulo de rotación

  for (int i = 0; i < 360; i += 5) {
    tft.fillScreen(ST77XX_BLACK);

    angle = radians(i);

    // Coordenadas 3D del cubo
    int x1 = offset + size * cos(angle);
    int y1 = offset + size * sin(angle);
    int x2 = offset + size * cos(angle + PI/2);
    int y2 = offset + size * sin(angle + PI/2);
    int x3 = offset + size * cos(angle + PI);
    int y3 = offset + size * sin(angle + PI);
    int x4 = offset + size * cos(angle + 3*PI/2);
    int y4 = offset + size * sin(angle + 3*PI/2);

    // Dibujar el cubo
    tft.drawLine(x1, y1, x2, y2, ST77XX_WHITE);
    tft.drawLine(x2, y2, x3, y3, ST77XX_WHITE);
    tft.drawLine(x3, y3, x4, y4, ST77XX_WHITE);
    tft.drawLine(x4, y4, x1, y1, ST77XX_WHITE);
    
    // Lado trasero
    int zOffset = 40;
    tft.drawLine(x1 + zOffset, y1 + zOffset, x2 + zOffset, y2 + zOffset, ST77XX_WHITE);
    tft.drawLine(x2 + zOffset, y2 + zOffset, x3 + zOffset, y3 + zOffset, ST77XX_WHITE);
    tft.drawLine(x3 + zOffset, y3 + zOffset, x4 + zOffset, y4 + zOffset, ST77XX_WHITE);
    tft.drawLine(x4 + zOffset, y4 + zOffset, x1 + zOffset, y1 + zOffset, ST77XX_WHITE);
    
    // Conectar esquinas
    tft.drawLine(x1, y1, x1 + zOffset, y1 + zOffset, ST77XX_WHITE);
    tft.drawLine(x2, y2, x2 + zOffset, y2 + zOffset, ST77XX_WHITE);
    tft.drawLine(x3, y3, x3 + zOffset, y3 + zOffset, ST77XX_WHITE);
    tft.drawLine(x4, y4, x4 + zOffset, y4 + zOffset, ST77XX_WHITE);

    delay(50);
  }
}

// Función para mostrar una esfera con gradiente
void mostrarEsferaConGradiente() {
  int cx = 120;  // Centro X
  int cy = 120;  // Centro Y
  int maxRadius = 50;  // Radio máximo

  for (int r = maxRadius; r > 0; r -= 2) {
    uint16_t color = tft.color565(r * 5, 255 - r * 5, 128 + r * 2);  // Crear un color basado en el radio
    tft.fillCircle(cx, cy, r, color);
    delay(100);
  }
}
