#ifndef UTILITY_H_
#define UTILITY_H_

#include <types.h>

#ifndef __cplusplus
#error Trying to include C++ header in non-C++ code
#endif

namespace pp {

  template <typename T>
  struct remove_reference { using type = T; };

  template <typename T>
  struct remove_reference<T&> { using type = T; };

  template <typename T>
  struct remove_reference<T&&> { using type = T; };

  template <typename T>
  using remove_reference_t = typename remove_reference<T>::type;

  template <typename T>
  T &&forward(remove_reference_t<T> &t) { return t; }

  template <typename T>
  T &&forward(remove_reference_t<T> &&t) { return t; }

}

#endif // UTILITY_H_
