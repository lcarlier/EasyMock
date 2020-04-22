#ifndef STRUCTFILEFROMSTDIO_H
#define STRUCTFILEFROMSTDIO_H

#ifdef __cplusplus
extern "C"
{
#endif

  struct MY_IO_FILE;

  struct MY_IO_MARK
  {
    struct MY_IO_MARK *_next;
    struct MY_IO_FILE *_sbuf;
  };

  struct MY_IO_FILE
  {
    struct MY_IO_MARK *_markers;
    struct MY_IO_FILE *_chain;
  };

  typedef struct MY_IO_FILE T_MY_IO_FILE;

  void structFileFromStdio(T_MY_IO_FILE *file);

#ifdef __cplusplus
}
#endif

#endif /* STRUCTFILEFROMSTDIO_H */

