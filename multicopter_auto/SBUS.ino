
void read_sbus(){
    if (sbus_rx.Read()) {
    digitalWrite(25,HIGH);
    /* Grab the received data */
    sbus_data = sbus_rx.ch();
    /* Display the received data */
    for (int8_t i = 0; i < bfs::SbusRx::NUM_CH(); i++) {
      Serial.print(sbus_data[i]);
      Serial.print("\t");
      Serial.print(sbus_data[i]-PWM_N);
      Serial.print("\t"); 
      
    }
    last_received_time = millis();
  }else{
    digitalWrite(LED,LOW);
  }
}

void send_sbus(){
  sbus_tx.ch(sbus_data);
  sbus_tx.Write();
}

void fail_safe(){
    if(millis()-last_received_time>300){
    //motor_l.writeMicroseconds(TH_MIN); 
    //motor_r.writeMicroseconds(TH_MIN);
    }
    Serial.print("no signal/n");
}

void killswitch(){
    if(sbus_data[KILL_CH-1]<1000){
      for(int i=0; i<4; i++){
        sbus_data[i]=PWM_N;
      }
    }
}
