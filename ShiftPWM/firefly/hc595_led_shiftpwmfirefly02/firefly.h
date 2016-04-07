enum ffstate {
  ffIdle=0,ffActive,ffTired};

class firefly
{
public:  
  ffstate state;
  const unsigned char *pattern;
  int pos;
  int length;
  long tired;
  int repeat;

  firefly() :
    state(ffIdle), pattern(NULL), pos(0), length(0),
    tired(0), repeat(0)
    {}
};
