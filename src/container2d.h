#pragma once

#include <cstddef>
#include <vector>

template <typename T>
class Container2d {
public:
    Container2d(size_t rows, size_t cols) : cols_(cols), data_(rows * cols) {
    }

    T& operator()(size_t i, size_t j) {
        return data_[i * cols_ + j];
    }
    const T& operator()(size_t i, size_t j) const {
        return data_[i * cols_ + j];
    }
    size_t rows() const {
        return data_.size() / cols_;
    }
    size_t cols() const {
        return cols_;
    }

private:
    size_t cols_;
    std::vector<T> data_;
};
