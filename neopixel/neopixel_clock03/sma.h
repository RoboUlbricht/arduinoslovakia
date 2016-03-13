///
/// Moving average
///
/// Simple moving average with fast calculation.
/// typ - any type (int, float, ...)
/// sz - size of buffer
///
template<typename typ, int sz> class MovingAverage
{
  typ data[sz]; // buffer
  int pos;      // actual position in buffer
  typ sum;      // precalculated sum
  
public:
  MovingAverage()
  : pos(0), sum(0)
    {
    memset(data,0,sizeof(data));
    }
    
  void Push(typ value)
    {
    sum-=data[pos];  
    sum+=value;
    data[pos]=value;
    pos++;
    if(pos==sz)
      pos=0;
    }
    
  typ MA()
    {
    return sum/sz;
    }
};

