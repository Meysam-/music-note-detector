
const short MaxSampelingSize = 100;
const short proccessSize = MaxSampelingSize / 2;

short input[MaxSampelingSize];
short cor[proccessSize];

char cnt;
short epsilon;
short threshold;

void setup() {
  // put your setup code here, to run once:
  cnt = 0;
  epsilon = 2;
  threshold = 35;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //TODO: think through the way we want to produce outputs
  

  //In the proceeding code, we assusme that the input array is filled with the right data
  if(cnt == MaxSampelingSize){
      int T = findT();
      
      outputFunction(T);
  }
}

int findT(){
  cor[0] = autocorrelation(0);
  cor[1] = autocorrelation(1);
  for(int i = 2 ; i < proccessSize ; i++){
      cor[i] = autocorrelation(i);
      if(cor[i] > threshold && (cor[i-1]-cor[i-2] > -epsilon && cor[i-1]-cor[i] > -epsilon)){
          return i; 
      }
  }
}

int autocorrelation(short t0){
  int ret = 0;
  int tmp1,tmp2;
  for(int i = 0 ; i < proccessSize ; i++){
    tmp1 = input[i];
    tmp2 = input[i+t0];
    ret += tmp1 * tmp2; 
  }
  return ret;
}

void outputFunction(int T){
  //Just a placeholder for now
}

