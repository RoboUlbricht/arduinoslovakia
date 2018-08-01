// ESP8266 Core: 2.4.1
// Windows
//
// Find file 'c:\Users\[your name]\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.4.1\platform.txt'. 
// In the same directory create file 'platfom.local.txt'. Insert text
// 'compiler.cpp.extra_flags=-D_SSID="xxx" -D_PWD="xxx"' into the file.
//
// Or change the parameters in this file.

#if defined(_SSID)
  const char* ssid     = _SSID;
  const char* password = _PWD;
#else
  const char* ssid     = "your-ssid";
  const char* password = "your-password";
#endif


