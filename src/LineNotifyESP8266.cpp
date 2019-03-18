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

#ifndef LineNotifyESP8266_CPP
#define LineNotifyESP8266_CPP

#include "LineNotifyESP8266.h"

LineNotifyESP8266::LineNotifyESP8266(){};
LineNotifyESP8266 ::~LineNotifyESP8266() {}

void LineNotifyESP8266::end()
{
  std::string().swap(_token);
};

void LineNotifyESP8266::init(const String &token)
{
  SPIFFS.begin();
  _token = token.c_str();
}

void LineNotifyESP8266::setToken(const String &token)
{
  _token = token.c_str();
}

bool LineNotifyESP8266::send_request_header(WiFiClientSecure &client, const std::string &token, size_t contentLength)
{

  std::string data = "";
  char *val = new char[10];
  memset(val, 0, 10);

  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_5, true);
  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_4);

  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_6);
  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_4);

  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_7);
  data += token;
  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_4);

  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_8);
  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_2);
  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_4);

  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_9);
  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_3);
  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_4);

  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_10);
  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_4);

  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_11);
  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_1);
  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_4);

  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_12);
  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_4);

  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_13);
  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_4);

  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_14);

  itoa(contentLength, val, 10);
  data += val;
  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_4);
  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_4);

  int res = client.print(data.c_str());
  int dlen = data.length();

  std::string().swap(data);
  delete[] val;

  return res == dlen;
}

void LineNotifyESP8266::set_multipart_header(std::string &data, const std::string &arg)
{
  char *t = new char[20];
  bool flag = false;

  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_24);
  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_2);
  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_4);

  memset(t, 0, 20);
  strcpy_P(t, ESP8266_LINE_NOTIFY_STR_19);
  flag = strcmp(t, arg.c_str()) == 0;

  memset(t, 0, 20);
  strcpy_P(t, ESP8266_LINE_NOTIFY_STR_20);
  flag |= strcmp(t, arg.c_str()) == 0;

  memset(t, 0, 20);
  strcpy_P(t, ESP8266_LINE_NOTIFY_STR_21);
  flag |= strcmp(t, arg.c_str()) == 0;

  memset(t, 0, 20);
  strcpy_P(t, ESP8266_LINE_NOTIFY_STR_22);
  flag |= strcmp(t, arg.c_str()) == 0;

  memset(t, 0, 20);
  strcpy_P(t, ESP8266_LINE_NOTIFY_STR_23);
  flag |= strcmp(t, arg.c_str()) == 0;

  if (flag)
  {
    p_memCopy(data, ESP8266_LINE_NOTIFY_STR_18);
    data += arg;
    p_memCopy(data, ESP8266_LINE_NOTIFY_STR_25);
    p_memCopy(data, ESP8266_LINE_NOTIFY_STR_4);
    p_memCopy(data, ESP8266_LINE_NOTIFY_STR_4);
  }
  else
  {
    p_memCopy(data, ESP8266_LINE_NOTIFY_STR_16);
    data += arg;
    p_memCopy(data, ESP8266_LINE_NOTIFY_STR_25);
    p_memCopy(data, ESP8266_LINE_NOTIFY_STR_4);

    p_memCopy(data, ESP8266_LINE_NOTIFY_STR_17);
    getContentType(arg, data);
    p_memCopy(data, ESP8266_LINE_NOTIFY_STR_4);
    p_memCopy(data, ESP8266_LINE_NOTIFY_STR_4);
  }
  delete[] t;
}

void LineNotifyESP8266::set_multipart_boundary(std::string &data)
{
  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_24);
  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_2);
  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_24);
  p_memCopy(data, ESP8266_LINE_NOTIFY_STR_4);
}

