void fixSerial(){
  long serialDT = (millis() - lastSerialTime)/1000;
  if(errors.containsKey(SERIAL_ERR) || serialDT > serialTimeout || serialDT < 0){
    connectSerial(baudRate);
  }
}

boolean connectSerial(int baudRate){
  lastSerialTime = millis();
  try {
    String[] tty = Serial.list();
    //println(Arrays.toString(tty));
    for(String s : tty){
      if (s.startsWith("/dev/ttyACM")){
        new Serial(this, s, baudRate).bufferUntil('.');
        println("Serial connected.");
        errors.remove(SERIAL_ERR);
        return true;
      }
    }
    errors.put(SERIAL_ERR, "Serial not connected!");
  }
  catch (Exception e) {
    //println("didn't connect");
    //e.printStackTrace();
    //println();
  }
  return false;
}

void serialEvent(Serial p) {
  String input = p.readString();
  
  if(input.startsWith("scroll")) state = SEARCHING;
  else if(input.startsWith("anna")) state = AP_FIND;
  else if(input.startsWith("endanna")) state = AP_LEAVE;
  else if(input.startsWith("fjr")) state = FJR_FIND;
  else if(input.startsWith("endfjr")) state = FJR_LEAVE;
  println(input);
  lastSerialTime = millis();
  loop();
} 