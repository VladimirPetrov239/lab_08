#include "shared_ptr.hpp"
#include "algorithm"


shared_ptr::shared_ptr(Matrix* obj) {
    if (obj) {
        storage_ = new Storage(obj);
    } else {
        storage_ = nullptr;
    }
}

shared_ptr::shared_ptr(const shared_ptr& other) {
    storage_ = other.storage_;
    if(other.storage_) {
        storage_->incr();
    }
}

shared_ptr& shared_ptr::operator=(shared_ptr other) {
    if(this == &other)
        return *this;

    std::swap(storage_, other.storage_);
    return *this;
}

void shared_ptr::cleanData() {
    if(storage_) {
        storage_->decr();
        if(storage_->getCounter() == 0) {
            delete storage_;
        }
    }
}

shared_ptr::~shared_ptr() {
    cleanData();
}

Matrix* shared_ptr::ptr() const{
    if(storage_) {
        return storage_->getObject();
    } else {
        return nullptr;
    }
}

bool shared_ptr::isNull() const {
    return (ptr() == nullptr);
}

void shared_ptr::reset(Matrix* obj) {
    cleanData();
    if (obj) {
        storage_ = new Storage(obj);
    } else {
        storage_ = nullptr;
    }
}

Matrix* shared_ptr::operator->() const {
    return ptr();
}

Matrix& shared_ptr::operator*() const {
    return *ptr();
}

shared_ptr::Storage::Storage(Matrix* mtx) {
    data_ = mtx;
    ref_count_ = 1;
}

shared_ptr::Storage::~Storage() {
    if(data_) {
        delete data_;
    }
}

void shared_ptr::Storage::incr() {
    ref_count_++;
}

void shared_ptr::Storage::decr() {
    ref_count_--;
}

int shared_ptr::Storage::getCounter() const {
    return ref_count_;
}

Matrix* shared_ptr::Storage::getObject() const {
    return data_;
}

