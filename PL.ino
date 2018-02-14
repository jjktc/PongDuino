void PL_update() {
  //calculate positions
  int ang = angY;
  if(ang < 200) {
    ang = 200;
  }
  if(ang > 250) {
    ang = 250;
  }
  PL_y = map(ang, 200, 250, 0, 16 - PL_h);
  //calculate rendering
  PL_yLoc = (int) (PL_y / 8);
  PL_yMod = PL_y % 8;
  if(PL_yMod > (8 - PL_h)) {
    PL_splits = 1;
    PDL_request(PL_y, 0);
    PDL_request(PL_y + PL_h - 1, 1);
  } else {
    PL_splits = 0;
    PDL_request(PL_yMod, 0);
  }
}

void PL_render() {
  if(PL_splits == 0) {
    PDL_renderChar(0, PL_xLoc, PL_yLoc);
    if(PL_yLoc == 0) {
      PDL_clear(PL_xLoc, 1);
    } else if(PL_yLoc == 1) {
      PDL_clear(PL_xLoc, 0);
    }
  } else if(PL_splits == 1) {
    PDL_renderChar(0, PL_xLoc, 0);
    PDL_renderChar(1, PL_xLoc, 1);
  }
}
