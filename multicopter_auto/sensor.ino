 
void init_rangefinder(){  
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  rangefinder.setTimeout(500);
  if (!rangefinder.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }
  rangefinder.setDistanceMode(VL53L1X::Long);
  rangefinder.setMeasurementTimingBudget(50000);
  rangefinder.startContinuous(50);
}

int get_hight(){
  height = rangefinder.read()
  Serial.print(height);
  if (rangefinder.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.println();
  return height;
}
