#include "leaks.h"
#include <string.h>

#ifdef _DEBUG

    ALLOC_INFO *g_LeakList;

    void AddTrack (unsigned int addr, unsigned int asize, const char *fname, unsigned int lnum)
    {
        ALLOC_INFO *info;

        info = (ALLOC_INFO *)malloc(sizeof(ALLOC_INFO));
        info->address   = addr;
        info->line      = lnum;
        info->size      = asize;
        info->pNext     = g_LeakList;
        g_LeakList      = info;
        strncpy(info->file, fname, _MAX_PATH - 1);
    }

    void RemoveTrack (unsigned int addr)
    {
        ALLOC_INFO *pLastItem = 0;
        ALLOC_INFO *pCurrItem = g_LeakList;

        while (pCurrItem)
        {
            if (pCurrItem->address == addr)
            {
                if (pLastItem)
                {
                    pLastItem->pNext = pCurrItem->pNext;
                }
                else
                {
                    g_LeakList = pCurrItem->pNext;
                }

                free(pCurrItem);
                break;
            }
            else
            {
                pLastItem = pCurrItem;
                pCurrItem = pCurrItem->pNext;
            }
        }
    }


    #ifdef _WIN32

        #include <windows.h>
        #include "leaks.h"
        #include <stdio.h>

        void DumpUnfreed ()
        {
            DWORD totalSize = 0;
            char buf[1024];

            if (!g_LeakList)
            {
                return;
            }

            ALLOC_INFO *pCurrItem = g_LeakList;
            while (pCurrItem)
            {
                sprintf(buf, "%s(%d): ADDRESS %d\t%d unfreed\n", pCurrItem->file, pCurrItem->line, pCurrItem->address, pCurrItem->size);
                OutputDebugStringA(buf);
                totalSize += pCurrItem->size;
                pCurrItem = pCurrItem->pNext;
            }

            sprintf(buf, "-----------------------------------------------------------\n");
            OutputDebugStringA(buf);
            sprintf(buf, "Total Unfreed: %d bytes\n", totalSize);
            OutputDebugStringA(buf);
        };

    #endif

#endif