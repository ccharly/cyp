#ifndef CYP_ANY_HPP
#define CYP_ANY_HPP

#include <cyp/config.hpp>
#include <cyp/traits.hpp>
#include <cyp/static_operators.hpp>
#include <array>
#include <typeinfo>
#include <typeindex>

namespace cyp {

namespace detail {

using byte_t = std::uint8_t;

static constexpr int any_max_static_size = 16;

union any_data_t {
  void* ptr;
  std::array<byte_t, detail::any_max_static_size> static_data;
};

template <typename T>
struct type_ {};

template <typename T>
constexpr bool fits_into_static_storage() {
  return sizeof(T) <= any_max_static_size;
}

template <typename T>
T& cast_any_data(any_data_t& data) {
  if (fits_into_static_storage<T>()) {
    return *reinterpret_cast<T*>(data.static_data.data());
  } else {
    return *static_cast<T*>(data.ptr);
  }
}

template <typename T>
T const& cast_any_data(any_data_t const& data) {
  if (fits_into_static_storage<T const>()) {
    return *reinterpret_cast<T const*>(data.static_data.data());
  } else {
    return *static_cast<T const*>(data.ptr);
  }
}

struct any_resource_handler {
  bool use_static_storage;

  template <typename T>
  any_resource_handler(type_<T>)
    : use_static_storage(fits_into_static_storage<T>()) {
  }

  virtual void destroy(void*, void*) const = 0;
  virtual bool is(std::type_index const&) const = 0;
  virtual const char* type_name() const = 0;
  virtual str __str__(any_data_t const&) const = 0;
};

template <typename T>
struct any_typed_resource_caster {
  using cast_type = T;

  static T& cast(any_data_t& data) {
    return cast_any_data<T>(data);
  }

  static T const& cast(any_data_t const& data) {
    return cast_any_data<T>(data);
  }
};

template <typename T>
struct any_typed_resource_caster<cyp::ref_t<T>> {
  using cast_type = T;

  static T const& cast(any_data_t const& data) {
    return cast_any_data<cyp::ref_t<T>>(data).get();
  }

  static T& cast(any_data_t& data) {
    return cast_any_data<cyp::ref_t<T>>(data).get();
  }
};

template <typename T>
struct any_typed_resource_handler : any_resource_handler {
  using cast_type = typename any_typed_resource_caster<T>::cast_type;

  any_typed_resource_handler() : any_resource_handler(type_<T>{}) {
  }

  cast_type& cast(any_data_t& data) {
    return any_typed_resource_caster<T>::cast(data);
  }

  cast_type const& cast(any_data_t const& data) const {
    return any_typed_resource_caster<T>::cast(data);
  }

  virtual void destroy(void* ptr, void* static_storage_data) const {
    if (use_static_storage) {
      reinterpret_cast<T*>(static_storage_data)->~T();
    } else {
      delete static_cast<T*>(ptr);
    }
  }

  virtual bool is(std::type_index const& ti) const {
    return std::type_index(typeid(T)) == ti;
  }

  virtual const char* type_name() const {
    return typeid(T).name();
  }

  str __str__case(any_data_t const& data, true_t) const {
    return ::cyp::__str__(cast(data));
  }

  str __str__case(any_data_t const&, false_t) const {
    throw NotImplementedError(std::string("__str__ not implemented on type: ") + type_name());
  }

  virtual str __str__(any_data_t const& data) const {
    return __str__case(data, cyp::static_bool_t<hasattr__str__<cast_type>::value>{});
  }
};

template <typename T>
struct any_resource_handlers {
  static any_resource_handler* handler;
};

template <typename T>
any_resource_handler* any_resource_handlers<T>::handler = new any_typed_resource_handler<T>();

} // ::detail


class any {
  detail::any_data_t _storage;
  detail::any_resource_handler* _resource_handler;

  public:
  ~any() {
    destroy();
  }

  any() : _storage(), _resource_handler(nullptr) {
  }

  any(any&& x) = default;
  any(any const& x) = default;

  template <typename T>
  any(T&& x) : any() {
    assign(std::forward<T>(x));
  }

  any& operator=(any const& x) {
    _storage = x._storage;
    _resource_handler = x._resource_handler;
    return *this;
  }

  any& operator=(any& x) {
    _storage = x._storage;
    _resource_handler = x._resource_handler;
    return *this;
  }

  template <typename T>
  any& operator=(T&& x) {
    return assign(std::forward<T>(x));
  }

  void destroy() {
    if (_resource_handler) {
      _resource_handler->destroy(_storage.ptr, _storage.static_data.data());
    }
  }

  template <typename T>
  any& assign(T&& x) {
    // First destroy resoure if any
    destroy();
    // Reset the typed handler
    _resource_handler = detail::any_resource_handlers<T>::handler;
    // Now assign the value where it belongs
    if (_resource_handler->use_static_storage) {
      new (_storage.static_data.data()) T(std::forward<T>(x));
    } else {
      _storage.ptr = new T(std::forward<T>(x));
    }
    return *this;
  }

  template <typename T>
  bool is() const {
    if (_resource_handler) {
      return _resource_handler->is(std::type_index(typeid(T)));
    } else {
      return false;
    }
  }

  template <typename T>
  T const& get() const {
    if (not is<T>()) {
      throw TypeError("Invalid type cast");
    }
    // Now assign the value where it belongs
    if (_resource_handler->use_static_storage) {
      return *reinterpret_cast<T const*>(_storage.static_data.data());
    } else {
      return *static_cast<T const*>(_storage.ptr);
    }
  }

  template <typename T>
  T& get() {
    return const_cast<T&>(const_cast<const any*>(this)->get<T>());
  }

  template <typename F>
  auto exec(F f) const {
    if (_resource_handler) {
      return f();
    } else {
      throw UndefinedError();
    }
  }

  const char* type_name() const {
    return exec([this]() {
        return _resource_handler->type_name();
        });
  }

  str __str__() const {
    return exec([this]() {
        return _resource_handler->__str__(_storage);
        });
  }
};

class any_ref {
  public:
  any _ref;

  public:
  template <typename T>
  any_ref(T& r) {
    _ref = std::ref(r);
  }

  any_ref(any_ref const& r) {
    _ref = r._ref;
  }

  any_ref(any_ref& r) {
    _ref = r._ref;
  }

  template <typename T>
  any_ref& operator=(T const& x) {
    _ref.get<cyp::ref_t<T>>().get() = x;
    return *this;
  }

  template <typename T>
  bool is() const {
    return _ref.is<cyp::ref_t<T>>();
  }

  template <typename T>
  T const& get() const {
    return _ref.get<cyp::ref_t<T>>().get();
  }

  template <typename T>
  T& get() {
    return _ref.get<cyp::ref_t<T>>().get();
  }

  str __str__() const {
    return _ref.__str__();
  }
};

}

#endif
