// #include "OTA.h"
#include "GUI/myUI.h"
#include "ESP/ESP_Init.h"
UI *ui = new UI(TFT_WIDTH, TFT_HEIGHT);

void setup()
{
    #ifdef DEBUG_FLAG
        Serial.begin(115200);
    #endif
    ESP_Init();
    ui->initUI();
}

void loop()
{
    delay(5);
    ESP_Loop();
}

// #include <Arduino.h>
// #include <WiFi.h>
// #include <AsyncTCP.h>
// #include <ESPAsyncWebServer.h>
// #include <AsyncElegantOTA.h>

// const char* ssid = "mi";
// const char* password = "wpq5201314";

// AsyncWebServer server(80);

// void setup(void) {
//   Serial.begin(115200);
//   WiFi.mode(WIFI_STA);
//   WiFi.begin(ssid, password);
//   Serial.println("");

//   // Wait for connection
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("");
//   Serial.print("Connected to ");
//   Serial.println(ssid);
//   Serial.print("IP address: ");
//   Serial.println(WiFi.localIP());
//   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
//     AsyncResponseStream *response = request->beginResponseStream("text/html");
//     response->print("<!DOCTYPE html><html><head><title>主页</title><meta heep-equiv='Content-Type' content='text/html' charset='utf-8'></head><body>");
//     response->print("<h1>主页还在建设中,,,</h1>");
//     response->print("<p>目前只能OTA更新固件<a href='/update'>点击跳转</a></p>");
//     response->print("</body></html>");
//     request->send(response);
//     // request->send(200, "text/plain", "<h1>主页还在建设中</h1><p>目前只能OTA更新固件<a href='/update'>点击跳转</a></p>");
//   });

//   AsyncElegantOTA.begin(&server);    // Start ElegantOTA
//   server.begin();
//   Serial.println("HTTP server started");
// }

// void loop(void) {
// }

// #include <WiFi.h>
// #include <AsyncTCP.h>
// #include <ESPAsyncWebServer.h>
// #include <AsyncElegantOTA.h>

// const char* ssid = "mi";
// const char* password = "wpq5201314";

// AsyncWebServer server(80);


// void setup(void) {
//   Serial.begin(115200);
//   WiFi.mode(WIFI_STA);
//   WiFi.begin(ssid, password);
//   Serial.println("");

//   // Wait for connection
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("");
//   Serial.print("Connected to ");
//   Serial.println(ssid);
//   Serial.print("IP address: ");
//   Serial.println(WiFi.localIP());

//   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
//     request->send(200, "text/plain", "Hi! I am ESP32.");
//   });

//   AsyncElegantOTA.begin(&server);    // Start ElegantOTA
//   server.begin();
//   Serial.println("HTTP server started");
// }

// void loop(void) {
// }
