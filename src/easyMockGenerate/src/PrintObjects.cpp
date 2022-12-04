#include <PrintObjects.h>

#include <TypeItf.h>
#include <Function.h>
#include <ReturnValue.h>
#include <EasyMock_CType.h>
#include <ComposableField.h>
#include <StructType.h>
#include <ClassType.h>
#include <UnionType.h>
#include <Pointer.h>
#include <Reference.h>
#include <FunctionType.h>
#include <FunctionDeclaration.h>
#include <Enum.h>
#include <IncompleteType.h>
#include <ComposableBitfield.h>
#include <ConstQualifiedType.h>
#include <Namespace.h>

#include "TypedefType.h"

#include <cassert>

static std::string gs_indentation;

namespace {
    template<typename T>
    std::ostream &printFunction(std::ostream &os, const T &fun) {
        os << "funPrototype: " << fun.getFunctionPrototype() << ", ";
        os << "isVariadic: " << (fun.isVariadic() ? "yes" : "no") << ", ";
        os << "isInline: " << (fun.isInlined() ? "yes" : "no") << ", ";
        os << "isInline: " << (fun.isStatic() ? "yes" : "no") << ", ";
        os << "isClassConst: " << (fun.isClassConst() ? "yes" : "no") << std::endl;

        const Function::AttributesList &attributesList = fun.getAttributes();
        os << gs_indentation << "Attributes:" << std::endl;
        gs_indentation.push_back('\t');
        for (const auto &attr: attributesList) {
            os << gs_indentation << attr.getName();
            const FunctionAttribute::ParametersList &parametersList = attr.getParameters();
            if (!parametersList.empty()) {
                os << "(";
                for (const auto &param: attr.getParameters()) {
                    os << " " << param << ",";
                }
                os << ")";
            }
            os << std::endl;
        }
        gs_indentation.pop_back();

        const ReturnValue *rv = fun.getReturnValue();
        os << gs_indentation << "Return value:";
        gs_indentation.push_back('\t');
        os << std::endl << gs_indentation;
        os << *rv << std::endl;
        gs_indentation.pop_back();

        const Parameter::Vector &params = fun.getFunctionsParameters();
        const Parameter::Vector::size_type nbParams = params.size();
        Parameter::Vector::size_type curParamIdx;
        for (curParamIdx = 0; curParamIdx < nbParams; curParamIdx++) {
            const Parameter &curParamObj = params[curParamIdx];
            os << gs_indentation << "Parameter " << curParamIdx << ": " << curParamObj;
        }
        return os;
    }

    template<class T>
    static void printComposableTypeToOstream(std::ostream &os, const T &composableType, std::string classname) {
        os << classname << "(";
        os << "name: '" << composableType.getName() << "'" << ", ";
        os << "anonymous: " << (composableType.isAnonymous() ? "yes" : " no") << ", ";
        os << "DeclEmbedded: " << (composableType.isDeclarationEmbeddedInOtherType() ? "yes" : " no");
        os << "ForwardDeclared: " << (composableType.isForwardDeclared() ? "yes" : " no");
        os << ")" << std::endl;

        const ComposableType::ComposableFieldTypeVector &structFields = composableType.getContainedFields();
        const ComposableType::ComposableFieldTypeVector::size_type nbFields = structFields.size();
        ComposableType::ComposableFieldTypeVector::size_type fieldIdx;
        for (fieldIdx = 0; fieldIdx < nbFields; fieldIdx++) {
            gs_indentation.push_back('\t');
            const auto &curFieldVariant = structFields[fieldIdx];
            std::visit([&os, &fieldIdx](auto &&curField) {
                os << gs_indentation << "Field: " << fieldIdx << ": " << curField << std::endl;
            }, curFieldVariant);
            gs_indentation.pop_back();
        }
        for(const auto& fun : composableType.getFunctions())
        {
          gs_indentation.push_back('\t');
          auto useCount = fun.use_count();

          assert(useCount > 0);
          os << gs_indentation << useCount << "Function: " << fun->getFunctionPrototype() << std::endl;

          gs_indentation.pop_back();
        }
    }

    void PrintTo(const __int128 &int128Type, std::ostream *os) {
        uint64_t lowDigit = int128Type & 0xffffffffffffffff;
        uint64_t highDigit = int128Type >> 64;
        *os << "0x" << std::hex << highDigit << lowDigit;
    }

    void PrintTo(const unsigned __int128 &uint128Type, std::ostream *os) {
        uint64_t lowDigit = uint128Type & 0xffffffffffffffff;
        uint64_t highDigit = uint128Type >> 64;
        *os << "0x" << std::hex << highDigit << lowDigit;
    }
}

namespace std {
    ostream &operator<<(ostream &os, const Function &fun) {
        return printFunction(os, fun);
    }

