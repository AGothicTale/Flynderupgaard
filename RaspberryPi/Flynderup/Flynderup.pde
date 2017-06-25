import processing.serial.*;
import java.io.File;
import java.util.Arrays;

int state = 0;
int states = 7;
int persons = 10;
int serialTimeout = 30;

Runtime runtime = Runtime.getRuntime();
float memoryPeak = 0;
float memoryUsed = 0;
float memoryMax = runtime.maxMemory()*0.000001;

final int IDLE = 0;
final int SEARCHING = 1;
final int AP_FIND = 2;
final int AP_LEAVE = 3;
final int SEARCHING2 = 4;
final int FJR_FIND = 5;
final int FJR_LEAVE = 6;

HashMap<Integer, ArrayList<PImage>> imgs = new HashMap<Integer, ArrayList<PImage>>(); // Images for all the people

Integer[] ids =    { 101,           102,          0,   1,   2,   3,   4,   5,   6,   7,   8,   9  };
String[] folders = {"Anna Paulina","Frederik Jr","F1","M1","F2","M2","F3","M3","F4","F4","F5","M5"};
int loadingState = 0;
int loadingAnim = 0;
float imgScale = 0.5;
boolean loading = true;
//PImage ffhDefault = null;
String loadingFrame = "+";

final Integer FFH = 100;
final Integer AP = 101;
final Integer FJR = 102;

final int FFH_MID = 6;
final int AP_MID = 6;
final int FJR_MID = 9;

Integer personNo = 0;
int glitchImgNo = 0;

float centerX, centerY;

int baudRate = 38400;

HashMap<Integer, String> errors = new HashMap<Integer, String>();
final Integer SERIAL_ERR = 0;
long lastSerialTime = 0;

void setup(){
  //FIXME: hardcode dev/tty?
  //if(!connectSerial(baudRate)){
  //  println("Serial not connected!!");
  //}
  //size(200,200);
  //size(405,720);
  //size(768,1280); 
  fullScreen();
  println(width+"x"+height);
  frameRate(15);
  noCursor();
  background(0);
  imageMode(CENTER);
  
  personNo = 0;
  
  centerX = width/2;
  centerY = height/2;
  //ffhDefault = loadImage(sketchPath()+"/data/Frederik/Frederik-Ferinand-Hansen-glitched-5-16-2017-8-43-51-PM copy.png");
  //resizeImg(ffhDefault);
  for(int i = 0; i < 3+persons-2; i++) loadingFrame = loadingFrame+"-";
  loadingFrame = loadingFrame+"+";
}

void draw(){
  background(0);
  
  if(loading) {
    loading = loadImages();
    if(!loading) {
      //ffhDefault = null;
      System.gc();
    }
    else {
      //float imgHeight = width*ffhDefault.height/ffhDefault.width;
      //image(ffhDefault, centerX, centerY);
    }
  }
  else {
    switch (state) {
      case IDLE: break;
      case AP_FIND: findImage(AP, AP_MID); break;
      case AP_LEAVE: leaveImage(AP); break;
      case FJR_FIND: findImage(FJR, FJR_MID); break;
      case FJR_LEAVE: leaveImage(FJR); break;
      case SEARCHING:
      case SEARCHING2: 
        displayGlitch(personNo);
        if(glitchImgNo == 0){
          personNo = (personNo+1) % persons;
          System.gc();
        }
        break;
    }
    displayState();
    displayErrors();
    fixSerial();
  }
  showMemory(memoryUsed());
}

void nextState(){
  state = (state+1) % states;
  if(state != AP_LEAVE && state != FJR_LEAVE){
    glitchImgNo = 0;
  }
  System.gc();
}

void mouseClicked(){
  nextState();
}

float memoryUsed(){
  float total = runtime.totalMemory()*0.000001;
  float free = runtime.freeMemory()*0.000001;
  float used = total-free;
  if(used > 0.8*memoryMax) System.gc();
  memoryPeak = used > memoryPeak ? used : memoryPeak;
  return used;
}