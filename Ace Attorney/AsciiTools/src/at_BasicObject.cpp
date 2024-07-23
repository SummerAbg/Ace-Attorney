#include "at_BasicObject.h"
#include "at_Exception.h"

namespace AsciiTools {
std::string serialize(const AsciiBasicObject *obj) {
  if (obj == nullptr) {
    throw AsciiBasicException(__FUNC__, NotInitialized);
  }
  return obj->getSerializeStr();
}

void deserialize(AsciiBasicObject *obj, const std::string &str) {
  if (obj == nullptr) {
    throw AsciiBasicException(__FUNC__, NotInitialized);
  }
  obj->loadSerializeStr(str);
}
} // namespace AsciiTools