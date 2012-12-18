//*!!Sensor,    S2,          lightsensor, sensorLightActive,      ,              !!*//
//*!!                                                                            !!*//
//*!!Start automatically generated configuration code.                           !!*//
const tSensors lightsensor          = (tSensors) S2;   //sensorLightActive  //*!!!!*//
//*!!CLICK to edit 'wizard' created sensor & motor configuration.                !!*//


// This program uses the light sensor to track the left side of a line


task main() {
        int threshold = 43;
        ClearTimer(T1);
        while(time1[T1] < 3000) {
          if(SensorValue(lightsensor) < threshold) {
                        motor[motorC]=0;
                        motor[motorB]=50;
                } else {
                        motor[motorC]=50;
                        motor[motorB]=0;
                }
        }
}