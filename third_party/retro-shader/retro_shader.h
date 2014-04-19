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

#ifndef __RARCH_SHADER_H
#define __RARCH_SHADER_H

#include <stdlib.h>

#include "boolean.h"
#include "shader_common.h"

static bool gl_shader_init(void* data, const char* shader_path)
{
   gl_t *gl = (gl_t*)data;
   const gl_shader_backend_t *backend = NULL;

   enum rarch_shader_type type = gfx_shader_parse_type(shader_path,
         gl->core_context ? RARCH_SHADER_GLSL : DEFAULT_SHADER_TYPE);

   if (type == RARCH_SHADER_NONE)
   {
      RARCH_LOG("[GL]: Not loading any shader.\n");
      return true;
   }

   switch (type)
   {
#ifdef HAVE_CG
      case RARCH_SHADER_CG:
         RARCH_LOG("[GL]: Using Cg shader backend.\n");
         backend = &gl_cg_backend;
         break;
#endif

#ifdef HAVE_GLSL
      case RARCH_SHADER_GLSL:
         RARCH_LOG("[GL]: Using GLSL shader backend.\n");
         backend = &gl_glsl_backend;
         break;
#endif

      default:
         break;
   }

   if (!backend)
   {
      RARCH_ERR("[GL]: Didn't find valid shader backend. Continuing without shaders.\n");
      return true;
   }

#ifdef HAVE_GLSL
   if (gl->core_context && RARCH_SHADER_CG)
   {
      RARCH_ERR("[GL]: Cg cannot be used with core GL context. Falling back to GLSL.\n");
      backend = &gl_glsl_backend;
      shader_path = NULL;
   }
#endif

   gl->shader = backend;
   bool ret = gl->shader->init(gl, shader_path);
   if (!ret)
   {
      RARCH_ERR("[GL]: Failed to init shader, falling back to stock.\n");
      ret = gl->shader->init(gl, NULL);
   }

   return ret;
}

static inline void gl_shader_deinit(void *data)
{
   gl_t *gl = (gl_t*)data;

   if (gl->shader)
      gl->shader->deinit();
   
   gl->shader = NULL;
}


#endif