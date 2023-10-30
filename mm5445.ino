/**********************************************************************/
/*This code is not clean and OFFCOURSE will be possible do it better! */
/*this is only a group of functions to be used as independent code,   */
/*and by this way will be possible to any person can do the changes   */
/*of code and see what happen.                                        */
/*The code don't depend of any external library or extenal functions  */
/*complicated.                                                        */
/*I'm let the values to sent as binnary, this allow swap bit by bit   */
/* to is possible test segment by segment without convert to HEX      */
/**********************************************************************/
/* This code show how is possible work with the driver SN75518 Sanyo  */
/*                                                                    */
/**********************************************************************/

#define VFD_in 8  // This is the pin number 8 on Arduino UNO
#define VFD_clk 9 // This is the pin number 9 on Arduino UNO
#define VFD_stb1 10 // This is the pin number 10 on Arduino UNO

//ATT: On the Uno and other ATMEGA based boards, unsigned ints (unsigned integers) are the same as ints in that they store a 2 byte value.
//Long variables are extended size variables for number storage, and store 32 bits (4 bytes), from -2,147,483,648 to 2,147,483,647.

//........................SGGGGGGGGGGGGGabcdeg'f
//.....................(0b10000100001100000111111111111111);
//......................................abcdeg'f
uint32_t numbers[11] = {0b10000000000000111110010000000000, //0
                        0b10000000000000011000000000000000, //1
                        0b10000000000000110111000000000000, //2
                        0b10000000000000111101000000000000, //3
                        0b10000000000000011001010000000000, //4
                        0b10000000000000101101010000000000, //5
                        0b10000000000000101111010000000000, //6
                        0b10000000000000111000000000000000, //7
                        0b10000000000000111111010000000000, //8
                        0b10000000000000111001010000000000, //9
                        0b11111111111111111111111111111111};//All ON

//........................SGGGGGGGGGGGGGabcdeg'f
uint32_t letters[13] = {0b10000000000000100111010000000000, //E
                        0b10000000000000000110010000000000, //L
                        0b10000000000000110011010000000000, //P
                        0b10000000000000111110010000000000, //O
                        0b10000000000000100111010000000000, //E
                        0b10000000000000110011010000000000, //P
                        0b10000000000000000000000000000000, //
                        0b10000000000000111110010000000000, //O
                        0b10000000000000000110010000000000, //L
                        0b10000000000000000110010000000000, //L
                        0b10000000000000100111010000000000, //E
                        0b10000000000000011011010000000000}; //H
                                            
//........................SGGGGGGGGGGGGGabcdeg'f                           
uint32_t grids[12]   = {0b11000000000000000000000000000000, //Grid 0
                        0b10100000000000000000000000000000, //Grid 1
                        0b10010000000000000000000000000000, //Grid 2
                        0b10001000000000000000000000000000, //Grid 3
                        0b10000100000000000000000000000000, //Grid 4
                        0b10000010000000000000000000000000, //Grid 5
                        0b10000001000000000000000000000000, //Grid 6
                        0b10000000100000000000000000000000, //Grid 7
                        0b10000000010000000000000000000000, //Grid 8
                        0b10000000001000000000000000000000, //Grid 9
                        0b10000000000100000000000000000000, //Grid 10
                        0b10000000000010000000000000000000}; //Grid 11
                      
