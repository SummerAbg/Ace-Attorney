#include "Resources.h"

namespace AceAttorney {
AsciiTextColor clr_ChatBox_Name = {ASCII_COLOR_WHITE, ASCII_COLOR_BLUE};
AsciiTextColor clr_ChatBox_Text = {ASCII_COLOR_WHITE, ASCII_COLOR_GREY};

AsciiBasicString str_ChatBox_Border = getAdaptiveStr({
    '=',
    AsciiTextColor(ASCII_COLOR_WHITE, ASCII_COLOR_GREY),
    false,
});
AsciiBasicString str_ChatBox = getAdaptiveStr({
    '#',
    AsciiTextColor(ASCII_COLOR_GREY, ASCII_COLOR_GREY),
    false,
});
} // namespace AceAttorney