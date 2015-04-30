//Daniel Eisterhold
//dte130030@utdallas.edu
//CS3376.502

#ifndef __MATRIX__
#define __MATRIX__

#include <cdk.h>
#include <inttypes.h>
#include <string>

#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 5

using namespace std;

class Matrix {
 private:
  WINDOW *window;
  CDKSCREEN *screen;
  CDKMATRIX* matrix;
 public:
  Matrix();
  ~Matrix();
  void setCell(uint8_t row, uint8_t column, std::string data);
};

#endif
