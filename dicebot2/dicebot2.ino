/*
 Serial1 : Dynamixel_Poart
 Serial2 : Serial_Poart(4pin_Molex)
 Serial3 : Serial_Poart(pin26:Tx3, pin27:Rx3)
 
 TxD3(Cm9_Pin26) <--(Connect)--> RxD(PC)
 RxD3(Cm9_Pin27) <--(Connect)--> TxD(PC)
 */

#define DXL_BUS_SERIAL1 1 //Dynamixel on Serial1(USART1) <-OpenCM9.04 
#define DXL_BUS_SERIAL2 3 //Dynamixel on Serial2(USART2) <-LN101,BT210 
#define DXL_BUS_SERIAL3 3 //Dynamixel on Serial3(USART3) <-OpenCM 485EXP

Dynamixel Dxl(DXL_BUS_SERIAL1);

char inChar;
byte index = 0;
double maxspeed = 400.0;
double inspeed;
int clawangle = 300;
int maxclaw = 825;
int minclaw = 300;
int fireclaw = 800;
int fireangle = 900;
int downangle = 505;
int value = 0;
int dir = 0;

void setup() {
  // Set up the pin 10 as an output:
  pinMode(BOARD_LED_PIN, OUTPUT);
  Serial3.begin(9600);
  Dxl.begin(3);
  Dxl.wheelMode(3); //left wheel
  Dxl.wheelMode(4); //right wheel
  Dxl.jointMode(1); //left claw
  Dxl.jointMode(2); //right claw
  Dxl.writeWord(1, 32, 250);
  Dxl.writeWord(2, 32, 250);
  //Dxl.wheelMode(5); //trigger
  Dxl.jointMode(5);
  Dxl.wheelMode(6); //camera
  Dxl.goalPosition(5, downangle);
  Dxl.goalPosition(1, minclaw);
  Dxl.goalPosition(2, minclaw);

}


void loop() {
   while(Serial3.available()<0){}
   if(Serial3.available() > 0){
    char inData[20];
    while(Serial3.available()>0){
      if(index < 19){
        inChar = Serial3.read(); //read a character
        inData[index] = inChar;
        index++;
        inData[index] = '\0';
      }
    }
  
  index = 0;
  
  inspeed = ((double)inData[1]/255.0)*maxspeed;
  
  //SerialUSB.println(int(inspeed));
  
  //forward
  if(inData[0] == char(70)){
    SerialUSB.println(inData[0]);
//    Dxl.goalSpeed(3, int(inspeed)); 
//    Dxl.goalSpeed(4, int(inspeed) | 0x400);
  }
  //back
  if(inData[0] == char(66)){
//    Dxl.goalSpeed(4, int(inspeed));
//    Dxl.goalSpeed(3, int(inspeed) | 0x400);
    SerialUSB.println(inData[0]);
  }
  //left
  if(inData[0] == char(76)){
//    Dxl.goalSpeed(3, int(inspeed)/2 | 0x400);
 //   Dxl.goalSpeed(4, int(inspeed)/2 | 0x400);
   SerialUSB.println(inData[0]);
  }
  //right
  if(inData[0] == char(82)){
 //   Dxl.goalSpeed(4, int(inspeed)/2);
  //  Dxl.goalSpeed(3, int(inspeed)/2);
    SerialUSB.println(inData[0]);
  }
  
 //close claw
  if(inData[0] == char(67)){
/*    Dxl.goalSpeed(4, 0);
    Dxl.goalSpeed(3, 0);
    Dxl.goalPosition(1,clawangle);
    Dxl.goalPosition(2,clawangle);
    delay(2000);
    Dxl.goalPosition(1, maxclaw);
    Dxl.goalPosition(2, maxclaw);
    delay(2000);
    Dxl.goalPosition(1, fireclaw);
    Dxl.goalPosition(2, fireclaw);
    delay(1000);
    Dxl.goalPosition(5, fireangle);
    delay(1000);
    Dxl.goalPosition(5, downangle);
    Dxl.goalPosition(1, minclaw);
    Dxl.goalPosition(2, minclaw);
  */
    SerialUSB.println(inData[0]);
  }

  //stop
  if(inData[0] == char(83)){
    Dxl.goalSpeed(4, 0);
    Dxl.goalSpeed(3, 0);
  }
  SerialUSB.println("end");
  delay(500);
}
}

//leftwheel 1
//righwheel 3
