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

void outputFunction(long T){
  
    float timeSt = micros2 - micros1;
    timeSt = MaxSampelingSize / timeSt;
    timeSt *= 1000000;
    answer = T;
    answer = 1 / answer;
    answer *= timeSt;

    Serial.print(answer);
    Serial.print(" -> ");
    
    char* note;
    if(answer >= 85 && answer < 92.50)
         note = "F2";
    if(answer >= 92.5 && answer < 98)
         note = "F#2/Gb2";
    if(answer >= 98 && answer < 103.83)
         note = "G2";
    if(answer >= 103.83 && answer < 110.00)
         note = "G#2/Ab2";
    if(answer >= 110.00 && answer < 116.54)
         note = "A2";
    if(answer >= 116.54 && answer < 123.47)
         note = "A#2/Bb2";
    if(answer >= 123.47 && answer < 130.81)
         note = "B2";
    if(answer >= 130.81 && answer < 138.59)
         note = "C3";
    if(answer >= 138.59 && answer < 146.83)
         note = "C#3/Db3";
    if(answer >= 146.83 && answer < 155.56)
         note = "D3";
    if(answer >= 155.56 && answer < 164.81)
         note = "D#3/Eb3";
    if(answer >= 164.81 && answer < 174.61)
         note = "E3";
    if(answer >= 174.61 && answer < 185.00)
         note = "F3";
    if(answer >= 185.00 && answer < 196.00)
         note = "F#3/Gb3";
    if(answer >= 196.00 && answer < 207.65)
         note = "G3";
    if(answer >= 207.65 && answer < 220.00)
         note = "G#3/Ab3";
    if(answer >= 220.00 && answer < 233.08)
         note = "A3";
    if(answer >= 233.08 && answer < 246.94)
         note = "A#3/Bb3";
    if(answer >= 246.94 && answer < 261.63)
         note = "B3";
    if(answer >= 261.63 && answer < 277.18)
         note = "C4";
    if(answer >= 277.18 && answer < 293.63)
         note = "C#4/Db4";
    if(answer >= 293.63 && answer < 311.13)
         note = "D4";
    if(answer >= 311.13 && answer < 329.63)
         note = "D#4/Eb4";
    if(answer >= 329.63 && answer < 349.23)
         note = "E4";
    if(answer >= 349.23 && answer < 369.99)
         note = "F4";
    Serial.println(note);
}



