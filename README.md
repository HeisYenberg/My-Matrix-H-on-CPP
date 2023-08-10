# My-Matrix-H-on-CPP

## My version of the my_matrix_oop.h library in the C programming language.

## Usage :

- To build a library run `make my_matrix_oop.a`
- To see tests run `make test`, might need to install `check`
- To see tests code coverage run `make gcov_report`, might need to install `lcov`

### Overview of "my_matrix_oop.h" functions

### Constructors :

| No. | Constructor                        | Description                                                                |
|-----|------------------------------------|----------------------------------------------------------------------------|
| 1   | `MyMatrix()`                       | A basic constructor that initialises a matrix of some predefined dimension |
| 2   | `MyMatrix(int rows, int cols)`     | Parametrized constructor with number of rows and columns                   |
| 3   | `MyMatrix(const MyMatrix& other)`  | Copy constructor                                                           |
| 4   | `MyMatrix(const MyMatrix&& other)` | Move constructor                                                           |
| 5   | `~MyMatrix()  `                    | Destructor                                                                 |

### Overloaded operators :

| Operator         | Description                                                                  | Exceptional situations                                                                           |
|------------------|------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------|
| `+`              | Addition of two matrices                                                     | Different matrix dimensions                                                                      |
| `-`              | Subtraction of one matrix from another                                       | Different matrix dimensions                                                                      |
| `*`              | Matrix multiplication and matrix multiplication by a number                  | The number of columns of the first matrix does not equal the number of rows of the second matrix |
| `==`             | Checks for matrices equality (`EqMatrix`)                                    |                                                                                                  |
| `=`              | Assignment of values from one matrix to another one (copy operator and move) |                                                                                                  |
| `+=`             | Addition assignment (`SumMatrix`)                                            | Different matrix dimensions                                                                      |
| `-=`             | Difference assignment (`SubMatrix`)                                          | Different matrix dimensions                                                                      |
| `*=`             | Multiplication assignment (`MulMatrix`/`MulNumber`)                          | The number of columns of the first matrix does not equal the number of rows of the second matrix |
| `(int i, int j)` | Indexation by matrix elements (row, column)                                  | Index is outside the matrix                                                                      |

### Matrix operations :

| Operation                                | Description                                                                                                                                              | Exceptional situations                                                                            |
|------------------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------|
| get_rows()                               | Get the amount of rows from a class                                                                                                                      |                                                                                                   |
| get_cols()                               | Get the amount of cols from a class                                                                                                                      |                                                                                                   |
| set_rows()                               | Set the amount of rows from a class.  If the matrix increases in size, it is filled with zeros. If it decreases in size, the excess is simply discarded. |                                                                                                   |
| set_cols()                               | Set the amount of rows from a class.  If the matrix increases in size, it is filled with zeros. If it decreases in size, the excess is simply discarded. |                                                                                                   |
| `bool EqMatrix(const S21Matrix& other)`  | Checks matrices for equality with each other                                                                                                             |                                                                                                   |
| `void SumMatrix(const S21Matrix& other)` | Adds the second matrix to the current one                                                                                                                | different matrix dimensions                                                                       |
| `void SubMatrix(const S21Matrix& other)` | Subtracts another matrix from the current one                                                                                                            | different matrix dimensions                                                                       |
| `void MulNumber(const double num) `      | Multiplies the current matrix by a number                                                                                                                |                                                                                                   |
| `void MulMatrix(const S21Matrix& other)` | Multiplies the current matrix by the second matrix                                                                                                       | the number of columns of the first matrix is not equal to the number of rows of the second matrix |
| `MyMatrix Transpose()`                   | Creates a new transposed matrix from the current one and returns it                                                                                      |                                                                                                   |
| `MyMatrix CalcComplements()`             | Calculates the algebraic addition matrix of the current one and returns it                                                                               | the matrix is not square                                                                          |
| `double Determinant()`                   | Calculates and returns the determinant of the current matrix                                                                                             | the matrix is not square                                                                          |
| `MyMatrix InverseMatrix()`               | Calculates and returns the inverse matrix                                                                                                                | matrix determinant is 0                                                                           |