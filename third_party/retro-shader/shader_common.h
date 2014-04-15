/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2010-2014 - Hans-Kristian Arntzen
 * 
 *  RetroArch is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  RetroArch is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with RetroArch.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SHADER_COMMON_H__
#define SHADER_COMMON_H__

#include "boolean.h"
#include "gl_common.h"

#include "math/matrix.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PATH_MAX 512
#define GL_SHADER_STOCK_BLEND (GFX_MAX_SHADERS - 1)

enum rarch_shader_type
{
   RARCH_SHADER_CG,
   RARCH_SHADER_HLSL,
   RARCH_SHADER_GLSL,
   RARCH_SHADER_NONE
};

#define GFX_MAX_SHADERS 16
#define GFX_MAX_TEXTURES 8
#define GFX_MAX_VARIABLES 64

enum gfx_scale_type
{
   RARCH_SCALE_INPUT = 0,
   RARCH_SCALE_ABSOLUTE,
   RARCH_SCALE_VIEWPORT
};

enum gfx_filter_type
{
   RARCH_FILTER_UNSPEC = 0,
   RARCH_FILTER_LINEAR,
   RARCH_FILTER_NEAREST
};

enum gfx_wrap_type
{
   RARCH_WRAP_BORDER = 0, // Kinda deprecated, but keep as default. Will be translated to EDGE in GLES.
   RARCH_WRAP_DEFAULT = RARCH_WRAP_BORDER,
   RARCH_WRAP_EDGE,
   RARCH_WRAP_REPEAT,
   RARCH_WRAP_MIRRORED_REPEAT
};

struct gfx_fbo_scale
{
   enum gfx_scale_type type_x;
   enum gfx_scale_type type_y;
   float scale_x;
   float scale_y;
   unsigned abs_x;
   unsigned abs_y;
   bool fp_fbo;
   bool valid;
};

struct gfx_shader_pass
{
   struct
   {
      char cg[PATH_MAX];
      struct
      {
         char *vertex; // Dynamically allocated. Must be free'd.
         char *fragment; // Dynamically allocated. Must be free'd.
      } xml;
   } source;

   struct gfx_fbo_scale fbo;
   enum gfx_filter_type filter;
   enum gfx_wrap_type wrap;
   unsigned frame_count_mod;
};

struct gfx_shader_lut
{
   char id[64];
   char path[PATH_MAX];
   enum gfx_filter_type filter;
   enum gfx_wrap_type wrap;
};

// This is pretty big, shouldn't be put on the stack.
// Avoid lots of allocation for convenience.
struct gfx_shader
{
   enum rarch_shader_type type;

   // custom
   bool gfx_use_rgba;
   bool frame_is_reverse;

   bool modern; // Only used for XML shaders.
   char prefix[64];

   unsigned passes;
   struct gfx_shader_pass pass[GFX_MAX_SHADERS];

   unsigned luts;
   struct gfx_shader_lut lut[GFX_MAX_TEXTURES];

   unsigned variables;
   char script_path[PATH_MAX];
   char *script; // Dynamically allocated. Must be free'd. Only used by XML.
   char script_class[512];
};

struct gl_shader_backend
{
   bool (*init)(void *data, const char *path);
   void (*deinit)(void);
   void (*set_params)(void *data, unsigned width, unsigned height, 
         unsigned tex_width, unsigned tex_height, 
         unsigned out_width, unsigned out_height,
         unsigned frame_counter,
         const struct gl_tex_info *info, 
         const struct gl_tex_info *prev_info,
         const struct gl_tex_info *fbo_info, unsigned fbo_info_cnt);

   void (*use)(void *data, unsigned index);
   unsigned (*num_shaders)(void);
   bool (*filter_type)(unsigned index, bool *smooth);
   enum gfx_wrap_type (*wrap_type)(unsigned index);
   bool (*set_coords)(const struct gl_coords *coords);
   bool (*set_mvp)(void *data, const math_matrix *mat);
   unsigned (*get_prev_textures)(void);

   enum rarch_shader_type type;
};

typedef struct gl_shader_backend gl_shader_backend_t;

#if defined(HAVE_PSGL)
#define RARCH_GL_INTERNAL_FORMAT32 GL_ARGB_SCE
#define RARCH_GL_INTERNAL_FORMAT16 GL_RGB5 // TODO: Verify if this is really 565 or just 555.
#define RARCH_GL_TEXTURE_TYPE32 GL_BGRA
#define RARCH_GL_TEXTURE_TYPE16 GL_BGRA
#define RARCH_GL_FORMAT32 GL_UNSIGNED_INT_8_8_8_8_REV
#define RARCH_GL_FORMAT16 GL_RGB5
#elif defined(HAVE_OPENGLES)
// Imgtec/SGX headers have this missing.
#ifndef GL_BGRA_EXT
#define GL_BGRA_EXT 0x80E1
#endif
#ifdef IOS
#define RARCH_GL_INTERNAL_FORMAT32 GL_RGBA // Stupid Apple
#else
#define RARCH_GL_INTERNAL_FORMAT32 GL_BGRA_EXT
#endif
#define RARCH_GL_INTERNAL_FORMAT16 GL_RGB
#define RARCH_GL_TEXTURE_TYPE32 GL_BGRA_EXT
#define RARCH_GL_TEXTURE_TYPE16 GL_RGB
#define RARCH_GL_FORMAT32 GL_UNSIGNED_BYTE
#define RARCH_GL_FORMAT16 GL_UNSIGNED_SHORT_5_6_5
#else
// On desktop, we always use 32-bit.
#define RARCH_GL_INTERNAL_FORMAT32 GL_RGBA8
#define RARCH_GL_INTERNAL_FORMAT16 GL_RGBA8
#define RARCH_GL_TEXTURE_TYPE32 GL_BGRA
#define RARCH_GL_TEXTURE_TYPE16 GL_BGRA
#define RARCH_GL_FORMAT32 GL_UNSIGNED_INT_8_8_8_8_REV
#define RARCH_GL_FORMAT16 GL_UNSIGNED_INT_8_8_8_8_REV

// GL_RGB565 internal format isn't in desktop GL until 4.1 core (ARB_ES2_compatibility).
// Check for this.
#ifndef GL_RGB565
#define GL_RGB565 0x8D62
#endif
#define RARCH_GL_INTERNAL_FORMAT16_565 GL_RGB565
#define RARCH_GL_TEXTURE_TYPE16_565 GL_RGB
#define RARCH_GL_FORMAT16_565 GL_UNSIGNED_SHORT_5_6_5
#endif

struct texture_image
{
   unsigned width;
   unsigned height;
   uint32_t *pixels;
};

typedef struct gl
{
   bool core_context;
   const gl_shader_backend_t *shader;

   bool (*texture_image_load)(const char *path, struct texture_image* img);
   void (*texture_image_free)(struct texture_image *img);
};

typedef struct gl gl_t;

#ifdef __cplusplus
}
#endif

#endif

