#define CLK 2    //the digital pin connected to the PIR sensor's output
#define CLKIN 3
#define CLKOUT 4

void testInterrupt() {
  int clkState = 0;
  String sClkState = "";
  clkState = digitalRead(CLKIN);
  sClkState = String(clkState);
  Serial.println("Interrupt - CLK State:" + sClkState);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(CLK, OUTPUT);
  pinMode(CLKIN, INPUT);
  pinMode(CLKOUT, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(CLKIN), testInterrupt, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  int clkState = 0;
  String sClkState = "";
  Serial.println("Beginning tests");
  // Test 1
  pinMode(CLK, OUTPUT);
  digitalWrite(CLK, HIGH);
  clkState = digitalRead(CLKIN);
  sClkState = String(clkState);
  Serial.println("Test 1 CLK:" + sClkState);
  delay(2000);
  // Test 2
  pinMode(CLK, INPUT);
  digitalWrite(CLKOUT, HIGH);
  clkState = digitalRead(CLK);
  sClkState = String(clkState);
  Serial.println("Test 2 CLK:" + sClkState);
  delay(2000);
  // Test 3
  pinMode(CLK, OUTPUT);
  digitalWrite(CLKOUT, LOW);
  digitalWrite(CLK, LOW);
  clkState = digitalRead(CLKIN);
  sClkState = String(clkState);
  Serial.println("Test 3 CLK:" + sClkState);
  delay(2000);
  // Test 4
  pinMode(CLK, INPUT);
  digitalWrite(CLKOUT, LOW);
  clkState = digitalRead(CLK);
  sClkState = String(clkState);
  Serial.println("Test 4 CLK:" + sClkState);

  delay(5000);

}
