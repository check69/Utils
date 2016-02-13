#ifndef __TEMPLATE_SINGLETON_H__
#define __TEMPLATE_SINGLETON_H__

#include <cstdio>

template<class T>
class TSingleton
{
    public:
        static T *instance ()
        {
            if (!m_pInstance)
            {
                m_pInstance = new T;
            }

            return m_pInstance;
        }

        static void destroy ()
        {
            if (m_pInstance)
            {
                delete m_pInstance;
            }

            m_pInstance = NULL;
        }

    protected:
        TSingleton () {}
       ~TSingleton () {}

    private:
        static T *m_pInstance;
};

template <class T> T *TSingleton<T>::m_pInstance = NULL;

#endif // __TEMPLATE_SINGLETON_H__