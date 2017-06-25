//Arm 5
//Sequence 14
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

void ghostON()
{

  playState = 1;  //set playState to 1 as the sequence is now playing
  g_bIKMode = IKM_BACKHOE;
  Serial.write("scroll.");

  //Scrolling
  for (int i = 0; i < 2; i++) {
    // Scroll start
    IKSequencingControl(1534, 2398, 1325, 2330, 0 , 1580, 2000, 200, 1);
    // Scroll end
    IKSequencingControl(1526, 1546, 1641, 792, 0 , 1593, 2000, 200, 1);
  }

  //AP line start
  Serial.write("anna.");
  IKSequencingControl(1840, 1623, 1706, 851, 0 , 1583, 2000, 1000, 1);

  //AP name start
  IKSequencingControl(1537, 1565, 1674, 794, 0 , 1579, 2000, 3000, 1);

  //AP name end
  IKSequencingControl(1419, 1568, 1682, 794, 0 , 1583, 2000, 1000, 1);

  //Tapping AP
  for (int i = 0; i < 10; i++) {
    //AP name tap up
    IKSequencingControl(1419, 1503, 1676, 794, 0 , 1580, 100, 10, 1);
    //FFH name tap down
    IKSequencingControl(1419, 1568, 1682, 794, 0 , 1583, 100, 10, 1);
  }
  delay(5000);
  Serial.write("endanna.");





  //Scrolling
  for (int i = 0; i < 2; i++) {
    // Scroll start
    Serial.write("scroll.");
    IKSequencingControl(1534, 2398, 1325, 2330, 0 , 1580, 2000, 200, 1);
    // Scroll end
    IKSequencingControl(1526, 1546, 1641, 792, 0 , 1593, 2000, 200, 1);
  }

  //FFH line start
  Serial.write("fjr.");
  IKSequencingControl(1782, 1771, 1914, 950, 0 , 1580, 2000, 1000, 1);

  //FFH name start
  IKSequencingControl(1589, 1719, 1921, 866, 0 , 1579, 1000, 3000, 1);

  //FFH name end
  IKSequencingControl(1467, 1689, 1790, 899, 0 , 1582, 1000, 2000, 1);

  //Tapping FFH
  for (int i = 0; i < 3; i++) {
    //FFH name tap up
    IKSequencingControl(1467, 1689, 1892, 899, 0 , 1577, 100, 10, 1);
    //FFH name tap down
    IKSequencingControl(1467, 1689, 1790, 899, 0 , 1582, 100, 10, 1);
  }
  delay(5000);
  Serial.write("endfjr.");

  IKSequencingControl(1500, 1565, 2167, 784, 0 , 1585, 2000, 10, 1);
  IKSequencingControl(1500, 1175, 600, 1186, 0 , 1587, 2000, 10, 1);



}

void sleep() {
  
  playState = 1;  //set playState to 1 as the sequence is now playing
  g_bIKMode = IKM_BACKHOE;

  
  //Sleep position
  Serial.write("idleSleep.");
  IKSequencingControl(1490, 827, 626, 893, 0 , 1585, 2000, 1000, 1);
  //IKSequencingControl(1500 , 1311 , 926 , 1500 , 1500 , 1500 , 2000 , 1000, playState); old catch sleep
  //###########################################################//
}

void point() {
  playState = 1;  //set playState to 1 as the sequence is now playing
  g_bIKMode = IKM_BACKHOE;

  Serial.write("point.");

  //###########################################################//
  // SEQUENCE 2
  //###########################################################//
  IKSequencingControl(900, 2095, 1400, 2209, 0 , 1580, 300, 2000, 1);
  //IKSequencingControl(1000 , 2083 , 2331 , 1895 , 1500 , 1500 , 500 , 2000, playState); old catch point
  //###########################################################//

}

