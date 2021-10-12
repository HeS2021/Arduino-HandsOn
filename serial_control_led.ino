// C++ code
//
#define ON 		0
#define OFF 	1
#define BLINK 	2

String c;
bool led;
int stato = OFF;
long time = 1000;
int time_passed = 0;
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available()){
    c = Serial.readString();
    Serial.println("Command: " + c);
    if (c.indexOf ("ON")>=0){
		stato = ON;
    }
    else if(c.indexOf ("OFF")>=0){
		stato = OFF;
    }
    else if (c.indexOf ("BLINK")>=0){
      stato = BLINK;
	  int ind = c.indexOf(':')+1;
      if (ind>0 && ind<c.length()){
      	String timeStr = c.substring(ind);
        time = timeStr.toInt();
        Serial.println("Delay: " + String(time));
      }
    }
  }
  
  switch(stato){
    case ON:
    	digitalWrite(LED_BUILTIN, HIGH);
	    break;
    case OFF:
        digitalWrite(LED_BUILTIN, LOW);
	    break;
    case BLINK:
	    if (millis()-time_passed > time){
			digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    		time_passed = millis();
        }
    	break;
  }
}