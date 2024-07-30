/******************************************************************************
Project: Capacitance Tester
Author: Stephen J. Heilman
Date: 7/29/2024
Purpose: To fibd the capacitance of a componet.

Requirements: 
1) Code build on Ubo R4. Adjustments may have to ve made for other devices.
2) The following circuit.

.        1 Mega Ohm  Cap under Test  
pin 3  o----/\/\/\/\---+-||----=======GND
pin A0 o---------------+

******************************************************************************/


int timeconst = 639;    // 62.5% of 1023 where 1023 is 5 volts on UNO R4
double resistor = 1000000.0;   // resistor in series with cap. in ohms
int capPin = 3;         // The cap power is supplied here
int voltPin = A0;            // read voltages
int val;                // analog read value
int lowHigh = HIGH;


float actualTime;
unsigned long timeTickStart;
unsigned long timeTickStop;
unsigned long timeDiff;
double seconds;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(capPin, OUTPUT);

  // This code is to vwerify ticks/second. Maybe differant with oyher boards
  Serial.println("Initializing...");
  timeTickStart = micros();
  delay(1000);
  timeTickStop = micros();
  timeDiff = timeTickStop - timeTickStart;
  seconds = timeDiff / 1000000.0;
  Serial.print("Ticks: ");
  Serial.print(timeDiff);
  Serial.print(" seconds: ");
  Serial.println(seconds);
  delay(1000);
}

void loop() {
  String inputData = "";
  int highThresh = 900;
  int lowThresh = 10;
//  double volts;
//  double voltConv=0.00488;
  double capacitance;
 
  // put your main code here, to run repeatedly:

  // just pressing enter ib sebd line wikk work
  Serial.println("Enter anything to start,");

  while(Serial.available() == 0){}  // wait for start
  inputData = Serial.readString();

// Serial.println("Start: ");

  digitalWrite(capPin, LOW);
  do {
    val = analogRead(voltPin);  // read the input pin
    delay(1);
//    Serial.println(val);
  }while(val >= lowThresh);

  Serial.print("Low value: ");
  Serial.println(val);

  digitalWrite(capPin, HIGH);
  timeTickStart = micros();
  do {
    val = analogRead(voltPin);  // read the input pin
//    volts = val * voltConv;
    Serial.println(val);
//    Serial.print("Volts: ");
//    Serial.println(volts);

  }while(val >= timeconst); // loop until 62.5%  of voltage

  timeTickStop = micros();
  Serial.print("High value: ");
  Serial.println(val);


  timeDiff = timeTickStop - timeTickStart;
  seconds = (double)timeDiff / 1000000.0;
  Serial.print("Ticks: ");
  Serial.print(timeDiff);
  Serial.print(" seconds: ");
  Serial.println(seconds, 6);

//  capacitance = seconds / resistor;
  capacitance = seconds;

//  capacitance = capacitance * 1000000.0;  // to convert to micro farads
  Serial.print("capacitance: ");
  Serial.print(capacitance, 12);
  Serial.print(" ");
  Serial.println(capacitance * 1000, 6);

  delay(50);
}
