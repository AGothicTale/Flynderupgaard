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

//void playSequence()
//{
//  Serial.println("Running Ghost sequence");
//  playState = 1;  //set playState to 1 as the sequence is now playing
//  g_bIKMode = IKM_BACKHOE;
//  //###########################################################//
//  // Helsingør
//  //###########################################################//
//  IKSequencingControl(988, 1500, 2300, 600, 0 , 1622, 4000, 3000, 1);
//  //IKSequencingControl(1052, 1542, 1910, 1109, 0 , 1587, 2000, 1000, 1);
//  //###########################################################//
//
//  //###########################################################//
//  //  Way point 1 to St. Croix
//  //###########################################################//
//  //IKSequencingControl(1037, 1075, 1195, 1381, 0 , 1627, 2000, 10, 1);
//
//  // IKSequencingControl(1192, 2190, 2250, 1522, 0 , 1590, 2000, 100, 1);
//  //###########################################################//
//
//  //###########################################################//
//  //  Way point 2 to St. Croix
//  //###########################################################//
//  IKSequencingControl(1247, 2014, 2065, 1580, 0 , 1577, 2000, 10, 1);
//  //###########################################################//
//
//  //###########################################################//
//  //  North of St. Croix
//  //###########################################################//
//  IKSequencingControl(1424, 1490, 1672, 1251, 0 , 1614, 1000, 10, 1);
//  //IKSequencingControl(1369, 2104, 2318, 1346, 0 , 1609, 1000, 1000, 1);
//  //###########################################################//
//
//  //###########################################################//
//  //  Circle waypoint 1
//  //###########################################################//
//  IKSequencingControl(1472, 1490, 1672, 1251, 0 , 1600, 1000, 10, 1);
//  //###########################################################//
//
//  //###########################################################//
//  //  Circle waypoint 2
//  //###########################################################//
//  IKSequencingControl(1484, 1228, 1412, 1228, 0 , 1572, 1000, 10, 1);
//  //###########################################################//
//
//  //###########################################################//
//  //  Circle waypoint 2
//  //###########################################################//
//  IKSequencingControl(1446, 988, 1218, 1179, 0 , 1604, 1000, 10, 1);
////  IKSequencingControl(1446, 988, 1218, 1179, 0 , 1604, 1000, 10, 1);
//  //###########################################################//
//
//
//  //###########################################################//
//  // St. Croix
//  //###########################################################//
//  IKSequencingControl(1422, 1072, 1231, 1249, 0 , 1614, 1000, 3000, 1);
//  //IKSequencingControl(1373, 1933, 2366, 1074, 0 , 1582, 2000, 1000, 1);
//  //###########################################################//
//
//
//  for (int i = 0; i < 3; i++) {
//    //###########################################################//
//    // Tap up St. Croix
//    //###########################################################//
//    IKSequencingControl(1422, 1072, 1231, 1274, 0 , 1616, 200, 100, 1);
//    //###########################################################//
//    //###########################################################//
//    // St. Croix
//    //###########################################################//
//    IKSequencingControl(1422, 1072, 1231, 1249, 0 , 1614, 200, 100, 1);
//    //###########################################################//
//  }
//
// IKSequencingControl(1422, 1072, 1231, 1249, 0 , 1614, 200, 5000, 1);
//
//
//
//  //###########################################################//
//  //  Way point 1 to DK
//  //###########################################################//
//  IKSequencingControl(1247, 2014, 2065, 1580, 0 , 1577, 2000, 10, 1);
//  //###########################################################//
//
////###########################################################//
//  // Way point 2 to DK
//  //###########################################################//
////  IKSequencingControl(988, 714, 1521, 800, 0 , 1622, 2000, 10, 1);
//
//  //###########################################################//
//
//
//  Serial.println("Pausing Sequencing Mode.");
//
//}

// JUST TAPPING ALONG... No other movement
void playSequence()
{
  for (int i = 0; i < 3; i++) {
    //###########################################################//
    // Tap up St. Croix
    //###########################################################//
    IKSequencingControl(1422, 1500, 2180, 750, 0 , 1616, 200, 100, 1);
    //###########################################################//
    //###########################################################//
    // St. Croix
    //###########################################################//
    IKSequencingControl(1422, 1500, 2180, 720, 0 , 1614, 200, 100, 1);
    //###########################################################//
  }
  int randomDelay = random(5000,15000);
  delay(randomDelay);
}

/*

  void point(){
  Serial.println("Pointing");
  playState = 1;  //set playState to 1 as the sequence is now playing
  g_bIKMode = IKM_BACKHOE;
   //###########################################################//
    IKSequencingControl(1500 , 1900 , 2200 , 1900 , 1500 , 1500 , 640 , 1000, playState);
    //###########################################################//
  delay(50);
  }
*/

void sleep () {
  Serial.println("Sleeping");
  playState = 1;  //set playState to 1 as the sequence is now playing
  g_bIKMode = IKM_BACKHOE;
  IKSequencingControl(1500, 1500, 2400, 1540, 0 , 1556, 5000, 500, 1);

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

