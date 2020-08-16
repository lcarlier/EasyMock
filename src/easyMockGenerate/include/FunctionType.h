/*! \file
 * \brief Contains the class to represent a function type.
 */
#ifndef FUNCTIONTYPE_H
#define FUNCTIONTYPE_H

#include "Function.h"
#include "TypeItf.h"

/*!
 * \brief Represents a function type.
 *
 * This class can be used to represent a pointer to a function with the
 * usage combination of the Pointer class.
 *
 * This pointer to a function can then be used to represents function's
 * parameters, or structure/union fields.
 */
class FunctionType : public Function, public TypeItf {
public:
    /*!
     * \brief Instantiates a new FunctionType object
     *
     * \copydetails Function
     */
    FunctionType(std::string p_functionName, ReturnValue p_functionReturnType, Parameter::Vector p_functionParameters);

    FunctionType(const FunctionType &other) = default;
    FunctionType& operator=(const FunctionType &other) = default;
    FunctionType(FunctionType &&other) = default;
    FunctionType& operator=(FunctionType &&other) = default;

    bool operator==(const FunctionType &other) const;
    bool operator!=(const FunctionType &other) const;

    virtual FunctionType* clone() const override;
    virtual ~FunctionType();
private:

};

#endif /* FUNCTIONTYPE_H */

