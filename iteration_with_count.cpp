#include <algorithm>
#include <iostream>

namespace corp_namespace {
// This is the best class ever!
// Do not dare to modify it!!!
class SuperTextContainer {
  std::string text_;
public:
  SuperTextContainer(std::string t):
    text_{std::move(t)} {}
  char* First()             { return &text_.front(); }
  const char* First() const { return &text_.front(); }
  char* Last()              { return &text_.back(); }
  const char* Last() const  { return &text_.back(); }
};

inline char* begin(SuperTextContainer& stc) {
  return stc.First();
}

inline const char* begin(const SuperTextContainer& stc) {
  return stc.First();
}

inline char* end(SuperTextContainer& stc) {
  return stc.Last() + 1;
}

inline const char* end(const SuperTextContainer& stc) {
  return stc.Last() + 1;
}

}

void print(const corp_namespace::SuperTextContainer& txt)
{
  for(auto it=txt.First(); it!=txt.Last() + 1; ++it)
    std::cout << *it;
  std::cout << '\n';
}

void smart_print(const corp_namespace::SuperTextContainer& txt)
{
  for(char c : txt)
    std::cout << c;
  std::cout << '\n';
}

template<typename Container>
void count_a(const Container& txt) {
  using std::begin;
  using std::end;
  std::cout << "Count: " << std::count(begin(txt), end(txt), 'a') << '\n';
}

int main() {
  corp_namespace::SuperTextContainer txt{"I hate this class"};
  count_a(txt);
  count_a ("I love standard library interface");
}