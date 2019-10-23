#ifndef FUNCTIONFACTORY_H
#define FUNCTIONFACTORY_H

#include <Function.h>

template<class T>
Parameter::Vector getIntFunIntIntPamrameters();

template<class T>
Function functionFactory();

template<class T>
Function* newFunctionFactory();

#endif /* FUNCTIONFACTORY_H */

