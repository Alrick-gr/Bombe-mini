void param_bombeCode()
{
  uint16_t temps = 0;
  int8_t codeJeu[4] = {-3, -3, -3, -3};
  temps = _recupTemps();
  code(codeJeu);
  pressToStart();
  bombeCode(temps, codeJeu);
}

void param_bombeFreq()
{
  uint16_t temps = 0;
  int8_t codeJeu[4] = {-3, -3, -3, -3};
  temps = _recupTemps();
  pressToStart();
  bombeCode(temps, codeJeu);
}
void param_bombeNum()
{
  uint16_t temps = 0;
  int8_t codeJeu[4] = {-3, -3, -3, -3};
  temps = _recupTemps();
  codeNum(codeJeu);
  pressToStart();
  bombeCode(temps, codeJeu);
}
