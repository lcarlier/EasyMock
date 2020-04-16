#ifndef DECLARATOR_H
#define DECLARATOR_H

#include <string>

class TypeItf;

class Declarator
{
public:
  Declarator();
  explicit Declarator(TypeItf* typeItf);
  virtual ~Declarator();

  Declarator(const Declarator& other);
  Declarator &operator=(Declarator other);

  Declarator(Declarator &&other);

  virtual TypeItf* getType();
  virtual const TypeItf* getType() const;

  virtual void setType(TypeItf* type);
  const std::string& getTypeName() const;

  bool operator==(const Declarator &other) const;
  bool operator!=(const Declarator &other) const;
protected:
  TypeItf* m_type;

  friend void swap(Declarator &first, Declarator &second);
};

#endif /* DECLARATOR_H */

