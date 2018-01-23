const short MaxSampelingSize = 360;
const short proccessSize = MaxSampelingSize / 2;
const short inputPin = A0;
long micros1,micros2;

short input[MaxSampelingSize];
long cor[proccessSize];

short cnt;
short epsilon;
short threshold;
long T;
long test = 0;

float answer;

void setup() {
  // put your setup code here, to run once:
  pinMode(inputPin, INPUT);
  
  cnt = 0;
  epsilon = 2;
  threshold = 300;
/**/
  Serial.begin(9600);
  // prints title with ending line break
  Serial.println("Meysam & Amirhossein proudly presents:");
  Serial.println("Music note detector");
  /**/
  
}

void loop() {
  if(cnt == 0) micros1 = micros();
  if(cnt == MaxSampelingSize-1) micros2 = micros();
  input[cnt] = analogRead(inputPin);
  delayMicroseconds(250);
  /**
  Serial.print("On ");
  Serial.print(cnt);
  Serial.print("read: ");
  Serial.println(input[cnt]);
  /**/
  //In the proceeding code, we assusme that the input array is filled with the right data
  cnt++;
  if(cnt == MaxSampelingSize){
      T = findT(0);
      /**
      Serial.println(micros1);
      Serial.println(micros2);
      Serial.println(T);
      /**/
      outputFunction(T);
      cnt = 0;
  }
  
}

long findT(short j){
  cor[0] = autocorrelation(j,0);
  cor[1] = autocorrelation(j,1);
  for(short i = 2 ; i < proccessSize ; i++){
      cor[i] = autocorrelation(j,i);
      if(cor[i-1] > threshold && (cor[i-1]-cor[i-2] > -epsilon && cor[i-1]-cor[i] > -epsilon)){
          return i-1; 
      }
  }
}

short rightJ(short j, short i){
  return((j+i+MaxSampelingSize)%MaxSampelingSize);
}

long autocorrelation(short j ,short t0){
  long ret = 0;
  long tmp1,tmp2;
  for(short i = 0 ; i < proccessSize ; i++){
    tmp1 = input[rightJ(j,i)];
    tmp2 = input[rightJ(j,i+t0)];
    ret += tmp1 * tmp2; 
  }
  return ret;
}

char* relateNote(float frequency){
   if(frequency >= 85 && frequency < 92.50)
         return "F2";
   if(frequency >= 92.5 && frequency < 98)
         return "F#2/Gb2";
   if(frequency >= 98 && frequency < 103.83)
         return "G2";
   if(frequency >= 103.83 && frequency < 110.00)
         return "G#2/Ab2";
   if(frequency >= 110.00 && frequency < 116.54)
      return "A2";
   if(frequency >= 116.54 && frequency < 123.47)
         return "A#2/Bb2";
   if(frequency >= 123.47 && frequency < 130.81)
         return "B2";
   if(frequency >= 130.81 && frequency < 138.59)
         return "C3";
   if(frequency >= 138.59 && frequency < 146.83)
         return "C#3/Db3";
   if(frequency >= 146.83 && frequency < 155.56)
         return "D3";
   if(frequency >= 155.56 && frequency < 164.81)
         return "D#3/Eb3";
   if(frequency >= 164.81 && frequency < 174.61)
         return "E3";
   if(frequency >= 174.61 && frequency < 185.00)
         return "F3";
   if(frequency >= 185.00 && frequency < 196.00)
         return "F#3/Gb3";
   if(frequency >= 196.00 && frequency < 207.65)
         return "G3";
   if(frequency >= 207.65 && frequency < 220.00)
         return "G#3/Ab3";
   if(frequency >= 220.00 && frequency < 233.08)
         return "A3";
   if(frequency >= 233.08 && frequency < 246.94)
         return "A#3/Bb3";
   if(frequency >= 246.94 && frequency < 261.63)
         return "B3";
   if(frequency >= 261.63 && frequency < 277.18)
         return "C4";
   if(frequency >= 277.18 && frequency < 293.63)
         return "C#4/Db4";
   if(frequency >= 293.63 && frequency < 311.13)
         return "D4";
   if(frequency >= 311.13 && frequency < 329.63)
         return "D#4/Eb4";
   if(frequency >= 329.63 && frequency < 349.23)
         return "E4";
   if(frequency >= 349.23 && frequency < 369.99)
         return "F4";
}

void outputFunction(long T){
  
    float timeSt = micros2 - micros1;
    timeSt = MaxSampelingSize / timeSt;
    timeSt *= 1000000;
    answer = T;
    answer = 1 / answer;
    answer *= timeSt;

    Serial.print(answer);
    Serial.print(" -> ");
    Serial.println(relateNote(answer));
}



