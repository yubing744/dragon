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

#include <stdlib.h>
#include <string.h>

#include "shader_common.h"

static char *find_last_slash(const char *str)
{
   const char *slash = strrchr(str, '/');
#ifdef _WIN32
   const char *backslash = strrchr(str, '\\');
   if (backslash && ((slash && backslash > slash) || !slash))
      slash = backslash;
#endif

   return (char*)slash;
}

const char *path_basename(const char *path)
{
   const char *last = find_last_slash(path);

   if (last)
      return last + 1;
   else
      return path;
}

const char *path_get_extension(const char *path)
{
   const char *ext = strrchr(path_basename(path), '.');
   if (ext)
      return ext + 1;
   else
      return "";
}

enum rarch_shader_type gfx_shader_parse_type(const char *path, enum rarch_shader_type fallback)
{
   if (!path)
      return fallback;

   const char *ext = path_get_extension(path);

   if (strcmp(ext, "cg") == 0 || strcmp(ext, "cgp") == 0)
      return RARCH_SHADER_CG;
   else if (strcmp(ext, "shader") == 0 || strcmp(ext, "glslp") == 0 || strcmp(ext, "glsl") == 0)
      return RARCH_SHADER_GLSL;

   return fallback;
}