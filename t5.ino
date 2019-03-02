#define enA 9
#define in1 7
#define in2 6
#define enB 3
#define in3 4
#define in4 5
#define button 2
#define s1 13
#define s2 12
#define s4 11
#define s5 10
#define s3 8
//#define mode 

int pressed=0,end=0,mode=0,len=0;
String path="";

void setup() {
  mode=0;
  end=1;
  path="";
  pressed=0;
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(button, INPUT);
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(s5, INPUT);
  Serial.begin(9600);
  analogWrite(enA, 250);
  analogWrite(enB, 100);
}
void reset()
{
  mode=0;
  end=1;
  path="";
  pressed=0;
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(button, INPUT);
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(s5, INPUT);
  Serial.begin(9600);
  analogWrite(enA, 250);
  analogWrite(enB, 100);
}

int check()
{
  
  return(digitalRead(s1)*10000 + digitalRead(s2)*1000 + digitalRead(s3)*100 + digitalRead(s4)*10 + digitalRead(s5));
}

void fw()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void rev()
{
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void right()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  //digitalWrite(enB, 0);
  while(check()!=100);
}

void left()
{
  digitalWrite(in2, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  //digitalWrite(enA, 0);
  while(check()!=100);
}

void sl_right()
{
  
  digitalWrite(in2, LOW);
  digitalWrite(in1, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(enB, 250);
  digitalWrite(enA, 100);
}
void uturn()
{
  stp();
  analogWrite(enB,180);
  analogWrite(enA,180);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  while(check()!=100);
  stp();
}

void sl_left()
{
  digitalWrite(in2, LOW);
  digitalWrite(in1, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(enA, 250);
  digitalWrite(enB, 100);
}

void stp()
{
  digitalWrite(in2, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  //digitalWrite(enA, 0);
  //digitalWrite(enB, 0);
}
int fwchck()
{
  fw();
  delay(1000);
  int c=digitalRead(s3);
  return c;
}
int fwchck2()
{
  fw();
  delay(1000);
  if(check()==11111)
    return 1;
  else
    return 0;
}
String solve(String p)
{
  char temp[100];
  p.toCharArray(temp,100);
  int i,j,k,len2;
  len=p.length();
  for(j=0;j<len;j++)
  {
    Serial.println(temp[j]+'\n');
    if(temp[j]=='U')
    {
      i=j-1;
      k=j+1;
      /*while((temp[i]!='L'&&temp[k]!='R')&&(temp[i]!='R'&&temp[k]!='L')){
        temp[i]='D';
        temp[k]='D';
        i--;
        k++;
      }*/
      if(temp[i]=='L'&&temp[k]=='R')
        temp[i]='U';
      else if(temp[i]=='R'&&temp[k]=='L')
        temp[i]='U';
      else if(temp[i]=='L'&&temp[k]=='L')
        temp[i]='S';
      else if(temp[i]=='S'&&temp[k]=='L')
        temp[i]='R';
      else if(temp[i]=='L'&&temp[k]=='S')
        temp[i]='R';
      i++;
      j=i-1;
      k++;
      for(i;k<len;i++,k++)
        temp[i]=temp[k];
      len-=2;
    }
  }
  Serial.println(temp);
  return temp;
}

void loop() {
  int i,sw,s;
  if(mode==0)
  { 
   delay(10);
    if(end==1){
      s = check();
      Serial.print(s);
      switch(s)
      {
        case 0:
            uturn();
            path=path+'U';
            Serial.println(":u");
            break;
        case 100: 
            fw();
           // path=path+'S';
            Serial.println(":s");
           break;
        case 11100:
            left();
            path=path+'L';
            Serial.println(":l");
            break;
        case 111:
            if(fwchck())
            {
              path=path+'S';
              Serial.println(":s");
            }
            else
            {
              right();
              path=path+'R';
              Serial.println(":r");
            }
            break;
        case 110:
            sl_left();
            Serial.println(":sl");
            break;
        case 1100:
            sl_right();
            Serial.println(":sr");
            break;
        case 11111:
            if(fwchck2())
            {
              path=path+'e';
              Serial.println(":stop");
              Serial.println(path);
              path=solve(path);
              end=0;
              stp();
            }
            else 
            {
              left();
              path=path+'L';
              Serial.println(":l");
            }
            break;
      }
        //default:
        //Serial.println("ghn");
    Serial.println(path);
    }
  }
  else if(mode)
  {
    boolean flag=false;
    Serial.println(path+"/t hello");
    sw = digitalRead(s1)*10 + digitalRead(s5);
    if(sw==10||sw==1||sw==11)
      flag=true;
    if(flag&&i<len)
    {
      char t=path.charAt(i);
      switch(t)
      {
        case 'L': {left(); Serial.print("L .  ");}
        case 'R': {right(); Serial.print("R .   ");}
        case 'S': {fw(); Serial.print("F .  ");}
        case 'e': {i++; Serial.print("e .   ");}
        case ' ': {stp(); Serial.print("S   ");}
      }
      i++;
    }
  }
  pressed=digitalRead(button);
  if(pressed)
  {
    i=0;
    reset();
    mode=!mode;
  }
  pressed=0;  
  //Serial.println(mode);
}
