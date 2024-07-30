#include "Resources.h"

namespace AceAttorney {
AsciiColor clr_Background = ASCII_COLOR_INDIGO;

AsciiColor clr_ChatBox = {0, 0, 0, 0.5};

AsciiTextColor clr_ChatBox_Name = {ASCII_COLOR_WHITE, {0, 0, 255, 0.5}};
AsciiTextColor clr_ChatBox_Text = {ASCII_COLOR_WHITE, clr_ChatBox};

AsciiBasicString str_Background = getAdaptiveStr(
    {' ', AsciiTextColor(ASCII_COLOR_WHITE, clr_Background), false});
AsciiBasicString str_ChatBox_Border = getAdaptiveStr({
    '=',
    AsciiTextColor(ASCII_COLOR_WHITE, ASCII_COLOR_GREY),
    false,
});
AsciiBasicString str_ChatBox = getAdaptiveStr({
    ' ',
    AsciiTextColor(ASCII_COLOR_GREY, clr_ChatBox),
    false,
});
} // namespace AceAttorney