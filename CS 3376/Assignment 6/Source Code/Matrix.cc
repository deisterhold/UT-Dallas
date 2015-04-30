//Daniel Eisterhold
//dte130030@utdallas.edu
//CS3376.502

#include "Matrix.h"

Matrix::~Matrix() {
  endCDK();
}

Matrix::Matrix() {
  const char *rowNames[MATRIX_HEIGHT+1] = {"R0","R1","R2","R3","R4","R5"};
  const char *colNames[MATRIX_WIDTH+1] = {"C0","C1","C2","C3","C4","C5"};
  int boxWidths[MATRIX_WIDTH+1] = {15,15,15,15,15,15};
  int boxTypes[MATRIX_WIDTH+1] = {vMIXED,vMIXED,vMIXED,vMIXED,vMIXED,vMIXED};

  window = initscr();
  screen = initCDKScreen(window);

  initCDKColor();

  matrix = newCDKMatrix(screen,CENTER,CENTER,MATRIX_WIDTH,MATRIX_HEIGHT,MATRIX_WIDTH,MATRIX_HEIGHT,"Worker Matrix",(char **)colNames,(char **) rowNames,boxWidths,boxTypes,1,1,' ',ROW,true,true, false);
  if(matrix == NULL) {
    fprintf(stderr,"Error creating Matrix\n");
    exit(1);
  }
  drawCDKMatrix(matrix, true);
}

void Matrix::setCell(uint8_t row, uint8_t column, std::string data) {
  setCDKMatrixCell(matrix, row, column, data.c_str());
  drawCDKMatrix(matrix, true);
}
