enum ffstate {
  ffIdle=0,ffActive,ffTired};

struct firefly
{
  ffstate state;
  const unsigned char *pattern;
  int pos;
  int length;
  long tired;
  int repeat;
};
