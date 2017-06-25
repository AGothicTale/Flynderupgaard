//Arm 5
//Sequence 8
//Mode 3
//Orientation 1
//DIO 0
#include "Kinematics.h"
#include "GlobalArm.h"
extern void IKSequencingControl(float X, float Y, float Z, float GA, float WR, int grip, int interpolate, int pause, int enable);
// We need to declare the data exchange
// variable to be volatile - the value is
// read from memory.
volatile int playState = 0; // 0 = stopped 1 = playing

void playSequence()
{
  Serial.println("Running Ghost sequence");
  playState = 1;  //set playState to 1 as the sequence is now playing
  g_bIKMode = IKM_BACKHOE;




  //Searching hand sequence
  //Hand vertical extended palm right
  IKSequencingControl(1500, 637, 1472, 1521, 0 , 1600, 2000, 2000, 1);

  //Hand horisontal extended pointing right
  IKSequencingControl(1500, 1480, 1472, 1521, 0 , 1564, 2000, 1000, 1);

  //Horisontal towards painting
  IKSequencingControl(2189, 1480, 1472, 1521, 0 , 1575, 2000, 1000, 1);

  //Pointing picture 1
  IKSequencingControl(2225, 1496, 1472, 1958, 0 , 1593, 1000, 2000, 1);

  //Pointing picture 2
  IKSequencingControl(2084, 1496, 1472, 1958, 0 , 1591, 1000, 4000, 1);

  //Searching center
  IKSequencingControl(1500, 1800, 1613, 1562, 0 , 1608, 2000, 3000, 1);

  //Searching left
  IKSequencingControl(1986, 1800, 1613, 1562, 0 , 1558, 2000, 1000, 1);

  //Searching right
  IKSequencingControl(1200, 1800, 1613, 1562, 0 , 1572, 2000, 3000, 1);



  for (int i = 0; i < 3; i++) {

    // Hand out
    IKSequencingControl(1720, 2295, 1572, 2130, 0 , 1562, 2000, 500, 1);

    //  Hand in
    IKSequencingControl(1720, 1975, 2115, 1236, 0 , 1608, 2000, 500, 1); 
  }

  //Hand waits in
  IKSequencingControl(1720, 1975, 2115, 1236, 0 , 1608, 2000, 5000, 1); ;

  // Go slowly to position for hand up
  IKSequencingControl(2200, 1700, 1661, 1607, 0 , 1572, 2000, 100, 1);
  for (int i = 0; i < 2; i++) {
    // Hand up
    IKSequencingControl(2200, 1900, 1661, 1607, 0 , 1572, 1200, 100, 1);

    //Hand down
    IKSequencingControl(2200, 2000, 1646, 1580, 0 , 1595, 800, 500, 1);

  }

  //Hand down
  IKSequencingControl(2200, 2000, 1646, 1580, 0 , 1595, 800, 5000, 1);

  // Hand up
  IKSequencingControl(2200, 1700, 1661, 1607, 0 , 1572, 1200, 100, 1);
  /*
    for (int i = 0; i < 5; i++) {
    //Hand vertical palm right
    IKSequencingControl(600, 605, 2351, 600, 0 , 1579, 2000, 200, 1);

    //Hand vertical palm left
    IKSequencingControl(2336, 660, 2351, 600, 0 , 1583, 2000, 200, 1);
    }
  */

  Serial.println("Pausing Sequencing Mode.");

}



void sleep () {
  Serial.println("Sleeping");
  playState = 1;  //set playState to 1 as the sequence is now playing
  g_bIKMode = IKM_BACKHOE;
  //Hand vertical extended palm right
  IKSequencingControl(1500, 637, 1472, 1521, 0 , 1600, 2000, 2000, 1);

  delay(50);
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

