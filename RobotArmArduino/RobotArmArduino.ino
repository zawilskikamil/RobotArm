#include <ArduinoJson.h>

long dest_AX_1 = 0;
long dest_AX_2 = 0;
long dest_AX_3 = 0;
long dest_AX_4 = 0;
long dest_AX_5 = 0;
StaticJsonDocument<200> doc;

//Enable pin - DON'T MODIFY
#define EN        8
//Direction pin - DON'T MODIFY
#define X_DIR     5
#define Y_DIR     6
#define Z_DIR     7
//Step pin - DON'T MODIFY
#define X_STP     2
#define Y_STP     3
#define Z_STP     4


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  pinMode(X_DIR, OUTPUT); pinMode(X_STP, OUTPUT);
  pinMode(Y_DIR, OUTPUT); pinMode(Y_STP, OUTPUT);
  pinMode(Z_DIR, OUTPUT); pinMode(Z_STP, OUTPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);

}

void loop() {
  if (Serial.available() > 0) {
    String request = Serial.readString();
    request.trim();
    handleRequest(request);
    
  }
}

void handleRequest(String request) {
  if (request.equals("status")) {
    printStatus();
    return;
  }
  
  char json[200];
  request.toCharArray(json, 200);
  DeserializationError error = deserializeJson(doc, json);
  
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
  } else {
    // {Y: { dir: 1, steps: 1000, delay: 2 }}
    
    if (doc.containsKey("Y")) {
      if (doc["Y"]["dir"] > 0) {
        moveAxisYforward(doc["Y"]["steps"], doc["Y"]["delay"]);
      } else {
        moveAxisYbackward(doc["Y"]["steps"], doc["Y"]["delay"]);
      }
    }

    if (doc.containsKey("X")) {
      if (doc["X"]["dir"] > 0) {
        moveAxisXforward(doc["X"]["steps"], doc["X"]["delay"]);
      } else {
        moveAxisXbackward(doc["X"]["steps"], doc["X"]["delay"]);
      }
    }

    if (doc.containsKey("Z")) {
      if (doc["Z"]["dir"] > 0) {
        moveAxisZforward(doc["Z"]["steps"], doc["Z"]["delay"]);
      } else {
        moveAxisZbackward(doc["Z"]["steps"], doc["Z"]["delay"]);
      }
    }
    
    
    
    
  }
  
}

void printStatus() {
  Serial.println("connected");
  Serial.print("AX1: ");
  Serial.println(dest_AX_1);
    Serial.print("AX2: ");
  Serial.println(dest_AX_2);
    Serial.print("AX3: ");
  Serial.println(dest_AX_3);
    Serial.print("AX4: ");
  Serial.println(dest_AX_4);
    Serial.print("AX5: ");
  Serial.println(dest_AX_5);
}


void moveAxisYforward(long steps, long delay_value) {
  moveAxisForward(Y_DIR, Y_STP, steps, delay_value);
}


void moveAxisYbackward(long steps, long delay_value) {
   moveAxisBackward(Y_DIR, Y_STP, steps, delay_value);
}

void moveAxisXforward(long steps, long delay_value) {
  moveAxisForward(X_DIR, X_STP, steps, delay_value);
}


void moveAxisXbackward(long steps, long delay_value) {
   moveAxisBackward(X_DIR, X_STP, steps, delay_value);
}

void moveAxisZforward(long steps, long delay_value) {
  moveAxisForward(Z_DIR, Z_STP, steps, delay_value);
}


void moveAxisZbackward(long steps, long delay_value) {
   moveAxisBackward(Z_DIR, Z_STP, steps, delay_value);
}


void moveAxisForward(int y_dir, int y_stp, long steps, long delay_value) {
  for (int i = 0; i < steps; i++) { 
      digitalWrite(y_dir, HIGH); //Direction of the Y axis.
      digitalWrite(y_stp, HIGH);
      delay(delay_value);
      digitalWrite(y_stp, LOW);
      delay(delay_value);
  }
}


void moveAxisBackward(int y_dir, int y_stp, long steps, long delay_value) {
  for (int i = 0; i < steps; i++) { 
      digitalWrite(y_dir, LOW); //Direction of the Y axis.
      digitalWrite(y_stp, HIGH);
      delay(delay_value);
      digitalWrite(y_stp, LOW);
      delay(delay_value);
  }
}


 
