void Ball_touchYWall() {
  Ball_yV = -Ball_yV;
}

void Ball_touchLWall() {
  int b = (Ball_y + (Ball_h / 2));
  int p = (PL_y + (PL_h / 2));
  int a = p - b;
  if(abs(a) <= (PL_h / 2)) {
    Ball_xV = -Ball_xV;
    if(a > 0) {
      Ball_yV = -((float) a / (float) PL_h / 2) * 20.0f;
    } else if(a < 0) {
      Ball_yV = -((float) a / (float) PL_h / 2) * 20.0f;
    } else {
      Ball_yV /= 2.0f;
    }
  } else {
    sR++;
    Ball_x = 39;
    Ball_y = 7;
    Ball_xF = (float) Ball_x;
    Ball_yF = (float) Ball_y;
    Ball_xV = 20.0f;
    Ball_yV = 0.0f;
    delay(250);
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("SCORE:");
    lcd.setCursor(2, 1);
    lcd.print((String) sL);
    lcd.setCursor(13, 1);
    lcd.print((String) sR);
    delay(2000);
    lcd.clear();
    cTime2 = 0;
    lTime2 = 0;
  }
}

void Ball_touchRWall() {
  int b = (Ball_y + (Ball_h / 2));
  int p = (PR_y + (PR_h / 2));
  int a = p - b;
  if(abs(a) <= (PR_h / 2)) {
    Ball_xV = -Ball_xV;
    if(a > 0) {
      Ball_yV = -((float) a / (float) PR_h / 2) * 20.0f;
    } else if(a < 0) {
      Ball_yV = -((float) a / (float) PR_h / 2) * 20.0f;
    } else {
      Ball_yV /= 2.0f;
    }
  } else {
    sL++;
    Ball_x = 39;
    Ball_y = 7;
    Ball_xF = (float) Ball_x;
    Ball_yF = (float) Ball_y;
    Ball_xV = -20.0f;
    Ball_yV = 0.0f;
    delay(250);
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("SCORE:");
    lcd.setCursor(2, 1);
    lcd.print((String) sL);
    lcd.setCursor(13, 1);
    lcd.print((String) sR);
    delay(2000);
    lcd.clear();
    cTime2 = 0;
    lTime2 = 0;
  }
}

void Ball_update() {
  //calculate positions
  Ball_xF += (Ball_xV * (float) aTime2 / (float) 1000);
  Ball_yF += (Ball_yV * (float) aTime2 / (float) 1000);
  Ball_x = (int) (Ball_xF);
  Ball_y = (int) (Ball_yF);
  if(Ball_y < 0) {
    Ball_y = 0;
    Ball_yF = (float) Ball_y;
  } else if(Ball_y > 14) {
    Ball_y = 14;
    Ball_yF = (float) Ball_y;
  }
  if(Ball_x < 4) {
    Ball_x = 4;
    Ball_xF = (float) Ball_x;
  } else if(Ball_x > 73) {
    Ball_x = 73;
    Ball_xF = (float) Ball_x;
  }
  if(Ball_y <= 0) {
    if(Ball_yV < 0) {
      Ball_touchYWall();
    }
  } else if(Ball_y >= 14) {
    if(Ball_yV > 0) {
      Ball_touchYWall();
    }
  }
  if(Ball_x <= 4) {
    if(Ball_xV < 0) {
      Ball_touchLWall();
    }
  } else if(Ball_x >= 73) {
    if(Ball_xV > 0) {
      Ball_touchRWall();
    }
  }
  //calculate rendering
  Ball_pastX = Ball_xLoc;
  Ball_pastY = Ball_yLoc;
  Ball_pastSplitsX = Ball_splitsX;
  Ball_pastSplitsY = Ball_splitsY;
  Ball_xLoc = (int) (Ball_x / 5);
  Ball_yLoc = (int) (Ball_y / 8);
  Ball_xMod = Ball_x % 5;
  Ball_yMod = Ball_y % 8;
  if(Ball_xMod > (5 - Ball_w)) {
    Ball_splitsX = 1;
  } else {
    Ball_splitsX = 0;
  }
  if(Ball_yMod > (8 - Ball_h)) {
    Ball_splitsY = 1;
  } else {
    Ball_splitsY = 0;
  }
  if(Ball_splitsX == 0) {
    if(Ball_splitsY == 0) {//split on nothing
      PDL_request(13 + (Ball_yMod * 6) + Ball_xMod, 4);
    } else if(Ball_splitsY == 1) {//split on y
      PDL_request(55 + Ball_xMod, 4);
      PDL_request(61 + Ball_xMod, 6);
    }
  } else if(Ball_splitsX == 1) {
    if(Ball_splitsY == 0) {//split on x
      PDL_request(17 + (Ball_yMod * 6), 4);
      PDL_request(18 + (Ball_yMod * 6), 5);
    } else if(Ball_splitsY == 1) {//split on x and y
      PDL_request(59, 4);
      PDL_request(60, 5);
      PDL_request(65, 6);
      PDL_request(66, 7);
    }
  }
}

void Ball_render() {
  PDL_clear(Ball_pastX, Ball_pastY);
  if(Ball_pastSplitsX == 0) {
    if(Ball_pastSplitsY == 0) {
    } else if(Ball_pastSplitsY == 1) {
      PDL_clear(Ball_pastX, Ball_pastY + 1);
    }
  } else if(Ball_pastSplitsX == 1) {
    if(Ball_pastSplitsY == 0) {
      PDL_clear(Ball_pastX + 1, Ball_pastY);
    } else if(Ball_pastSplitsY == 1) {
      PDL_clear(Ball_pastX + 1, Ball_pastY);
      PDL_clear(Ball_pastX, Ball_pastY + 1);
      PDL_clear(Ball_pastX + 1, Ball_pastY + 1);
    }
  }
  if(Ball_splitsX == 0) {
    if(Ball_splitsY == 0) {//split on nothing
      PDL_renderChar(4, Ball_xLoc, Ball_yLoc);
    } else if(Ball_splitsY == 1) {//split on y
      PDL_renderChar(4, Ball_xLoc, Ball_yLoc);
      PDL_renderChar(6, Ball_xLoc, Ball_yLoc + 1);
    }
  } else if(Ball_splitsX == 1) {
    if(Ball_splitsY == 0) {//split on x
      PDL_renderChar(4, Ball_xLoc, Ball_yLoc);
      PDL_renderChar(5, Ball_xLoc + 1, Ball_yLoc);
    } else if(Ball_splitsY == 1) {//split on x and y
      PDL_renderChar(4, Ball_xLoc, Ball_yLoc);
      PDL_renderChar(5, Ball_xLoc + 1, Ball_yLoc);
      PDL_renderChar(6, Ball_xLoc, Ball_yLoc + 1);
      PDL_renderChar(7, Ball_xLoc + 1, Ball_yLoc + 1);
    }
  }
}
