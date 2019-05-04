#ifndef MENU_BITMAPS_H
#define MENU_BITMAPS_H

/*-------------------------
    scrollText
  ------------------------ */
void scrollText() {

  if (pSX >= 0) {
    pSX = pSX - pSSpeed;
  } else {
    pSX = pWidth;
  }

  arduboy.setCursor(pSX, pSY);
  arduboy.print(pText);
}

/*--------------------------
     Draw Header
  -------------------------*/
void drawHeader()
{
  arduboy.setTextSize(1);
  arduboy.fillRect(0, 0, 127, 10, 1);
  for (int i = 0; i < pLives; i++) {
    arduboy.drawBitmap(3 + (i * 10) , 1 , bHeart, 8, 8, 0);
  }
  arduboy.setCursor(72, 1);
  arduboy.write(' ');
  arduboy.write('S');
  arduboy.write('T');
  arduboy.write('A');
  arduboy.write('G');
  arduboy.write('E');
  arduboy.write(' ');
  arduboy.print(pStage);
  arduboy.write(' ');
}

/*-------------------------
    displayTitle
  ------------------------ */
void displayTitle()
{
  initStage();
  int flash = 0;
  while (true) {
    delay( 30 );
    arduboy.clearDisplay();

    arduboy.setCursor(20, 1);
    arduboy.setTextSize(2);
    arduboy.print("Number");

    arduboy.setCursor(20, 20);
    arduboy.setTextSize(2);
    arduboy.print("Puzzle");

    arduboy.setCursor(20, 42);
    arduboy.setTextSize(1);
    arduboy.print("ver 1.0.1");

    flash++;
    flash %= 50;

    if (flash < 25) {
      arduboy.setCursor(30, 54);
      arduboy.setTextSize(1);
      arduboy.print("Press A or B");
    }

    arduboy.display();

    if (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)) {
      break;
    }
  }
}

/*-------------------------
    displayStageClear
  ------------------------ */
void displayStageClear()
{
  if (!pIsStageClear) {
    return;
  }

  pIsStageClear = false;
  pWait = true;

  
  int row = sizeof(pStageMap) / sizeof(pStageMap[0]); 
  if (pStage >= row){
      strcpy(pText, "All Stage Clear!!!!");
      pStage = 1;
  }
  else{
    strcpy(pText, "Stage Clear!!!!");
    initStage();
  }


  arduboy.clearDisplay();
  arduboy.setCursor(20, 18);
  arduboy.setTextSize(1);
  arduboy.print(pText);
  arduboy.display();
  
  delay( 3000 );
  pWait = false;
  return;
}



/*-------------------------
    displayGameOver
  ------------------------ */
void displayGameOver()
{
  if (!pIsGameOver) {
    return;
  }
  pIsGameOver = false;
  pWait = true;
  pStage = 1;
  initStage();

  strcpy(pText, "Game Over!!!!");
  arduboy.clearDisplay();
  arduboy.setCursor(20, 18);
  arduboy.setTextSize(1);
  arduboy.print(pText);
  arduboy.display();
  
  delay( 3000 );
  pWait = false;
  displayTitle();
  
  return;
}

#endif
