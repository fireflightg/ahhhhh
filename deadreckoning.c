// circumference with 56 mm diameter wheel
float revolution = 3.1415 * 56; //175.924
float meter = revolution * 5.6842;


void turn90() {
  nMotorEncoder[motorB] = 0;
  nMotorEncoder[motorC] = 0;
 while(nMotorEncoder[motorC] < revolution * 3.2) {
         motor[motorC] = 100;
         motor[motorB] = 0;
 }
}


void move(int distance) {
  nMotorEncoder[motorB] = 0;
  nMotorEncoder[motorC] = 0;
 while(nMotorEncoder[motorB] < distance) {
         motor[motorC] = 100;
         motor[motorB] = 100;
        }
}


task main() {


 // complete 4 sides of square
 for(int i=0; i < 4; i++) {
          move(meter/2); //move half a meter
          turn90();
 }
}