# CQueue API Reference

A thread-safe, optionally bounded, blocking FIFO queue for C++.

---

## Template Parameters

- `T` — The type of elements stored in the queue.
- `Container` — The underlying container type (default: `std::deque<T>`).

---

## Constructors

```cpp
CQueue();
CQueue(size_t capacity);
CQueue(const Container& cont);
CQueue(Container&& cont);
```
- **Default constructor:** Unbounded queue.
- **With capacity:** Bounded queue of given size.
- **With container:** Initializes with existing container.

---

## Deleted Functions

- `CQueue(const CQueue&) = delete;`
- `CQueue& operator=(const CQueue&) = delete;`
- `CQueue(CQueue&&) = delete;`
- `CQueue& operator=(CQueue&&) = delete;`

---

## Member Functions

### Capacity and Control

```cpp
void SetCapacity(size_t cap)
```
- Set the maximum queue capacity. Zero means unbounded.

```cpp
void Close()
```
- Closes the queue. Wakes up all blocked threads. No more pushes allowed.

---

### Push Operations

```cpp
bool Push(const T& value)
bool Push(T&& value)
```
- Blocking push. Waits if queue is full (bounded).

```cpp
bool TryPush(const T& value)
bool TryPush(T&& value)
```
- Non-blocking push. Returns `false` if queue is full.

```cpp
template<typename... Args>
bool Emplace(Args&&... args)
```
- Blocking emplace. Constructs element in-place. Waits if queue is full.

---

### Pop Operations

```cpp
void Pop()
```
- Blocking pop. Waits if queue is empty.

```cpp
bool PopValue(T& out)
```
- Blocking pop. Assigns front value to `out`. Returns `false` if queue is empty and closed.

---

### Accessors

```cpp
reference Front()
const_reference Front() const
```
- Blocking access to front element. Waits if queue is empty.

```cpp
bool Empty() const noexcept
```
- Returns `true` if queue is empty.

```cpp
size_type Size() const noexcept
```
- Returns the number of elements in the queue.

---

## Internal Synchronization

- All operations are thread-safe.
- Uses `std::mutex` and `std::condition_variable`.

---

## Usage Example

```cpp
CQueue<int> q(5);         // bounded queue of 5
q.Push(42);               // blocks if full
int value;
if (q.PopValue(value)) {  // blocks if empty
  // use value
}
q.Close();                // wake up all blocked threads, disallow further pushes
```

---

## Notes

- Use `Close()` to terminate producer/consumer threads gracefully.
- After `Close()`, push operations fail, pop operations succeed until empty, then return immediately.