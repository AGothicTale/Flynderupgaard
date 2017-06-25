/*
    WIRING
      Servos
        Digital I/O 3 - Base Rotation - Robot Geek Servo
        Digital I/O 5 - Shoulder Joint - Robot Geek Servo
        Digital I/O 6 - Elbow Joint - Robot Geek Servo
        Digital I/O 9 - Wrist Joint - Robot Geek Servo
      Ping sensor
        Pin 8

 ***********************************************************************************/

#include <ServoEx.h>
#include <Wire.h>


//kinematics file - local
#include "Kinematics.h"

//armSequence
#include "armSequence.h"

const int pingPin = 8;



ServoEx    ArmServo[5]; //Start the servo object with 5 attachable servos

const int shortTrig = 90;
const int longTrig = 300;
long duration, inches, cm;

int lowRead() {
  int low = 9999;
  for (int i = 0; i < 3; i++) {
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);

    // The same pin is used to read the signal from the PING))): a HIGH
    // pulse whose duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(pingPin, INPUT);
    duration = pulseIn(pingPin, HIGH);
    int temp = microsecondsToCentimeters(duration);
    //Serial.println(temp);
    // convert the time into a distance
    if (temp < low) low = temp;

    delayMicroseconds(500);
  }

  return low;
}
//===================================================================================================
// Setup
//===================================================================================================
void setup() {
  // Attach servo and set limits
  ArmServo[BAS_SERVO].attach(3, BASE_MIN, BASE_MAX);
  ArmServo[SHL_SERVO].attach(5, SHOULDER_MIN, SHOULDER_MAX);
  ArmServo[ELB_SERVO].attach(6, ELBOW_MIN, ELBOW_MAX);
  ArmServo[WRI_SERVO].attach(9, WRIST_MIN, WRIST_MAX);
  ArmServo[GRI_SERVO].attach(10, GRIPPER_MIN, GRIPPER_MAX);


  // send arm to default X,Y,Z coord
  doArmIK(true, g_sIKX, g_sIKY, g_sIKZ, g_sIKGA);
  MoveArmTo(sBase, sShoulder, sElbow, sWrist, sWristRot, sGrip, sDeltaTime, true);

  SetServo(sDeltaTime);

  // start serial
  Serial.begin(38400);
  //Serial.println("Starting Playback Demo");
  delay(500);

  //  cm = longTrig+100;
}


void loop()
{

 
  
    // convert the time into a distance
    cm = lowRead();
    //Serial.println(cm);
    while (cm >= shortTrig && cm < longTrig) {
      point();
      //Serial.print("Point.");
      // convert the time into a distance
      cm = lowRead();
    }
    if (cm < shortTrig) {
      //Serial.print("ghostON.");
      ghostON();


    }
    else {
      Serial.write("sleep.");
      sleep();
    }
}






//===================================================================================================
// SetServo: Writes Servo Position Solutions
//===================================================================================================

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void SetServo(unsigned int DeltaTime)
{
  ServoGroupMove.start();
  ArmServo[BAS_SERVO].writeMicroseconds(Base + BAS_SERVO_ERROR);
  ArmServo[SHL_SERVO].writeMicroseconds(Shoulder + SHL_SERVO_ERROR);
  ArmServo[ELB_SERVO].writeMicroseconds(Elbow + ELB_SERVO_ERROR);
  ArmServo[WRI_SERVO].writeMicroseconds(Wrist + WRI_SERVO_ERROR);
  ArmServo[GRI_SERVO].writeMicroseconds(Gripper + GRI_SERVO_ERROR);
  ServoGroupMove.commit(DeltaTime);
}


/***********************************************************
   IKSequencingControl()
      Function used to set parameters for the Arm

   The following variables are named for Cartesian mode -
   however the data that will be held/sent will vary based on the current IK mode
 ****************************************************************************
   Variable name | Cartesian Mode | Cylindrcal Mode | Backhoe Mode          |
  _______________|________________|_________________|_______________________|
     x           |   x            |   base          |   base joint          |
     y           |   y            |   y             |   shoulder joint      |
     z           |   z            |   z             |   elbow joint         |
     GA          |  wristAngle    |  wristAngle     |   wrist angle joint   |
     gripper     |  gripper       |  gripper        |   gripper joint       |

   interpolate - the amount of time to complete a pose
   pause - time ti pause after a pose is completed
   enable - setting this to '1' makes the function work. Setting it to '0' bypasses the function. This can be usefull for breaking out of sequences


 **********************************************************/

void IKSequencingControl(float X, float Y, float Z, float GA, int grip, int interpolate, int pause, int enable ) {
  if (enable == 1)
  {

    if (g_bIKMode == IKM_IK3D_CARTESIAN || g_bIKMode == IKM_IK3D_CARTESIAN_90)
    {

      doArmIK(true, X, Y, Z, GA);

    }
    else if (g_bIKMode == IKM_CYLINDRICAL || g_bIKMode == IKM_CYLINDRICAL_90)
    {
      sBase = X;
      doArmIK(false, X, Y, Z, GA);

    }
    else if (g_bIKMode == IKM_BACKHOE)
    {
      sBase = X;
      sShoulder = Y;
      sElbow = Z;
      sWrist = GA;

    }



    sGrip = grip;
    MoveArmTo(sBase, sShoulder, sElbow, sWrist, sWristRot, sGrip, sDeltaTime, true);
    SetServo(interpolate);
    delay(interpolate + pause);
  }
}

//overloaded function to accout for extra empty wrist rotate packet
void IKSequencingControl(float X, float Y, float Z, float GA, float WR, int grip, int interpolate, int pause, int enable ) {
  IKSequencingControl( X, Y, Z, GA,  grip, interpolate,  pause,  enable );
}



