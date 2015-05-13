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
int clawangle = 575;
int maxclaw = 1023;
int minclaw = 250;


void setup() {
  // Set up the pin 10 as an output:
  pinMode(BOARD_LED_PIN, OUTPUT);
  Serial3.begin(9600);
  Dxl.begin(3);
  Dxl.wheelMode(1); //left wheel
  Dxl.wheelMode(2); //right wheel
  Dxl.jointMode(3); //left claw
  Dxl.jointMode(4); //right claw
  Dxl.goalPosition(3,clawangle);
  Dxl.goalPosition(4,clawangle);
}


void loop() {
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
    Dxl.goalSpeed(1, int(inspeed)); 
    Dxl.goalSpeed(3, int(inspeed) | 0x400);
  }
  //back
  if(inData[0] == char(66)){
    Dxl.goalSpeed(3, int(inspeed));
    Dxl.goalSpeed(1, int(inspeed) | 0x400);
  }
  //left
  if(inData[0] == char(76)){
    Dxl.goalSpeed(1, int(inspeed)/2 | 0x400);
    Dxl.goalSpeed(3, int(inspeed)/2 | 0x400);
  }
  //right
  if(inData[0] == char(82)){
    Dxl.goalSpeed(3, int(inspeed)/2);
    Dxl.goalSpeed(1, int(inspeed)/2);
  }
  
 //close claw
  if(inData[0] == char(67)){
    if (clawangle > minclaw){
        clawangle = clawangle - 15;
    }
    else{
        clawangle = minclaw;
    }
    Dxl.goalPosition(2,clawangle);
  }
  //open claw
  if(inData[0] == char(79)){
    if (clawangle < maxclaw){
        clawangle = clawangle + 15;
    }
    else{
        clawangle = maxclaw;
    }
    Dxl.goalPosition(2,clawangle);
  }
  //stop
  if(inData[0] == char(83)){
    Dxl.goalSpeed(1, 0);
    Dxl.goalSpeed(3, 0);
  }

  delay(10);
}
}

//leftwheel 1
//righwheel 3
