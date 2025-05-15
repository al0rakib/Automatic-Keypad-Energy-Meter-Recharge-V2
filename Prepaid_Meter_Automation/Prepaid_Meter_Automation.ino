#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <AccelStepper.h>
#include <Servo.h>

// Wi-Fi credentials
const char* ssid = "Your_WiFi_Name";
const char* password = "Your_WiFi_Password";

// Web server
ESP8266WebServer server(80);

// Keypad layout (3x4): 1-9, *, 0, #
const char KEYPAD[4][3] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

// Stepper X pins: GPIO 5, 4, 14, 12
AccelStepper stepperX(AccelStepper::FULL4WIRE, 5, 4, 14, 12);

// Stepper Y pins: GPIO 13, 15, 0, 2
AccelStepper stepperY(AccelStepper::FULL4WIRE, 13, 15, 0, 2);

// Servo pin: GPIO 16
Servo tapServo;
const int SERVO_PIN = 16;

// Button spacing (steps) — adjust to match physical layout
const int STEP_X_SPACING = 200;
const int STEP_Y_SPACING = 200;

// Last known (X, Y) position in steps
int lastX = 0;
int lastY = 0;

// Digit to (row, col) lookup
bool getDigitPosition(char digit, int &row, int &col) {
  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 3; c++) {
      if (KEYPAD[r][c] == digit) {
        row = r;
        col = c;
        return true;
      }
    }
  }
  return false;
}

// Move to specific digit and tap
void pressDigit(char digit) {
  int row, col;
  if (!getDigitPosition(digit, row, col)) {
    Serial.print("Invalid digit: ");
    Serial.println(digit);
    return;
  }

  int targetX = col * STEP_X_SPACING;
  int targetY = row * STEP_Y_SPACING;

  Serial.printf("Digit: %c at Grid(%d,%d) => Pos(%d,%d)\n", digit, row, col, targetX, targetY);

  // Move to digit
  stepperX.moveTo(targetX);
  stepperY.moveTo(targetY);
  while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0) {
    stepperX.run();
    stepperY.run();
  }

  // Tap with servo
  tapServo.write(90); // Press
  delay(300);
  tapServo.write(0);  // Lift
  delay(300);

  // Update last position
  lastX = targetX;
  lastY = targetY;
}

// Process 5-digit code
void handleSubmit() {
  if (!server.hasArg("code")) {
    server.send(400, "text/plain", "No code received");
    return;
  }

  String code = server.arg("code");
  Serial.print("Received code: ");
  Serial.println(code);

  if (code.length() != 5) {
    server.send(400, "text/plain", "Invalid code length");
    return;
  }

  for (int i = 0; i < 5; i++) {
    pressDigit(code.charAt(i));
    delay(500);
  }

  server.send(200, "text/plain", "Code received and executed: " + code);
}

void setup() {
  Serial.begin(115200);

  // Setup steppers
  stepperX.setMaxSpeed(800);
  stepperX.setAcceleration(400);
  stepperY.setMaxSpeed(800);
  stepperY.setAcceleration(400);

  // Setup servo
  tapServo.attach(SERVO_PIN);
  tapServo.write(0); // Up

  // Wi-Fi connection
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected. IP address:");
  Serial.println(WiFi.localIP());

  // Start server
  server.on("/submit", handleSubmit);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
