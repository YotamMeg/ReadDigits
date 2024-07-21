#include "Dense.h"


/**
 * constructor
 * @param weights array of matrix
 * @param bias array of matrix
 * @param ActivationFunction pointer to activation function
 */
Dense::Dense (const Matrix &weights, const Matrix &bias, activation::func
ActivationFunction)
{
  _weights = weights;
  _bias = bias;
  _activation_func = ActivationFunction;
}

/**
 * gets the weights
 * @return
 */
Matrix Dense::get_weights () const
{
  return _weights;
}

/**
 * gets the biases
 * @return
 */
Matrix Dense::get_bias () const
{
  return _bias;
}

/**
 * gets the function
 * @return
 */
activation::func Dense::get_activation () const
{
  return _activation_func;
}

/**
 * receives a matrix and preforms the function as instructed
 * @param x the given matrix
 * @return the function's output (matrix)
 */
Matrix Dense::operator() (Matrix& x)
{
  return _activation_func(_weights * x + _bias);
}
