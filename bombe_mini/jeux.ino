void bombeCode(uint16_t tempsJeu, int8_t* codeJeu)
{
  uint16_t delta = millis()/100;
  uint16_t temps = 0;
  uint8_t essais = 0;
  bool fin = false;
  int8_t entree[4] = {-3, -3, -3, -3,};
  while(!fin)
  {
    temps = (millis()/100) - delta;
    tempsMin = (tempsJeu - temps / 10) / 60;
    tempsSec = (tempsJeu - temps / 10) % 60;

    affichage(tempsMin, tempsSec);
    if(temps%5)
    {
      tone(Buzzer, 2500, 100);
    }
    
    if(temps >= tempsJeu || essais == 3) explosion();
    if (analogRead(BouttonJaune) < 400)
    {
      essais++;
      _code(entree);
      if(codeJeu[0] == -3)
      {
       fin = frequence();
      }
      else if(entree[0] == codeJeu[0] && entree[1] == codeJeu[1] && entree[2] == codeJeu[2] && entree[3] == codeJeu[3])
        fin = true;
    }
  }
  desam(tempsMin, tempsSec);
}

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
