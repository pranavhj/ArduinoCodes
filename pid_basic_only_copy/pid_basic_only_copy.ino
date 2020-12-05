float kp,ki,kd;


void setup() {
  // put your setup code here, to run once:

}

void loop() {int curval,tarval,pwmval;
  // put your main code here, to run repeatedly:
int pwmtofeed=pidfunc(curval,tarval,pwmval);
}
int pidfunc(int currentvalue, int targetvalue,int pwmvalue)
   {int error=targetvalue-currentvalue;static int lasterror=0;static int totalerror=0;
    float pidterm=0;
    totalerror=totalerror+error;
    pidterm=kp*(error)+ki*(totalerror)+kd*(error-lasterror);
    lasterror=error;
    return(constrain(pidterm,0,255));
   }
