#ifndef ZLOG_DETAILS_THREAD_POOL_H_
#define ZLOG_DETAILS_THREAD_POOL_H_

#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

namespace zlog {
namespace details {

const static uint32_t ZLOG_THREADS_MAX_NUM = 10;

    using std::bind;
    using std::condition_variable;
    using std::forward;
    using std::function;
    using std::future;
    using std::make_shared;
    using std::mutex;
    using std::packaged_task;
    using std::queue;
    using std::result_of;
    using std::thread;
    using std::unique_lock;
    using std::vector;

    class ThreadPool {
    public:
        ThreadPool(uint32_t threadNum);
        ThreadPool(const ThreadPool&) = delete;
        ThreadPool& operator=(ThreadPool&&) = delete;
        ~ThreadPool();

        template <class Func, class... Args>
        auto AddTask(Func&& func, Args&&... args) -> future<typename result_of<Func(Args...)>::type>;
        void AddTask(const function<void()>& func);
        void Stop();

    private:
        uint32_t threadNum;
        vector<thread> threads;
        queue<function<void()>> tasks;
        mutex mtx;
        condition_variable cv;
        bool stop;
    };

    ThreadPool::ThreadPool(uint32_t threadNum) : threadNum(threadNum), stop(false)
    {
        if (threadNum < 0 || threadNum > ZLOG_THREADS_MAX_NUM) {
            throw std::runtime_error("the number of threads is out if range.");
        }

        for (uint32_t i = 0; i < threadNum; i++) {
            threads.emplace_back([this]() {
                while (1) {
                    function<void()> task;
                    {
                        unique_lock<mutex> lk(mtx);
                        cv.wait(lk, [this]() { return this->stop || !this->tasks.empty(); });
                        if (this->stop && this->tasks.empty()) {
                            return;
                        }
                        task = move(this->tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    ThreadPool::~ThreadPool()
    {
        Stop();
    }

    template <class Func, class... Args>
    auto ThreadPool::AddTask(Func&& func, Args&&... args) -> future<typename result_of<Func(Args...)>::type>
    {
        using returnType = typename result_of<Func(Args...)>::type;
        auto task = make_shared<packaged_task<returnType()>>(bind(forward<Func>(func), forward<Args>(args)...));
        future<returnType> ret = task->get_future();

        {
            unique_lock<mutex> lk(mtx);
            if (!stop) {
                tasks.emplace([task]() { (*task)(); });
            }
        }
        cv.notify_one();
        return ret;
    }
    void ThreadPool::AddTask(const function<void()>& func)
    {
        {
            unique_lock<mutex> lk(mtx);
            if (!stop) {
                tasks.emplace(func);
            }
        }
        cv.notify_one();
    }

    void ThreadPool::Stop()
    {
        {
            unique_lock<mutex> lk(mtx);
            stop = true;
        }
        cv.notify_all();
        for (auto& thread : threads) {
            thread.join();
        }
    }
}  // namespace details
}  // namespace zlog
#endif  // ZLOG_DETAILS_THREAD_POOL_H_