
#include "sbus.h"
#include<Servo.h>
#include <VL53L1X.h>
#include <Wire.h>

//ピンの割り当て
const int RELEASE_GEAR_PIN = 20; //投下装置
const int LED = 25;


//チャンネル割り当て
const int KILL_CH = 5; //キルスイッチを割り当てるチャンネル番号
const int RELEASE_CH = 7; //投下装置
const int MODE_CH = 8; //飛行モード選択

//それぞれの舵への入力
int AIL=0;
int ELE=0;
int THR=0;
int RUD=0;

//プロポからの信号の値
const int PWM_MAX = 1680;
const int PWM_MIN = 368;
const int PWM_N = (PWM_MAX+PWM_MIN)/2;

//受信機から信号が来なくなった時のため
int last_received_time = 0;


Servo RELEASE_servo;


/* SbusRx object on Serial1 */
bfs::SbusRx sbus_rx(&Serial1);
/* SbusTx object on Serial1 */
bfs::SbusTx sbus_tx(&Serial1);
/* Array for storing SBUS data */
std::array<int16_t, bfs::SbusRx::NUM_CH()> sbus_data;

VL53L1X rangefinder;

void setup() {
  
  pinMode(25, OUTPUT);
  
  Serial1.setRX(17);
  Serial1.setTX(16);
  Serial1.begin(100000,SERIAL_8E2); // S-BUS
  /* Serial to display the received data */
  Serial.begin(115200);
  
  while (!Serial1) {
    Serial.printf("no signal");
    }
  /* Begin the SBUS communication */
  sbus_rx.Begin();
  sbus_tx.Begin();

  RELEASE_servo.attach(RELEASE_GEAR_PIN,500,2400);

  init_rangefinder();

  digitalWrite(25,HIGH);
  delay(1000);
  digitalWrite(25,LOW);
  
}

void loop() {
  read_sbus();
  fail_safe();
  killswitch();
  send_sbus();
}
