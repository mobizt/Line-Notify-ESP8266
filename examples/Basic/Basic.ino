
/*
 * 1. Install the Arduino ESP8266 filesystem uploader plugin in Arduino from
 * https://github.com/esp8266/arduino-esp8266fs-plugin
 * 
 * 2. From Arduino IDE, select Tools - > ESP8266 Sketch Data Upload (Serial Monitor Window need to be close)
 * This will upload sewing.jpg in data folder inside Basic examples folder to device and use in 
 * lineNotify.sendLineImageSPIF(client,"This image from device", "/sewing.jpg");
 * 
 * For PlatformIO, in project folder, create folder named "data" and copy sewing.jpg in examples/Basic/data to that created folder.
 * At terminal, type this command to upload sewing.jpg to SPIFS
 * pio run -t uploadfs
 * 
 * 3. Change the WIFI_SSID, WIFI_PASSWORD and LINE_TOKEN in sketch.
 * 
 * 4. Compile and upload sketch 
 * 
 */

//LineNotifyESP8266.h must be included before ESP8266WiFi.h
#include "LineNotifyESP8266.h"
#include <ESP8266WiFi.h>

//Include for use in this demo only
#include "image.h"

#define WIFI_SSID "YOUR_WIFI_AP"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#define LINE_TOKEN "YOUR_LINE_NOTIFY_TOKEN"


bool sdOK = false;

