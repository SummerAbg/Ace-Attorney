#pragma once

#include "AnalyzeCommand.h"
#include <iostream>
#include <shared_mutex>

namespace AceAttorney {
class AceAttorneyGame;
class AceAttorneyChatbox;

class AceAttorneyObject {
public:
  using pSharedMutex = std::shared_ptr<std::shared_mutex>;
  using pScreen = std::shared_ptr<AsciiGL::AsciiBasicLayerMngr>;
  using pGame = AceAttorneyGame *;
  using pChatbox = std::shared_ptr<AceAttorneyChatbox>;

  /**
   *  @brief AceAttorneyObject object constructor
   *  @param game - ��Ϸָ��
   */
  AceAttorneyObject(pGame game);

  /**
   *  @brief AceAttorneyObject object destructor
   */
  virtual ~AceAttorneyObject();

  /**
   *  @brief ����Ϸ
   *  @param game - ��Ϸָ��
   */
  virtual void bind(pGame game);

  /**
   *  @brief  �Ƿ��
   *  @retval  - �Ƿ�󶨵Ĳ���ֵ
   */
  bool isBind() const { return game; }

  /**
   *  @brief  ��ȡ��Ϸָ��
   *  @retval  - ��Ϸָ��
   */
  pGame getGamePointer() { return game; }

protected:
  pGame game = nullptr;
  pSharedMutex s_mtx = nullptr;
  irrklang::ISoundEngine *audioEngine = nullptr;
  pScreen screen = nullptr;
  pChatbox chatbox = nullptr;
};
} // namespace AceAttorney