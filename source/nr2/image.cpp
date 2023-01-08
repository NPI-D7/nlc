#include <3ds.h>
#include <citro2d.h>
#include <nr2/image.hpp>
#include <nuseful/lodepng.hpp>

std::vector<C2D_Image> image_storage;

C2D_Image *GetImage(int reg) {
  if (reg > 0)
    return &image_storage[reg - 1];
  return new C2D_Image;
}

namespace nlc {
image::image() {
  // Nothing to Do!
}

image::~image() {
  // Nothing to Do!
}

void image::LoadFile(std::string path) {
  std::vector<u8> ImageBuffer;
  unsigned width, height;
  if (loadet) {
    C3D_TexDelete(GetImage(this->regid)->tex);
    loadet = false;
  }
  if (regid == 0) {
    C2D_Image cnimg;
    image_storage.push_back(cnimg);
    this->regid = image_storage.size();
  }
  lodepng::decode(ImageBuffer, width, height, path);

  GetImage(this->regid)->tex = new C3D_Tex;
  GetImage(this->regid)->subtex =
      new Tex3DS_SubTexture({(u16)width, (u16)height, 0.0f, 1.0f,
                             width / 1024.0f, 1.0f - (height / 1024.0f)});

  C3D_TexInit(GetImage(this->regid)->tex, 1024, 1024, GPU_RGBA8);
  C3D_TexSetFilter(GetImage(this->regid)->tex, GPU_LINEAR, GPU_LINEAR);
  GetImage(this->regid)->tex->border = 0xFFFFFFFF;
  C3D_TexSetWrap(GetImage(this->regid)->tex, GPU_CLAMP_TO_BORDER,
                 GPU_CLAMP_TO_BORDER);

  for (u32 x = 0; x < width && x < 1024; x++) {
    for (u32 y = 0; y < height && y < 1024; y++) {
      const u32 dstPos = ((((y >> 3) * (1024 >> 3) + (x >> 3)) << 6) +
                          ((x & 1) | ((y & 1) << 1) | ((x & 2) << 1) |
                           ((y & 2) << 2) | ((x & 4) << 2) | ((y & 4) << 3))) *
                         4;

      const u32 srcPos = (y * width + x) * 4;
      ((uint8_t *)GetImage(this->regid)->tex->data)[dstPos + 0] =
          ImageBuffer.data()[srcPos + 3];
      ((uint8_t *)GetImage(this->regid)->tex->data)[dstPos + 1] =
          ImageBuffer.data()[srcPos + 2];
      ((uint8_t *)GetImage(this->regid)->tex->data)[dstPos + 2] =
          ImageBuffer.data()[srcPos + 1];
      ((uint8_t *)GetImage(this->regid)->tex->data)[dstPos + 3] =
          ImageBuffer.data()[srcPos + 0];
    }
  }
  loadet = true;
}

void image::LoadBuffer(std::vector<unsigned char *> buffer) {}

int image::GetReg() { return regid; }
} // namespace nlc