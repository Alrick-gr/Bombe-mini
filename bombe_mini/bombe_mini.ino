#define Buzzer A1
#define BouttonRouge 13
#define BouttonJaune A2

#define NbrModes 2

int tempsMin, tempsSec, tempsI, OldTime, essais = 0;
unsigned long temps, dT = 0;
uint8_t combinaison[4] = {12, 12, 12, 12};
bool code_mode = true;


uint8_t pinA = 11;
uint8_t pinB = 7;
uint8_t pinC = 4;
uint8_t pinD = 5;
uint8_t pinE = 6;
uint8_t pinF = 10;
uint8_t pinG = 3;
uint8_t D1   = 12;
uint8_t D2   = 9;
uint8_t D3   = 8;
uint8_t D4   = 2;

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
  menu();
  /*
  if (digitalRead(BouttonRouge))
  {
    tone(Buzzer, 3000, 500);
    code_mode = false;
    combinaison[3] = 1;
    delay(1000);
    tone(Buzzer, 3000, 500);
    delay(1000);
  }
*/
  Serial.begin(9600);
  //recupTemps();
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

void menu()
{
  uint8_t mode = 0;
  uint16_t temps = 0;
  uint8_t codeJeu[4] = {-3, -3, -3, -3};
  while(!digitalRead(BouttonRouge))
  {
    mode = map(analogRead(A0), 0, 1023, 0, NbrModes);
    affichage2(-3,-3,-3,mode);
  }
  while(digitalRead(BouttonRouge));
  
  switch(mode)
  {
    case 0:
    default:
      temps = _recupTemps();
      _code(codeJeu);
      bombeCode(temps, codeJeu);
      break;
    case 1:
      temps = _recupTemps();
      bombeCode(temps, codeJeu);
      break;
  }
}
/*
  void gameCapture()
  {

  }
*/


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
        desam(tempsMin, tempsSec);
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
    if (frequence()) desam(tempsMin, tempsSec);
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

void desam(uint8_t tempsMin, uint8_t tempsSec)
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
  for(uint8_t i = 0; i<20;i++)affichage2(-1,-1,-1,-1);
  for(uint8_t i = 0; i<20;i++)affichage2(-3,-3,-3,-3);
  for(uint8_t i = 0; i<20;i++)affichage2(-2,-2,-2,-2);
  for(uint8_t i = 0; i<20;i++)affichage2(8,8,8,8);
}
