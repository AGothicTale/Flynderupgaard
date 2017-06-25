void showMemory(float used){
  textSize(18);
  if(used > memoryMax*0.8) fill(255, 80, 80);
  else                     fill(180,180,180);
  text(String.format("%s %3.2f / %3.2f MB","Used Memory  = ", used, memoryMax), 10, height-60);
  if(memoryPeak > memoryMax*0.8) fill(255, 80, 80);
  else                     fill(180,180,180);
  text(String.format("%s %3.2f MB","Peak Memory   = ", memoryPeak), 10, height-40);
}

void displayState(){
  fill(255);
  textSize(20);
  float posY = 20;
  text("state: "+ state + " \tglitchImgNo: "+glitchImgNo, 20, posY);
}

void displayErrors(){
  fill(150,10,10);
  textSize(20);
  float posY = height-20;
  for(String err : errors.values()){
    text(err, 10, posY);
    posY -= 30;
  }
}

void loadingText(int id, String txt){
  fill(180,180,180);
  textSize(18);
  for(int i = 0; i < loadingAnim; i++){
    txt = txt+".";
  }
  String person = "";
  for(int i = 0; i < id; i++) person = person+"#";
  text(txt, 10, 20);
  text(loadingFrame, 10, 40);
  text(person, 10, 55);
  text(loadingFrame, 10, 70);
  loadingAnim = (loadingAnim+1)%4;
}