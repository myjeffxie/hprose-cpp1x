/**********************************************************\
|                                                          |
|                          hprose                          |
|                                                          |
| Official WebSite: http://www.hprose.com/                 |
|                   http://www.hprose.org/                 |
|                                                          |
\**********************************************************/

/**********************************************************\
 *                                                        *
 * hprose/Variant.h                                       *
 *                                                        *
 * variant type for cpp.                                  *
 *                                                        *
 * LastModified: Nov 6, 2016                              *
 * Author: Chen fei <cf@hprose.com>                       *
 *                                                        *
\**********************************************************/

#include <hprose/Variant.h>

namespace hprose {

#define HP_DYNAMIC_APPLY(type, apply)        \
  do {                                       \
    switch ((type)) {                        \
      case Null:                             \
        apply(void*);                        \
        break;                               \
      case String:                           \
        apply(std::shared_ptr<std::string>); \
        break;                               \
      case Time:                             \
        apply(std::shared_ptr<std::tm>);     \
        break;                               \
      default:                               \
        abort();                             \
    }                                        \
  } while (0)

const char *Variant::typeName() const {
    switch (type) {
        case Null:
            return "void *";
        case String:
            return "std::string";
        case Time:
            return "std::tm";
        default:
            abort();
    }
}

Variant &Variant::operator=(const Variant &o) {
    if (&o != this) {
        if (type == o.type) {
#define HP_X(T) *getAddress<T>() = *o.getAddress<T>()
            HP_DYNAMIC_APPLY(type, HP_X);
#undef HP_X
        } else {
            destroy();
#define HP_X(T) new (getAddress<T>()) T(*o.getAddress<T>())
            HP_DYNAMIC_APPLY(o.type, HP_X);
#undef HP_X
            type = o.type;
        }
    }
    return *this;
}

Variant &Variant::operator=(Variant &&o) noexcept {
    if (&o != this) {
        if (type == o.type) {
#define HP_X(T) *getAddress<T>() = std::move(*o.getAddress<T>())
            HP_DYNAMIC_APPLY(type, HP_X);
#undef HP_X
        } else {
            destroy();
#define HP_X(T) new (getAddress<T>()) T(std::move(*o.getAddress<T>()))
            HP_DYNAMIC_APPLY(o.type, HP_X);
#undef HP_X
            type = o.type;
        }
    }
    return *this;
}

void Variant::destroy() noexcept {
    if (type == Null) return;
#define HP_X(T) detail::Destroy::destroy(getAddress<T>())
  HP_DYNAMIC_APPLY(type, HP_X);
#undef HP_X
    type = Null;
    data.null = nullptr;
}

} // hprose
