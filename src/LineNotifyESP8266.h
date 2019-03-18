/*
 * LINE Notify Arduino Library for ESP8266 version 1.0.0
 * 
 * March 18, 2019
 *
 * This library provides ESP8266 to perform REST API call to LINE Notify service to post the several message types.
 *
 * The library was test and work well with ESP8266s based module.
 * 
 * The MIT License (MIT)
 * Copyright (c) 2019 K. Suwatchai (Mobizt)
 * 
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef LineNotifyESP8266_H
#define LineNotifyESP8266_H

#include <Arduino.h>
#include <Arduino.h>
#if ARDUINO_ESP8266_GIT_VER == 0xbb28d4a3 || ARDUINO_ESP8266_GIT_VER == 0x614f7c32 || ARDUINO_ESP8266_GIT_VER == 0x4ceabea9 //2.4.0, 2.4.1, 2.4.2
#include <WiFiClientSecure.h>
#else
#include <WiFiClientSecureAxTLS.h>
using namespace axTLS;
#endif

#if ARDUINO_ESP8266_GIT_VER != 0xbb28d4a3 && ARDUINO_ESP8266_GIT_VER != 0x614f7c32 && ARDUINO_ESP8266_GIT_VER != 0x4ceabea9 //2.4.0, 2.4.1, 2.4.2
#define USING_AXTLS
#endif
#include <ESP8266WiFi.h>
#define FS_NO_GLOBALS
#include <FS.h>
#include <SD.h>
#include <vector>

static const char ESP8266_LINE_NOTIFY_STR_1[] PROGMEM = "notify-api.line.me";
static const char ESP8266_LINE_NOTIFY_STR_2[] PROGMEM = "{BOUNDARY}";
static const char ESP8266_LINE_NOTIFY_STR_3[] PROGMEM = "ESP32";
static const char ESP8266_LINE_NOTIFY_STR_4[] PROGMEM = "\r\n";
static const char ESP8266_LINE_NOTIFY_STR_5[] PROGMEM = "POST /api/notify HTTP/1.1";
static const char ESP8266_LINE_NOTIFY_STR_6[] PROGMEM = "cache-control: no-cache";
static const char ESP8266_LINE_NOTIFY_STR_7[] PROGMEM = "Authorization: Bearer ";
static const char ESP8266_LINE_NOTIFY_STR_8[] PROGMEM = "Content-Type: multipart/form-data; boundary=";
static const char ESP8266_LINE_NOTIFY_STR_9[] PROGMEM = "User-Agent: ";
static const char ESP8266_LINE_NOTIFY_STR_10[] PROGMEM = "Accept: */*";
static const char ESP8266_LINE_NOTIFY_STR_11[] PROGMEM = "Host: ";
static const char ESP8266_LINE_NOTIFY_STR_12[] PROGMEM = "accept-encoding: gzip, deflate";
static const char ESP8266_LINE_NOTIFY_STR_13[] PROGMEM = "Connection: close";
static const char ESP8266_LINE_NOTIFY_STR_14[] PROGMEM = "content-length: ";
static const char ESP8266_LINE_NOTIFY_STR_15[] PROGMEM = "/api/notify";
static const char ESP8266_LINE_NOTIFY_STR_16[] PROGMEM = "Content-Disposition: form-data; name=\"imageFile\"; filename=\"";
static const char ESP8266_LINE_NOTIFY_STR_17[] PROGMEM = "Content-Type: ";
static const char ESP8266_LINE_NOTIFY_STR_18[] PROGMEM = "Content-Disposition: form-data; name=\"";
static const char ESP8266_LINE_NOTIFY_STR_19[] PROGMEM = "message";
static const char ESP8266_LINE_NOTIFY_STR_20[] PROGMEM = "stickerPackageId";
static const char ESP8266_LINE_NOTIFY_STR_21[] PROGMEM = "stickerId";
static const char ESP8266_LINE_NOTIFY_STR_22[] PROGMEM = "imageThumbnail";
static const char ESP8266_LINE_NOTIFY_STR_23[] PROGMEM = "imageFullsize";
static const char ESP8266_LINE_NOTIFY_STR_24[] PROGMEM = "--";
static const char ESP8266_LINE_NOTIFY_STR_25[] PROGMEM = "\"";
static const char ESP8266_LINE_NOTIFY_STR_26[] PROGMEM = ".jpg";
static const char ESP8266_LINE_NOTIFY_STR_27[] PROGMEM = ".jpeg";
static const char ESP8266_LINE_NOTIFY_STR_28[] PROGMEM = "image/jpeg";
static const char ESP8266_LINE_NOTIFY_STR_29[] PROGMEM = ".gif";
static const char ESP8266_LINE_NOTIFY_STR_30[] PROGMEM = "image/gif";
static const char ESP8266_LINE_NOTIFY_STR_31[] PROGMEM = ".png";
static const char ESP8266_LINE_NOTIFY_STR_32[] PROGMEM = "image/png";
static const char ESP8266_LINE_NOTIFY_STR_33[] PROGMEM = ".bmp";
static const char ESP8266_LINE_NOTIFY_STR_34[] PROGMEM = "image/bmp";
static const char ESP8266_LINE_NOTIFY_STR_35[] PROGMEM = ".";
static const char ESP8266_LINE_NOTIFY_STR_36[] PROGMEM = "HTTP/1.1 ";
static const char ESP8266_LINE_NOTIFY_STR_37[] PROGMEM = " ";
static const char ESP8266_LINE_NOTIFY_STR_38[] PROGMEM = "X-RateLimit-Limit: ";
static const char ESP8266_LINE_NOTIFY_STR_39[] PROGMEM = "X-RateLimit-ImageLimit: ";
static const char ESP8266_LINE_NOTIFY_STR_40[] PROGMEM = "X-RateLimit-Remaining: ";
static const char ESP8266_LINE_NOTIFY_STR_41[] PROGMEM = "X-RateLimit-ImageRemaining: ";
static const char ESP8266_LINE_NOTIFY_STR_42[] PROGMEM = " ";
static const char ESP8266_LINE_NOTIFY_STR_43[] PROGMEM = "/esp8.266";

