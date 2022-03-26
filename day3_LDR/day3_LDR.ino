const int LDR=21;
const int LED=22;
bool val;
void setup() {
  pinMode(LDR,INPUT);
  pinMode(LED,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  val=digitalRead(LDR);
Serial.println(val);
  if(val==1)
  {
     digitalWrite(LED,HIGH);
     Serial.println("LED HIGH\n");
     delay(2000);
  }
 else
 {
 digitalWrite(LED,LOW);
 Serial.println("LED LOW\n");
  delay(2000);
 }
}
