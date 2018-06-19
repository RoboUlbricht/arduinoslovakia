// ESP8266 Core: 2.3.0
// Windows
//
// Find file 'c:\Users\[your name]\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.3.0\platform.txt'. 
// In the same directory create file 'platfom.local.txt'. Insert text
// 'compiler.cpp.extra_flags=-D_SSID="xxx" -D_PWD="xxx" -D_APPID="xxx"' into the file.
//
// Or change the parameters in this file.

#if defined(_SSID)
  const char* ssid     = _SSID;
  const char* password = _PWD;
  const char* APPID    = _APPID;
#else
  const char* ssid     = "your-ssid";
  const char* password = "your-password";
  const char* APPID    = "your-appid-from-openweathermap";
#endif
