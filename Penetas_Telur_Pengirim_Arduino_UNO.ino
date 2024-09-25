#include <mcp2515.h>
#include <DHT.h>
#include <LCD_I2C.h>

#define DHTPIN 3
#define DHTTYPE DHT22
#define RELAY 8

LCD_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);
MCP2515 mcp2515(10);
struct can_frame canMsg;

void setup() {
  pinMode(RELAY, OUTPUT);

  lcd.begin();
  lcd.backlight();
  
  dht.begin();
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
  
  canMsg.can_id = 0x100;
  canMsg.can_dlc = 5;

  lcd.setCursor(4, 0);
  lcd.print("Penetas");
  lcd.setCursor(5, 1);
  lcd.print("telur");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("loading.");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("loading..");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("loading...");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("loading....");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("loading.....");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("loading......");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("loading.......");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("loading........");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("loading.........");
  delay(500);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) return;
  
  int suhu = t * 100;
  int kelembaban = h * 100;
  bool statuslampu = false;

  if (t <= 37.0) {
    digitalWrite(RELAY, LOW);
    statuslampu = true;
  } else if (t >= 39.0) {
    digitalWrite(RELAY, HIGH);
    statuslampu = false;
  }
  
  canMsg.data[0] = suhu >> 8;
  canMsg.data[1] = suhu & 0xFF;
  canMsg.data[2] = kelembaban >> 8;
  canMsg.data[3] = kelembaban & 0xFF;
  canMsg.data[4] = statuslampu;

  mcp2515.sendMessage(&canMsg);

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");

  delay(2000);
}