uint8_t LineNotifyESP8266::sendLineMessage(WiFiClientSecure &client, const String &msg)
{

  char *host = new char[strlen(ESP8266_LINE_NOTIFY_STR_1) + 1];
  memset(host, 0, strlen(ESP8266_LINE_NOTIFY_STR_1) + 1);
  strcpy_P(host, ESP8266_LINE_NOTIFY_STR_1);

  if (!client.connect(host, LINE_PORT))
  {
    delete[] host;
    return LineNotifyESP8266::LineStatus::CONNECTION_FAILED;
  }

  char *arg = new char[50];
  memset(arg, 0, 50);
  strcpy_P(arg, ESP8266_LINE_NOTIFY_STR_19);

  std::string textHeader = "";
  set_multipart_header(textHeader, arg);

  textHeader += msg.c_str();
  p_memCopy(textHeader, ESP8266_LINE_NOTIFY_STR_4);
  set_multipart_boundary(textHeader);

  delete[] host;
  delete[] arg;

  if (send_request_header(client, _token.c_str(), textHeader.length()))
  {

    client.print(textHeader.c_str());
    std::string().swap(textHeader);

    if (waitLineResponse(client))
      return LineNotifyESP8266::LineStatus::SENT_COMPLETED;
    else
      return LineNotifyESP8266::LineStatus::SENT_FAILED;
  }

  std::string().swap(textHeader);
  return LineNotifyESP8266::LineStatus::CONNECTION_FAILED;
}

uint8_t LineNotifyESP8266::sendLineSticker(WiFiClientSecure &client, const String &msg, uint16_t stickerPackageId, uint16_t stickerId)
{

  char *host = new char[strlen(ESP8266_LINE_NOTIFY_STR_1) + 1];
  memset(host, 0, strlen(ESP8266_LINE_NOTIFY_STR_1) + 1);
  strcpy_P(host, ESP8266_LINE_NOTIFY_STR_1);

  if (!client.connect(host, LINE_PORT))
  {
    delete[] host;
    return LineNotifyESP8266::LineStatus::CONNECTION_FAILED;
  }

  char *val = new char[20];
  std::string textHeader = "";

  char *arg = new char[50];
  memset(arg, 0, 50);
  strcpy_P(arg, ESP8266_LINE_NOTIFY_STR_19);

  set_multipart_header(textHeader, arg);
  textHeader += msg.c_str();
  p_memCopy(textHeader, ESP8266_LINE_NOTIFY_STR_4);

  memset(arg, 0, 50);
  strcpy_P(arg, ESP8266_LINE_NOTIFY_STR_20);

  set_multipart_header(textHeader, arg);
  memset(val, 0, 20);
  itoa(stickerPackageId, val, 10);
  textHeader += val;
  p_memCopy(textHeader, ESP8266_LINE_NOTIFY_STR_4);

  memset(arg, 0, 50);
  strcpy_P(arg, ESP8266_LINE_NOTIFY_STR_21);

  set_multipart_header(textHeader, arg);
  memset(val, 0, 20);
  itoa(stickerId, val, 10);
  textHeader += val;
  p_memCopy(textHeader, ESP8266_LINE_NOTIFY_STR_4);

  set_multipart_boundary(textHeader);

  delete[] val;
  delete[] arg;
  delete[] host;

  if (send_request_header(client, _token, textHeader.length()))
  {

    client.print(textHeader.c_str());

    std::string().swap(textHeader);

    if (waitLineResponse(client))
      return LineNotifyESP8266::LineStatus::SENT_COMPLETED;
    else
      return LineNotifyESP8266::LineStatus::SENT_FAILED;
  }

  std::string().swap(textHeader);

  return LineNotifyESP8266::LineStatus::CONNECTION_FAILED;
}

