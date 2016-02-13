#include <stdlib.h>

#define new DEBUG_NEW

#ifdef _DEBUG

    struct ALLOC_INFO 
    {
          unsigned int  address;
          unsigned int  size;
          char          file[_MAX_PATH];
          unsigned int  line;
          ALLOC_INFO   *pNext;
    };

    void RemoveTrack    (unsigned int addr);
    void AddTrack       (unsigned int addr,  unsigned int asize,  const char *fname, unsigned int lnum);

    inline void *__cdecl operator new (unsigned int  size, const char *file, int line)
    {
        void *ptr = (void *)malloc(size);
        AddTrack((unsigned int)ptr, size, file, line);
        return(ptr);
    };

    inline void __cdecl operator delete(void* p, const char* pszFilename, int nLine)
    {
        RemoveTrack((unsigned int)p);
        free(p);
    }

    inline void __cdecl operator delete (void *p)
    {
        RemoveTrack((unsigned int)p);
        free(p);
    };

    inline void * __cdecl operator new [] (unsigned int size, const char *file, int line)
    {
        void *ptr = (void *)malloc(size);
        AddTrack((unsigned int)ptr, size, file, line);
        return(ptr);
    };

    inline void __cdecl operator delete [] (void *p)
    {
        RemoveTrack((unsigned int)p);
        free(p);
    }

    void DumpUnfreed();

    extern ALLOC_INFO *g_LeakList;

#endif

#ifdef _DEBUG
    #define DEBUG_NEW new(__FILE__, __LINE__)
#else
    #define DEBUG_NEW new
#endif

#ifdef _DEBUG
    #define DISPOSE(p) delete p; RemoveTrack((unsigned int)p);
#endif