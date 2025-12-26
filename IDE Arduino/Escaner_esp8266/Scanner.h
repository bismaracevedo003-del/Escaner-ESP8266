#ifndef SCANNER_H
#define SCANNER_H

#include <ESP8266WiFi.h>
#include "WebServer.h"

extern String scanResultsHTML;

bool scanning = false;  // Para evitar iniciar múltiples escaneos

// Callback que se ejecuta cuando termina el escaneo asíncrono
void onScanComplete(int networksFound) {
  scanning = false;

  scanResultsHTML = "<p><strong>Escaneo completado:</strong> ";

  if (networksFound == 0) {
    scanResultsHTML += "No se encontraron redes.</p>";
    Serial.println("No se encontraron redes.");
  } else if (networksFound == -1) {  // Error (raro)
    scanResultsHTML += "Error en el escaneo.</p>";
    Serial.println("Error en escaneo asíncrono.");
  } else {
    scanResultsHTML += String(networksFound) + " redes encontradas</p><ul>";

    for (int i = 0; i < networksFound; ++i) {
      scanResultsHTML += "<li><strong>" + WiFi.SSID(i) + "</strong><br>";
      scanResultsHTML += "Señal: " + String(WiFi.RSSI(i)) + " dBm | ";
      scanResultsHTML += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? "Abierta" : "Protegida";
      scanResultsHTML += " | Canal: " + String(WiFi.channel(i));
      scanResultsHTML += " | MAC: " + WiFi.BSSIDstr(i);
      scanResultsHTML += "</li>";
    }
    scanResultsHTML += "</ul>";

    Serial.printf("%d redes encontradas\n", networksFound);
  }

  // Liberar memoria
  WiFi.scanDelete();
}

// Función para iniciar el escaneo (se llama desde el loop principal)
void performScan() {
  if (!scanning) {
    scanning = true;
    scanResultsHTML = "<p><em>Escaneando redes... (puede tardar unos segundos)</em></p>";
    Serial.println("\nIniciando escaneo asíncrono...");
    
    // Inicia escaneo en segundo plano, llama a onScanComplete al terminar
    WiFi.scanNetworksAsync(onScanComplete);
  }
}

#endif