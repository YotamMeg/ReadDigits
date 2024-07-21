#include "Matrix.h"

#include <cmath>


/**
 * construct a matrix with the given dimensions
 * @param rows number of rows
 * @param cols number of cols
 */
Matrix::Matrix (int rows, int cols)
{
  if (rows <= 0 || cols <= 0)
  {
    throw std::length_error (MATRIX_DIMS_ERROR);
  }
  values = new float [rows * cols];
  for (int i = 0; i < (rows * cols); i++)
  {
      values[i] = 0;
  }
  _rows = rows;
  _cols = cols;
  dims = new matrix_dims{rows, cols};
}

/**
 * default constructor, as instructed
 */
Matrix::Matrix ()
: Matrix(1,1)
{
}

/**
 * copy constructor
 * @param matrix the given matrix
 */
Matrix::Matrix (const Matrix& matrix)
{
  _rows = matrix._rows;
  _cols = matrix._cols;
  values = new float [_rows * _cols];
  for (int i = 0; i < _rows * _cols; i++)
  {
    this->values[i] = matrix.values[i];
  }
  dims = new matrix_dims {matrix.dims->rows, matrix.dims->cols};
}


/**
 * destructor
 */
Matrix::~Matrix ()
{
  delete[] values;
  delete dims;
}

/**
 * gets the rows
 * @return
 */
int Matrix::get_rows () const
{
  return _rows;
}

/**
 * gets the cols
 * @return
 */
int Matrix::get_cols () const
{
  return _cols;
}

/**
 * transposes the matrix
 * @return
 */
Matrix& Matrix::transpose ()
{
  Matrix tmp_mat = *this;
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      values[j * _cols + i] = values[i * _cols + j];
    }
  }
  _rows = tmp_mat._cols;
  _cols = tmp_mat._rows;
  return *this;
}

/**
 * turns the matrix into a vector
 * @return
 */
Matrix& Matrix::vectorize ()
{
  _rows = _rows * _cols;
  _cols = 1;
  dims->rows = _rows * _cols;
  dims->cols = 1;
  return *this;
}


/**
 * prints the matrix's values
 */
void Matrix::plain_print () const
{
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      std::cout << values[i * _cols + j] << " ";
    }
    std::cout << std::endl;
  }
}

/**
 * creates and returns a new matrix as instructed
 * @param mat
 * @return
 */
Matrix Matrix::dot (const Matrix &mat) const
{
  if (_rows != mat._rows || _cols != mat._cols)
  {
    throw std::length_error (MATRIX_DIMS_ERROR);
  }
  Matrix new_mat = Matrix(_rows, _cols);
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      new_mat(i,j) = values[i * _cols + j] * mat(i,j);
    }
  }
  return new_mat;
}


/**
 * returns the norm of a matrix as instructed
 * @return
 */
float Matrix::norm () const
{
  float sum = 0;
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      sum += (float) pow((values[i * _cols + j]), SQUARE);
    }
  }
  return sqrt (sum);
}

/**
 * returns the index of the largest element of the matrix
 * @return
 */
int Matrix::argmax () const
{
  float cur_max = values[0];
  int max_index = 0;
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      if (values[i * _cols + j] > cur_max)
      {
        cur_max = values[i * _cols + j];
        max_index = i * _cols + j;
      }
    }
  }
  return max_index;
}

/**
 * returns the sum of the matrix's values
 * @return
 */
float Matrix::sum () const
{
  float cur_sum = 0;
  for (int i = 0; i < _rows; i++)
  {
    for ( int j = 0; j < _cols; j++)
    {
      cur_sum += values[i * _cols + j];
    }
  }
  return cur_sum;
}

/**
 * returns a new matrix which is the sum of the current matrix and a given
 * matrix
 * @param mat the given matrix
 * @return
 */
Matrix Matrix::operator+ (const Matrix &mat) const
{
  if (_rows != mat._rows || _cols != mat._cols)
  {
    throw std::length_error (MATRIX_DIMS_ERROR);
  }
  Matrix new_mat = Matrix(_rows, _cols);
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      new_mat(i,j) = values[i * _cols + j] + mat(i, j);
    }
  }
  return new_mat;
}

/**
 * changes the matrix to match the given matrix
 * @param mat
 * @return
 */
