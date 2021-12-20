#include <VoidFunStructWithConstMemberFactory.h>

#include <StructType.h>
#include <Pointer.h>
#include <ConstQualifiedType.h>
#include <EasyMock_CType.h>
#include <ComposableField.h>

ElementToMockList VoidFunStructWithConstMemberFactory::functionFactoryArray()
{
    ElementToMockList returnedList;
    auto structWithConstMember = std::make_shared<StructType>("structWithConstMember", false);

    auto fieldWithConstQualifiedType = std::make_shared<Pointer>(std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_CHAR)));
    structWithConstMember->addField(ComposableField(std::move(fieldWithConstQualifiedType), "f"));

    auto f2Type = std::make_shared<ConstQualifiedType>(std::make_shared<CType>(CTYPE_SHORT));
    structWithConstMember->addField(ComposableField(std::move(f2Type), "f2"));

    Parameter::Vector pv{};
    pv.emplace_back(Parameter(std::move(structWithConstMember), "s"));
    FunctionDeclaration fd(functionGetFunctionName(), VoidReturnValue(), std::move(pv));

    returnedList.push_back(std::move(fd));

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
