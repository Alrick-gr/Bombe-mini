#define Buzzer A1
#define BouttonRouge 13
#define BouttonJaune A2


int tempsMin, tempsSec, tempsI, OldTime, essais = 0;
unsigned long temps, dT = 0;
int combinaison[4] = {12, 12, 12, 12};
bool code_mode = true;




int pinA = 11;
int pinB = 7;
int pinC = 4;
int pinD = 5;
int pinE = 6;
int pinF = 10;
int pinG = 3;
int D1 = 12;
int D2 = 9;
int D3 = 8;
int D4 = 2;

void setup() {
  // initialize the digital pins as outputs.
  randomSeed(analogRead(A6));
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  pinMode(BouttonRouge, INPUT);
  annimation();
  if (digitalRead(BouttonRouge))
  {
    tone(Buzzer, 3000, 500);
    code_mode = false;
    combinaison[3] = 1;
    delay(1000);
    tone(Buzzer, 3000, 500);
    delay(1000);
  }

  Serial.begin(9600);
  recupTemps();
}
void loop()
{
  temps = millis() - dT;
  tempsMin = (tempsI - temps / 1000) / 60;
  tempsSec = (tempsI - temps / 1000) % 60;

  if (tempsSec != OldTime)
  {
    OldTime = tempsSec;
    tone(Buzzer, 2500, 100);
  }

  if ((tempsMin == 0 && tempsSec == 0))
  {
    explosion();
  }

  if (essais == 3)
  {
    explosion();
  }
  if (analogRead(BouttonJaune) < 400)
  {
    essais++;
    code(true);
  }

  affichage(tempsMin, tempsSec);
  /*
    Serial.print("minutes : ");
    Serial.print(tempsMin);

    Serial.print(" temps : ");
    Serial.print(temps);

    Serial.print(" secondes : ");
    Serial.println(tempsSec);*/
}
/*
  void gameCapture()
  {

  }
*/
void modeCapture()
{


  tone(Buzzer, 3000, 250);
  delay(300);
  tone(Buzzer, 3000, 250);
  delay(300);
  int n = 0;
  tempsMin, tempsSec, tempsI, OldTime = 0;
  while (!digitalRead(BouttonRouge))
  {

    tempsMin = map(analogRead(A0), 0, 1023, 0, 60);
    tempsI = tempsMin * 60;


    if (tempsMin != OldTime)
    {
      OldTime = tempsMin;
      tone(Buzzer, 4000, 10);
    }

    if (analogRead(BouttonJaune) == 0)
    {
      n++;
      if (n == 200)
      {
        tone(Buzzer, 3000, 250);
        delay(500);
        recupTemps();
      }
    }
    else
    {
      n = 0;
    }

    affichage(tempsMin, 0);

    //Serial.println(analogRead(BouttonJaune));
    //Serial.println(n);
  }
}

void recupTemps()
{
  bool flagJ = false;
  int n = 0;
  while (!digitalRead(BouttonRouge) || combinaison[3] == 12)
  {
    Serial.println(analogRead(BouttonJaune));
    tempsMin = map(analogRead(A0), 0, 1023, 0, 60);
    tempsI = tempsMin * 60;

    if (tempsMin != OldTime)
    {
      OldTime = tempsMin;
      tone(Buzzer, 4000, 10);
    }
    if (analogRead(BouttonJaune) > 100)
    {
      flagJ = true;
      //n++;
    }

    if (n == 200)
    {
      n = 0;
      modeCapture();
    }


    if (analogRead(BouttonJaune) <= 100 && flagJ)
    {
      if(code_mode)code(false);
      else frequence();
      while(digitalRead(BouttonRouge));
      flagJ = false;
      n = 0;
    }
    affichage(tempsMin, 0);

    if (digitalRead(BouttonRouge) && combinaison[3] == 12)
    {
      tone(Buzzer, 500, 100);
    }

    //Serial.println(digitalRead(BouttonRouge));
    //Serial.println(analogRead(BouttonJaune));
    //Serial.println(n);
  }
  dT = millis();

  Serial.print(digitalRead(BouttonRouge));
  Serial.println(combinaison[3]);

}

