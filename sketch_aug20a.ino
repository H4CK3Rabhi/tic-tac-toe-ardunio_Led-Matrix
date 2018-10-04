#define RPIN 13
class Game
{
  
    public:
    int positions[2][9];
    Game()
    {
      for(int i=0;i<9;i++)
      {
        positions[0][i]=0;
        positions[1][i]=0;
      }
    }
    void makemove(int movep,int player)
    {
      if(player==1)
      positions[0][movep-1]=1;
      else
      positions[1][movep-1]=1;
    }
    bool ismovevalid(int mv)
    {
      if(positions[0][mv-1]==1 || positions[1][mv-1]==1)
      {
        return false; 
      }
      return true;
    }
    int checkwinner()
    {
      for(int i=0;i<3;i++)
      {
        if(positions[0][i]==1&& positions[0][i+3]==1&&positions[0][i+6]==1)
        {
          return 1;
        }
        else if(positions[1][i]==1&& positions[1][i+3]==1&&positions[1][i+6]==1)
        {
          return 2;
        }
      }
      if(positions[0][0]==1&& positions[0][4]==1&&positions[0][8]==1)
      {
        return 1;
      }
      else if(positions[0][2]==1&& positions[0][4]==1&&positions[0][6]==1)
      {
        return 1;
        }
         if(positions[1][0]==1&& positions[1][4]==1&&positions[1][8]==1)
      {
        return 2;
      }
      else if(positions[1][2]==1&& positions[1][4]==1&&positions[1][6]==1)
      {
        return 2;
        }
       for(int i=0;i<6;i+=3)
       {
        if(positions[0][i]==1&& positions[0][i+1]==1&&positions[0][i+2]==1)
      {
        return 1;
      }
      else if(positions[1][i]==1&& positions[1][i+1]==1&&positions[0][i+2]==1)
      {
        return 2;
        }
       }
       return 0;
      }
};
int i,p;
void setup() {
  // put your setup code here, to run once:
i=1;
pinMode(1,INPUT);
pinMode(2,INPUT);
pinMode(3,INPUT);
pinMode(4,INPUT);
pinMode(5,INPUT);
pinMode(6,INPUT);
pinMode(7,INPUT);
pinMode(8,INPUT);
pinMode(9,INPUT);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
pinMode(12,OUTPUT);
pinMode(RPIN,OUTPUT);

}
void store()
{
  digitalWrite(12,HIGH);
  delay(1);
  digitalWrite(12,LOW);
}
void printstate(Game o)
{ int glows[8]={36,36,36,36,36,36,36,36};
  for(int j=0;j<8;j++)
  { if(j!=5||j!=2)
  {
      if(o.positions[0][0]==1 || o.positions[0][3]==1||o.positions[0][6]==1)
      {
        glows[j]+=64;
      }
      if(o.positions[1][0]==1 || o.positions[1][3]==1||o.positions[1][6]==1)
      {
        glows[j]+=128;
      }
      if(o.positions[0][1]==1 || o.positions[0][4]==1||o.positions[0][7]==1)
      {
        glows[j]+=8;
      }
      if(o.positions[1][1]==1 || o.positions[1][4]==1||o.positions[1][7]==1)
      {
        glows[j]+=16;
      }
      if(o.positions[0][2]==1 || o.positions[0][5]==1||o.positions[0][8]==1)
      {
        glows[j]+=1;
      }
      if(o.positions[1][2]==1 || o.positions[1][5]==1||o.positions[1][8]==1)
      {
        glows[j]+=2;
      }
  }
      
    }
    glows[2]=255;
    glows[5]=255;
    for(int j=0;j<8;j++)
    {
      shiftOut(10,11,LSBFIRST,~glows[j]);
      shiftOut(10,11,LSBFIRST,128>>j);
      store();
    }
    
  
 
}
 Game ng;
void(* resetFunc) (void) = 0; 
void loop() {
  // put your main code here, to run repeatedly:
  printstate(ng);
  int mv=0;
  if(i%2==0)
  {
    p=2;    
  }
  else
  {
    p=1;
  }
  for(int j=1;j<=9;j++)
  {
    if(digitalRead(j-1))
  {
    mv=j+1;
   break;
  }
  }
printstate(ng);
  if(ng.ismovevalid(mv))
  {
    ng.makemove(mv,p);
    printstate(ng);
    if(ng.checkwinner()==1)
    {
      Serial.print("Player 1 won...");
      delay(700);
      digitalWrite(RPIN,HIGH);
      
    }
    if(ng.checkwinner()==2)
    {
      Serial.print("Player 2 won...");
      delay(700);
      digitalWrite(RPIN,HIGH);
    }
     i++;
  } 
  
}