uint8_t LineNotifyESP8266::sendLineImageData(WiFiClientSecure &client, const String &msg, const String &fileName, const uint8_t *imageData, size_t imageLength)
{

  char *host = new char[strlen(ESP8266_LINE_NOTIFY_STR_1) + 1];
  memset(host, 0, strlen(ESP8266_LINE_NOTIFY_STR_1) + 1);
  strcpy_P(host, ESP8266_LINE_NOTIFY_STR_1);

  if (!client.connect(host, LINE_PORT))
  {
    delete[] host;
    return LineNotifyESP8266::LineStatus::CONNECTION_FAILED;
  }

  std::string textHeader = "";
  std::string imageHeader = "";
  std::string boundary = "";

  char *arg = new char[50];
  memset(arg, 0, 50);
  strcpy_P(arg, ESP8266_LINE_NOTIFY_STR_19);

  set_multipart_header(textHeader, arg);
  textHeader += msg.c_str();
  p_memCopy(textHeader, ESP8266_LINE_NOTIFY_STR_4);

  set_multipart_header(imageHeader, fileName.c_str());

  set_multipart_boundary(boundary);

  uint32_t contentLength = textHeader.length() + imageHeader.length() + imageLength + boundary.length();

  if (send_request_header(client, _token, contentLength))
  {

    client.print(textHeader.c_str());

    client.print(imageHeader.c_str());

    size_t chunkSize = 512;

    size_t byteRead = 0;

    while (byteRead < imageLength)
    {
      if (byteRead + chunkSize < imageLength)
      {
        client.write(imageData, chunkSize);
        imageData += chunkSize;
        byteRead += chunkSize;
      }
      else
      {
        client.write(imageData, imageLength - byteRead);
        imageData += chunkSize;
        byteRead = imageLength;
      }
      yield();
    }

    memset(arg, 0, 50);
    strcpy_P(arg, ESP8266_LINE_NOTIFY_STR_4);

    client.print(arg);

    client.print(boundary.c_str());

    std::string().swap(textHeader);
    std::string().swap(imageHeader);
    std::string().swap(boundary);
    delete[] host;
    delete[] arg;

    if (waitLineResponse(client))
      return LineNotifyESP8266::LineStatus::SENT_COMPLETED;
    else
      return LineNotifyESP8266::LineStatus::SENT_FAILED;
  }

  std::string().swap(textHeader);
  std::string().swap(imageHeader);
  std::string().swap(boundary);
  delete[] host;
  delete[] arg;

  return LineNotifyESP8266::LineStatus::CONNECTION_FAILED;
}

uint8_t LineNotifyESP8266::sendLineImageURL(WiFiClientSecure &client, const String &msg, const String &imageURL)
{

  char *host = new char[strlen(ESP8266_LINE_NOTIFY_STR_1) + 1];
  memset(host, 0, strlen(ESP8266_LINE_NOTIFY_STR_1) + 1);
  strcpy_P(host, ESP8266_LINE_NOTIFY_STR_1);

  if (!client.connect(host, LINE_PORT))
  {
    delete[] host;
    return LineNotifyESP8266::LineStatus::CONNECTION_FAILED;
  }

  std::string textHeader = "";
  char *arg = new char[50];
  memset(arg, 0, 50);
  strcpy_P(arg, ESP8266_LINE_NOTIFY_STR_19);

  set_multipart_header(textHeader, arg);
  textHeader += msg.c_str();
  p_memCopy(textHeader, ESP8266_LINE_NOTIFY_STR_4);

  memset(arg, 0, 50);
  strcpy_P(arg, ESP8266_LINE_NOTIFY_STR_22);

  set_multipart_header(textHeader, arg);
  textHeader += imageURL.c_str();
  p_memCopy(textHeader, ESP8266_LINE_NOTIFY_STR_4);

  memset(arg, 0, 50);
  strcpy_P(arg, ESP8266_LINE_NOTIFY_STR_23);

  set_multipart_header(textHeader, arg);
  textHeader += imageURL.c_str();
  p_memCopy(textHeader, ESP8266_LINE_NOTIFY_STR_4);

  set_multipart_boundary(textHeader);

  if (send_request_header(client, _token, textHeader.length()))
  {

    client.print(textHeader.c_str());
    std::string().swap(textHeader);
    delete[] host;
    delete[] arg;

    if (waitLineResponse(client))
      return LineNotifyESP8266::LineStatus::SENT_COMPLETED;
    else
      return LineNotifyESP8266::LineStatus::SENT_FAILED;
  }

  std::string().swap(textHeader);
  delete[] host;
  delete[] arg;
  return LineNotifyESP8266::LineStatus::CONNECTION_FAILED;
}

