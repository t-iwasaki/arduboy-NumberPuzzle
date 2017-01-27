#ifndef PLAYER_H
#define PLAYER_H




/*-------------------------
    movePlayer
  ------------------------ */
void movePlayer() {

  int save_pX = pX;
  int save_pY = pY;


  if (pX % 8 == 0 && pY % 8 ==0) {
    if (arduboy.pressed(UP_BUTTON)) {
      pArrow = pLastPress = UP_BUTTON;
      pY -= pSpeed;
    } else if (arduboy.pressed(DOWN_BUTTON)) {
      pArrow = pLastPress = DOWN_BUTTON;
      pY += pSpeed;
    } else if (arduboy.pressed(LEFT_BUTTON)) {
      pArrow = pLastPress = LEFT_BUTTON;
      pX -= pSpeed;
    } else if (arduboy.pressed(RIGHT_BUTTON)) {
      pArrow = pLastPress = RIGHT_BUTTON;
      pX += pSpeed;
    }
  } else {
    if (pLastPress == UP_BUTTON) pY -= pSpeed;
    if (pLastPress == DOWN_BUTTON) pY += pSpeed;
    if (pLastPress == LEFT_BUTTON) pX -= pSpeed;
    if (pLastPress == RIGHT_BUTTON) pX += pSpeed;
  }

  // giveup
  if (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)) {
    arduboy.clearDisplay();
    arduboy.display();
    delay(500);

    pLives--;

    if (pLives<=0) {
      pIsGameOver = true;
    }
    pX = pWidth - pCharSize;
    pY = pHeight - pCharSize;

    initBox(concurrent_box_max);
  }

  // collision
  for (int i = 0; i < box.concurrent_box_max; i++) {
    if (boxes[i].active) {

      if (abs(boxes[i].x - pX) < pCharSize / 2 + pCharSize / 2 &&
          abs(boxes[i].y - pY) < pCharSize / 2 + pCharSize / 2 )
      {
        arduboy.tunes.tone(NOTE_G3, 80);
        boxes[i].arrow = pArrow;
        pX = save_pX;
        pY = save_pY;
      }
    }
  }

  // display area ajast.
  if (pX < 8) {
    pX = 8;
  }
  if (pX > pWidth - pCharSize -8) {
    pX = pWidth - pCharSize -8;
  }
  if (pY < 16) {
    pY = 16;
  }
  if (pY > pHeight - pCharSize) {
    pY = pHeight - pCharSize;
  }
}



/*-------------------------
    Draw Player
  ------------------------ */
void drawPlayer()
{
  arduboy.drawSlowXYBitmap(pX , pY, bMan, 8, 8, 1);
}

#endif
