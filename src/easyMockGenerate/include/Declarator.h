#ifndef DECLARATOR_H
#define DECLARATOR_H

#include <string>

class TypeItf;

class Declarator
{
public:
  Declarator();
  Declarator(TypeItf* typeItf, bool isPointer);
  virtual ~Declarator();

  Declarator(const Declarator& other);
  Declarator &operator=(Declarator other);

  Declarator(Declarator &&other);

  bool isPointer() const;
  bool setPointer(bool value);

  virtual const TypeItf* getType() const;
  virtual void setType(TypeItf* type);
  const std::string& getTypeName() const;

  bool operator==(const Declarator &other) const;
  bool operator!=(const Declarator &other) const;
protected:
  TypeItf* m_type;
  bool m_isPointer;

  friend void swap(Declarator &first, Declarator &second);
};

#endif /* DECLARATOR_H */

