





/////////////////////////////
//VARS
//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 30;        

//the time when the sensor outputs a low impulse
long unsigned int highIn;         

//the amount of milliseconds the sensor has to be high 
//before we assume all motion has stopped
long unsigned int pause = 1000;  

boolean lockHigh = true;
boolean takeHighTime;  

int pirPin = 2;    //the digital pin connected to the PIR sensor's output
int ledPin = 13;

// the Button
const int buttonPin1 = 7;



/////////////////////////////
//SETUP
void setup(){
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);
  


  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
  }

////////////////////////////
//LOOP
void loop(){
  
  
  
     if(digitalRead(pirPin) == LOW){
       //digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
       if(lockHigh){  
         //makes sure we wait for a transition to HIGH before any further output is made:
         lockHigh = false;            
         Serial.println("---");
         Serial.print("motion detected at ");
         Serial.print(millis()/1000);
         Serial.println(" sec"); 
         delay(50);
         }         
         takeHighTime = true;
       }

     if(digitalRead(pirPin) == HIGH){       
       //digitalWrite(ledPin, LOW);  //the led visualizes the sensors output pin state

       if(takeHighTime){
        highIn = millis();          //save the time of the transition from high to LOW
        takeHighTime = false;       //make sure this is only done at the start of a HIGH phase
        }
       //if the sensor is high for more than the given pause, 
       //we assume that no more motion is going to happen
       if(!lockHigh && millis() - highIn > pause){  
           //makes sure this block of code is only executed again after 
           //a new motion sequence has been detected
           lockHigh = true;                        
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(50);
           }
       }
  }
