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


uint16_t _recupTemps()
{
  uint16_t tempsMin, tempsSecondes, OldTime;
  uint16_t ;
  while (digitalRead(BouttonRouge));
  while (!digitalRead(BouttonRouge))
  {
    tempsMin = map(analogRead(A0), 0, 1023, 0, 60);
    tempsSecondes = tempsMin * 60;

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


void code(int8_t* nbr)
{
  //numero(-3);
  uint8_t index = 0;
  for(uint8_t i = 0; i<4; i++)nbr[i] = -3;
  
  while(pressed(BouttonRouge));
  while (nbr[3] == -3)
  {
    
    if (pressed(BouttonRouge))
    {
      
      nbr[index] = -1;
      tone(Buzzer, 4000, 50);
      while(pressed(BouttonRouge));
      index++;
    }
    else if (pressed(BouttonJaune))
    {
      //Serial.println(analogRead
      nbr[index] = -2;
      tone(Buzzer, 4000, 50);
      index++;
      while(pressed(BouttonJaune));
    }
    affichage2(nbr[0], nbr[1], nbr[2], nbr[3]);
  }
}
void codeNum(int8_t* nbr)
{
  uint8_t index = 0;
  for(uint8_t i = 0; i<4; i++)nbr[i] = -3;
  while(pressed(BouttonRouge));
  while (nbr[3] == -3 || !pressed(BouttonJaune))
  {
    
    nbr[index] = map(analogRead(A0), 0, 1023, 0, 9);
    if (pressed(BouttonJaune))
    {
      tone(Buzzer, 4000, 50);
      index++;
      while(pressed(BouttonJaune));
    }
    affichage2(nbr[0], nbr[1], nbr[2], nbr[3]);
  }
}
bool pressed(uint8_t btn)
{
  switch(btn)
  {
    default:
    case(BouttonRouge):
      if(digitalRead(BouttonRouge))
        return true;
      break;
    case(BouttonJaune):
      if(analogRead(BouttonJaune) < 250)
        return true;
      break;
  }
  return false;
}

void pressToStart()
{
  while(!pressed(BouttonRouge))
  {
    affichage2(8, 8, 8, 8);
  }
}
