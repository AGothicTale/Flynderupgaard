void displayGlitch(int id){
  displayImage(id, glitchImgNo);
  //if(random(20) < 5){
  //  glitchImgNo = (int)random(imgs.get(id).size()*0.99);
  //}
  if(random(20) < 5 || glitchImgNo == 0){
    glitchImgNo = (glitchImgNo + 1) % imgs.get(id).size();
  }
}

void displayImage(int id, int index){
  if(index < imgs.get(id).size()){
    image(imgs.get(id).get(index), centerX, centerY);
  }
}

void findImage(int id, int index){
  float r = random(20);
  if(r < 5){
    if(glitchImgNo < index){
      glitchImgNo++;
    }
    else if(glitchImgNo > index){
      glitchImgNo--;
    }
    else {
      if(r < 1){
        if(r < 0.5){
          glitchImgNo++;
        }
        else{
          glitchImgNo--;
        }
      }
    }
  }
  displayImage(id, glitchImgNo);
}

void leaveImage(int id){
  displayGlitch(id);
  if(glitchImgNo == 0){
    nextState();
  }
}

// true means still loading
// false means done loading
boolean loadImages(){
  int person = loadingState / 100;
  if(person < persons+2){
    loadingText(person, "Loading");
    Integer id = ids[person];
    String imgPath = sketchPath()+"/data/"+folders[person]+"/";
    String[] filenames = new File(imgPath).list();
    Arrays.sort(filenames);
    
    int imgNo = loadingState % 100;
    if(imgNo == 0) print(folders[person]+":");
    print(" "+imgNo);
    
    while(imgNo < filenames.length && !correctExtension(filenames[imgNo]))
      imgNo++;
    
    if(imgNo < filenames.length) {
      if(!imgs.containsKey(id))
        imgs.put(id,new ArrayList<PImage>());
      
      PImage img = loadImage(imgPath+filenames[imgNo]);
      //resizeImg(img);
      imgs.get(id).add(img);
      imgNo++;
    }
    if(imgNo >= filenames.length) {
      loadingState = (person + 1) * 100;
      println();
    }
    else
      loadingState = (person * 100) + imgNo;
    return true;
  }
  else return false;
}

boolean correctExtension(String f){
  return f.endsWith(".png") || f.endsWith(".jpg") || f.endsWith(".jpeg");
}

void resizeImg(PImage img){
  if((width / img.width) > (height / img.height))
        img.resize(0,height);
      else
        img.resize(width,0);
}