void setup()
{

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

  //Write demo image to SD card

  if (SD.begin(15))
  {
    sdOK = true;

    File file = SD.open("/test.jpg", FILE_WRITE);

    int len = sizeof(dummyImageData);
    int pos = 0;

    while (len)
    {
      size_t toWrite = len;
      if (toWrite > 512)
      {
        toWrite = 512;
      }
      file.write(dummyImageData + pos, toWrite);
      len -= toWrite;
      pos += toWrite;
    }

    file.close();
  }

  LineNotifyHTTPClient net;
  lineNotify.init(&net, LINE_TOKEN);

  lineNotify.setSDSelectPin(15);

  uint8_t status;
  
  status = lineNotify.sendLineMessage("Hello!");
  if (status == LineNotifyESP8266::LineStatus::SENT_COMPLETED)
  {
    Serial.println("Send text message completed");
    Serial.println("Text message limit: " + String(lineNotify.textMessageLimit()));
    Serial.println("Text message remaining: " + String(lineNotify.textMessageRemaining()));
    Serial.println("Image message limit: " + String(lineNotify.imageMessageLimit()));
    Serial.println("Image message remaining: " + String(lineNotify.imageMessageRemaining()));
  }
  else if (status == LineNotifyESP8266::LineStatus::SENT_FAILED)
    Serial.println("Send text message was failed!");
  else if (status == LineNotifyESP8266::LineStatus::CONNECTION_FAILED)
    Serial.println("Connection to LINE sevice faild!");
  else if (status == LineNotifyESP8266::LineStatus::NOT_INITIALIZED)
    Serial.println("Line notify was not initialized!");
  Serial.println();

  status = lineNotify.sendLineImageData("This is the image from memory", "image.jpg", dummyImageData, sizeof(dummyImageData));
  if (status == LineNotifyESP8266::LineStatus::SENT_COMPLETED)
  {
    Serial.println("send image data completed");
    Serial.println("Text message limit: " + String(lineNotify.textMessageLimit()));
    Serial.println("Text message remaining: " + String(lineNotify.textMessageRemaining()));
    Serial.println("Image message limit: " + String(lineNotify.imageMessageLimit()));
    Serial.println("Image message remaining: " + String(lineNotify.imageMessageRemaining()));
  }
  else if (status == LineNotifyESP8266::LineStatus::SENT_FAILED)
    Serial.println("Send image data was failed!");
  else if (status == LineNotifyESP8266::LineStatus::CONNECTION_FAILED)
    Serial.println("Connection to LINE sevice faild!");
  else if (status == LineNotifyESP8266::LineStatus::NOT_INITIALIZED)
    Serial.println("Line notify was not initialized!");
  Serial.println();

  status = lineNotify.sendLineSticker("Goodbye", 2, 157);
  if (status == LineNotifyESP8266::LineStatus::SENT_COMPLETED)
  {
    Serial.println("Send sticker completed");
    Serial.println("Text message limit: " + String(lineNotify.textMessageLimit()));
    Serial.println("Text message remaining: " + String(lineNotify.textMessageRemaining()));
    Serial.println("Image message limit: " + String(lineNotify.imageMessageLimit()));
    Serial.println("Image message remaining: " + String(lineNotify.imageMessageRemaining()));
  }
  else if (status == LineNotifyESP8266::LineStatus::SENT_FAILED)
    Serial.println("Send sticker was failed!");
  else if (status == LineNotifyESP8266::LineStatus::CONNECTION_FAILED)
    Serial.println("Connection to LINE sevice faild!");
  else if (status == LineNotifyESP8266::LineStatus::NOT_INITIALIZED)
    Serial.println("Line notify was not initialized!");
  Serial.println();


  status = lineNotify.sendLineImageURL("This is image I found on web.", "https://cdn.pixabay.com/photo/2017/05/17/18/35/sewing-2321532_640.jpg");
  if (status == LineNotifyESP8266::LineStatus::SENT_COMPLETED)
  {
    Serial.println("Send image URL completed");
    Serial.println("Text message limit: " + String(lineNotify.textMessageLimit()));
    Serial.println("Text message remaining: " + String(lineNotify.textMessageRemaining()));
    Serial.println("Image message limit: " + String(lineNotify.imageMessageLimit()));
    Serial.println("Image message remaining: " + String(lineNotify.imageMessageRemaining()));
  }
  else if (status == LineNotifyESP8266::LineStatus::SENT_FAILED)
    Serial.println("Send image URL failed!");
  else if (status == LineNotifyESP8266::LineStatus::CONNECTION_FAILED)
    Serial.println("Connection to LINE sevice faild!");
  else if (status == LineNotifyESP8266::LineStatus::NOT_INITIALIZED)
    Serial.println("Line notify was not initialized!");
  Serial.println();


  status = lineNotify.sendLineImageSPIF("This image from device", "/sewing.jpg");
  if (status == LineNotifyESP8266::LineStatus::SENT_COMPLETED)
  {
    Serial.println("Send image from SPIFS file completed");
    Serial.println("Text message limit: " + String(lineNotify.textMessageLimit()));
    Serial.println("Text message remaining: " + String(lineNotify.textMessageRemaining()));
    Serial.println("Image message limit: " + String(lineNotify.imageMessageLimit()));
    Serial.println("Image message remaining: " + String(lineNotify.imageMessageRemaining()));
  }
  else if (status == LineNotifyESP8266::LineStatus::SENT_FAILED)
    Serial.println("Send image from SPIFS was failed!");
  else if (status == LineNotifyESP8266::LineStatus::CONNECTION_FAILED)
    Serial.println("Connection to LINE sevice faild!");
  else if (status == LineNotifyESP8266::LineStatus::NOT_INITIALIZED)
    Serial.println("Line notify was not initialized!");
  Serial.println();

  if (sdOK)
  {
    status = lineNotify.sendLineImageSD("This image from SD card", "/test.jpg");
    if (status == LineNotifyESP8266::LineStatus::SENT_COMPLETED)
    {
      Serial.println("Send image from SD card completed");
      Serial.println("Text message limit: " + String(lineNotify.textMessageLimit()));
      Serial.println("Text message remaining: " + String(lineNotify.textMessageRemaining()));
      Serial.println("Image message limit: " + String(lineNotify.imageMessageLimit()));
      Serial.println("Image message remaining: " + String(lineNotify.imageMessageRemaining()));
    }
    else if (status == LineNotifyESP8266::LineStatus::SENT_FAILED)
      Serial.println("Send image from SD card was failed!");
    else if (status == LineNotifyESP8266::LineStatus::CONNECTION_FAILED)
      Serial.println("Connection to LINE sevice faild!");
    else if (status == LineNotifyESP8266::LineStatus::NOT_INITIALIZED)
      Serial.println("Line notify was not initialized!");
    Serial.println();
  }


  lineNotify.end();
}

void loop()
{
}
