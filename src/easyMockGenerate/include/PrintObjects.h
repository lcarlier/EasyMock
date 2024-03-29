#ifndef EASYMOCKPRINTOBJECTS_H
#define EASYMOCKPRINTOBJECTS_H

#include <ostream>
class Function;
enum class FunctionAccessSpecifier;
class ReturnValue;
class TypeItf;
class StructType;
class Parameter;
class CType;
class ComposableField;
class UnionType;
class Pointer;
class Reference;
class FunctionType;
class FunctionDeclaration;
class Enum;
class IncompleteType;
class ComposableFieldItf;
class ComposableBitfield;
class ConstQualifiedType;
class TypedefType;
struct Namespace;
class ClassType;

namespace std {
    ostream &operator<<(ostream &os, const Function &fun);
    ostream &operator<<(ostream &os, const FunctionAccessSpecifier& visibility);
    ostream &operator<<(ostream &os, const ReturnValue &rv);
    ostream &operator<<(ostream &os, const TypeItf &typeItf);
    ostream &operator<<(ostream &os, const StructType &structType);
    ostream &operator<<(ostream &os, const ClassType &classType);
    ostream &operator<<(ostream &os, const Parameter &param);
    ostream &operator<<(ostream &os, const CType &ctype);
    ostream &operator<<(ostream &os, const ComposableField &composableField);
    ostream &operator<<(ostream &os, const UnionType &unionType);
    ostream &operator<<(ostream &os, const Pointer &pointer);
    ostream &operator<<(ostream &os, const Reference &referenceType);
    ostream &operator<<(ostream &os, const FunctionType &pointer);
    ostream &operator<<(ostream &os, const FunctionDeclaration &pointer);
    ostream &operator<<(ostream &os, const Enum &e);
    ostream &operator<<(ostream &os, const IncompleteType &incType);
    ostream &operator<<(ostream &os, const ComposableFieldItf &composableFieldItf);
    ostream &operator<<(ostream &os, const ComposableBitfield &composableBitfield);
    ostream &operator<<(ostream &os, const ConstQualifiedType &constQualifiedType);
    ostream &operator<<(ostream &os, const TypedefType &p_typedefType);
    ostream &operator<<(ostream &os, const __int128 &uint128Type);
    ostream &operator<<(ostream &os, const unsigned __int128 &uint128Type);
    ostream &operator<<(ostream &os, const Namespace &p_namespace);
}

#endif /* EASYMOCKPRINTOBJECTS_H */