    ostream &operator<<(ostream &os, const FunctionAccessSpecifier& visibility)
    {
      switch(visibility)
      {
        case FunctionAccessSpecifier::NA:
          os << "Not applicable";
          break;
        case FunctionAccessSpecifier::PUBLIC:
          os << "public";
          break;
        case FunctionAccessSpecifier::PRIVATE:
          os << "private";
          break;
        case FunctionAccessSpecifier::PROTECTED:
          os << "protected";
          break;
      }
      return os;
    }

    ostream &operator<<(ostream &os, const FunctionType &fun) {
        gs_indentation.push_back('\t');
        ostream &tos = printFunction(os, fun);
        gs_indentation.pop_back();
        return tos;
    }

    ostream &operator<<(ostream &os, const FunctionDeclaration &fun) {
        gs_indentation.push_back('\t');
      os << std::endl << gs_indentation << "Namespace: " << *fun.getNamespace();
      os << std::endl << gs_indentation << "HasThisDeclABody: " << (fun.doesThisDeclarationHasABody() ? "yes" : "no");
      os << std::endl << gs_indentation << "isMemberClass: " << (fun.isMemberClass() ? "yes" : "no");
      os << std::endl << gs_indentation << "Visbility: " << fun.getAccessSpecifier()
           << std::endl;
      if(fun.isMemberClass())
      {
        auto parentData = fun.getParentData();
        printComposableTypeToOstream(os, *parentData, parentData->getComposableTypeKeyword());
      }
        gs_indentation.pop_back();
        return printFunction(os, fun);
    }

    ostream &operator<<(ostream &os, const ReturnValue &rv) {
        const TypeItf *typeItf = rv.getType();
        os << "ReturnValue " << " declString: '" << rv.getDeclareString() << "'";
        gs_indentation.push_back('\t');
        os << std::endl << gs_indentation;
        os << *typeItf;
        gs_indentation.pop_back();
        return os;
    }

    ostream &operator<<(ostream &os, const TypeItf &typeItf) {
        bool isConst = typeItf.isConst();
        os << "TypeItf:" << typeItf.getName() << ", ";
        os << "isTypeDef:" << (typeItf.isTypedDef() ? "yes" : "no") << ", ";
        os << "isAnonymous:" << (typeItf.isAnonymous() ? "yes" : "no") << ", ";
        os << "isPointer:" << (typeItf.isPointer() ? "yes" : "no") << ", ";
        os << "isReference:" << (typeItf.isReference() ? "yes" : "no") << ", ";
        os << "isCType:" << (typeItf.isCType() ? "yes" : "no") << ", ";
        os << "isStruct:" << (typeItf.isStruct() ? "yes" : "no") << ", ";
        os << "isUnion:" << (typeItf.isUnion() ? "yes" : "no") << ", ";
        os << "isImplicit:" << (typeItf.isImplicit() ? "yes" : "no") << ", ";
        os << "isEnum:" << (typeItf.isEnum() ? "yes" : "no") << ", ";
        os << "isIncomplete:" << (typeItf.isIncompleteType() ? "yes" : "no") << ", ";
        os << "isConst:" << (isConst ? "yes" : "no") << ", ";
        os << "isFunctionType:" << (typeItf.isFunctionType() ? "yes" : "no");
        os << std::endl << gs_indentation;

        if (typeItf.isCType()) {
            os << static_cast<const CType &>(typeItf);
        } else if (typeItf.isStruct()) {
            os << static_cast<const StructType &>(typeItf);
        } else if (typeItf.isUnion()) {
            os << static_cast<const UnionType &>(typeItf);
        } else if (typeItf.isPointer()) {
            os << static_cast<const Pointer &>(typeItf);
        } else if (typeItf.isReference()) {
            os << static_cast<const Reference &>(typeItf);
        } else if (typeItf.isEnum()) {
            os << static_cast<const Enum &>(typeItf);
        } else if (typeItf.isIncompleteType()) {
            os << static_cast<const IncompleteType &>(typeItf);
        } else if (isConst) {
            os << static_cast<const ConstQualifiedType &>(typeItf);
        } else if (typeItf.isTypedDef()) {
            os << static_cast<const TypedefType &>(typeItf);
        } else if (typeItf.isFunctionType()) {
            os << static_cast<const FunctionType &>(typeItf);
        } else {
            os << std::endl;
        }
        return os;
    }

    ostream &operator<<(ostream &os, const CType &ctype) {
        return os << "Ctype: " << ctype.getName() << std::endl;
    }

    ostream &operator<<(ostream &os, const StructType &structType) {
        printComposableTypeToOstream(os, structType, "StructType");
        return os;
    }

