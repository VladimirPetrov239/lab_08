#include "matrix.hpp"
#include <fstream>
#include <algorithm>
#include <cstring>
#include <iostream>


bool Matrix::check_sizes(const Matrix& m1, const Matrix& m2) {
    return (m1._rows == m2._rows) && (m1._cols == m2._cols);
}

Matrix::Matrix(std::size_t r, std::size_t c) {
    _rows = r;
    _cols = c;
    _data = new int*[_rows];
    if(_rows > 0) {
        _data[0] = new int[_rows * _cols];
        for(int i = 1; i < _rows; i ++) {
            _data[i] = _data[0] + (_cols) * i;
        }
        memset(_data[0], 0, _cols * _rows * sizeof(int));
    }
}

//creates matrix with _data addressed to given arr
Matrix::Matrix(std::size_t r, std::size_t c, int** arr) {
    _rows = r;
    _cols = c;
    _data = arr;
}

Matrix::Matrix(const Matrix& oth) {
    _rows = oth._rows;
    _cols = oth._cols;
    _data = new int*[_rows];
    if(_rows > 0) {
        _data[0] = new int[_rows * _cols];
        for(int i = 1; i < _rows; i ++) {
            _data[i] = _data[0] + (_cols) * i;
        }
        memcpy(_data[0], oth._data[0], _cols * _rows * sizeof(int));
    }
}

std::size_t Matrix::get_rows() { return _rows; }
std::size_t Matrix::get_cols() { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) {
    return _data[i][j];
}

void Matrix::swap(Matrix& oth) {
    std::swap(_rows, oth._rows);
    std::swap(_cols, oth._cols);
    std::swap(_data, oth._data);
}

void Matrix::print(FILE* f) {
    for(int i = 0; i < _rows; i++) {
        for(int j = 0; j < _cols; j++) {
            fprintf(f, "%d ", _data[i][j]);
        }
        fprintf(f, "\n");
    }
}

bool Matrix::operator==(const Matrix& m) {
    if(!check_sizes(*this, m))
        return false;
    for(int i = 0; i < _rows; i++) {
        for(int j = 0; j < _cols; j++) {
            if(_data[i][j] != m._data[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& m) {
    return !operator==(m);
}

Matrix& Matrix::operator=(const Matrix& m) {
    if (this == &m)
        return *this;

    Matrix(m).swap(*this);
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& m) {
    for(int i = 0; i < _rows; i ++) {
        for(int j = 0; j < _cols; j++) {
            _data[i][j] += m._data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
    for(int i = 0; i < _rows; i ++) {
        for(int j = 0; j < _cols; j++) {
            _data[i][j] -= m._data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
    int** res_array = multiply_array(*this, m);
    Matrix multiply = Matrix(_rows, m._cols, res_array);
    multiply.swap(*this);
    return *this;
}

int** Matrix::multiply_array(const Matrix& m1, const Matrix& m2) {
    int** res = new int*[m1._rows];
    if(m1._rows > 0) {
        res[0] = new int[m1._rows * m2._cols];
        for (int i = 0; i < m1._rows; i++) {
            if(i > 0) {
                res[i] = res[0] + (m2._cols) * i;
            }
            for (int j = 0; j < m2._cols; j++) {
                res[i][j] = 0;
                for(int pos = 0; pos < m1._cols; pos++) {
                    res[i][j] += m1._data[i][pos] * m2._data[pos][j];
                }
            }
        }
    }
    return res;
}

Matrix Matrix::operator+(const Matrix& m) {
    return Matrix(*this) += m;
}

Matrix Matrix::operator-(const Matrix& m) {
    return Matrix(*this) -= m;
}

Matrix Matrix::operator*(const Matrix& m) {
    return Matrix(*this) *= m;
}


