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

std::ostream& operator<<(std::ostream& os, const Function& fun);
std::ostream& operator<<(std::ostream& os, const ReturnValue& rv);
std::ostream& operator<<(std::ostream& os, const TypeItf& typeItf);
std::ostream& operator<<(std::ostream& os, const StructType& structType);
std::ostream& operator<<(std::ostream& os, const Parameter& param);
std::ostream& operator<<(std::ostream& os, const CType& ctype);
std::ostream& operator<<(std::ostream& os, const ComposableField& composableField);
std::ostream& operator<<(std::ostream& os, const UnionType& unionType);
std::ostream& operator<<(std::ostream& os, const Pointer& pointer);

#endif /* GTESTPRINTCLASSES_H */

