#pragma once

#include "AceAttorneyObject.h"

namespace AceAttorney {
// һ��chatbox��Ҫlayer_chatbox_text��layer_chatbox��layer_chatbox_name����ͼ��
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
  // ����Ϊʲôchatbox��ͼ��������"layer_chatbox_text"��
  // ����Ϊchatboxʵ�ʲ�������textͼ�㣬�������壬��������������Ч��
  // ��վ��chatbox���ڵ�����ĽǶ��ϣ���"layer_chatbox"��Ϊͼ�����Ƹ����ʣ������
  const std::string name_layer = "layer_chatbox_text";
  // �˴�ΪʲôҪע�͵�chatboxͼ�����
  // ����Ϊ����ͨ��ͼ����ķ�ʽȥ����chatbox������ͼ�㣬
  // �������ڻ�û��ʵ��ͼ����Ĺ��ܣ����������Դ˴�Ҳ��������ж�ͼ���ϸ΢�Ĳ�����
  // ���Խ������ҿ������ע�ͣ���ǵ�ʵ��ͼ������֮������������չ��chatboxͼ��Ĺ���
  // pAsciiBasicLayer layer_chatbox;
  int speed;
};
} // namespace AceAttorney