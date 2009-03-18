#ifndef MSVC_COMPAT_H_
#define MSVC_COMPAT_H_

#ifndef S_ISBLK
  #ifndef S_IFBLK
    #define S_ISBLK(m) (0)
  #else
    #define S_ISBLK(m) (((m) & S_IFMT)==S_IFBLK)
  #endif /* S_IFBLK */
#endif /* S_ISBLK */

#define strcasecmp stricmp
#define close(x) closesocket(x)

#endif