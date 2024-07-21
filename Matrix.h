// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <cmath>
#define MATRIX_DIMS_ERROR "invalid matrix dimensions"
#define OUT_OF_RANGE_ERROR "invalid index"
#define RUN_TIME_ERROR "run time error"
#define PRINT_THRESHOLD 0.1
#define SQUARE 2
/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
	int rows, cols;
} matrix_dims;

// Insert Matrix class here...
class Matrix
{
 public:
  Matrix(int rows, int cols);
  Matrix();
  Matrix(const Matrix& mat);
  ~Matrix();
  int get_rows() const;
  int get_cols() const;
  Matrix& transpose();
  Matrix& vectorize();
  void plain_print() const;
  Matrix dot(const Matrix& mat) const;
  float norm() const;
  int argmax() const;
  float sum() const;
  Matrix operator+(const Matrix& mat) const;
  Matrix& operator+=(const Matrix& mat);
  Matrix& operator=(const Matrix& mat);
  Matrix operator*(const Matrix& mat) const;
  Matrix operator*(float c) const;
  friend Matrix operator*(float c, const Matrix& mat);
  float operator()(int i, int j) const;
  float& operator()(int i, int j);
  float operator[](int i) const;
  float& operator[](int i);
  friend std::ostream& operator<<(std::ostream& stream, const Matrix& mat);
  friend std::istream& operator>>(std::istream& stream, const Matrix& mat);



 private:
  int _rows;
  int _cols;
  matrix_dims* dims;
  float * values;
};



#endif //MATRIX_H