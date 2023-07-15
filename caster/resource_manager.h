#ifndef __RESOURCE_MANAGER_H
#define __RESOURCE_MANAGER_H

#include "texture2d.h"
#include "shader.h"
#include "level.h"

/**********************************************************
 * \brief Initialize Resource Manager
 **********************************************************/
void rm_init(void);

/**********************************************************
 * \brief Destroy Resource Manager
 **********************************************************/
void rm_destroy(void);

/**********************************************************
 * \brief Load shader into Resource Manager
 *
 * \param vertex_file       path to vertex file
 * \param fragment_file     path to fragment file
 * \param geometry_file     path to geometry file
 * \param name              key to define
 *
 * \returns shader_t * from Resource Manager
 **********************************************************/
shader_t *rm_load_shader(const char *vertex_file, const char *fragment_file, const char *geometry_file, const char *name);

/**********************************************************
 * \brief Load texture into Resource Manager
 *
 * \param file              path to texture
 * \param alpha             enable alpha
 * \param name              key to define
 *
 * \returns texture2d_t * from Resource Manager
 **********************************************************/
texture2d_t *rm_load_texture(const char *file, bool alpha, const char *name);

/**********************************************************
 * \brief Load level into Resource Manager
 *
 * \param file              path to level file
 * \param name              key to define
 *
 * \returns level_t * from Resource Manager
 **********************************************************/
level_t *rm_load_level(const char *file, const char *name);

/**********************************************************
 * \brief Load shader from Resource Manager
 *
 * \param name              key
 *
 * \returns shader_t * from Resource Manager
 **********************************************************/
shader_t *rm_get_shader(const char *name);

/**********************************************************
 * \brief Load texture from Resource Manager
 *
 * \param name              key
 *
 * \returns texture2d_t * from Resource Manager
 **********************************************************/
texture2d_t *rm_get_texture(const char *name);

/**********************************************************
 * \brief Load level from Resource Manager
 *
 * \param name              key
 *
 * \returns level_t * from Resource Manager
 **********************************************************/
level_t *rm_get_level(const char *name);

#endif /* __RESOURCE_MANAGER_H */
