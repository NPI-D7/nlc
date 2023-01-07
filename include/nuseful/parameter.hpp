#pragma once
#include <tuple>

namespace nlc {
/**
 * @brief A parameter that can take any type
 */
class parameter {
private:
  using id = size_t;

  template <typename T> struct type {
    static void id() {}
  };

  template <typename T> static id type_id() {
    return reinterpret_cast<id>(&type<T>::id);
  }

  template <typename T> using decay = typename std::decay<T>::type;

  template <typename T>
  using none =
      typename std::enable_if<!std::is_same<parameter, T>::value>::type;

  struct base {
    virtual ~base() {}
    virtual bool is(id) const = 0;
    virtual base *copy() const = 0;
  } *p = nullptr;

  template <typename T> struct data : base, std::tuple<T> {
    using std::tuple<T>::tuple;

    T &get() & { return std::get<0>(*this); }
    T const &get() const & { return std::get<0>(*this); }

    bool is(id i) const override { return i == type_id<T>(); }
    base *copy() const override { return new data{get()}; }
  };

  template <typename T> T &stat() { return static_cast<data<T> &>(*p).get(); }

  template <typename T> T const &stat() const {
    return static_cast<data<T> const &>(*p).get();
  }

  template <typename T> T &dyn() { return dynamic_cast<data<T> &>(*p).get(); }

  template <typename T> T const &dyn() const {
    return dynamic_cast<data<T> const &>(*p).get();
  }

public:
  /**
   * @brief Default constructor
   */
  parameter() {}

  /**
   * @brief Destructs the parameter
   */
  ~parameter() { delete p; }

  /**
   * @brief Copy constructor
   * @param s The parameter to copy
   */
  parameter(parameter &&s) : p{s.p} { s.p = nullptr; }

  /**
   * @brief Const copy constructor
   * @param s The parameter to copy
   */
  parameter(parameter const &s) : p{s.p->copy()} {}

  /**
   * @brief Initializes the parameter with the given value
   * @param x The value to initialize the parameter with
   */
  template <typename T, typename U = decay<T>, typename = none<U>>
  parameter(T &&x) : p{new data<U>{std::forward<T>(x)}} {}

  /**
   * @brief Overloads the assignment operator
   * @param s The value to set the parameter to
   */
  parameter &operator=(parameter s) {
    swap(*this, s);
    return *this;
  }

  friend void swap(parameter &s, parameter &r) { std::swap(s.p, r.p); }

  /**
   * @brief Clears the parameter
   */
  void clear() {
    delete p;
    p = nullptr;
  }

  /**
   * @brief Checks whether the parameter is the given type
   * @tparam T The type to check
   * @return   Whether the parameter has the given type or not
   */
  template <typename T> bool is() const {
    return p ? p->is(type_id<T>()) : false;
  }

  /**
   * @brief Returns the value of the parameter
   * @tparam T The type of the parameter
   * @return The value of the parameter
   * @warning If the type of the parameter doesn't match the type of it's stored
   * value, it will result in undefined behaviour.
   */
  template <typename T> T &get() & { return stat<T>(); }
};
} // namespace nlc
