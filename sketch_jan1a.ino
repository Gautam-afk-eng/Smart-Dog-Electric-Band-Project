// Pin definitions
const int trigPin = 2;     // Trigger pin for ultrasonic sensor
const int echoPin = 3;     // Echo pin for ultrasonic sensor
const int greenPin = 6;    // Green LED pin
const int bluePin = 5;     // Blue LED pin
const int redPin = 4;      // Red LED pin
const int buzzerPin = 8;   // Passive Buzzer pin

const int blinkThreshold = 20;  // Distance (cm) below which the Red LED glows steadily
const int glowThresholdHigh = 35;   // Distance (cm) above which the Green LED glows
const int glowThresholdLow = 25;    // Distance (cm) below which Blue LED glows

void setup() {
  // Initialize pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);  // Buzzer pin as output

  // Start Serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Get the distance from the ultrasonic sensor
  long duration, distance;
  
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);  
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);  
  distance = (duration / 2) / 29.1;  // Distance in cm

  // Print the distance for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check the distance and control LEDs and buzzer
  if (distance > glowThresholdHigh) {
    // If the distance is greater than 20cm, Green LED glows
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
    digitalWrite(redPin, LOW);
    noTone(buzzerPin);  // Stop the buzzer if the distance is greater than 20cm
  } 
  else if (distance >= glowThresholdLow && distance <= glowThresholdHigh) {
    // If the distance is between 10-20 cm, Blue LED glows
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
    digitalWrite(redPin, LOW);
    noTone(buzzerPin);  // Stop the buzzer if the distance is in the mid-range
  } 
  else if (distance < blinkThreshold) {
    // If the distance is less than 10 cm, Red LED glows steadily and Buzzer cycles
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    digitalWrite(redPin, HIGH);  // Red LED ON
    
    // Buzzer cycle beep (beep on for 500ms, off for 500ms)
    tone(buzzerPin, 1600);  // Play tone at 1000 Hz
    delay(510);  // Wait for 500ms
    noTone(buzzerPin);  // Stop the tone
    delay(390);  // Wait for 500ms
  }

  // Small delay before next reading
  delay(150);
}
