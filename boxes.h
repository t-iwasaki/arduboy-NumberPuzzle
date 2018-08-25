#ifndef BOXES_H
#define BOXES_H

/*-------------------------
    _checkwall
  ------------------------ */
void _checkwall(int i)
{
  if (boxes[i].x < 8) boxes[i].x = 8;
  if (boxes[i].x > pWidth - pCharSize - 8) boxes[i].x = pWidth - pCharSize - 8;
  if (boxes[i].y < 16) boxes[i].y = 16;
  if (boxes[i].y > pHeight - pCharSize - 8) boxes[i].y = pHeight - pCharSize;
}

/*-------------------------
    _makeMap
  ------------------------ */
void _makeMap(int stageno)
{
  stageno--;

  //TODO:
  //Serial.println("MAP ----------------------");

  int offsetY = 8;
  int i = 0;

  box.qty = 0;

  for (int y = 0; y < 6; y++) {
    for (int x = 0; x < 13; x++) {
      int kind = pgm_read_byte(&pStageMap[stageno][x + y * 13]);

      if (kind > 0) {

        // 数字ボックスだけをカウントする。
        if (kind < 7) {
          box.qty++;
        }

        boxes[i].x = (x + 1) * pCharSize;
        boxes[i].y = offsetY + (y + 1) * pCharSize;

        //外壁範囲チェック
        _checkwall(i);

        boxes[i].kind = kind;
        boxes[i].arrow = 0;
        boxes[i].active = true;

        /*
          Serial.print("X:Y=");
          Serial.print(boxes[i].x);
          Serial.print(":");
          Serial.println(boxes[i].y);
        */
        i++;
      }
    }
  }
}


/*-------------------------
    initBox
  ------------------------ */
void initBox(int concurrent_box_max)
{
  box.spCount = 0;
  box.qty = 0;
  box.concurrent_box_max = (concurrent_box_max > CONCURRENT_BOX_MAX ) ? CONCURRENT_BOX_MAX : concurrent_box_max;

  for (int i = 0; i < box.concurrent_box_max; i++) {
    boxes[i].active = false;
  }

  _makeMap(pStage);
}


/*-------------------------
    moveBox
  ------------------------ */
void moveBox()
{
  for (int i = 0; i < box.concurrent_box_max; i++) {
    if (boxes[i].active == true && boxes[i].arrow != 0) {


      if (boxes[i].kind >= 7) {
        boxes[i].arrow = 0;
      }


      boxes[i].boxSpeed = 1;

      int save_x = boxes[i].x;
      int save_y = boxes[i].y;

      switch (boxes[i].arrow) {
        case UP_BUTTON:
          boxes[i].y -= boxes[i].boxSpeed;
          break;
        case DOWN_BUTTON:
          boxes[i].y += boxes[i].boxSpeed;
          break;
        case LEFT_BUTTON:
          boxes[i].x -= boxes[i].boxSpeed;
          break;
        case RIGHT_BUTTON:
          boxes[i].x += boxes[i].boxSpeed;
          break;
      }

      // collision.
      for (int j = 0; j < box.concurrent_box_max; j++) {
        if (j != i && boxes[j].active) {
          if (abs(boxes[j].x - boxes[i].x) < pCharSize / 2 + pCharSize / 2 &&
              abs(boxes[j].y - boxes[i].y) < pCharSize / 2 + pCharSize / 2 ) {
            arduboy.tunes.tone(NOTE_G3, 80);
            boxes[i].arrow = 0;
            boxes[i].boxSpeed = 0;

            boxes[i].x = save_x;
            boxes[i].y = save_y;


            if (boxes[j].kind == 7 ||
                boxes[i].kind < 8 && boxes[i].kind == boxes[j].kind
               ) {
              boxes[i].active = false;
              boxes[j].active = false;

              if (boxes[i].kind < 7) {
                box.qty--;
              }
              if (boxes[j].kind < 7) {
                box.qty--;
              }
            }


            break;
          }
        }
      }

      //外壁範囲チェック
      _checkwall(i);

      // ステージクリア
      if (box.qty <= 0) {
        pStage++;
        pIsStageClear = true;
      }

    }
  }
}


/*-------------------------
    drawBox
  ------------------------ */
void drawBox()
{
  for (int y = 1; y < 8; y++) {
      arduboy.drawSlowXYBitmap(0, y*8, bOuterWall, 8, 8, 1);
      arduboy.drawSlowXYBitmap(15*8, y*8, bOuterWall, 8, 8, 1);
  }
/*
  for (int x = 1; x < 15; x++) {
      arduboy.drawSlowXYBitmap(x*8, 8, bOuterWall, 8, 8, 1);
  }
*/

  for (int i = 0; i < box.concurrent_box_max; i++) {
    if (boxes[i].active) {
      switch (boxes[i].kind) {
        case 1:
          arduboy.drawSlowXYBitmap(boxes[i].x, boxes[i].y, bOne, 8, 8, 1);
          break;
        case 2:
          arduboy.drawSlowXYBitmap(boxes[i].x, boxes[i].y, bTwo, 8, 8, 1);
          break;
        case 3:
          arduboy.drawSlowXYBitmap(boxes[i].x, boxes[i].y, bThree, 8, 8, 1);
          break;
        case 4:
          arduboy.drawSlowXYBitmap(boxes[i].x, boxes[i].y, bFour, 8, 8, 1);
          break;
        case 7:
          arduboy.drawSlowXYBitmap(boxes[i].x, boxes[i].y, bHatena, 8, 8, 1);
          break;
        case 8:
          arduboy.drawSlowXYBitmap(boxes[i].x, boxes[i].y, bHoll, 8, 8, 1);
          break;
        case 9:
          arduboy.drawSlowXYBitmap(boxes[i].x, boxes[i].y, bWall, 8, 8, 1);
          break;
        default:
          arduboy.drawSlowXYBitmap(boxes[i].x, boxes[i].y, bBox, 8, 8, 1);
          break;
      }
    }
  }
}


/*-------------------------
    getBoxQty
  ------------------------ */
uint8_t getBoxQty()
{
  return box.qty;
}


#endif
