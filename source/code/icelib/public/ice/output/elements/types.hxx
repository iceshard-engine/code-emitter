#pragma once
#include <ice/output/elements/type.hxx>

namespace ice::output
{

    //! Base types
    static Type t_bool{ "bool",               { Type::Property::NATIVE } };
    static Type t_void{ "void",               { Type::Property::NATIVE } };

    //! Integral types
    static Type t_char{ "char",               { Type::Property::NATIVE } };
    static Type t_byte{ "unsigned char",      { Type::Property::NATIVE } };
    static Type t_short{ "short",              { Type::Property::NATIVE } };
    static Type t_int{ "int",                { Type::Property::NATIVE } };
    static Type t_long{ "long",               { Type::Property::NATIVE } };
    static Type t_longlong{ "long long",          { Type::Property::NATIVE } };
    static Type t_ushort{ "unsigned short",     { Type::Property::NATIVE } };
    static Type t_uint{ "unsigned int",       { Type::Property::NATIVE } };
    static Type t_ulong{ "unsigned long",      { Type::Property::NATIVE } };
    static Type t_ulonglong{ "unsigned long long", { Type::Property::NATIVE } };

    //! Integral specific types
    static Type t_int8{ "int8_t",             { Type::Property::NATIVE } };
    static Type t_int16{ "int16_t",            { Type::Property::NATIVE } };
    static Type t_int32{ "int32_t",            { Type::Property::NATIVE } };
    static Type t_int64{ "int64_t",            { Type::Property::NATIVE } };
    static Type t_uint8{ "uint8_t",            { Type::Property::NATIVE } };
    static Type t_uint16{ "uint16_t",           { Type::Property::NATIVE } };
    static Type t_uint32{ "uint32_t",           { Type::Property::NATIVE } };
    static Type t_uint64{ "uint64_t",           { Type::Property::NATIVE } };

    //! Floating point types
    static Type t_float{ "float",              { Type::Property::NATIVE } };
    static Type t_double{ "double",             { Type::Property::NATIVE } };
    static Type t_longdouble{ "long double",        { Type::Property::NATIVE } };

    //! Additional native c++ types
    static Type t_cstring{ "char",               { Type::Property::NATIVE, Type::Property::CONSTANT,  Type::Property::POINTER } };

    //! Special types
    static Type t_auto{ "auto",               { Type::Property::NATIVE } };
    static Type t_pointer{ "auto",               { Type::Property::NATIVE, Type::Property::POINTER } };
    static Type t_reference{ "auto",               { Type::Property::NATIVE, Type::Property::REFERENCE } };

} // namespace ice::output
