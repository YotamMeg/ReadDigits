#include "Activation.h"

/**
 * receives a matrix and creates a new matrix with only non-negative values.
 * @param mat the input matrix
 * @return the created matrix
 */
Matrix activation::relu (const Matrix &mat)
{
  Matrix new_mat = mat;
  for (int j = 0; j < mat.get_cols(); j++)
  {
    for (int i = 0; i < mat.get_rows (); i++)
    {
      if (mat(i,j) < 0)
      {
        new_mat(i,j) = 0;
      }
    }
  }
  return new_mat;
}

/**
 * receives a matrix and creates a matrix according to the instructions
 * @param mat the input matrix
 * @return the created matrix
 */
Matrix activation::softmax (const Matrix &mat)
{
  Matrix new_mat = mat;
  float cur_sum = 0;
  for (int k = 0; k < mat.get_rows() * mat.get_cols(); k++)
  {
    new_mat[k] = std::exp (mat[k]);
    cur_sum += std::exp (mat[k]);
  }
  return ((1 /cur_sum) * new_mat);
}