class LineNotifyESP8266
{

public:
  struct LineStatus
  {
    static const uint8_t SENT_COMPLETED = 0;
    static const uint8_t SENT_FAILED = 1;
    static const uint8_t CONNECTION_FAILED = 2;
  };

  LineNotifyESP8266();
  ~LineNotifyESP8266();

  /*
   
    The LINE Notify Service's credentials initialization.

    @param token - LINE Notify token String.

  */
  void
  init(const String &token);

  /*

    Set the LINE Notify token.

    @param token - LINE Notify token string.

  */
  void setToken(const String &token);

  /*
   
    Send text message.
   
    @param client - SSL WiFi client from WiFiClientSecure initialization.
    @param msg - The text message String to be send.
    
    @return The LineStatus structed value, SENT_COMPLETED = 0, SENT_FAILED = 1, CONNECTION_FAILED = 2.
   
  */
  uint8_t sendLineMessage(WiFiClientSecure &client, const String &msg);

  /*

    Send text message with sticker.

    @param client - SSL WiFi client from WiFiClientSecure initialization.
    @param msg - The text message String to be send.
    @param stickerPackageId - Sticker Package ID number to send, see https://devdocs.line.me/files/sticker_list.pdf for STKPKGID
    @param stickerId - Sticker ID number to send, see https://devdocs.line.me/files/sticker_list.pdf for STKID

    return The LineStatus structed value, SENT_COMPLETED = 0, SENT_FAILED = 1, CONNECTION_FAILED = 2.

  */
  uint8_t sendLineSticker(WiFiClientSecure &client, const String &msg, uint16_t stickerPackageId, uint16_t stickerId);

  /*

    Send Image message. The image data from flash memory or EEPROM

    @param client - SSL WiFi client from WiFiClientSecure initialization.
    @param msg - The text message String to be send.
    @param fileName - The user's specified file name String.
    @param imageData - The byte data of image from memory or EEPROM.
    @param imageLength - The byte length of image data.

    @return The LineStatus structed value, SENT_COMPLETED = 0, SENT_FAILED = 1, CONNECTION_FAILED = 2.

  */
  uint8_t sendLineImageData(WiFiClientSecure &client, const String &msg, const String &fileName, const uint8_t *imageData, size_t imageLength);

  /**
    Send Image message. The image data from web URL.

    @param client - SSL WiFi client from WiFiClientSecure initialization.
    @param msg - The text message String to be send.
    @param imageURL - The image URL String.

    @return The LineStatus structed value, SENT_COMPLETED = 0, SENT_FAILED = 1, CONNECTION_FAILED = 2.

  */
  uint8_t sendLineImageURL(WiFiClientSecure &client, const String &msg, const String &imageURL);

  /*

    Send Image message. The image data from SPI Flash File.

    @param client - SSL WiFi client from WiFiClientSecure initialization.
    @param msg - The text message String to be send.
    @param filePath - The image file name and path String inside SPIF.

    @return The LineStatus structed value, SENT_COMPLETED = 0, SENT_FAILED = 1, CONNECTION_FAILED = 2.

  */
  uint8_t sendLineImageSPIF(WiFiClientSecure &client, const String &msg, const String &filePath);

  /*

    Send Image message. The image data from SD card File.

    @param client - SSL WiFi client from WiFiClientSecure initialization.
    @param msg - The text message String to be send.
    @param filePath - The image file name and path String inside SD card.

    @return The LineStatus structed value, SENT_COMPLETED = 0, SENT_FAILED = 1, CONNECTION_FAILED = 2.

  */
  uint8_t sendLineImageSD(WiFiClientSecure &client, const String &msg, const String &filePath);

  /*
    Get the text message limit.

    @return The limit count of sending text message.

  */
  uint16_t textMessageLimit(void);

  /*

    Get the image message limit.

    @return The limit count of sending image message.

  */
  uint16_t imageMessageLimit(void);

  /*
    Get the remaining count of sending text message.

    @return The remaining count of sending text message.

  */
  uint16_t textMessageRemaining(void);

  /*
    Get the remaining count of sending image message.

    @return The remaining count of sending image message.

  */
  uint16_t imageMessageRemaining(void);

  /*
    End Line Notify.
  */
  void end(void);

private:
  const uint16_t LINE_PORT = 443;
  std::string _token = "";
  int _textLimit;
  int _imageLimit;
  int _textRemaining;
  int _imageRemaining;

  uint8_t sendLineImageFile(WiFiClientSecure &client, const String &msg, const String &filePath, bool internal);
  bool sdTest();
  bool send_request_header(WiFiClientSecure &client, const std::string &token, size_t contentLength);
  void set_multipart_header(std::string &data, const std::string &arg);
  void set_multipart_boundary(std::string &data);
  bool waitLineResponse(WiFiClientSecure &client);
  void getContentType(const std::string &filename, std::string &buf);
  inline std::string trim(std::string &str);
  void p_memCopy(std::string &buf, const char *p, bool empty = false);

  void strcat_c(char *str, char c);
  int strpos(const char *haystack, const char *needle, int offset);
  int rstrpos(const char *haystack, const char *needle, int offset);
  char *rstrstr(const char *haystack, const char *needle);
  char *replace_char(char *str, char in, char out);
};

extern LineNotifyESP8266 lineNotify;

#endif
