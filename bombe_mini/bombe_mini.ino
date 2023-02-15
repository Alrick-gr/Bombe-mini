#define Buzzer A1
#define BouttonRouge 13
#define BouttonJaune A2

#define NbrModes 3



const uint8_t pinA = 11;
const uint8_t pinB = 7;
const uint8_t pinC = 4;
const uint8_t pinD = 5;
const uint8_t pinE = 6;
const uint8_t pinF = 10;
const uint8_t pinG = 3;
const uint8_t D1   = 12;
const uint8_t D2   = 9;
const uint8_t D3   = 8;
const uint8_t D4   = 2;

void setup() {
  
  Serial.begin(9600);
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
}
void loop()
{

}

void menu()
{
  uint8_t mode;
  int8_t codeJeu[4] = {-3, -3, -3, -3};
  while(!pressed(BouttonRouge))
  {
    mode = map(analogRead(A0), 0, 1023, 0, NbrModes);
    affichage2(-3,-3,-3,mode);
  }
  while(pressed(BouttonRouge));
  
  switch(mode)
  {
    case 0:
    default:
      param_bombeCode();
      break;
    case 1:
      param_bombeFreq();
      break;
    case 2:
      param_bombeNum();
      break;
  }
}

bool frequence()
{
  uint16_t freq = random(105, 4700);
  uint16_t freq_pot = map(analogRead(A0), 0, 1023, 100, 4800);
  uint8_t sensi = 50;
  uint16_t delta;
  while (!pressed(BouttonJaune))
  {
    tone(Buzzer, freq_pot);
    freq_pot = map(analogRead(A0), 0, 1023, 100, 4800);

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
  for (uint8_t i = 1; i <= 7; i++)
  {
    tone(Buzzer, 1000 * i, 75);
    delay(100);
  }
  tone(Buzzer, 7000, 1000);
  uint16_t f_min = 1000;
  uint16_t f_max = 3000;
  uint16_t f = f_min;
  bool flag_f = true;
  while (!pressed(BouttonRouge))
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
  while (pressed(BouttonRouge))
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
  while (!pressed(BouttonRouge))
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
