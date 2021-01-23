#include <VoidFunStructWithConstMemberFactory.h>

#include <StructType.h>
#include <Pointer.h>
#include <ConstQualifiedType.h>
#include <EasyMock_CType.h>
#include <ComposableField.h>

ElementToMockList VoidFunStructWithConstMemberFactory::functionFactoryArray()
{
    ElementToMockList returnedList;
    StructType *structWithConstMember = new StructType("structWithConstMember", false);

    Pointer *fieldWithConstQualifiedType = new Pointer(new ConstQualifiedType(new CType(CTYPE_CHAR)));
    structWithConstMember->addField(new ComposableField(fieldWithConstQualifiedType, "f"));

    ConstQualifiedType *f2Type = new ConstQualifiedType(new CType(CTYPE_SHORT));
    structWithConstMember->addField(new ComposableField(f2Type, "f2"));

    FunctionDeclaration *fd = new FunctionDeclaration(functionGetFunctionName(), VoidReturnValue(), Parameter::Vector({new Parameter(structWithConstMember, "s")}));

    returnedList.push_back(fd);

    return returnedList;
}

std::string VoidFunStructWithConstMemberFactory::functionGetFunctionName()
{
    return "voidFunStructWithConstMember";
}

std::string VoidFunStructWithConstMemberFactory::getFilename()
{
    return "voidFunStructWithConstMember.h";
}
