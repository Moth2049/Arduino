#include <WebServer.h>
#include "esp_camera.h"

WebServer server(80);

void handleJPGStream(void) {
  WiFiClient client = server.client();
  String response = "HTTP/1.1 200 OK\r\n";
  response += "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n\r\n";
  server.sendContent(response);

  while (1) {
    camera_fb_t * fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Camera capture failed");
      return;
    }

    response = "--frame\r\n";
    response += "Content-Type: image/jpeg\r\n\r\n";
    server.sendContent(response);

    server.sendContent((const char *)fb->buf, fb->len);
    server.sendContent("\r\n");

    esp_camera_fb_return(fb);

    if (!client.connected()) break;
  }
}

void handleRoot() {
  server.send(200, "text/html", "<html><body><h1>ESP32-CAM</h1><img src='/stream'></body></html>");
}

void startCameraServer() {
  server.on("/", handleRoot);
  server.on("/stream", HTTP_GET, handleJPGStream);
  server.begin();
}
