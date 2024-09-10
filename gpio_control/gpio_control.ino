// Buffer for storing incoming serial data
String inputString = "";  
bool stringComplete = false;  // Flag to check if the input is complete

void setup() {
  // Initialize Serial communication at 115200 baud rate
  Serial.begin(115200);
  
  // Print instructions
  Serial.println("Enter command in format: s<pin><h/l> to set pin, g<pin> to get pin status");
}

void loop() {
  // Check if a command has been entered
  if (stringComplete) {
    // Process the received command
    processCommand(inputString);

    // Clear the string
    inputString = "";
    stringComplete = false;
  }
}

// Function to process the received command
void processCommand(String command) {
  int pin_num;
  char action;

  // Parse the command (e.g., "s14h" to set pin 14 HIGH)
  if (sscanf(command.c_str(), "s%d%c", &pin_num, &action) == 2) {
    pinMode(pin_num, OUTPUT);  // Configure the pin as output

    if (action == 'h') {
      digitalWrite(pin_num, HIGH);  // Set the pin HIGH
      Serial.print("GPIO ");
      Serial.print(pin_num);
      Serial.println(" set to HIGH");
    } else if (action == 'l') {
      digitalWrite(pin_num, LOW);  // Set the pin LOW
      Serial.print("GPIO ");
      Serial.print(pin_num);
      Serial.println(" set to LOW");
    } else {
      Serial.println("Invalid action. Use 'h' for HIGH or 'l' for LOW.");
    }

  } else if (sscanf(command.c_str(), "g%d", &pin_num) == 1) {
    pinMode(pin_num, INPUT);  // Configure the pin as input
    int state = digitalRead(pin_num);  // Get the pin state

    Serial.print("GPIO ");
    Serial.print(pin_num);
    Serial.print(" is currently ");
    Serial.println(state == HIGH ? "HIGH" : "LOW");

  } else {
    Serial.println("Invalid command. Use 's<pin><h/l>' to set or 'g<pin>' to get pin state.");
  }
}

// Function to read serial input
void serialEvent() {
  while (Serial.available()) {
    // Get the new byte from the serial buffer
    char inChar = (char)Serial.read();
    
    // Add it to the inputString
    inputString += inChar;

    // If the incoming character is a newline, set stringComplete to true
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
