#include <algorithm>
#include <iostream>

class my_string {
  char* buf_{};

  using traits = std::char_traits<char>;

public:
  constexpr my_string() = default;

  my_string(const char* text) : buf_(nullptr) {
    if (text) {
      size_t size = strlen(text) + 1;
      buf_ = new char[size];
      traits::copy(buf_, text, size);
    }
  }

  my_string(const my_string& other) :
      my_string(other.buf_) {}

  my_string(my_string&& other) noexcept : buf_() {
    swap(*this, other);
  }

  ~my_string() {
    delete buf_;
  }

  my_string& operator=(my_string&& other) noexcept {
    swap(*this, s);
    return *this;
  }

  my_string& operator=(const my_string& other) {
    my_string copy(other);
    swap(buf_, copy.buf_);
    return *this;
  }

  [[nodiscard]] const char* c_str() { return buf_; }

  friend void swap(my_string& lhs, my_string& rhs) noexcept {
    std::swap(lhs.buf_, rhs.buf_);
  }
};

int main() {
  my_string my_str;
}
