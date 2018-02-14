void PR_update() {
  //calculate positions
  /*if(Ball_x >= 40) {
    if(((Ball_y + Ball_h / 2) - (PR_y + PR_h / 2)) > 0) {
      PR_dir = -1;
    } else if(((Ball_y + Ball_h / 2) - (PR_y + PR_h / 2)) < 0) {
      PR_dir = 1;
    } else if(((Ball_y + Ball_h / 2) - (PR_y + PR_h / 2)) == 0) {
      PR_dir = 0;
    }
  }
  PR_yV = -6.0f * (float) PR_dir;
  //calculate rendering
  PR_y += (int) (PR_yV * (float) aTime2 / (float) 1000);*/
  PR_y = Ball_y - PR_h / 2;
  if(PR_y < 0) {
    PR_y = 0;
  } else if(PR_y + PR_h > 15) {
    PR_y = 15 - PR_h;
  }
  PR_yLoc = (int) (PR_y / 8);
  PR_yMod = PR_y % 8;
  if(PR_yMod > (8 - PR_h)) {
    PR_splits = 1;
    PDL_request(PR_y, 2);
    PDL_request(PR_y + PR_h - 1, 3);
  } else {
    PR_splits = 0;
    PDL_request(PR_yMod, 2);
  }
}

void PR_render() {
  if(PR_splits == 0) {
    PDL_renderChar(2, PR_xLoc, PR_yLoc);
    if(PR_yLoc == 0) {
      PDL_clear(PR_xLoc, 1);
    } else if(PR_yLoc == 1) {
      PDL_clear(PR_xLoc, 0);
    }
  } else if(PR_splits == 1) {
    PDL_renderChar(2, PR_xLoc, 0);
    PDL_renderChar(3, PR_xLoc, 1);
  }
}
