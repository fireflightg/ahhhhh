#pragma config(Sensor, S1, touchSensor, sensorTouch)
#pragma config(Sensor, S2, irSensor, sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3, sonarSensor, sensorSONAR)
#pragma config(Sensor, S4, analogSensor, sensorAnalogActive)

// 10 inches or less is considered near
int NEAR_SONAR = 25;
int NEAR_ANALOG = 1020;
int SPEED = 50;

typedef struct {
  float dir;
  float mag;
} VECTOR;

void vectorSum(VECTOR const& a, VECTOR const& b, VECTOR& sum)
{
  float atheta = PI * a.dir / 180;
  float btheta = PI * b.dir / 180;
  float ax = a.mag * cos(atheta);
  float ay = a.mag * sin(atheta);
  float bx = b.mag * cos(btheta);
  float by = b.mag * sin(btheta);
  float rx = ax + bx;
  float ry = ay + by;
  float r = sqrt(rx * rx + ry * ry);

  //nxtDisplayCenteredTextLine(5, "%f %f", ax, bx);

  sum.mag = r;

  if (rx == 0)
    sum.dir = (ry > 0 ? 90 : (ry < 0 ? -90 : 0));
  else
  {
    sum.dir = 180 * atan(ry / rx) / PI; // arctan approximation
    if (rx < 0) {
      if (ry < 0)
        sum.dir = sum.dir - 180;
      else
        sum.dir = 180 + sum.dir;
    }
  }
  //nxtDisplayCenteredTextLine(6, "%f %f", sum.mag, sum.dir);
}

/* Checks if the EOPD sensor detects an obstacle. */
bool obstacleNearAnalog() {
  return (SensorValue[analogSensor] < NEAR_ANALOG) ? true : false;
}

/* Checks if the SONAR sensor detects an obstacle. */
bool obstacleNearSonar() {
  return (SensorValue[sonarSensor] < NEAR_SONAR) ? true : false;
}

/*
 * Creates a Vector that runs away from obstacles
 * detected by SONAR and EOPD sensor.
 *
 * Assumes the SONAR is facing 45 degrees left of the robot.
 * Assumes the EOPD is facing 45 degrees right of the robot.
 */
void runaway(VECTOR& v) {
  bool sonar = obstacleNearSonar();
  bool analog = obstacleNearAnalog();

  VECTOR analogVector;
  analogVector.mag = (analog) ? 1.0 : 0;
  analogVector.dir = (analog) ? 135 : 0;

  VECTOR sonarVector;
  sonarVector.mag = (sonar) ? 1.0 : 0;
  sonarVector.dir = (sonar) ? -135 : 0;

  vectorSum(analogVector, sonarVector, v);
}

/*
 * Directs Vector v to the IR signal.
 * Moves left or right by 30 degrees
 * if no IR signal is detected.
 */
void move2Goal(VECTOR& v) {
  int irSensor = SensorValue[S2];
  v.mag = 1.0;

  if(irSensor == 0)
    v.dir = (random(1) == 1) ? 30 : -30;
  else
    v.dir = (5 - irSensor) * 22; //22 degrees
}

/*
 * Turns the robot by a rotation value.
 * A rotation value of 348 is equivalent
 * to 180 degree turn.
 */
void turn(float rot)
{
  float dir = (rot * 348) / 180;
  float speed = abs(dir / 5.8);
  if (dir > 0)
  {
    motor[motorA] = -speed;
    motor[motorC] = speed;
    wait1Msec(500);
  }
  else if (dir < 0)
  {
    motor[motorA] = speed;
    motor[motorC] = -speed;
    wait1Msec(500);
  }
  motor[motorA] = 0;   //power level of 100.
  motor[motorC] = 0;
}

/*
 * Moves the robot forward by its speed and magnitude.
 */
void move(float mag) {
  motor[motorA] = mag * SPEED;   //Motor A & C is at
  motor[motorC] = mag * SPEED;   //power level of 100.
  wait1Msec(500);
}

task main() {

  VECTOR goalVector, repulseVector, attractVector;

  nxtDisplayCenteredTextLine(0, "Running...");
  while(true) {
    move2Goal(goalVector);
    nxtDisplayCenteredTextLine(1, "%f %f", goalVector.dir, goalVector.mag);

    runaway(repulseVector);
    nxtDisplayCenteredTextLine(2, "%f %f", repulseVector.dir, repulseVector.mag);

    vectorSum(goalVector, repulseVector, attractVector);
    nxtDisplayCenteredTextLine(3, "%f %f", attractVector.dir, attractVector.mag);

    // now move robot
    turn(attractVector.dir);
    move(attractVector.mag);
  }

}
