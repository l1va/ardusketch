#define BUTTON_PIN 8
#define BUZZER_PIN  3
#define LDR_PIN     A0
#define BUFFER_SIZE 500

void setup()
{
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}
int buttonState =0;

void loop()
{
  buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == HIGH) {
    int save[BUFFER_SIZE];
    int p = 0;
    while (buttonState == HIGH) {
      int val, frequency;
      val = analogRead(LDR_PIN);
      frequency = map(val, 0, 1023, 1500, 8500);
      tone(BUZZER_PIN, frequency, 20);
      save[p] = frequency;
      p++;
      if (p==BUFFER_SIZE){
        p = 0; // safe restarting from the start
      }
      delay(30);
      buttonState = digitalRead(BUTTON_PIN);
    }
    delay(2000);
    for(int i=0;i<p;i++){
      tone(BUZZER_PIN, save[i], 20);
      delay(30);
    }
  }
}
