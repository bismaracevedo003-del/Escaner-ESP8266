#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

// Variable global que contiene el HTML de los resultados (compartida con Scanner.h)
String scanResultsHTML = "<p>Iniciando escáner...</p>";

void setupWebServer() {
  // Ruta principal
  server.on("/", []() {
    String html = "<!DOCTYPE html><html lang=\"es\"><head>";
    html += "<meta charset=\"UTF-8\">";
    html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    html += "<title>Escáner WiFi ESP8266</title>";
    html += "<style>body{font-family:Arial,sans-serif;margin:20px;background:#f0f0f0;}";
    html += "h1{color:#333;} ul{list-style:none;padding:0;} li{margin:10px 0;padding:10px;background:white;border-radius:8px;box-shadow:0 2px 5px rgba(0,0,0,0.1);}";
    html += ".info{text-align:center;color:#666;}</style>";
    html += "<meta http-equiv=\"refresh\" content=\"12\">";  // Refresco automático
    html += "</head><body>";
    html += "<h1>📶 Escáner de Redes WiFi</h1>";
    html += scanResultsHTML;
    html += "<hr><p class=\"info\">Conectado a: " + String(ap_ssid) + " | IP: 192.168.4.1</p>";
    html += "<p class=\"info\">Actualiza automáticamente cada 12 segundos</p>";
    html += "</body></html>";

    server.send(200, "text/html", html);
  });

  server.begin();
  Serial.println("Servidor web iniciado en http://192.168.4.1");
}

void handleWebClients() {
  server.handleClient();
}

#endif