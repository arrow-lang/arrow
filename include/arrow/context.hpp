// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_CONTEXT_H
#define ARROW_CONTEXT_H

#include <memory>
#include <stack>

namespace arrow {

template <typename T>
class Context {
 public:
  class Block {
   public:
    Block(Context& ctx) : _exited(false), _ctx(ctx) {
    }

    ~Block() noexcept {
      exit();
    }

    void exit() noexcept {
      if (!_exited) {
        _ctx._s.pop();
        _exited = true;
      }
    }

   private:
    bool _exited;
    Context& _ctx;
  };

  Context() : _s() {
  }

  ~Context() noexcept {
  }

  std::unique_ptr<Block> enter(T value) {
    _s.push(value);

    return std::make_unique<Block>(*this);
  }

  bool empty() const {
    return _s.empty();
  }

  T const& top() const {
    return _s.top();
  }

 private:
  friend class Block;

  std::stack<T> _s;

};

}  // namespace arrow

#endif  // ARROW_CONTEXT_H