uint8_t LineNotifyESP8266::sendLineImageFile(WiFiClientSecure &client, const String &msg, const String &filePath, bool internal)
{
  bool fileExisted = false;

  if (internal)
    fileExisted = SPIFFS.exists(filePath);
  else
  {
    if (!sdTest())
      return LineNotifyESP8266::LineStatus::SENT_FAILED;

    fileExisted = SD.exists(filePath);
  }

  if (fileExisted)
  {

    std::string textHeader = "";
    std::string imageHeader = "";
    std::string boundary = "";

    File file;
    fs::File _file;

    uint32_t imageLength = 0;

    if (internal)
    {
      _file = SPIFFS.open(filePath, "r");
      imageLength = _file.size();
    }

    else
    {
      file = SD.open(filePath, FILE_READ);
      imageLength = file.size();
    }

    char *host = new char[strlen(ESP8266_LINE_NOTIFY_STR_1) + 1];
    memset(host, 0, strlen(ESP8266_LINE_NOTIFY_STR_1) + 1);
    strcpy_P(host, ESP8266_LINE_NOTIFY_STR_1);

    if (!client.connect(host, LINE_PORT))
    {
      delete[] host;
      return LineNotifyESP8266::LineStatus::CONNECTION_FAILED;
    }

    char *arg = new char[50];
    memset(arg, 0, 50);
    strcpy_P(arg, ESP8266_LINE_NOTIFY_STR_19);

    set_multipart_header(textHeader, arg);
    textHeader += msg.c_str();
    p_memCopy(textHeader, ESP8266_LINE_NOTIFY_STR_4);

    set_multipart_header(imageHeader, filePath.c_str());

    set_multipart_boundary(boundary);

    uint32_t contentLength = textHeader.length() + imageHeader.length() + imageLength + boundary.length();

    if (send_request_header(client, _token, contentLength))
    {

      client.print(textHeader.c_str());

      client.print(imageHeader.c_str());

      size_t chunkSize = 256;
      uint8_t *chunk = new uint8_t[chunkSize];
      size_t byteRead = 0;

      while (byteRead < imageLength)
      {
        memset(chunk, 0, chunkSize);
        if (byteRead + chunkSize < imageLength)
        {
          if (internal)
            _file.read(chunk, chunkSize);
          else
            file.read(chunk, chunkSize);

          client.write(chunk, chunkSize);
          byteRead += chunkSize;
        }
        else
        {
          if (internal)
            _file.read(chunk, imageLength - byteRead);
          else
            file.read(chunk, imageLength - byteRead);

          client.write(chunk, imageLength - byteRead);
          byteRead = imageLength;
          break;
        }
        yield();
      }

      delete[] chunk;

      if (internal)
        _file.close();
      else
        file.close();

      memset(arg, 0, 50);
      strcpy_P(arg, ESP8266_LINE_NOTIFY_STR_4);

      client.print(arg);

      client.print(boundary.c_str());

      std::string().swap(textHeader);
      std::string().swap(imageHeader);
      std::string().swap(boundary);
      delete[] host;
      delete[] arg;

      if (waitLineResponse(client))
        return LineNotifyESP8266::LineStatus::SENT_COMPLETED;
      else
        return LineNotifyESP8266::LineStatus::SENT_FAILED;
    }

    std::string().swap(textHeader);
    std::string().swap(imageHeader);
    std::string().swap(boundary);

    delete[] host;
    delete[] arg;
    return LineNotifyESP8266::LineStatus::CONNECTION_FAILED;
  }
}

uint8_t LineNotifyESP8266::sendLineImageSPIF(WiFiClientSecure &client, const String &msg, const String &filePath)
{
  return sendLineImageFile(client, msg, filePath, true);
}

uint8_t LineNotifyESP8266::sendLineImageSD(WiFiClientSecure &client, const String &msg, const String &filePath)
{
  return sendLineImageFile(client, msg, filePath, false);
}

