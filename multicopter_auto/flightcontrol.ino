int KP_HEIGHT = 1;
int KI_HEIGHT = 1;
int KD_HEIGHT = 1;

int error_pre = 0;
int error_i = 0; 
int last_calculated_time = 0

void overwrite_ch(){
  mode = sbus_data[mode-1]

  if mode < 1000{
    auto_takeoff(1000);
  }
}

void auto_takeoff(int target_height){
  
  dt = millis()-last_calculated_time;
  
  height = get_height();
  error = target_height-height;
  error_i += (error+pre_error)/2*dt;
  error_d = (error-error_pre)/dt;
  error_pre = error;
  
  last_calculated_time = millis();
  
  input = KP_HEIGHT*error + KI_HEIGHT*error_i + KD_HEIGHT*error_d;
  
  
}

void height_()