void code(bool partie)
{
  if (code_mode)
  {
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW);

    int entre[] = {12, 12, 12, 12};

    delay(500);
    for (int i = 0; i <= 3; i++)
    {
      Serial.println(combinaison[0] - 2);
      while (digitalRead(BouttonRouge) or analogRead(BouttonJaune) < 100);
      while (!digitalRead(BouttonRouge) && analogRead(BouttonJaune) > 100)
      {
        /*
          switch(i)
          {
          case(0):
                  digitalWrite(D1, HIGH);
                  digitalWrite(D2, LOW);
                  digitalWrite(D3, LOW);
                  digitalWrite(D4, LOW);
                  numero(10);
                  break;

          case(1):
                  digitalWrite(D1, HIGH);
                  digitalWrite(D2, HIGH);
                  digitalWrite(D3, LOW);
                  digitalWrite(D4, LOW);
                  numero(10);
                  break;

          case(2):
                  digitalWrite(D1, HIGH);
                  digitalWrite(D2, HIGH);
                  digitalWrite(D3, HIGH);
                  digitalWrite(D4, LOW);
                  numero(10);
                  break;

          case(3):
                  digitalWrite(D1, HIGH);
                  digitalWrite(D2, HIGH);
                  digitalWrite(D3, HIGH);
                  digitalWrite(D4, HIGH);
                  numero(10);
                  break;  */
        switch (i)
        {
          case (3):
            digitalWrite(D1, LOW);
            digitalWrite(D2, LOW);
            digitalWrite(D3, LOW);
            digitalWrite(D4, HIGH);
            if (!partie)numero(combinaison[3] - 2);
            else numero(entre[3] - 2);
            delay(5);

          case (2):
            digitalWrite(D1, LOW);
            digitalWrite(D2, LOW);
            digitalWrite(D3, HIGH);
            digitalWrite(D4, LOW);
            if (!partie)numero(combinaison[2] - 2);
            else numero(entre[2] - 2);
            delay(5);

          case (1):
            digitalWrite(D1, LOW);
            digitalWrite(D2, HIGH);
            digitalWrite(D3, LOW);
            digitalWrite(D4, LOW);
            if (!partie)numero(combinaison[1] - 2);
            else numero(entre[1] - 2);
            delay(5);

          case (0):
            digitalWrite(D1, HIGH);
            digitalWrite(D2, LOW);
            digitalWrite(D3, LOW);
            digitalWrite(D4, LOW);
            if (!partie)numero(combinaison[0] - 2);
            else numero(entre[0] - 2);
            delay(5);
            break;


        }
      }

      if (digitalRead(BouttonRouge))
      {
        if (!partie)combinaison[i] = 0;
        entre[i] = 0;
        tone(Buzzer, 4000, 50);
      }

      if (analogRead(BouttonJaune) < 100)
      {
        if (!partie)combinaison[i] = 1;
        entre[i] = 1;
        tone(Buzzer, 4000, 50);
      }
      delay(250);
    }

    if (partie)
    {

      bool var = true;

      for (int i = 0; i <= 3; i++)
      {
        if (entre[i] != combinaison[i])
        {
          var = false;
        }
      }

      if (var)
      {
        desam();
      }
      else
      {
        tone(Buzzer, 2000, 500);
        delay(500);
      }
    }

  }

  else
  {
    if (frequence()) desam();
  }

  /*
    Serial.println(combinaison[0]);
    Serial.println(combinaison[1]);
    Serial.println(combinaison[2]);
    Serial.println(combinaison[3]);*/

}


bool frequence()
{
  int freq = random(105, 4700);
  int freq_pot = map(analogRead(A0), 0, 1023, 100, 4800);
  int sensi = 50;
  int delta;
  while (!digitalRead(BouttonRouge))
  {
    tone(Buzzer, freq_pot);
    freq_pot = map(analogRead(A0), 0, 1023, 100, 4800);
    Serial.print(delta);
    Serial.print("    ");
    Serial.print(freq);
    Serial.print("    ");
    Serial.println(freq_pot);

    if (freq_pot >= freq)
    {
      delta = freq_pot - freq;
    }
    else delta = freq - freq_pot;

    if (delta < sensi / 2)affichage2(-3, -3, -3, -3);
    else if (delta < sensi * 1)affichage2(-3, -3, -3, random(2) - 2);
    else if (delta < sensi * 3)affichage2(-3, -3, random(2) - 2, random(2) - 2);
    else if (delta < sensi * 4)affichage2(-3, random(2) - 2, random(2) - 2, random(2) - 2);
    else affichage2(random(2) - 2, random(2) - 2, random(2) - 2, random(2) - 2);
  }
  if ((freq_pot < freq - (sensi / 2)) || (freq_pot > freq + (sensi / 2)))return false;
  else return true;
}