uint8_t numberOfBit =0x00;                          
void send_fourBits_without(unsigned char a){
  unsigned char data = 170; //value to transmit, binary 10101010
  unsigned char mask = 0x00; //our bitmask
  data = a;
  uint8_t value1=0x01;
  uint8_t value8=128;
  
//  Serial.print("data :");Serial.println(data, BIN);
  for(mask = 0b00001000; mask >= 1; mask >>= 1) { //iterate through bit mask
    numberOfBit++;
    digitalWrite(VFD_clk, LOW);
    delayMicroseconds(2);
//    Serial.print("Val 1:");Serial.println(value1, BIN);
//    Serial.print("Val 8:");Serial.println(value8, BIN);
//    Serial.print("mask :");Serial.println(mask, BIN);
            if (data & mask) { // if bitwise AND resolves to true
              digitalWrite(VFD_in, HIGH);
              //Serial.print(1);
            }
            else { //if bitwise and resolves to false
              digitalWrite(VFD_in, LOW);
              //Serial.print(0);
            }
    digitalWrite(VFD_clk, HIGH);// need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(2);
          if(numberOfBit == 36){
//            Serial.println();
//            Serial.println("You reach this point, bit nº 36");
          //numberOfBit++;
          //stopBit();
          }
   }
   
//  Serial.println();
//  Serial.println(numberOfBit, DEC);
}
void send_32_without(uint32_t a){
  uint32_t data = 170; //value to transmit, binary 10101010
  uint32_t mask = 1; //our bitmask
  data = a;
  data = (data | 0x80000000);
  
  for (mask = 0b10000000000000000000000000000000; mask > 0; mask >>= 1) { //iterate through bit mask
    numberOfBit++;
    digitalWrite(VFD_clk, LOW);
    delayMicroseconds(2);
    if (data & mask) { // if bitwise AND resolves to true
      digitalWrite(VFD_in, HIGH);
      //Serial.print(1);
    }
    else { //if bitwise and resolves to false
      digitalWrite(VFD_in, LOW);
      //Serial.print(0);
    }
    digitalWrite(VFD_clk, HIGH);// need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(2);         
  }
  if(numberOfBit == 32){
   //only to check if you reach this point
   //Serial.println("Reach 32 bits!");
  }
      
//  Serial.println();
//  Serial.println(numberOfBit, DEC);
}
void startBit(){
  //This is the start bit of message of 36 bits.
  //Also the Active data must go down when clock is down!
  digitalWrite(VFD_clk, LOW);
  delayMicroseconds(5);
  digitalWrite(VFD_stb1, HIGH);
  delayMicroseconds(50); 
  digitalWrite(VFD_clk, HIGH);
  delayMicroseconds(5);
  digitalWrite(VFD_clk, LOW);
  delayMicroseconds(5);
  digitalWrite(VFD_stb1, LOW);
  delayMicroseconds(50);  
}
void setup() {
  pinMode(VFD_clk, OUTPUT);
  pinMode(VFD_in, OUTPUT);
  pinMode(VFD_stb1, OUTPUT);

  Serial.begin(115200); // only to debug

  //attachInterrupt(digitalPinToInterrupt(2),buttonPressed1,RISING);  // Configuration of Interrupt to the pin 2
  //attachInterrupt(digitalPinToInterrupt(3),buttonPressed2,RISING);  // Configuration of Interrupt to the pin 3
  //sei();

}
void loop() {
uint32_t num =0x00000000;
uint32_t grid = 0x00000000;
uint32_t toSend = 0x00000000;
uint32_t letter = 0x00000000;
uint32_t tmp = 0x00000000;
uint32_t mov = 0x00000000;
uint32_t cycle = 0;
startBit();
for(uint8_t r = 0; r<8; r++){
    //................SGGGGGGGGGGGGGabcdeg'f
    send_32_without(0b10000000001000011000001111111111);
    send_fourBits_without(0b00001111);
    delay(500);
    //................SGGGGGGGGGGGGGabcdeg'f
    send_32_without(0b10001000000000110111001111111111);
    send_fourBits_without(0b00001111);
    delay(500);
    
    for(uint8_t arr = 0; arr < 11; arr++){
        for (uint32_t n = 0b1000000000000; n>0; n >>=1){
          tmp=((n << 19) & 0x7FF80000);
          send_32_without((numbers[arr] | tmp));
          send_fourBits_without(0b00001111);
          numberOfBit= 0;
          delay(150);
        }
    }
      for(unsigned int u= 0; u<1000; u++){
            startBit();
              for(uint8_t arr = 0; arr < 12; arr++){ 
                tmp = grids[arr];
                    send_32_without((letters[arr] | tmp));
                    send_fourBits_without(0b00001111);
                    numberOfBit= 0;
              }
      }
    
}
}
