// #ifndef __OTA_H
// #define __OTA_H

// #include "ESP_WiFi.h"
// #include <AsyncTCP.h>
// #include <ESPAsyncWebServer.h>
// #include <AsyncElegantOTA.h>

// static AsyncWebServer server(80);

// void OTA_Init()
// {
//   ESPWifi_ConnectToWifi("mi", "wpq5201314");
//   while (!ESPWifi_Status())
//   {
//       Serial.print(".");
//       delay(500);
//   }
//   Serial.printf("\n%s", WiFi.localIP());
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
// }

// #endif // !__OTA_H