void explosion()
{
  for (int i = 1; i <= 7; i++)
  {
    tone(Buzzer, 1000 * i, 75);
    delay(100);
  }
  tone(Buzzer, 7000, 1000);
  int f_min = 1000;
  int f_max = 3000;
  int f = f_min;
  bool flag_f = true;
  while (!digitalRead(BouttonRouge))
  {
    if (flag_f)f += 10;
    else f -= 100;
    if (f > f_max)flag_f = false;
    if (f < f_min)flag_f = true;

    tone(Buzzer, f, 5);
    delay(5);

    digitalWrite(D1, random(2));
    digitalWrite(D2, random(2));
    digitalWrite(D3, random(2));
    digitalWrite(D4, random(2));

    digitalWrite(pinA, random(2));
    digitalWrite(pinB, random(2));
    digitalWrite(pinC, random(2));
    digitalWrite(pinD, random(2));
    digitalWrite(pinE, random(2));
    digitalWrite(pinF, random(2));
    digitalWrite(pinG, random(2));
  }
  while (digitalRead(BouttonRouge))
  {

    digitalWrite(D1, 0);
    digitalWrite(D2, 0);
    digitalWrite(D3, 0);
    digitalWrite(D4, 0);

    digitalWrite(pinA, 0);
    digitalWrite(pinB, 0);
    digitalWrite(pinC, 0);
    digitalWrite(pinD, 0);
    digitalWrite(pinE, 0);
    digitalWrite(pinF, 0);
    digitalWrite(pinG, 0);
  }
  delay(500);
  asm volatile ("  jmp 0");
  /*
    tempsMin, tempsSec,tempsI,OldTime, essais = 0;
    recupTemps();*/
}

void desam()
{
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);

  tone(Buzzer, 1000, 500);
  delay(500);
  tone(Buzzer, 3000, 100);
  delay(1000);
  while (!digitalRead(BouttonRouge))
  {
    if ((millis() / 500 % 2 ))
    {
      affichage(tempsMin, tempsSec);
    }
    else
    {
      digitalWrite(D1, 0);
      digitalWrite(D2, 0);
      digitalWrite(D3, 0);
      digitalWrite(D4, 0);

      digitalWrite(pinA, 0);
      digitalWrite(pinB, 0);
      digitalWrite(pinC, 0);
      digitalWrite(pinD, 0);
      digitalWrite(pinE, 0);
      digitalWrite(pinF, 0);
      digitalWrite(pinG, 0);
    }
  }
  asm volatile ("  jmp 0");
}



void annimation()
{
  for(int i = 0; i<20;i++)affichage2(-1,-1,-1,-1);
  for(int i = 0; i<20;i++)affichage2(-3,-3,-3,-3);
  for(int i = 0; i<20;i++)affichage2(-2,-2,-2,-2);
  for(int i = 0; i<20;i++)affichage2(8,8,8,8);
}
void affichage(int minutes, int secondes)
{
  int Seg1 = minutes / 10;
  int Seg2 = minutes - (Seg1 * 10);
  int Seg3 = secondes / 10;
  int Seg4 = secondes - (Seg3 * 10);
  affichage2(Seg1, Seg2, Seg3, Seg4);
}
void affichage2(int Seg1, int Seg2, int Seg3, int Seg4)
{
  /*
    int Seg1 = minutes/10;
    int Seg2 = minutes-(Seg1*10);
    int Seg3 = secondes/10;
    int Seg4 = secondes-(Seg3*10);
  */
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  numero(Seg1);

  delay(5);

  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  numero(Seg2);

  delay(5);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
  numero(Seg3);

  delay(5);

  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);
  numero(Seg4);
  delay(5);

}


void numero(int Segment)
{
  switch (Segment)
  {
    case (0):
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, LOW);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, HIGH);
      break;
    case (1):
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, LOW);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      break;
    case (2):
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, LOW);
      break;
    case (3):
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, LOW);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, LOW);
      break;
    case (4):
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, LOW);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
      break;
    case (5):
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, LOW);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
      break;

    case (6):
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, LOW);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
      break;
    case (7):
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, LOW);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      break;
    case (8):
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, LOW);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, LOW);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
      break;
    case (9):
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, LOW);
      digitalWrite(pinC, LOW);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
      break;
    case (-1): //BT rouge trait en haut
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      break;
    case (-2): //BT jaune trait en bas
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      break;
    default: // trait milieu
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, HIGH);
      digitalWrite(pinC, HIGH);
      digitalWrite(pinD, HIGH);
      digitalWrite(pinE, HIGH);
      digitalWrite(pinF, HIGH);
      digitalWrite(pinG, LOW);
      break;
  }
}
