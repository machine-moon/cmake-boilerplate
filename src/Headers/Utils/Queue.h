#pragma once

#include <condition_variable>
#include <limits>
#include <mutex>
#include <queue>

template<typename T, typename Container = std::deque<T>>
class CQueue
{
public:
    using value_type = typename std::queue<T, Container>::value_type;
    using size_type = typename std::queue<T, Container>::size_type;
    using reference = typename std::queue<T, Container>::reference;
    using const_reference = typename std::queue<T, Container>::const_reference;

    CQueue() = default;
    explicit CQueue(size_t capacity)
        : m_capacity(capacity)
    {
    }
    explicit CQueue(const Container& cont)
        : m_queue(cont)
    {
    }
    explicit CQueue(Container&& cont)
        : m_queue(std::move(cont))
    {
    }

    CQueue(const CQueue&) = delete;
    CQueue& operator=(const CQueue&) = delete;
    CQueue(CQueue&&) = delete;
    CQueue& operator=(CQueue&&) = delete;

    void SetCapacity(size_t cap)
    {
        std::lock_guard<std::mutex> lk(m_mutex);
        m_capacity = cap ? cap : std::numeric_limits<size_t>::max();
        m_notFull.notify_all();
    }

    void Close()
    {
        {
            std::lock_guard<std::mutex> lk(m_mutex);
            m_closed = true;
        }
        m_notEmpty.notify_all();
        m_notFull.notify_all();
    }

    bool Push(const T& value) { return DoPush(value); }
    bool Push(T&& value) { return DoPush(std::move(value)); }

    bool TryPush(const T& value) { return DoTryPush(value); }
    bool TryPush(T&& value) { return DoTryPush(std::move(value)); }

    template<typename... Args>
    bool Emplace(Args&&... args)
    {
        std::unique_lock<std::mutex> lk(m_mutex);
        m_notFull.wait(lk, [&] { return m_closed || m_queue.size() < m_capacity; });
        if (m_closed)
        {
            return false;
        }
        m_queue.emplace(std::forward<Args>(args)...);
        m_notEmpty.notify_one();
        return true;
    }

    void Pop()
    {
        std::unique_lock<std::mutex> lk(m_mutex);
        m_notEmpty.wait(lk, [&] { return m_closed || !m_queue.empty(); });
        if (m_queue.empty())
        {
            return;
        }
        m_queue.pop();
        m_notFull.notify_one();
    }

    bool PopValue(T& out)
    {
        std::unique_lock<std::mutex> lk(m_mutex);
        m_notEmpty.wait(lk, [&] { return m_closed || !m_queue.empty(); });
        if (m_queue.empty())
        {
            return false;
        }
        out = std::move(m_queue.front());
        m_queue.pop();
        m_notFull.notify_one();
        return true;
    }

    bool TryPopValue(T& out)
    {
        std::lock_guard<std::mutex> lk(m_mutex);
        if (m_queue.empty())
        {
            return false;
        }
        out = std::move(m_queue.front());
        m_queue.pop();
        m_notFull.notify_one();
        return true;
    }

    [[nodiscard]] reference Front()
    {
        std::unique_lock<std::mutex> lk(m_mutex);
        m_notEmpty.wait(lk, [&] { return m_closed || !m_queue.empty(); });
        return m_queue.front();
    }

    [[nodiscard]] const_reference Front() const
    {
        std::unique_lock<std::mutex> lk(m_mutex);
        const_cast<CQueue*>(this)->m_notEmpty.wait(lk, [&] { return m_closed || !m_queue.empty(); });
        return m_queue.front();
    }

    [[nodiscard]] bool Empty() const noexcept
    {
        std::lock_guard<std::mutex> lk(m_mutex);
        return m_queue.empty();
    }

    [[nodiscard]] size_type Size() const noexcept
    {
        std::lock_guard<std::mutex> lk(m_mutex);
        return m_queue.size();
    }

private:
    template<typename U>
    bool DoPush(U&& value)
    {
        std::unique_lock<std::mutex> lk(m_mutex);
        m_notFull.wait(lk, [&] { return m_closed || m_queue.size() < m_capacity; });
        if (m_closed)
        {
            return false;
        }
        m_queue.push(std::forward<U>(value));
        m_notEmpty.notify_one();
        return true;
    }

    template<typename U>
    bool DoTryPush(U&& value)
    {
        std::lock_guard<std::mutex> lk(m_mutex);
        if (m_closed || m_queue.size() >= m_capacity)
        {
            return false;
        }
        m_queue.push(std::forward<U>(value));
        m_notEmpty.notify_one();
        return true;
    }

    size_t m_capacity{std::numeric_limits<size_t>::max()};
    std::queue<T, Container> m_queue;
    mutable std::mutex m_mutex;
    std::condition_variable m_notEmpty;
    std::condition_variable m_notFull;
    bool m_closed{false};
};