

#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"
// Insert Activation class here...

namespace activation
{
    Matrix relu(const Matrix& mat);
    Matrix softmax(const Matrix& mat);
    typedef Matrix (*func)(const Matrix&mat);
}


#endif //ACTIVATION_H