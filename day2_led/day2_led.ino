const int LED=22;
void setup() {
pinMode(LED,OUTPUT);
Serial.begin(115200);

}

void loop() {
digitalWrite(LED,HIGH);
Serial.println("LED HIGH\n");
delay(20);
digitalWrite(LED,LOW);
Serial.println("LED LOW\n");
delay(20);
}