Matrix& Matrix::operator= (const Matrix &mat)
{
  if (this != &mat)
  {
    delete[] values;
    delete dims;
    _rows = mat._rows;
    _cols = mat._cols;
    values = new float [_rows * _cols];
    dims = new matrix_dims{mat.dims->rows, mat.dims->cols};
    for (int i = 0; i < (_rows * _cols); i++)
    {
      values[i] = mat.values[i];
    }
  }
  return *this;
}

/**
 * adds the values of a given matrix to the current matrix
 * @param mat
 * @return
 */
Matrix& Matrix::operator+= (const Matrix &mat)
{
  if (_rows != mat._rows || _cols != mat._cols)
  {
    throw std::length_error (MATRIX_DIMS_ERROR);
  }
  for (int i = 0; i < _rows * _cols; i++)
  {
    values[i] += mat[i];
  }
  return *this;
}

/**
 * matrix multiply
 * @param mat
 * @return
 */
Matrix Matrix::operator* (const Matrix &mat) const
{
  if (_cols != mat._rows)
  {
    throw std::length_error (MATRIX_DIMS_ERROR);
  }
  Matrix new_mat = Matrix(_rows, mat._cols);
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < mat._cols; ++j)
    {
      float cur_sum = 0;
      for (int k = 0; k < _cols; k++)
      {
        cur_sum += values[i * _cols + k] * mat(k,j);
      }
      new_mat(i,j) = cur_sum;
    }
  }
  return new_mat;
}

/**
 * scalar multiply (on the right)
 * @param c
 * @return
 */
Matrix Matrix::operator* (float c) const
{
  Matrix new_mat = Matrix(_rows, _cols);
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      new_mat(i,j) = c * values[i * _cols + j];
    }
  }
  return new_mat;
}

/**
 * scalar multiply (on the left)
 * @param c
 * @param mat
 * @return
 */
Matrix operator*(float c, const Matrix& mat)
{
  Matrix new_mat = Matrix(mat._rows, mat._cols);
  for (int i = 0; i < mat._rows; i++)
  {
    for (int j = 0; j < mat._cols; j++)
    {
      new_mat(i,j) = mat(i,j) * c;
    }
  }
  return new_mat;
}

/**
 * returns the value at the (i,j) location
 * @param i
 * @param j
 * @return
 */
float Matrix::operator() (int i, int j) const
{
  if (i < 0 || j < 0 || i >= _rows || j >= _cols)
  {
    throw std::out_of_range (OUT_OF_RANGE_ERROR);
  }
  return values[i * _cols + j];
}

/**
 * can change the value at the (i,j) location
 * @param i
 * @param j
 * @return
 */
float& Matrix::operator() (int i, int j)
{
  if (i < 0 || j < 0 || i >= _rows || j >= _cols)
  {
    throw std::out_of_range (OUT_OF_RANGE_ERROR);
  }
  return values[i * _cols + j];
}

/**
 * returns the value at the [i] location
 * @param i
 * @return
 */
float Matrix::operator[] (int i) const
{
  if (i < 0 || i >= _rows * _cols)
  {
    throw std::out_of_range (OUT_OF_RANGE_ERROR);
  }
  return values[i];
}

/**
 * can change the value at the [i] location
 * @param i
 * @return
 */
float& Matrix::operator[] (int i)
{
  if (i < 0 || i >= _rows * _cols)
  {
    throw std::out_of_range (OUT_OF_RANGE_ERROR);
  }
  return values[i];
}

/**
 * ostream operator, prints the matrix as instructed
 * @param stream
 * @param mat
 * @return
 */
std::ostream& operator<<(std::ostream& stream, const Matrix& mat)
{
  for (int i = 1; i < mat._rows; i++)
  {
    for (int j = 0; j < mat._cols; j++)
    {
      if (mat(i,j) > PRINT_THRESHOLD)
      {
        stream << "**";
      }
      else
      {
        stream << "  ";
      }
    }
    stream << std::endl;
  }
  return stream;
}

/**
 * istream operator, reads a file into the matrix
 * @param stream
 * @param mat
 * @return
 */
std::istream& operator>>(std::istream& stream, const Matrix& mat)
{
  size_t matrix_size = mat._rows * mat._cols * sizeof (float);
  stream.seekg(0, std::ios_base::end);
  size_t stream_size = stream.tellg();
  if (stream_size < (mat._rows * mat._cols * sizeof(float )))
  {
    throw std::runtime_error(RUN_TIME_ERROR);
  }
  stream.seekg (0, std::ios::beg);
  if (!stream.read ((char*) mat.values,(long) matrix_size))
  {
    throw std::runtime_error(RUN_TIME_ERROR);
  }

  return stream;
}
