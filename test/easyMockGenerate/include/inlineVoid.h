#ifndef INLINEVOID_H
#define INLINEVOID_H

#ifdef __cplusplus
extern "C" {
#endif

    void inlineVoid();

    inline int inline1()
    {
        return 42;
    }

    inline int inline2()
    {
        return 42;
    }


#ifdef __cplusplus
}
#endif

#endif /* INLINEVOID_H */

