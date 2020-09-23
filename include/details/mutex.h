#ifndef ZLOG_DETAILS_MUTEX_H_
#define ZLOG_DETAILS_MUTEX_H_
#include <mutex>
#include <cassert>
namespace zlog {
namespace details {

#if ZLOG_MUTI_THREADS
    using MutexType = std::mutex;
#else
    using MutexType = int;
#endif

    class Mutex {
    public:
        Mutex();
        ~Mutex();
        void Lock();
        void UnLock();
        bool TryLock();

    private:
        MutexType mtx;
    };

#if ZLOG_MUTI_THREADS

    Mutex::Mutex() {}
    Mutex::~Mutex() {}

    void Mutex::Lock()
    {
        mtx.lock();
    }

    void Mutex::UnLock()
    {
        mtx.unlock();
    }

    bool Mutex::TryLock()
    {
        return mtx.try_lock();
    }
#else
    Mutex::Mutex() : mtx(0) {}
    Mutex::~Mutex() {}
    void Mutex::Lock()
    {
        assert(--mtx == -1);
    }
    void Mutex::UnLock()
    {
        assert(mtx++ == -1);
    }
    bool Mutex::TryLock()
    {
        if (mtx != 0) {
            return false;
        }
        Lock();
        return true;
    }
#endif

}  // namespace details
}  // namespace zlog

#endif  // ZLOG_DETAILS_MUTEX_H_