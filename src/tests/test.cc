#include "test.h"

TEST(TestConstructor, DefaultConstructor) {
  MyMatrix matrix;
  EXPECT_EQ(matrix.get_rows(), 0);
  EXPECT_EQ(matrix.get_cols(), 0);
}

TEST(TestConstructor, ParametrizedConstructor) {
  MyMatrix matrix(5, 5);
  EXPECT_EQ(matrix.get_rows(), 5);
  EXPECT_EQ(matrix.get_cols(), 5);
  for (int i = 0; i < matrix.get_rows(); ++i)
    for (int j = 0; j < matrix.get_cols(); ++j) EXPECT_EQ(matrix(i, j), 0);
}

TEST(TestConstructor, ParametrizedConstructorThrow) {
  EXPECT_THROW(MyMatrix matrix(-1, 5), std::out_of_range);
}

TEST(TestConstructor, CopyConstructor) {
  MyMatrix matrix1(5, 5);
  MyMatrix matrix2(matrix1);
  EXPECT_EQ(matrix1.get_rows(), matrix2.get_rows());
  EXPECT_EQ(matrix1.get_cols(), matrix2.get_cols());
  for (int i = 0; i < matrix1.get_rows(); ++i)
    for (int j = 0; j < matrix1.get_cols(); ++j)
      EXPECT_EQ(matrix1(i, j), matrix2(i, j));
}

TEST(TestConstructor, MoveConstructor) {
  int rows = 5, cols = 5;
  MyMatrix matrix1(rows, cols);
  MyMatrix matrix2(std::move(matrix1));
  EXPECT_EQ(matrix1.get_rows(), 0);
  EXPECT_EQ(matrix1.get_cols(), 0);
  EXPECT_EQ(matrix2.get_rows(), rows);
  EXPECT_EQ(matrix2.get_cols(), cols);
}

TEST(TestPrivateAccess, Getters) {
  int rows = 5, cols = 5;
  MyMatrix matrix(rows, cols);
  EXPECT_EQ(matrix.get_rows(), rows);
  EXPECT_EQ(matrix.get_cols(), cols);
}

TEST(TestPrivateAccess, Mutators) {
  int rows = 5, cols = 5;
  MyMatrix matrix(rows, cols);
  matrix.set_rows(10);
  matrix.set_cols(2);
  EXPECT_NE(matrix.get_rows(), rows);
  EXPECT_NE(matrix.get_cols(), cols);
}

TEST(MatrixOperations, EqMatrix) {
  for (int i = 0; i < 5; ++i) {
    MyMatrix matrix1(3, 3);
    setMatrix(&matrix1, kVal1[i]);
    MyMatrix matrix2(3, 3);
    setMatrix(&matrix2, kVal2[i]);
    EXPECT_EQ(matrix1.EqMatrix(matrix2), kCompareResults[i]);
  }
}

TEST(MatrixOperations, EqualThis) {
  MyMatrix test(1, 1);
  EXPECT_EQ(test.EqMatrix(test), true);
}

TEST(MatrixOperations, SumMatrix) {
  for (int i = 0; i < 5; ++i) {
    MyMatrix matrix1(3, 3);
    setMatrix(&matrix1, kVal1[i]);
    MyMatrix matrix2(3, 3);
    setMatrix(&matrix2, kVal2[i]);
    matrix1.SumMatrix(matrix2);
    compareMatrix(matrix1, kSumResult[i]);
  }
}

TEST(TestConstructor, SumMatrixThrow) {
  MyMatrix matrix1(2, 3);
  MyMatrix matrix2(3, 2);
  EXPECT_THROW(matrix1.SumMatrix(matrix2), std::out_of_range);
}

TEST(MatrixOperations, SubMatrix) {
  for (int i = 0; i < 5; ++i) {
    MyMatrix matrix1(3, 3);
    setMatrix(&matrix1, kVal1[i]);
    MyMatrix matrix2(3, 3);
    setMatrix(&matrix2, kVal2[i]);
    matrix1.SubMatrix(matrix2);
    compareMatrix(matrix1, kSubResult[i]);
  }
}

TEST(TestConstructor, SubMatrixThrow) {
  MyMatrix matrix1(2, 3);
  MyMatrix matrix2(3, 2);
  EXPECT_THROW(matrix1.SubMatrix(matrix2), std::out_of_range);
}

