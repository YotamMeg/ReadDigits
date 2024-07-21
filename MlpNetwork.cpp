#include "MlpNetwork.h"

/**
 * constructs MlpNetwork object, initializes the 4 layers
 * @param weights array of 4 matrix
 * @param biases array of 4 matrix
 */
MlpNetwork::MlpNetwork (Matrix weights[], Matrix biases[]) :
r1 (weights[0], biases[0], activation::relu),
r2 (weights[1], biases[1], activation::relu),
r3 (weights[2], biases[2], activation::relu),
r4 (weights[3], biases[3], activation::softmax)

{
}

/**
 * receives a matrix, and preforms the layers' operation on it, each layer's
 * output is the next layer's inout
 * @param x the input matrix
 * @return a struct containing the estimated digit and the estimated
 * probability.
 */
digit MlpNetwork::operator() (const Matrix &x)
{
  Matrix new_mat = Matrix(x);
  new_mat.vectorize();
  new_mat = r1(new_mat);
  new_mat = r2(new_mat);
  new_mat = r3(new_mat);
  new_mat = r4(new_mat);
  unsigned int value = new_mat.argmax();
  float prob = new_mat[(int) value];
  return digit {value, prob};
}