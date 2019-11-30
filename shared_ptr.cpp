template<typename Pointer>
class state_base : noncopyable {
public:
  virtual void release_ptr(Ptr ptr) noexcept = 0;
  virtual ~state_base() = default;
};

template<typename Ptr, typename Deleter>
class state final : public state_base<Ptr>, ebo_helper<Deleter> {
  using DeleterBase = ebo_helper<Deleter>;
  Deleter& deleter() { return DeleterBase::get(); }

public:
  explicit state(Deleter&& d = Deleter{}) noexcept :
      DeleterBase(std::move(d)) {}

  explicit state(const Deleter& deleter) noexcept :
      DeleterBase(deleter) {}

  void release_ptr(Ptr ptr) noexcept override {
    deleter()(ptr);
  }
};

template<typename T>
class smart_ptr {
public:
  template<typename Deleter>
  smart_ptr(pointer ptr, Deleter&& d) :
      ptr_{ptr},
      state_(new state<pointer, Deleter>(std::forward<Deleter>(d))) {}
      catch(...) {
        d(ptr);
        throw;
      }

  ~smart_ptr()

private:
  pointer ptr_{};
  std::unique_ptr<state_base<pointer>> state_;
};
