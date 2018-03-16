//*!!Sensor,    dgt16,          Bumbswitch, BumbswitchActive,      ,              !!*//
//*!! Motor,     motor1,         Motorvalue, MotorActive,                                                                !!*//
//*!!Start automatically generated configuration code.                           !!*//
const tSensors Bumbsensor          = dgt16;
const tMotor  Motorsensor          = Motor393;
//sensorLightActive  //*!!!!*//
//*!!CLICK to edit 'wizard' created sensor & motor configuration.                !!*//


// This program uses the light sensor to track the left side of a line

task main ()

{

if (untilTouch(dgtl6);)

{
    
startmotor(Motor393);
        
 

forward(23);
     until


// do something

}
else if (sensorValue[0]){

forward(0);
}
 else () {
  forward(0);       
 } 
stop(); 
}
