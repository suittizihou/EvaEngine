#ifndef HAS_METHOD_CHECK_H_
#define HAS_METHOD_CHECK_H_

#include <type_traits>


#define HAS_METHOD(func_name)
template<class ClassType> struct has_method_##func_name
{
    static auto check(...) -> decltype(std::false_type());                                                  \
                                                                                                            \
    template<typename _ClassType>                                                                           \
    static auto check(_ClassType&) ->                                                                       \
        decltype(static_cast<decltype(_ClassType::func_name)*>(&_ClassType::func_name), std::true_type());  \
                                                                                                            \
    enum : bool { value = decltype(check(std::declval<ClassType&>()))::value };                             \
}

#endif
