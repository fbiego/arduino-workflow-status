#include <WS2812FX.h>

#define LED_COUNT 8
#define LED_PIN 2


WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);



void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  ws2812fx.init();
  ws2812fx.setBrightness(55);
  ws2812fx.setSpeed(1000);
  ws2812fx.setColor(CYAN);
  ws2812fx.setMode(FX_MODE_BREATH);
  ws2812fx.start();

  digitalWrite(NINA_RESETN, LOW);
  delay(100);
  digitalWrite(NINA_RESETN, HIGH);
  delay(100);
}

void loop() {

  ws2812fx.service();
  if (Serial2.available()) {
    String cmd = Serial2.readStringUntil('\n');
    Serial.println(cmd);
    if (cmd.startsWith("connecting")) {
      ws2812fx.setColor(MAGENTA);
      ws2812fx.setMode(FX_MODE_BREATH);
    }
    if (cmd.startsWith("connected")) {
      ws2812fx.setColor(MAGENTA);
      ws2812fx.setMode(FX_MODE_STATIC);
    }
    if (cmd.startsWith("passing")) {
      ws2812fx.setColor(GREEN);
      ws2812fx.setMode(FX_MODE_BREATH);
    }
    if (cmd.startsWith("failing")) {
      ws2812fx.setColor(RED);
      ws2812fx.setMode(FX_MODE_BREATH);
    }
    if (cmd.startsWith("running")) {
      ws2812fx.setColor(YELLOW);
      ws2812fx.setMode(FX_MODE_LARSON_SCANNER);
    }
    if (cmd.startsWith("cancelled")) {
      ws2812fx.setColor(YELLOW);
      ws2812fx.setMode(FX_MODE_BREATH);
    }
  }


}
