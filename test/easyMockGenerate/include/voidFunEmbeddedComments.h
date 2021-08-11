#ifndef EASYMOCK_VOIDFUNEMBEDDEDCOMMENTS_H
#define EASYMOCK_VOIDFUNEMBEDDEDCOMMENTS_H

#define myInt int

void /* Funky comment */ voidFunEmbeddedComments();
void /* Funky
 * Multiline
 * Comment
 */ voidFunEmbeddedComments2();

 void voidFunEmbeddedComments3(myInt /* Funky comment */ a);
 void voidFunEmbeddedComments4(myInt /* Funky
 * multiline
 * comment */ a);

void //one line comment
voidFunEmbeddedOneLineComments();

void voidFunEmbeddedOneLineComments2( myInt //one line comment
a);

#endif //EASYMOCK_VOIDFUNEMBEDDEDCOMMENTS_H
