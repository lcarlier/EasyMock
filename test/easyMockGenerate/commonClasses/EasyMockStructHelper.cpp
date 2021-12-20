#include <EasyMockStructHelper.h>

#include <EasyMock_CType.h>
#include <StructType.h>
#include <Pointer.h>
#include <ComposableField.h>

std::shared_ptr<StructType> newStructS1Type()
{
  bool isEmbeddedInOtherType = false;
  ComposableType::ComposableFieldTypeVector fieldVector{};
  fieldVector.emplace_back(ComposableField(CTYPE_INT, "a"));
  fieldVector.emplace_back(ComposableField(CTYPE_FLOAT, "b"));
  return std::make_shared<StructType>("s1", std::move(fieldVector), isEmbeddedInOtherType);
}

std::shared_ptr<StructType> newStructS2Type()
{
  bool isEmbeddedInOtherType = false;
  auto s1StructType = newStructS1Type();
  ComposableField s1 {std::move(s1StructType), "s"};
  ComposableField floatStructField{std::make_shared<Pointer>(std::make_shared<CType>(CTYPE_FLOAT)), "d"};
  ComposableType::ComposableFieldTypeVector fieldVector{};
  fieldVector.emplace_back(ComposableField(CTYPE_INT, "c"));
  fieldVector.emplace_back(std::move(floatStructField));
  fieldVector.emplace_back(std::move(s1));
  auto s2 = std::make_shared<StructType>("s2", std::move(fieldVector), isEmbeddedInOtherType);

  return s2;
}

Parameter::Vector structS2Parameter()
{
  auto s2 = newStructS2Type();
  Parameter p{std::move(s2), "s"};

  Parameter::Vector funParameter{};
  funParameter.emplace_back(std::move(p));

  return funParameter;
}
