void bombeCode(uint16_t tempsJeu, int8_t* codeJeu)
{
  uint16_t delta = millis()/1000;
  uint16_t temps, oldTemps = 0;
  uint8_t essais = 0;
  bool fin = false;
  int8_t entree[4] = {-3, -3, -3, -3,};
  uint8_t tempsMin, tempsSec;
  while(!fin)
  {
    temps = (millis()/1000) - delta;
    tempsMin = (tempsJeu - temps) / 60;
    tempsSec = (tempsJeu - temps) % 60;

    affichage(tempsMin, tempsSec);
    if(oldTemps != temps)
    {
      oldTemps = temps;
      tone(Buzzer, 2500, 100);
    }
    if(temps >= tempsJeu || essais == 3) explosion();
    if (pressed(BouttonJaune))
    {
      while(pressed(BouttonJaune));
      essais++;
      if(codeJeu[0] == -3)
        fin = frequence();
      else if(codeJeu[0] >= 0)
        codeNum(entree);
      else
        code(entree);
      if(entree[0] == codeJeu[0] && entree[1] == codeJeu[1] && entree[2] == codeJeu[2] && entree[3] == codeJeu[3])
        fin = true;
      
    }
  }
  desam(tempsMin, tempsSec);
}
