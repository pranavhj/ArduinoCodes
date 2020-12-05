double x1=300;
double y1=00;
float x[100];
float y[100];
double theta11[100];
double theta21[100];
void setup() {
  // put y1our setup code here, to run once:
Serial.begin(9600);

double x2=200;                                                 //equatoin of line
int i=0;
for(double m=0;m<80;m=m+1)
{x[i]=100;                                                     //getting x,y co-ordinates of points
y[i]=m;
i++; 
}


//for(int l=0;l<i;l++)
//{x1=x[l];
//y1=y[l];  
double theta2=acos(((x1*x1)+(y1*y1)-72148)/32376/2);
//double theta2=atan2(pow(1-pow((x1*x1)+(y1*y1)-72148/2/32376,2),0.5),((x1*x1)+(y1*y1)-72148/32376/2));
double theta1=(atan2(y1,x1)-atan2(228*sin(theta2),(142+(228*cos(theta2)))));                 //getting values of joint angles
theta2=theta2*180/3.142;    theta1=theta1*180/3.142;

Serial.print(theta1);Serial.print("           ");Serial.print(theta2);Serial.print("        ");Serial.print(x1);Serial.print("      ");Serial.println(y1);
//theta11[l]=theta1;
//theta21[l]=theta2;
//}
}

void loop() {
  // put y1our main code here, to run repeatedly1:



}
