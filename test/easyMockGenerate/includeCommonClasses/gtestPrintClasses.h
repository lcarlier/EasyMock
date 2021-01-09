#ifndef GTESTPRINTCLASSES_H
#define GTESTPRINTCLASSES_H

#include <ostream>
class Function;
class ReturnValue;
class TypeItf;
class StructType;
class Parameter;
class CType;
class ComposableField;
class UnionType;
class Pointer;
class FunctionType;
class FunctionDeclaration;
class Enum;
class IncompleteType;

std::ostream& operator<<(std::ostream& os, const Function& fun);
std::ostream& operator<<(std::ostream& os, const ReturnValue& rv);
std::ostream& operator<<(std::ostream& os, const TypeItf& typeItf);
std::ostream& operator<<(std::ostream& os, const StructType& structType);
std::ostream& operator<<(std::ostream& os, const Parameter& param);
std::ostream& operator<<(std::ostream& os, const CType& ctype);
std::ostream& operator<<(std::ostream& os, const ComposableField& composableField);
std::ostream& operator<<(std::ostream& os, const UnionType& unionType);
std::ostream& operator<<(std::ostream& os, const Pointer& pointer);
std::ostream& operator<<(std::ostream& os, const FunctionType& pointer);
std::ostream& operator<<(std::ostream& os, const FunctionDeclaration& pointer);
std::ostream& operator<<(std::ostream& os, const Enum& e);
std::ostream& operator<<(std::ostream& os, const IncompleteType& incType);
std::ostream& operator<<(std::ostream& os, const __int128& int128Type);
void PrintTo(const __int128& bar, std::ostream* os);
std::ostream& operator<<(std::ostream& os, const unsigned __int128& uint128Type);
void PrintTo(const unsigned __int128& bar, std::ostream* os);

#endif /* GTESTPRINTCLASSES_H */

