int rowCounter = 0;
float distanceArray[10][10];
String inputString = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available()) {
    inputString = Serial.readString();
  }
  for (int c = 0; c < 10; c++) {
    distanceArray[rowCounter][c] = inputString.substring(inputString.indexOf(',') + 1, inputString.indexOf(",", +1)).toFloat(); // find string between 2 commas
    Serial.println(distanceArray[rowCounter][c]);
    inputString.remove(0, 5); //remove first comma and number
  }
  delay(2000);
}
