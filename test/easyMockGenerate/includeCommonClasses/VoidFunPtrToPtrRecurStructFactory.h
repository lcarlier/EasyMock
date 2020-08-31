#ifndef VOIDFUNPTRTOPTRRECURSTRUCTFACTORY_H
#define VOIDFUNPTRTOPTRRECURSTRUCTFACTORY_H

#include <FunctionFactory.h>
#include <easyMock.h>

#include <voidFunPtrToPtrRecurStruct.h>

class VoidFunPtrToPtrRecurStructFactory : public FunctionFactory<int, std::tuple<struct ptrToPtrStructRecur>, std::tuple<EasyMock_Matcher>>
{
public:
  ElementToMockList functionFactoryArray() override;
  std::string functionGetFunctionName() override;
  std::string getFilename() override;

};

#endif /* VOIDFUNPTRTOPTRRECURSTRUCTFACTORY_H */

