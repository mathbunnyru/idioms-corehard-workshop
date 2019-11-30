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
}
void print(const corp_namespace::SuperTextContainer& txt)
{
  for(auto it=txt.First(); it!=txt.Last() + 1; ++it)
    std::cout << *it;
  std::cout << '\n';
}
corp_namespace::SuperTextContainer t{"I hate this class"};
print(t);