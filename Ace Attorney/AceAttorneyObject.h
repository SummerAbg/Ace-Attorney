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
   *  @param game - 游戏指针
   */
  AceAttorneyObject(pGame game);

  /**
   *  @brief AceAttorneyObject object destructor
   */
  virtual ~AceAttorneyObject();

  /**
   *  @brief 绑定游戏
   *  @param game - 游戏指针
   */
  virtual void bind(pGame game);

  /**
   *  @brief  是否绑定
   *  @retval  - 是否绑定的布尔值
   */
  bool isBind() const { return game; }

  /**
   *  @brief  获取游戏指针
   *  @retval  - 游戏指针
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