    ostream &operator<<(ostream &os, const ClassType &classType) {
      printComposableTypeToOstream(os, classType, "ClassType");
      return os;
    }

    ostream &operator<<(ostream &os, const Parameter &param) {
        const TypeItf *type = param.getType();
        os << "Parameter declString: '" << param.getDeclareString() << "', ";
        os << "name: '" << param.getName() << "'";
        os << std::endl;
        gs_indentation.push_back('\t');
        os << gs_indentation << *type;
        gs_indentation.pop_back();

        return os;
    }

    ostream &operator<<(ostream &os, const ComposableField &composableField) {
        os << "ComposableField(";
        os << "declString: '" << composableField.getDeclareString() << "', ";
        os << "name: '" << composableField.getName() << "', ";
        os << "isIncomplete: " << (composableField.isIncompleteTypeField() ? "yes" : " no") << ", ";
        os << "type: " << std::endl;
        gs_indentation.push_back('\t');
        os << gs_indentation << *composableField.getType();
        gs_indentation.pop_back();
        os << gs_indentation << ")END ComposableField '" << composableField.getName() << "'";
        return os;
    }

    ostream &operator<<(ostream &os, const UnionType &unionType) {
        printComposableTypeToOstream(os, unionType, "UnionType");
        return os;
    }

    ostream &operator<<(ostream &os, const Pointer &pointerType) {
        os << "Pointer: ";
        gs_indentation.push_back('\t');
        os << std::endl << gs_indentation;
        os << "pointedType pointer: " << *pointerType.getPointedType();
        gs_indentation.pop_back();
        return os;
    }

    ostream &operator<<(ostream &os, const Reference &referenceType) {
      os << "Reference: ";
      gs_indentation.push_back('\t');
      os << std::endl << gs_indentation;
      os << "pointedType reference: " << *referenceType.getPointedType();
      gs_indentation.pop_back();
      return os;
    }

    ostream &operator<<(ostream &os, const Enum &etype) {
        os << "Enum: name:'" << etype.getName() << "'" << std::endl;
        gs_indentation.push_back('\t');
        for (auto enumVal: etype.getValues()) {
            os << gs_indentation << enumVal.second << " = " << enumVal.first << std::endl;
        }
        gs_indentation.pop_back();
        return os;
    }

    ostream &operator<<(ostream &os, const IncompleteType &incType) {
        return os << "Incomplete Type: name:'" << incType.getName() << "'" << std::endl;
    }

    ostream &operator<<(ostream &os, const __int128 &int128Type) {
        PrintTo(int128Type, &os);
        return os;
    }

    ostream &operator<<(ostream &os, const unsigned __int128 &uint128Type) {
        PrintTo(uint128Type, &os);
        return os;
    }

    ostream &operator<<(ostream &os, const ComposableFieldItf &composableFieldItf) {
        if (composableFieldItf.isComposableField()) {
            return operator<<(os, dynamic_cast<const ComposableField &>(composableFieldItf));
        }
        if (composableFieldItf.isComposableBitfield()) {
            return operator<<(os, dynamic_cast<const ComposableBitfield &>(composableFieldItf));
        }
        return os;
    }

    ostream &operator<<(ostream &os, const ComposableBitfield &composableBitfield) {
        os << "ComposableBitfield(";
        os << "declString: '" << composableBitfield.getDeclareString() << "', ";
        os << "name: '" << composableBitfield.getName() << "', ";
        os << "size: '" << static_cast<unsigned>(composableBitfield.getSize()) << "', ";
        os << "type: " << std::endl;
        gs_indentation.push_back('\t');
        os << gs_indentation << *composableBitfield.getType();
        gs_indentation.pop_back();
        os << gs_indentation << ")END ComposableBitfield '" << composableBitfield.getName() << "'";
        return os;
    }

    ostream &operator<<(ostream &os, const ConstQualifiedType &constQualifiedType) {
        os << "ConstQualifiedType(" << std::endl;
        gs_indentation.push_back('\t');
        os << gs_indentation << *constQualifiedType.getUnqualifiedType();
        gs_indentation.pop_back();
        os << gs_indentation << ")END ConstQualifiedType '" << std::endl;
        return os;
    }

    ostream &operator<<(ostream &os, const TypedefType &p_typedefType) {
        os << "TypedefType " << p_typedefType.getName() << std::endl;
        gs_indentation.push_back('\t');
        os << gs_indentation << *p_typedefType.getTypee() << std::endl;
        gs_indentation.pop_back();
        return os;
    }

    ostream &operator<<(ostream &os, const Namespace &p_namespace)
    {
      if(p_namespace.m_parent)
      {
        os << *p_namespace.m_parent;
        if(!p_namespace.m_parent->isGlobal())
        {
          os << "::";
        }
      }
      os << p_namespace.m_name;
      return os;
    }
}