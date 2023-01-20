void numero(int8_t Segment)
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

void affichage(int minutes, int secondes)
{
  uint8_t Seg1 = minutes / 10;
  uint8_t Seg2 = minutes - (Seg1 * 10);
  uint8_t Seg3 = secondes / 10;
  uint8_t Seg4 = secondes - (Seg3 * 10);
  affichage2(Seg1, Seg2, Seg3, Seg4);
}

void affichage2(int8_t Seg1, int8_t Seg2, int8_t Seg3, int8_t Seg4)
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

uint16_t _recupTemps()
{
  uint16_t tempsSecondes;
  while (!digitalRead(BouttonRouge))
  {
    tempsMin = map(analogRead(A0), 0, 1023, 0, 60);
    uint16_t tempsSecondes = tempsMin * 60;

    if (tempsMin != OldTime)
    {
      OldTime = tempsMin;
      tone(Buzzer, 4000, 10);
    }
    affichage(tempsMin, 0);
  }
  while (digitalRead(BouttonRouge));
  return tempsSecondes;
}


void _code(int8_t* nbr)
{
  numero(-3);
  uint8_t index = 0;
  for(uint8_t i = 1; i<=3; i++)nbr[i] = -3;
  
  while (!digitalRead(BouttonRouge))
  {
    if (digitalRead(BouttonRouge))
    {
      nbr[index] = -1;
      tone(Buzzer, 4000, 50);
      while(digitalRead(BouttonRouge));
      index++;
    }
    else if (analogRead(BouttonJaune) < 100)
    {
      nbr[index] = -2;
      tone(Buzzer, 4000, 50);
      index++;
    }
    affichage2(nbr[0], nbr[1], nbr[2], nbr[3]);
  }
}
