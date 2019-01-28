/*
 * 1. Install the Arduino ESP8266 filesystem uploader plugin in Arduino from
 * https://github.com/esp8266/arduino-esp8266fs-plugin
 * 
 * 2. From Arduino IDE, select Tools - > ESP8266 Sketch Data Upload (Serial Monitor Window need to be close)
 * This will upload sewing.jpg in data folder inside Basic examples folder to device and use in 
 * lineNotify.sendLineImageSPIF(client,"This image from device", "/sewing.jpg");
 * 
 * 3. Change the WIFI_SSID, WIFI_PASSWORD and LINE_TOKEN in sketch.
 * 
 * 4. Compile and upload sketch 
 * 
 */


#include <FS.h>
#include "image.h"
#include "LineNotifyESP8266.h"


#define WIFI_SSID "YOUR_WIFI_AP"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#define LINE_TOKEN "YOUR_LINE_NOTIFY_TOKEN"

WiFiClientSecure client;


void setup() {
  Serial.begin(115200);



  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(200);
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  
  lineNotify.init(LINE_TOKEN);

  //lineNotify.setToken(LINE_TOKEN);  

  lineNotify.sendLineMessage(client,"Hello!");

  lineNotify.sendLineImageData(client,"This is the image from memory", "image.jpg", dummyImageData, sizeof(dummyImageData));

  lineNotify.sendLineSticker(client,"Goodbye", 2,157);

  lineNotify.sendLineImageURL(client,"This is image I found on web.","https://cdn.pixabay.com/photo/2017/05/17/18/35/sewing-2321532_640.jpg");

  lineNotify.sendLineImageSPIF(client,"This image from device", "/sewing.jpg");


}

void loop() {

}
