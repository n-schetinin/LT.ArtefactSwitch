// inner leds
int in_r = 12;
int in_w = 11;
int in_b = 10;

// outer leds
int out_r = 9;
int out_w = 8;
int out_b = 7;

// switches
int sw_r = 6;
int sw_w = 5;
int sw_b = 4;

//speaker
int spk = 3;


int mode, mode_r, mode_w, mode_b;
int last_r, last_b, last_w, cur_w, cur_r, cur_b;


void setup() {  
  pinMode(in_r, OUTPUT);
  pinMode(in_w, OUTPUT);
  pinMode(in_b, OUTPUT);
  pinMode(out_r, OUTPUT);
  pinMode(out_w, OUTPUT);
  pinMode(out_b, OUTPUT);
  pinMode(sw_r, INPUT);
  pinMode(sw_w, INPUT);
  pinMode(sw_b, INPUT);
  pinMode(spk, OUTPUT);
  mode = 2; // wait mode;

  mode_r = LOW;
  mode_b = LOW;
  mode_w = HIGH;
  last_r = LOW;
  last_b = LOW;
  digitalWrite(in_w, mode_w);
  digitalWrite(out_w, mode_w);
}


void signal_tone(int freq, int pin) {  // beeping on capture
  digitalWrite(pin, HIGH);
  tone(spk, freq);
  delay(200);
  digitalWrite(pin, LOW);
  noTone(spk);
  delay(100);
  digitalWrite(pin, HIGH);
  tone(spk, freq);
  delay(200);
  digitalWrite(pin, LOW);
  noTone(spk);
  delay(100);
  digitalWrite(pin, HIGH);
  tone(spk, freq);
  delay(200);
  noTone(spk);
}


void kill() { // when reset button is pushed
  int i;
  digitalWrite(out_w, HIGH);
  tone(spk, 300); // low tone
  delay(1000);
  noTone(spk);
  
  for (i = 1; i <= 20; i++) { // 20 secs all led blinking. May change to any seconds you need.
    digitalWrite(in_w, HIGH);
    digitalWrite(in_r, HIGH);
    digitalWrite(in_b, HIGH);    
    delay(50);
    digitalWrite(in_w, LOW);
    digitalWrite(in_r, LOW);
    digitalWrite(in_b, LOW);    
    delay(950);
  }
  mode=2; // set wait mode
}


void loop() {

  cur_r = digitalRead(sw_r);
  cur_w = digitalRead(sw_w);
  cur_b = digitalRead(sw_b);

  if (cur_r == HIGH && cur_r != last_r && mode != 1) { // if red pressed and mode not red
    signal_tone(700, in_r);
    digitalWrite(in_r, HIGH);
    digitalWrite(out_r, HIGH);
    digitalWrite(in_w, LOW);
    digitalWrite(out_w, LOW);
    digitalWrite(in_b, LOW);
    digitalWrite(out_b, LOW);
    
    mode = 1; // mode set red captured
  }

  if (cur_b == HIGH && cur_b != last_b && mode != 3) { //same for blue
    signal_tone(700,in_b);
    digitalWrite(in_r, LOW);
    digitalWrite(out_r, LOW);
    digitalWrite(in_w, LOW);
    digitalWrite(out_w, LOW);
    digitalWrite(in_b, HIGH);
    digitalWrite(out_b, HIGH);
    
    mode = 3;
  }

  if (cur_w == HIGH && cur_w != last_w) { // if reset switch pressed
    digitalWrite(in_r, LOW);
    digitalWrite(out_r, LOW);
    digitalWrite(in_w, LOW);
    digitalWrite(out_w, LOW);
    digitalWrite(in_b, LOW);
    digitalWrite(out_b, LOW);
    kill();
    mode = 0;
    digitalWrite(in_r, LOW);
    digitalWrite(out_r, LOW);
    digitalWrite(in_w, HIGH);
    digitalWrite(out_w, HIGH);
    digitalWrite(in_b, LOW);
    digitalWrite(out_b, LOW);
    mode=2;
  }

  last_r = cur_r;
  last_w = cur_w;
  last_b = cur_b;



}
