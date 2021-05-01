#include <functional>

class MemoryMapper {
public:
  void unmap();
  std::function<void()> map(device);
}