TEST(MatrixOperations, MulNumber) {
  for (int i = 0; i < 5; ++i) {
    MyMatrix matrix1(3, 3);
    setMatrix(&matrix1, kVal1[i]);
    matrix1.MulNumber(kNumberToMulBy[i]);
    compareMatrix(matrix1, kMulNumberResult[i]);
  }
}

TEST(MatrixOperations, MulMatrix) {
  for (int i = 0; i < 5; ++i) {
    MyMatrix matrix1(3, 3);
    setMatrix(&matrix1, kVal1[i]);
    MyMatrix matrix2(3, 3);
    setMatrix(&matrix2, kVal2[i]);
    matrix1.MulMatrix(matrix2);
    compareMatrix(matrix1, kMulMatrixResult[i]);
  }
}

TEST(TestConstructor, MulMatrixThrow) {
  MyMatrix matrix1(2, 2);
  MyMatrix matrix2(3, 2);
  EXPECT_THROW(matrix1.MulMatrix(matrix2), std::out_of_range);
}

TEST(MatrixOperations, Transpose) {
  for (int i = 0; i < 5; ++i) {
    MyMatrix matrix(3, 3);
    setMatrix(&matrix, kVal1[i]);
    matrix = matrix.Transpose();
    compareMatrix(matrix, kTransposeResults[i]);
  }
}

TEST(MatrixOperations, CalcComplements) {
  for (int i = 0; i < 5; ++i) {
    MyMatrix matrix(3, 3);
    setMatrix(&matrix, kVal1[i]);
    matrix = matrix.CalcComplements();
    compareMatrix(matrix, kCalcComplementsResults[i]);
  }
}

TEST(TestConstructor, CalcComplements1X1) {
  MyMatrix matrix(1, 1);
  EXPECT_THROW(matrix.CalcComplements(), std::out_of_range);
}

TEST(TestConstructor, CalcComplementsThrow) {
  MyMatrix matrix(2, 3);
  EXPECT_THROW(matrix.CalcComplements(), std::out_of_range);
}

TEST(MatrixOperations, Determinant) {
  for (int i = 0; i < 5; ++i) {
    MyMatrix matrix(3, 3);
    setMatrix(&matrix, kVal1[i]);
    EXPECT_NEAR(matrix.Determinant(), kDeterminantResult[i], 1E-5);
  }
}

TEST(TestConstructor, Determinant1X1) {
  double element = 21.21;
  MyMatrix matrix(1, 1);
  matrix(0, 0) = element;
  EXPECT_NEAR(matrix.Determinant(), element, 1E-5);
}

TEST(TestConstructor, DeterminantThrow) {
  MyMatrix matrix(2, 3);
  EXPECT_THROW(matrix.Determinant(), std::out_of_range);
}

TEST(MatrixOperations, InverseMatrix) {
  for (int i = 0; i < 5; ++i) {
    MyMatrix matrix(3, 3);
    setMatrix(&matrix, kVal1[i]);
    if (i == 1) {
      EXPECT_THROW(matrix.InverseMatrix(), std::out_of_range);
    } else {
      matrix = matrix.InverseMatrix();
      compareMatrix(matrix, kInverseResults[i]);
    }
  }
}

TEST(TestConstructor, InverseMatrix1X1) {
  double element = 21.21;
  MyMatrix matrix(1, 1);
  matrix(0, 0) = element;
  EXPECT_NEAR(matrix.InverseMatrix()(0, 0), 0.0471475719, 1E-5);
}

TEST(MatrixOperators, Addition) {
  for (int i = 0; i < 5; ++i) {
    MyMatrix matrix1(3, 3);
    setMatrix(&matrix1, kVal1[i]);
    MyMatrix matrix2(3, 3);
    setMatrix(&matrix2, kVal2[i]);
    matrix1 = matrix1 + matrix2;
    compareMatrix(matrix1, kSumResult[i]);
  }
}

TEST(MatrixOperators, Subtraction) {
  for (int i = 0; i < 5; ++i) {
    MyMatrix matrix1(3, 3);
    setMatrix(&matrix1, kVal1[i]);
    MyMatrix matrix2(3, 3);
    setMatrix(&matrix2, kVal2[i]);
    matrix1 = matrix1 - matrix2;
    compareMatrix(matrix1, kSubResult[i]);
  }
}

