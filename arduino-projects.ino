
const int ledPin = 13; // the number of the LED pin
const int analogPin = 9;

const int trigPin = 7; // green
const int echoPin = 8; // yellow

int ledState = LOW; // variable for reading the LED status

int brightness = 0; // how bright the LED is
int previousTime = 0; // the last time the output pin was toggled

String buffer = "";
bool bufferComplete = false;

float distance = 0.0;

void setup()
{
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  pinMode(analogPin, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(trigPin, LOW);
  digitalWrite(echoPin, LOW);

  Serial.begin(115200);
  buffer.reserve(200);
}

void loop()
{
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  int echoTime = pulseIn(echoPin, HIGH);
  
  distance = max(0, (float)echoTime * 34 / 2000.0);
  
  if (distance > 1)
    brightness = max(255 - (int)distance * 2, 0);
  else
    brightness = 0;

  Serial.println("Distance:   " + String(distance) + "cm");
  Serial.println("Brightness: " + String(brightness));

  analogWrite(analogPin, brightness);
  digitalWrite(ledPin, ledState);
}

