#ifndef MY_MATRIX_H_ON_CPP_MY_MATRIX_OOP_H_
#define MY_MATRIX_H_ON_CPP_MY_MATRIX_OOP_H_

class MyMatrix {
 public:
  MyMatrix();
  MyMatrix(int rows, int cols);
  MyMatrix(const MyMatrix& other);
  MyMatrix(MyMatrix&& other) noexcept;
  ~MyMatrix();

  MyMatrix operator+(const MyMatrix& other);
  MyMatrix operator-(const MyMatrix& other);
  MyMatrix operator*(const MyMatrix& other);
  MyMatrix operator*(const double num);
  bool operator==(const MyMatrix& other);
  MyMatrix& operator=(const MyMatrix& other);
  MyMatrix& operator=(MyMatrix&& other) noexcept;
  MyMatrix& operator+=(const MyMatrix& other);
  MyMatrix& operator-=(const MyMatrix& other);
  MyMatrix& operator*=(const MyMatrix& other);
  MyMatrix& operator*=(const double num);
  double operator()(int i, int j) const;
  double& operator()(int i, int j);

  int get_rows() const;
  int get_cols() const;
  void set_rows(int rows);
  void set_cols(int cols);

  bool EqMatrix(const MyMatrix& other);
  void SumMatrix(const MyMatrix& other);
  void SubMatrix(const MyMatrix& other);
  void MulNumber(const double num);
  void MulMatrix(const MyMatrix& other);
  MyMatrix Transpose();
  MyMatrix CalcComplements();
  double Determinant();
  MyMatrix InverseMatrix();

 private:
  int rows_ = 0, cols_ = 0;
  double** matrix_ = nullptr;
  void RemoveMatrix();
  void NullifyMatrix();
  void AllocateMemory();
  void CopyMatrix(const MyMatrix& other);
  void PassValues(const MyMatrix& other);
  MyMatrix Minor(int row, int col);
};

#endif  // MY_MATRIX_H_ON_CPP_MY_MATRIX_OOP_H_