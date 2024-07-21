#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"


// Insert Dense class here...
class Dense
{
 public:
  Dense(const Matrix& weights, const Matrix& bias, activation::func
  ActivationFunction);
  Matrix get_weights() const;
  Matrix get_bias() const;
  activation::func get_activation() const;
  Matrix operator()(Matrix& x);
 private:
  Matrix _weights;
  Matrix _bias;
  activation::func _activation_func;
};

#endif //DENSE_H
