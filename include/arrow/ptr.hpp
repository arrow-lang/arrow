// Copyright © 2014-2016 Ryan Leckey, All Rights Reserved.

// Distributed under the MIT License
// See accompanying file LICENSE

#ifndef ARROW_PTR_H
#define ARROW_PTR_H

#include <memory>

namespace arrow {

template <typename T>
using ptr = std::shared_ptr<T>;

template <typename T, typename... Args>
inline ptr<T> make(Args&&... args) {
  return std::make_shared<T>(args...);
}

template <typename T, typename U>
inline ptr<T> cast(const ptr<U>& p) {
  return std::dynamic_pointer_cast<T>(p);
}

}  // namespace arrow

#endif  // ARROW_PTR_H
