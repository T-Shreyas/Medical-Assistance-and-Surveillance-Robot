#include <SoftwareSerial.h>
SoftwareSerial BT_Serial(2, 3); // RX, TX

#include <IRremote.h>
const int RECV_PIN = A5;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define enA 10//Enable1 L298 Pin enA 
#define in1 9 //Motor1  L298 Pin in1 
#define in2 8 //Motor1  L298 Pin in1 
#define in3 7 //Motor2  L298 Pin in1 
#define in4 6 //Motor2  L298 Pin in1 
#define enB 5 //Enable2 L298 Pin enB 


int bt_ir_data; // variable to receive data from the serial port and IRremote
int Speed = 130;  
int mode=0;
int IR_data;

void setup(){ // put your setup code here, to run once


pinMode(enA, OUTPUT); // declare as output for L298 Pin enA 
pinMode(in1, OUTPUT); // declare as output for L298 Pin in1 
pinMode(in2, OUTPUT); // declare as output for L298 Pin in2 
pinMode(in3, OUTPUT); // declare as output for L298 Pin in3   
pinMode(in4, OUTPUT); // declare as output for L298 Pin in4 
pinMode(enB, OUTPUT); // declare as output for L298 Pin enB 

irrecv.enableIRIn(); // Start the receiver
//irrecv.blink13(True);

Serial.begin(9600); // start serial communication at 9600bps
BT_Serial.begin(9600); 

void loop(){  

if(BT_Serial.available() > 0){  //if some date is sent, reads it and saves in state     
bt_ir_data = BT_Serial.read(); 
Serial.println(bt_ir_data);     
if(bt_ir_data > 20){Speed = bt_ir_data;}      
}

if (irrecv.decode(&results)) {
Serial.println(results.value,HEX);
bt_ir_data = IRremote_data();
Serial.println(bt_ir_data); 
irrecv.resume(); // Receive the next value
delay(100);
}

if(bt_ir_data == 8){mode=0; Stop();}    //IR Remote Control Command   

analogWrite(enA, Speed); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
analogWrite(enB, Speed); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed 

if(mode==0){     
//===============================================================================
//                          Key Control Command
//=============================================================================== 
     if(bt_ir_data == 1){turnLeft(); }  // if the bt_data is '1' the DC motor will go forward----turnLeft();
else if(bt_ir_data == 2){turnRight();}  // if the bt_data is '8' the motor will Reverse----------turnRight();
else if(bt_ir_data == 3){forword();}  // if the bt_data is '3' the motor will turn left--------forword();
else if(bt_ir_data == 4){backword();} // if the bt_data is '4' the motor will turn right-------backword();
else if(bt_ir_data == 5){Stop(); }     // if the bt_data '5' the motor will Stop

//===============================================================================
//                          Voice Control Command
//===============================================================================    
else if(bt_ir_data == 6){forword();  delay(800);  bt_ir_data = 5;}
else if(bt_ir_data == 7){backword(); delay(800);  bt_ir_data = 5;}
}

delay(10);
}

long IRremote_data(){
     if(results.value==33480735){IR_data=0;}
else if(results.value==33444015){IR_data=1;}  
else if(results.value==16732335){forword();} //turnLeft()
else if(results.value==33486855){IR_data=3;} 
else if(results.value==16742535){backword();} //turnRight()
else if(results.value==16752735){Stop();} 
else if(results.value==16740495){turnLeft();} //forword()
else if(results.value==33423615){IR_data=7;} 
else if(results.value==16734375){turnRight();} //backword()
else if(results.value==33462375){IR_data=9;} 
return IR_data;
}

void forword(){  //forword
digitalWrite(in1, HIGH); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
digitalWrite(in3, LOW);  //Left Motor backword Pin 
digitalWrite(in4, HIGH); //Left Motor forword Pin 
}

void backword(){ //backword
digitalWrite(in1, LOW);  //Right Motor forword Pin 
digitalWrite(in2, HIGH); //Right Motor backword Pin 
digitalWrite(in3, HIGH); //Left Motor backword Pin 
digitalWrite(in4, LOW);  //Left Motor forword Pin 
}

void turnRight(){ //turnRight
digitalWrite(in1, LOW);  //Right Motor forword Pin 
digitalWrite(in2, HIGH); //Right Motor backword Pin  
digitalWrite(in3, LOW);  //Left Motor backword Pin 
digitalWrite(in4, HIGH); //Left Motor forword Pin 
}

void turnLeft(){ //turnLeft
digitalWrite(in1, HIGH); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
digitalWrite(in3, HIGH); //Left Motor backword Pin 
digitalWrite(in4, LOW);  //Left Motor forword Pin 
}

void Stop(){ //stop
digitalWrite(in1, LOW); //Right Motor forword Pin 
digitalWrite(in2, LOW); //Right Motor backword Pin 
digitalWrite(in3, LOW); //Left Motor backword Pin 
digitalWrite(in4, LOW); //Left Motor forword Pin 
}
}
