#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#define VECTOR_SIZE 4
#define MATRIX_ROWS 4
#define MATRIX_COLS 4

//=======================================================

class Vector
{
private:
  double v[VECTOR_SIZE];

public:
  void Set(int index, double value);
  double Get(int index) const;
};

void Vector::Set(int index, double value) {
  if (index < VECTOR_SIZE){
    v[index] = value;
  }
}

double Vector::Get(int index) const{
  if (index < VECTOR_SIZE){
    return v[index];
  }
}

//=======================================================

class Matrix
{
private:
  double m[MATRIX_ROWS][MATRIX_COLS];
public:
  void Set(int row, int col, double value);
  double Get(int row, int col) const;
};

void Matrix::Set(int row, int col, double value){
  if (row < MATRIX_ROWS and col < MATRIX_COLS and row >= 0 and col >= 0) {
      m[row][col] = value;
  }
}

double Matrix::Get(int row, int col) const{
  if (row < MATRIX_ROWS and col < MATRIX_COLS){
    return m[row][col];
  }
}
//=======================================================

Vector Multiply(const Matrix &m, const Vector &v) {
  Vector result;
  for (int i = 0; i < MATRIX_ROWS; i++){
    double res = 0.0;
    for (int j = 0; j < MATRIX_COLS; j++){
      res += m.Get(i,j) * v.Get(j);
    }
    result.Set(i, res);
  }
  return result;
}


int main()
{
  string vector_file, matrix_file, result_file;
  double tmp;
  Vector v;
  Matrix m;

  // Reading the vector file
  cout << "Enter vector filename: ";
  cin >> vector_file;

  // Reading the matrix file
  cout << "Enter matrix filename: ";
  cin >> matrix_file;

  // File for the results
  cout << "Enter result filename: ";
  cin >> result_file;

  cout << endl;

  // Open the files
  ifstream myfile;
  myfile.open (vector_file);
  if (!myfile.is_open ()){
     cout << "Unable to open vector file." << endl;
  }
  else {
    for(int i =0; i<4; i++){
      if (!(myfile >> tmp)){
    cout << "Unable to read vector file." << endl;
    break;
      }
      else
    v.Set(i, tmp);
    }
    
    cout << "File " << vector_file << " has the following values:" << endl
     << v.Get(0) << endl
     << v.Get(1) << endl
     << v.Get(2) << endl
     << v.Get(3) << endl << endl;

    myfile.close();
  }

 
  myfile.open(matrix_file);
  if (!myfile.is_open()){
    cout << "Unable to open matrix file." << endl;
  }
  else{
    for (int i = 0; i<16; i++){
      if(!(myfile >> tmp)){
    cout << "Unable to read matrix file." << endl;
    break;
      }
      else
    m.Set(i%4, i/4, tmp);
      
    }
    cout << "File " <<matrix_file << ", row 1 has the following values:" << endl
     << m.Get(0,0) << " " << m.Get(0,1) << " " << m.Get(0,2) << " " << m.Get(0,3) << endl << endl;
    myfile.close();
  }

  // multipy m and v
  Vector vv = Multiply(m, v);

  ofstream resultf;
  resultf.open (result_file);
  resultf << vv.Get(0) << " " << vv.Get(1) << " " << vv.Get(2) << " " << vv.Get(3) << endl;
  resultf.close();
 
 
  return 1;
}