bool LineNotifyESP8266::waitLineResponse(WiFiClientSecure &client)
{

  size_t resSize = 200;
  size_t bufSize = 50;
  char *lineBuf = new char[resSize];
  memset(lineBuf, 0, resSize);

  char *tmp = new char[bufSize];
  memset(tmp, 0, bufSize);

  long dataTime = millis();
  char c;
  int p1, p2;

  int httpCode = -1000;
  _textLimit = 0;
  _textRemaining = 0;
  _imageLimit = 0;
  _imageRemaining = 0;

  while (client.connected() && !client.available() && millis() - dataTime < 5000)
    delay(1);

  dataTime = millis();
  if (client.connected() && client.available())
  {
    while (client.available())
    {

      yield();

      c = client.read();
      if (c != '\r' && c != '\n')
        strcat_c(lineBuf, c);

      if (c == '\n')
      {

        dataTime = millis();

        memset(tmp, 0, bufSize);
        strcpy_P(tmp, ESP8266_LINE_NOTIFY_STR_36);

        p1 = strpos(lineBuf, tmp, 0);
        if (p1 != -1)
        {
          memset(tmp, 0, bufSize);
          strcpy_P(tmp, ESP8266_LINE_NOTIFY_STR_37);

          p2 = strpos(lineBuf, tmp, p1 + strlen(ESP8266_LINE_NOTIFY_STR_36));
          if (p2 != -1)
          {
            memset(tmp, 0, bufSize);
            strncpy(tmp, lineBuf + p1 + strlen(ESP8266_LINE_NOTIFY_STR_36), p2 - p1 - strlen(ESP8266_LINE_NOTIFY_STR_36));
            httpCode = atoi(tmp);
          }
        }
        else
        {

          memset(tmp, 0, bufSize);
          strcpy_P(tmp, ESP8266_LINE_NOTIFY_STR_38);
          p1 = strpos(lineBuf, tmp, 0);
          if (p1 != -1)
          {
            memset(tmp, 0, bufSize);
            strncpy(tmp, lineBuf + p1 + strlen(ESP8266_LINE_NOTIFY_STR_38), strlen(lineBuf) - p1 - strlen(ESP8266_LINE_NOTIFY_STR_38));
            _textLimit = atoi(tmp);
          }

          memset(tmp, 0, bufSize);
          strcpy_P(tmp, ESP8266_LINE_NOTIFY_STR_39);
          p1 = strpos(lineBuf, tmp, 0);
          if (p1 != -1)
          {
            memset(tmp, 0, bufSize);
            strncpy(tmp, lineBuf + p1 + strlen(ESP8266_LINE_NOTIFY_STR_39), strlen(lineBuf) - p1 - strlen(ESP8266_LINE_NOTIFY_STR_39));
            _imageLimit = atoi(tmp);
          }

          memset(tmp, 0, bufSize);
          strcpy_P(tmp, ESP8266_LINE_NOTIFY_STR_40);
          p1 = strpos(lineBuf, tmp, 0);
          if (p1 != -1)
          {
            memset(tmp, 0, bufSize);
            strncpy(tmp, lineBuf + p1 + strlen(ESP8266_LINE_NOTIFY_STR_40), strlen(lineBuf) - p1 - strlen(ESP8266_LINE_NOTIFY_STR_40));
            _textRemaining = atoi(tmp);
          }

          memset(tmp, 0, bufSize);
          strcpy_P(tmp, ESP8266_LINE_NOTIFY_STR_41);
          p1 = strpos(lineBuf, tmp, 0);
          if (p1 != -1)
          {
            memset(tmp, 0, bufSize);
            strncpy(tmp, lineBuf + p1 + strlen(ESP8266_LINE_NOTIFY_STR_41), strlen(lineBuf) - p1 - strlen(ESP8266_LINE_NOTIFY_STR_41));
            _imageRemaining = atoi(tmp);
          }
        }

        memset(lineBuf, 0, resSize);
      }

      if (millis() - dataTime > 5000)
      {
        httpCode = -11;
        break;
      }
    }
  }

  delete[] lineBuf;
  delete[] tmp;

  return httpCode == 200;
}

