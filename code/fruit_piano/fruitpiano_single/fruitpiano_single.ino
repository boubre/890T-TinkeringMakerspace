
// Board: Arduino Leonardo
// Author: Zhenyu Lei

int notes[] = {262, 294, 330, 349, 392, 440, 494}; // The frequencies of tones of C4, D4, E4, F4, A4, B4 respectively
int analogRead_list[] = {A0}; // The input pins which accept analog inputs. The length should not be greater than that of notes[].
int output_port = 8; // The output pin which connects to a piezo (loudspeaker) to play the tones
int max_analogRead = 1023; // The ADC is 10-bit, which means the reading ranges from 0 to 1023

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i< sizeof(analogRead_list); i++){ // Iterate in all the input pins
    pinMode(analogRead_list[i], INPUT); // Set the pin to INPUT mode without pull-up
    }
  Serial.begin(9600); // Serial Baud rate
}

void loop() {
  // put your main code here, to run repeatedly:
  int KeyValue = 0; // The buffer of the reading value of one of the pins
  for(int i=0;  i< (sizeof(analogRead_list)/sizeof(int)); i++){
    KeyValue = analogRead(analogRead_list[i]); // Read the voltage of the pin, and pass it through ADC to generalize digital numbers.
//    Serial.println(KeyValue);
    if(KeyValue < (max_analogRead/2)){ // Set the threshold to half of the max value. If the input is lower than it, it means a "touch" happens.
      Serial.println(i); // Send the number (i) of the pin which is touched back to the laptop. You could monitor it in Tools - Serial monitor in Arduino IDE.
      tone(output_port, notes[i], 200); //Generate a PWM wave to the output port. The piezo will then turn it to tones we could hear by itself. The tone will last for 200ms until noTone() function.
      break; // We only permit one touch each time. We will ignore other pins once a touch has been detected. The reason is the MCU only has one timer for PWM, thus can only generate
             // one tone at a time.
      }
    }
    noTone(output_port); // Stop generating tones in this loop.
}
