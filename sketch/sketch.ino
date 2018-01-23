
const short MaxSampelingSize = 100;
const short proccessSize = MaxSampelingSize / 2;

short input[MaxSampelingSize];
long cor[proccessSize];

short cnt;
short epsilon;
short threshold;
long T;

void setup() {
  // put your setup code here, to run once:
  cnt = 0;
  epsilon = 2;
  threshold = 35;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  cnt++;
  
  //In the proceeding code, we assusme that the input array is filled with the right data
  if(cnt == MaxSampelingSize){
      T = findT(0);
      //TODO: think through the way we want to produce outputs
      outputFunction(T);
      cnt = 0;
  }
}

long findT(short j){
  cor[0] = autocorrelation(j,0);
  cor[1] = autocorrelation(j,1);
  for(short i = 2 ; i < proccessSize ; i++){
      cor[i] = autocorrelation(j,i);
      if(cor[i] > threshold && (cor[i-1]-cor[i-2] > -epsilon && cor[i-1]-cor[i] > -epsilon)){
          return i; 
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
  //Just a placeholder for now
}

