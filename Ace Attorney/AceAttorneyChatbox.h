#pragma once

#include "AceAttorneyObject.h"

namespace AceAttorney {
// 一个chatbox需要layer_chatbox_text，layer_chatbox，layer_chatbox_name三个图层
class AceAttorneyChatbox : public AceAttorneyObject {
public:
  using pAsciiBasicLayer = std::shared_ptr<AsciiGL::AsciiBasicLayer>;

  AceAttorneyChatbox();
  AceAttorneyChatbox(pGame game);
  AceAttorneyChatbox(int length, int width, pGame game);
  ~AceAttorneyChatbox();

  void initChatBox(int speed, const std::string &title = "Chatbox");
  // pAsciiBasicLayer getChatboxLayer() const { return layer_chatbox; }

  void outputText(const AsciiTools::AsciiBasicString &text);

  void setTitle(const std::string &title);
  void setSpeed(int speed) { this->speed = speed; }

private:
  // 至于为什么chatbox的图层名称是"layer_chatbox_text"？
  // 是因为chatbox实际操作的是text图层，而非整体，有利于提升程序效率
  // 但站在chatbox存在的意义的角度上，以"layer_chatbox"作为图层名称更合适（待深究）
  const std::string name_layer = "layer_chatbox_text";
  // 此处为什么要注释掉chatbox图层对象，
  // 是因为我想通过图层组的方式去管理chatbox的所有图层，
  // 但是由于还没有实现图层组的功能（懒），所以此处也不打算进行对图层更细微的操作（
  // 所以将来的我看到这个注释，请记得实现图层组类之后再来考虑拓展对chatbox图层的管理
  // pAsciiBasicLayer layer_chatbox;
  int speed;
};
} // namespace AceAttorney