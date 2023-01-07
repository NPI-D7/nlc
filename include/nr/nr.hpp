#pragma once

namespace nlc {
namespace nr {
void Init();
void Exit();
/// \brief Start Framedrawing
void DrawBeg();
/// \brief End Framedrawing
void DrawEnd();
/// \brief Draw On Screen
/// \param screen 0 = Top, 1 = Bottom, 2 = TopRight
} // namespace nr
} // namespace nlc