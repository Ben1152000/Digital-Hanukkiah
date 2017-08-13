void setup() {
  // put your setup code here, to run once:
  for (int i = 2; i < 12; i++) {
    pinMode(i, OUTPUT);
  }
  on();
  delay(50);
  off();
  delay(50);
  Serial.begin(9000);

  
}

void loop() {
  for (int i = 0; i < 10; i++) {
    simpleblink(1000);
  }

  for (int i = 0; i < 10; i++) {
    wavecont(800, 1, 1);
  }

  for (int i = 0; i < 10; i++) {
    wavecont(800, 1, -1);
  }
  
  for (int i = 0; i < 10; i++) {
    wavebounce(1600, 1, 1);
  }

  for (int i = 1; i < 9; i++) {
    wavebounce(1600, i, 1); wavebounce(1600, i, 1);
  }
  
  on(); delay(300); off(); delay(500);
  
  for (int i = 3000; i > 0; i = i * .9){
    wavebounce(i, 2, 1);
  }
  
  delay(10000);
}

void off() { for (int i = 2; i < 12; i++) {digitalWrite(i, LOW);} }

void on() { for (int i = 2; i < 12; i++) {digitalWrite(i, HIGH);} }

void light(int led) { digitalWrite(led + 2, HIGH); }

void dark(int led) { digitalWrite(led + 2, LOW); }

void simpleblink(int p) { on(); delay(p / 2); off(); delay(p / 2); }

void wavestop(int p, int n, int d) { // period p, number of lights n, direction d
  d = d/abs(d); for (int i = 0; i < n; i++) {light(4 - 4*d + i*d);}
  for (int i = n - 1; i < 8; i++) {
    light(4 - 4*d + i*d); dark((4 - 4*d + i*d - n*d + 9) % 9); delay(p/(9 - n));
  }
}

void wavecont(int p, int n, int d) { // period p, number of lights n, direction d
  d = d/abs(d); for (int i = 0; i < 9; i++) {
    light(4 - 4*d + i*d); dark((4 - 4*d + i*d - n*d + 9) % 9); delay(p/9);
  }
}

void wavebounce(int p, int n, int d) { // period p, number of lights n, direction d
  d = d/abs(d); wavestop(p/2, n, d); off();
  wavestop(p/2, n, -d); off();
}

void sinewavestop(int p, int n, int d) { // period p, number of lights n, direction d
  d = d/abs(d); for (int i = 0; i < n; i++) {light(4 - 4*d + i*d);}
  for (int i = n - 1; i < 8; i++) {
    light(4 - 4*d + i*d); dark((4 - 4*d + i*d - n*d + 9) % 9); 
    double x = i - n + 1; double m = 9 - n;
    delay((asin((2*x + 2)/m - 1) - asin(2*x/m - 1))*p/3.14159);
  }
}

void sinewavebounce(int p, int n, int d) { // period p, number of lights n, direction d
  d = d/abs(d); sinewavestop(p/2, n, d); double m = 9 - n; off(); 
  sinewavestop(p/2, n, -d); off();
}

void binaryclock(int p, int c) {
  for (int i = 0; i < c; i++) {
    for (int j = 0; j < 9; j++) {
      if (c % int(pow(2, j)) == 0) {light(j);} else {dark(j);}
    }
    delay(double(p)/double(c));
  }
}
