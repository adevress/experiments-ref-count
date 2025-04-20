#ifndef RC_EXPERIMENT_HPP
#define RC_EXPERIMENT_HPP

/// @brief Dummy unsafe reference counting
template <typename T, typename RC = std::uint32_t> class Durc {
  struct Impl {
    T data;
    RC counter{0};
  };

public:
  explicit Durc() : underlying_(nullptr) {}
  explicit Durc(T* data) : underlying_(create_from_ptr(data)) {}

  Durc(const Durc& other) : underlying_(other.underlying_) { inc_if_non_null(underlying_); }

  Durc(Durc&& other) : underlying_(other.underlying_) { other.underlying_ = nullptr; }

  ~Durc() { underlying_ = dec_if_non_null(underlying_); }

  Durc& operator=(const Durc& other) {
    if (this != &other) {
      this->underlying_ = other.underlying_;
      inc_if_non_null(this->underlying_);
    }
    return *this;
  }

  Durc& operator=(Durc&& other) {
    this->underlying_ = other.underlying_;
    other.underlying_ = nullptr;
    return *this;
  }

  T& operator*() const {
    assert(underlying_ != nullptr);
    return underlying_->data;
  }

  T* operator->() const {
    assert(underlying_ != nullptr);
    return &(underlying_->data);
  }

private:
  static void inc_if_non_null(Impl* impl) {
    if (impl != nullptr) {
      impl->counter += 1;
    }
  }

  static Impl* dec_if_non_null(Impl* impl) {
    if (impl != nullptr) {
      impl->counter -= 1;
      if (impl->counter == 0) {
        delete impl;
        impl = nullptr;
      }
    }
    return impl;
  }

  static Impl* create_from_ptr(T* d) {
    Impl* impl = new Impl{// accept one move or one copy here if constructed from
                          // an existing pointer. Irrelevant for benchmarks
                          .data = std::move(*d),
                          .counter = 1};
    return impl;
  }

  Impl* underlying_;
};

#endif