#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include <nr/nr.hpp>

C3D_RenderTarget *targets[3];

C2D_TextBuf TextBuf;
C2D_Font Font;

namespace nlc {
namespace nr {
void Init() {
  C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
  C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
  C2D_Prepare();
  targets[0] = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
  targets[2] = C2D_CreateScreenTarget(GFX_TOP, GFX_RIGHT);
  targets[1] = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

  TextBuf = C2D_TextBufNew(4096);
  Font = C2D_FontLoadSystem(CFG_REGION_USA);
}
void Exit() {
  C2D_TextBufDelete(TextBuf);
  C2D_Fini();
  C3D_Fini();
}
void DrawBeg() {
  C2D_TextBufClear(TextBuf);
  C2D_TargetClear(targets[0], C2D_Color32(0, 0, 0, 0));
  C2D_TargetClear(targets[1], C2D_Color32(0, 0, 0, 0));
  C2D_TargetClear(targets[2], C2D_Color32(0, 0, 0, 0));
  C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
}
void DrawEnd() { C3D_FrameEnd(0); }
} // namespace nr
} // namespace nlc