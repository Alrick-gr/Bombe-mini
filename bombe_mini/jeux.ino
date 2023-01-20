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
