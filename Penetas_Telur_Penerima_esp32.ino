#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6WsPGDFPU"
#define BLYNK_TEMPLATE_NAME "PenetasTelur"
#define BLYNK_AUTH_TOKEN "PMGD-8N47EubSVjPgUnJqXrHZUFly_TB"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <SPI.h>
#include <mcp2515.h>

char ssid[] = "Realme";
char pass[] = "123456789";

MCP2515 mcp2515(2);  
struct can_frame canMsg;

void setup() {
  Serial.begin(115200);

  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);  
  mcp2515.setNormalMode();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    if (canMsg.can_id == 0x100) {
      int t = (canMsg.data[0] << 8) | canMsg.data[1];  
      int h = (canMsg.data[2] << 8) | canMsg.data[3];
      bool statuslampu = canMsg.data[4];

      float kelembaban = h / 100.0;  
      float suhu = t / 100.0;

      Serial.print("Suhu: ");
      Serial.print(suhu);
      Serial.print(" °C, Kelembaban: ");
      Serial.print(kelembaban);
      Serial.println(" %, Lampu: ");

      if (statuslampu) {
        Serial.println("Menyala");
      } else {
        Serial.println("Mati");
      }

      Blynk.virtualWrite(V1, suhu);
      Blynk.virtualWrite(V2, kelembaban);
      Blynk.virtualWrite(V3, statuslampu ? "Menyala" : "Mati");
    }
  }

  Blynk.run();
  delay(1000); 
}