TEST(MatrixOperators, MultiplicationByNumber) {
  for (int i = 0; i < 5; ++i) {
    MyMatrix matrix1(3, 3);
    setMatrix(&matrix1, kVal1[i]);
    matrix1 = matrix1 * kNumberToMulBy[i];
    compareMatrix(matrix1, kMulNumberResult[i]);
  }
}

TEST(MatrixOperators, MultiplicationOfMatrices) {
  for (int i = 0; i < 5; ++i) {
    MyMatrix matrix1(3, 3);
    setMatrix(&matrix1, kVal1[i]);
    MyMatrix matrix2(3, 3);
    setMatrix(&matrix2, kVal2[i]);
    matrix1 = matrix1 * matrix2;
    compareMatrix(matrix1, kMulMatrixResult[i]);
  }
}

TEST(MatrixOperators, Comparing) {
  for (int i = 0; i < 5; ++i) {
    MyMatrix matrix1(3, 3);
    setMatrix(&matrix1, kVal1[i]);
    MyMatrix matrix2(3, 3);
    setMatrix(&matrix2, kVal2[i]);
    EXPECT_EQ(matrix1 == matrix2, kCompareResults[i]);
  }
}

TEST(MatrixOperators, Assignment) {
  int rows = 3, cols = 2;
  MyMatrix matrix1(rows, cols);
  MyMatrix matrix2(4, 4);
  matrix1 = matrix2;
  EXPECT_EQ(matrix1.get_rows(), matrix2.get_rows());
  EXPECT_EQ(matrix1.get_cols(), matrix2.get_cols());
  EXPECT_NE(matrix1.get_rows(), rows);
  EXPECT_NE(matrix1.get_cols(), cols);
}

TEST(MatrixOperators, AdditionAssignment) {
  for (int i = 0; i < 5; ++i) {
    MyMatrix matrix1(3, 3);
    setMatrix(&matrix1, kVal1[i]);
    MyMatrix matrix2(3, 3);
    setMatrix(&matrix2, kVal2[i]);
    matrix1 += matrix2;
    compareMatrix(matrix1, kSumResult[i]);
  }
}

TEST(MatrixOperators, SubtractionAssignment) {
  for (int i = 0; i < 5; ++i) {
    MyMatrix matrix1(3, 3);
    setMatrix(&matrix1, kVal1[i]);
    MyMatrix matrix2(3, 3);
    setMatrix(&matrix2, kVal2[i]);
    matrix1 -= matrix2;
    compareMatrix(matrix1, kSubResult[i]);
  }
}

TEST(MatrixOperators, MultiplicationByNumberAssignment) {
  for (int i = 0; i < 5; ++i) {
    MyMatrix matrix1(3, 3);
    setMatrix(&matrix1, kVal1[i]);
    matrix1 *= kNumberToMulBy[i];
    compareMatrix(matrix1, kMulNumberResult[i]);
  }
}

TEST(MatrixOperators, MultiplicationOfMatricesAssignment) {
  for (int i = 0; i < 5; ++i) {
    MyMatrix matrix1(3, 3);
    setMatrix(&matrix1, kVal1[i]);
    MyMatrix matrix2(3, 3);
    setMatrix(&matrix2, kVal2[i]);
    matrix1 *= matrix2;
    compareMatrix(matrix1, kMulMatrixResult[i]);
  }
}

TEST(MatrixOperators, IndexAccess) {
  MyMatrix matrix;
  EXPECT_THROW(matrix(1, 1), std::out_of_range);
}

TEST(MatrixOperators, ConstIndexAccess) {
  const MyMatrix matrix(4, 4);
  EXPECT_EQ(matrix(2, 2), 0);
  EXPECT_THROW(matrix(5, 5), std::out_of_range);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

void setMatrix(MyMatrix* matrix, double expected[3][3]) {
  for (int i = 0; i < matrix->get_rows(); ++i) {
    for (int j = 0; j < matrix->get_cols(); ++j) {
      matrix->operator()(i, j) = expected[i][j];
    }
  }
}

void compareMatrix(MyMatrix matrix, double expected[3][3]) {
  for (int i = 0; i < matrix.get_rows(); ++i)
    for (int j = 0; j < matrix.get_cols(); ++j)
      EXPECT_NEAR(matrix(i, j), expected[i][j], 1E-5);
}