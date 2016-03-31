// GPS Setup
#define rxGPS 3
#define txGPS 5
SoftwareSerial serialGPS = SoftwareSerial(rxGPS, txGPS);
String stringGPS = "";

// delaring all pins to be used here

const int start_alert_pin = 9;
const int cancel_alert_led = 11;
const int cancel_alert_pin = 10;

int start_alert_state = 0;
int cancel_alert_state = 0;

void loop()
{
  String s = checkGPS();
  if(s && s.substring(0, 6) == "$GPGGA")
  {
    Serial.println(s);
  }
}

// Check GPS and returns string if full line recorded, else false
String checkGPS()
{
  if (serialGPS.available())
  {
    char c = serialGPS.read();
    if (c != '\n' && c != '\r')
    {
      stringGPS  = c;
    }
    else
    {
      if (stringGPS != "")
      {
        String tmp = stringGPS;
        stringGPS = "";
        return tmp;
      }
    }
  }
  return false;
}


void setup() {

  //declaring output and input pins
  
  pinMode(start_alert_pin, INPUT);
  pinMode(cancel_alert_pin, INPUT);
  pinMode(cancel_alert_led, OUTPUT);

  //initialising all pins to low
  
  digitalWrite(start_alert_pin,LOW);
  digitalWrite(cancel_alert_pin,LOW);
  digitalWrite(cancel_alert_led,LOW);

  // initialize serial communication:
  pinMode(rxGPS, INPUT);
  pinMode(txGPS, OUTPUT);


  Serial.begin(9600);
  Serial.println("Started");

  // GPS Setup
  serialGPS.begin(4800);
  digitalWrite(txGPS,HIGH);

  // Cut first gibberish
  while(serialGPS.available())
    if (serialGPS.read() == '\r')
      break;
}


void loop() {
  
  start_alert_state = digitalRead(start_alert_pin);  
  
  //checking for collision detection
  
  while(start_alert_state==HIGH) {
    Serial.println("Alarm triggered");
    digitalWrite(cancel_alert_led,HIGH);
    //begin alert procedures



    //gathering GPS co-ordinates



    //preparing GSM module for message transmission





   //waiting for 2 seconds to see if the alarm has been cancelled
   delay(2000);


   cancel_alert_state = digitalRead(cancel_alert_pin);
   if(cancel_alert_state=HIGH) {
      Serial.println("Alarm cancelled");
      break;          
   }//end of if block

   else{
    Serial.println("Alarm not cancelled");
    digitalWrite(cancel_alert_led,LOW);

    //sending sms alert to hard-coded numbers

    Serial.println("Message sent");
    
    }//end of else block          
    
  }//end of while loop
  
}//end-of-setup-block
