
const short MaxSampelingSize = 425;
const short proccessSize = MaxSampelingSize / 2;
const short inputPin = A0;
long milis1,milis2;

short input[MaxSampelingSize];
long cor[proccessSize];

short cnt;
short epsilon;
short threshold;
long T;
long test = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(inputPin, INPUT);
  
  cnt = 0;
  epsilon = 2;
  threshold = 300;
/**/
  Serial.begin(9600);
  Serial.print(inputPin);
  // prints title with ending line break
  Serial.println("Meysam & Amirhossein proudly presents:");
  Serial.println("Music note detector");
  /**/
  
}

void loop() {
  if(cnt%2) milis1 = micros();
  else milis2 = micros();
  input[cnt] = analogRead(A0);
  delayMicroseconds(210);
  /**
  Serial.print("On ");
  Serial.print(cnt);
  Serial.print("read: ");
  Serial.println(input[cnt]);
  /**/
  //In the proceeding code, we assusme that the input array is filled with the right data
  cnt++;
  if(cnt == MaxSampelingSize){
      Serial.println(milis1);
      Serial.println(milis2);
      T = findT(0);
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
    Serial.println(T);
}

