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
int maxspeed = 400;


void setup() {
  // Set up the pin 10 as an output:
  pinMode(BOARD_LED_PIN, OUTPUT);
  Serial3.begin(57600);
  Dxl.begin(3);
  Dxl.wheelMode(1);
  Dxl.wheelMode(2);
}


void loop() {
  while(SerialUSB.available() == 0){}  //block until serial available
  if(SerialUSB.available() > 0){
    char inData[20];
    while(SerialUSB.available()>0){
      if(index < 19){
        inChar = SerialUSB.read(); //read a character
        inData[index] = inChar;
        index++;
        inData[index] = '\0';
      }
    }
  
  index = 0;
  SerialUSB.print(inData[0]);
  
  //forward
  if(inData[0] == char(70)){
    Dxl.goalSpeed(2, maxspeed | 0x400); 
  }
  //back
  if(inData[0] == char(66)){
    Dxl.goalSpeed(2, maxspeed | 0x400);
  }
  //left
  if(inData[0] == char(76)){
    Dxl.goalSpeed(1, maxspeed | 0x400);
  }
  //right
  if(inData[0] == char(82)){
    Dxl.goalSpeed(1, maxspeed);
  }
  //up
  if(inData[0] == char(85)){
    Dxl.goalSpeed(3, maxspeed);
  }
  //down
  if(inData[0] == char(68)){
    Dxl.goalSpeed(3, maxspeed | 0x400);
  }
  //close claw
  if(inData[0] == char(67)){
    Dxl.goalSpeed(4, maxspeed);
  }
  //open claw
  if(inData[0] == char(79)){
    Dxl.goalSpeed(4,maxspeed | 0x400);
  }
  //stop
  if(inData[0] == char(83)){
    Dxl.goalSpeed(1, 0);
    Dxl.goalSpeed(2, 0);
    Dxl.goalSpeed(3, 0);
    Dxl.goalSpeed(4, 0);
  }
  delay(100);
}
}


