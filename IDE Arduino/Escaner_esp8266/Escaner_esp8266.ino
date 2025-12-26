#include "APConfig.h"
#include "Scanner.h"
#include "WebServer.h"

unsigned long lastScanTime = 0;
const unsigned long scanInterval = 10000;  // 10 segundos

void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println("\n=== ESP8266 WiFi Scanner iniciado ===");

  // Inicializar Access Point
  setupAccessPoint();

  // Escaneo inicial
  performScan();
}

void loop() {
  // Manejar peticiones del servidor web
  handleWebClients();

  // Escanear periódicamente
  if (millis() - lastScanTime >= scanInterval) {
    performScan();
    lastScanTime = millis();
  }
}