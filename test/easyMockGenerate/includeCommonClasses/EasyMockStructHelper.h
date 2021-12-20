#ifndef EASYMOCKSTRUCTHELPER_H
#define EASYMOCKSTRUCTHELPER_H

#include <StructType.h>
#include <Parameter.h>

#include <memory>

std::shared_ptr<StructType>newStructS1Type();
std::shared_ptr<StructType>newStructS2Type();
Parameter::Vector structS2Parameter();

#endif /* EASYMOCKSTRUCTHELPER_H */