void LineNotifyESP8266::getContentType(const std::string &filename, std::string &buf)
{
  bool flag = false;
  bool match = false;
  size_t bufSize = 50;
  char *tmp = new char[bufSize];
  memset(tmp, 0, bufSize);

  strcpy_P(tmp, ESP8266_LINE_NOTIFY_STR_35);

  int p1 = filename.find_last_of(tmp);
  if (p1 != std::string::npos)
  {
    memset(tmp, 0, bufSize);
    strcpy_P(tmp, ESP8266_LINE_NOTIFY_STR_26);
    flag = filename.find(tmp, p1) != std::string::npos;

    memset(tmp, 0, bufSize);
    strcpy_P(tmp, ESP8266_LINE_NOTIFY_STR_27);
    flag |= filename.find(tmp, p1) != std::string::npos;

    if (flag)
    {
      memset(tmp, 0, bufSize);
      strcpy_P(tmp, ESP8266_LINE_NOTIFY_STR_28);
      buf += tmp;
      delete[] tmp;
      return;
    }

    memset(tmp, 0, bufSize);
    strcpy_P(tmp, ESP8266_LINE_NOTIFY_STR_29);

    if (filename.find(tmp, p1) != std::string::npos)
    {
      memset(tmp, 0, bufSize);
      strcpy_P(tmp, ESP8266_LINE_NOTIFY_STR_30);
      buf += tmp;
      delete[] tmp;
      return;
    }

    memset(tmp, 0, bufSize);
    strcpy_P(tmp, ESP8266_LINE_NOTIFY_STR_31);

    if (filename.find(tmp, p1) != std::string::npos)
    {
      memset(tmp, 0, bufSize);
      strcpy_P(tmp, ESP8266_LINE_NOTIFY_STR_32);
      buf += tmp;
      delete[] tmp;
      return;
    }

    memset(tmp, 0, bufSize);
    strcpy_P(tmp, ESP8266_LINE_NOTIFY_STR_33);

    if (filename.find(tmp, p1) != std::string::npos)
    {
      memset(tmp, 0, bufSize);
      strcpy_P(tmp, ESP8266_LINE_NOTIFY_STR_34);
      buf += tmp;
      delete[] tmp;
      return;
    }
  }
}

uint16_t LineNotifyESP8266::textMessageLimit(void)
{
  return _textLimit;
}

uint16_t LineNotifyESP8266::textMessageRemaining(void)
{
  return _textRemaining;
}

uint16_t LineNotifyESP8266::imageMessageLimit(void)
{
  return _imageLimit;
}

uint16_t LineNotifyESP8266::imageMessageRemaining(void)
{
  return _imageRemaining;
}

void LineNotifyESP8266::p_memCopy(std::string &buf, const char *p, bool empty)
{
  if (empty)
    buf.clear();
  size_t len = strlen(p) + 1;
  char *b = new char[len];
  memset(b, 0, len);
  strcpy(b, p);
  buf += b;
  delete[] b;
}

bool LineNotifyESP8266::sdTest()
{
  File file;
  std::string filepath = "";
  p_memCopy(filepath, ESP8266_LINE_NOTIFY_STR_43, true);

  SD.begin();

  file = SD.open(filepath.c_str(), FILE_WRITE);
  if (!file)
    goto EXIT_5;

  if (!file.write(32))
    goto EXIT_5;
  file.close();

  file = SD.open(filepath.c_str());
  if (!file)
    goto EXIT_5;

  while (file.available())
  {
    if (file.read() != 32)
      goto EXIT_5;
  }
  file.close();

  SD.remove(filepath.c_str());

  std::string().swap(filepath);

  return true;

EXIT_5:
  std::string().swap(filepath);
  return false;
}

void LineNotifyESP8266::strcat_c(char *str, char c)
{
  for (; *str; str++)
    ;
  *str++ = c;
  *str++ = 0;
}
int LineNotifyESP8266::strpos(const char *haystack, const char *needle, int offset)
{
  char _haystack[strlen(haystack)];
  strncpy(_haystack, haystack + offset, strlen(haystack) - offset);
  char *p = strstr(_haystack, needle);
  if (p)
    return p - _haystack + offset;
  return -1;
}

int LineNotifyESP8266::rstrpos(const char *haystack, const char *needle, int offset)
{
  char _haystack[strlen(haystack)];
  strncpy(_haystack, haystack + offset, strlen(haystack) - offset);
  char *p = rstrstr(_haystack, needle);
  if (p)
    return p - _haystack + offset;
  return -1;
}

char *LineNotifyESP8266::rstrstr(const char *haystack, const char *needle)
{
  int needle_length = strlen(needle);
  const char *haystack_end = haystack + strlen(haystack) - needle_length;
  const char *p;
  size_t i;
  for (p = haystack_end; p >= haystack; --p)
  {
    for (i = 0; i < needle_length; ++i)
    {
      if (p[i] != needle[i])
        goto next;
    }
    return (char *)p;
  next:;
  }
  return 0;
}
char *LineNotifyESP8266::replace_char(char *str, char in, char out)
{
  char *p = str;
  while (p != '\0')
  {
    if (*p == in)
      *p == out;
    ++p;
  }
  return str;
}

LineNotifyESP8266 lineNotify = LineNotifyESP8266();

#endif
