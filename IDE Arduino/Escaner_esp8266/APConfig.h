#ifndef APCONFIG_H
#define APCONFIG_H

#include <ESP8266WiFi.h>

const char* ap_ssid = "ESP8266_Scanner";
const char* ap_password = "";  // Deja "" para red abierta o pon una contraseña

const IPAddress apIP(192, 168, 4, 1);
const IPAddress subnet(255, 255, 255, 0);

void setupAccessPoint() {
  Serial.println("Configurando Access Point...");

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, subnet);
  bool started = WiFi.softAP(ap_ssid, ap_password);

  if (started) {
    Serial.print("AP iniciado: ");
    Serial.println(ap_ssid);
    Serial.print("IP del AP: ");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println("Error al iniciar el Access Point");
  }
}

#endif