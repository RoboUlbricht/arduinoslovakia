boolean debug=false;
PrintWriter output;

void b(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
fill(0);
if(debug)
  {
  stroke(255, 102, 0);
  line(x1, y1, x2, y2);
  line(x3, y3, x4, y4);
  }
stroke(0, 0, 0);
bezier(x1, y1, x2, y2, x3, y3, x4, y4);  
}

void emptycanvas()
{
background(255);
  
fill(0);
  
line(0,255,600,255);
for(int i=0;i<6;i++)
  {
  line(i*100,255,i*100,255+5);
  text(i,i*100+5,255+15);
  }  
}

void writeheader(String n, int mx, int siz)
{
int last=0;  
output.print("char "+n+"["+siz+"]={");
for(int i=0;i<siz;i++)
  {
  if(i>0) output.print(", ");
  if(i%10==0) output.println("");
  int v=0;
  for(int x=0;x<255;x++)
    {
    color c=get(i,x);
    if(c==color(0))
      {
      v=255-x;  
      x=255;
      last=i;
      }  
    }
  output.print(v);
  }
output.println("};");
output.println("#define MAX_"+n+" "+(last+1));   
output.println("#define DELAY_"+n+" "+(mx-last));   
output.println("");   
}

void setup()
{
size(600, 255+50); 
  
output = createWriter("firefly.h");
  
// test
emptycanvas();  
b(0,255,0,0,10,0,10,255);
b(20,255,20,0,50,0,50,255);
b(70,255,70,0,150,0,150,255);
writeheader("test",170,151);
  
// marginellus
emptycanvas();  
b(0,255,0,-80,40,-80,40,255);
writeheader("marginellus",270,41);

// sabulosus
emptycanvas();  
b(0,255,0,-80,20,-80,20,255);
writeheader("sabulosus",370,21);

// pyralis
emptycanvas();  
b(0,255,0,-80,90,-80,90,255);
writeheader("pyralis",570,91);
  
// umbratus
emptycanvas();  
b(0,255,0,-80,60,-80,60,255);
writeheader("umbratus",650,61);
  
// collustrans
emptycanvas();  
b(0,255,0,-80,40,-80,40,255);
writeheader("collustrans",220,41);
  
// ignitus
emptycanvas();  
b(0,255,0,-80,30,-80,30,255);
writeheader("ignitus",500,31);

// consanguineus
emptycanvas();  
b(0,255,0,-80,30,-80,30,255);
b(50,255,50,-80,80,-80,80,255);
writeheader("consanguineus",550,81);

// greeni
emptycanvas();  
b(0,255,0,-80,30,-80,30,255);
b(150,255,150,-80,180,-80,180,255);
writeheader("greeni",550,181);

// macdermotti
emptycanvas();  
b(0,255,0,-80,30,-80,30,255);
b(200,255,200,-80,230,-80,230,255);
writeheader("macdermotti",550,231);

// consimillis
emptycanvas();  
b(0,255,0,-80,20,-80,20,255);
writeheader("consimillis",40,21);

// carolinus
emptycanvas();  
b(0,255,0,-80,30,-80,30,255);
writeheader("carolinus",60,31);
   
output.flush();  // Writes the remaining data to the file
output.close();  // Finishes the file
}
