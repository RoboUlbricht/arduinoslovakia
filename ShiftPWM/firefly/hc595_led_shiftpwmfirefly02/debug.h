#ifdef DEBUG_PRINT

void initDebug()
{
Serial.begin(9600);
}

void printActive(int i, int r, long mil)
{
Serial.print("ff[");
Serial.print(i);
Serial.print("]=");
Serial.print(mil);
Serial.print(", ");
Serial.print(r);
Serial.print(", ");
Serial.print(pt[r].name);
Serial.println(", Active");
}

void printTired(int i)
{
Serial.print("ff[");
Serial.print(i);
Serial.print("]=");
Serial.print(f[i].tired);
Serial.println(", Tired");
}

void printIdle(int i, long mil)
{
Serial.print("ff[");
Serial.print(i);
Serial.print("]=");
Serial.print(mil);
Serial.println(", Idle");
}

#else

#define initDebug()
#define printActive(i, r, mil)
#define printTired(i)
#define printIdle(i, mil)

#endif
