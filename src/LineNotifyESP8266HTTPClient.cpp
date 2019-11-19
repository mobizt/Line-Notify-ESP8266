/*
 * HTTP Client wrapper v1.0.6
 * 
 * The MIT License (MIT)
 * Copyright (c) 2019 K. Suwatchai (Mobizt)
 * 
 * 
 * Permission is hereby granted, free of charge, to any person returning a copy of
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

#ifndef LineNotifyESP8266HTTPClient_CPP
#define LineNotifyESP8266HTTPClient_CPP

#include "LineNotifyESP8266HTTPClient.h"

LineNotifyHTTPClient::LineNotifyHTTPClient()
{
}

LineNotifyHTTPClient::~LineNotifyHTTPClient()
{
  end();
}
void LineNotifyHTTPClient::end()
{
  _client->stop();
  _client.reset();
  _client.release();
}

void LineNotifyHTTPClient::setRootCA(const char *rootCA)
{

#ifndef USING_AXTLS
    _client->setBufferSizes(512, 512);
#endif

  if (rootCA)
  {
#ifndef USING_AXTLS
    _client->setTrustAnchors(new X509List(rootCA));
#else
    _client->setCACert_P(rootCA, strlen_P(rootCA));
#endif
  }
  else
  {
#ifndef USING_AXTLS
    _client->setInsecure();
#endif
  }

  _client->setNoDelay(true);
}

void LineNotifyHTTPClient::setRootCAFile(std::string &rootCAFile, uint8_t storageType, uint8_t sdPin)
{

#ifndef USING_AXTLS
  _sdPin = sdPin;
    _client->setBufferSizes(512, 512);

  if (_clockReady && rootCAFile.length() > 0)
  {
    if (storageType == 0)
    {
      bool t = SPIFFS.begin();
      if (t)
      {
        fs::File f;
        if (SPIFFS.exists(rootCAFile.c_str()))
        {
          f = SPIFFS.open(rootCAFile.c_str(), "r");
          size_t len = f.size();
          uint8_t *der = new uint8_t[len];
          if (f.available())
            f.read(der, len);

          f.close();
          _client->setTrustAnchors(new X509List(der, len));
          delete[] der;
        }
      }
    }
    else
    {
      bool t = SD.begin(_sdPin);
      if (t)
      {
        File f;
        if (SD.exists(rootCAFile.c_str()))
        {
          f = SD.open(rootCAFile.c_str(), FILE_READ);
          size_t len = f.size();
          uint8_t *der = new uint8_t[len];
          if (f.available())
            f.read(der, len);

          f.close();
          _client->setTrustAnchors(new X509List(der, len));
          delete[] der;
        }
      }
    }
  }
#endif

  _client->setNoDelay(true);
}

bool LineNotifyHTTPClient::begin(const std::string host, uint16_t port)
{
  _host = host;
  _port = port;
  return true;
}

bool LineNotifyHTTPClient::connected()
{
  return _client->connected();
}

bool LineNotifyHTTPClient::sendHeader(const char *header)
{
  if (!connected())
    return false;
  _client->print(header);
  return true;
}

int LineNotifyHTTPClient::sendRequest(const char *header, const char *payload)
{
  size_t size = strlen(payload);
  if (!connect())
    return HTTPC_ERROR_CONNECTION_REFUSED;
  if (!sendHeader(header))
    return HTTPC_ERROR_SEND_HEADER_FAILED;
  if (size > 0)
    _client->print(payload);

  return 0;
}

bool LineNotifyHTTPClient::connect(void)
{
  if (connected())
  {
    while (_client->available() > 0)
      _client->read();
    return true;
  }

  if (!_client->connect(_host.c_str(), _port))
    return false;

  return connected();
}
#endif