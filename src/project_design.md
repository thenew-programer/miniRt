## Core Architecture Overview

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Scene Parser  │    │  Ray Tracer     │    │   Renderer      │
│   (rt_parser)   │───▶│   (rt_engine)   │───▶│  (rt_display)   │
└─────────────────┘    └─────────────────┘    └─────────────────┘
         │                       │                       │
         ▼                       ▼                       ▼
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│ Scene Model     │    │ Math/Geometry   │    │ MLX Wrapper     │
│ (rt_scene)      │    │ (rt_math)       │    │ (rt_window)     │
└─────────────────┘    └─────────────────┘    └─────────────────┘
```

## 1. Scene Model (rt_scene.h)

```c
#ifndef RT_SCENE_H
#define RT_SCENE_H

#include "rt_math.h"
#include "arena.h"

// Forward declarations
typedef struct s_scene t_scene;
typedef struct s_material t_material;

// Color representation
typedef struct s_color {
    float r, g, b;
} t_color;

// Material properties
typedef struct s_material {
    t_color color;
    float ambient_ratio;
    float diffuse_ratio;
    float specular_ratio;
    float shininess;
} t_material;

// Object types
typedef enum e_object_type {
    OBJ_SPHERE,
    OBJ_PLANE,
    OBJ_CYLINDER
} t_object_type;

// Generic object interface
typedef struct s_object {
    t_object_type type;
    t_material material;
    union {
        struct { t_vec3 center; float diameter; } sphere;
        struct { t_vec3 point; t_vec3 normal; } plane;
        struct { t_vec3 center; t_vec3 axis; float diameter; float height; } cylinder;
    } data;
    struct s_object *next;
} t_object;

// Lighting
typedef struct s_ambient_light {
    float ratio;
    t_color color;
} t_ambient_light;

typedef struct s_light {
    t_vec3 position;
    float brightness;
    t_color color;
    struct s_light *next;
} t_light;

// Camera
typedef struct s_camera {
    t_vec3 position;
    t_vec3 orientation;
    float fov;
} t_camera;

// Complete scene
typedef struct s_scene {
    t_camera camera;
    t_ambient_light ambient;
    t_light *lights;
    t_object *objects;
    
    // Validation flags
    bool has_camera;
    bool has_ambient;
} t_scene;

// Scene creation/destruction interface
t_scene *rt_scene_create(t_arena *arena);
void rt_scene_add_object(t_scene *scene, t_object *obj);
void rt_scene_add_light(t_scene *scene, t_light *light);
bool rt_scene_validate(const t_scene *scene);

#endif
```

## 2. Math/Geometry Module (rt_math.h)

```c
#ifndef RT_MATH_H
#define RT_MATH_H

#include <math.h>
#include <stdbool.h>

// Vector operations
typedef struct s_vec3 {
    float x, y, z;
} t_vec3;

typedef struct s_ray {
    t_vec3 origin;
    t_vec3 direction;
} t_ray;

typedef struct s_hit_info {
    bool hit;
    float distance;
    t_vec3 point;
    t_vec3 normal;
    struct s_object *object;
} t_hit_info;

// Vector operations interface
t_vec3 vec3_create(float x, float y, float z);
t_vec3 vec3_add(t_vec3 a, t_vec3 b);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
t_vec3 vec3_mul(t_vec3 v, float scalar);
t_vec3 vec3_normalize(t_vec3 v);
float vec3_dot(t_vec3 a, t_vec3 b);
t_vec3 vec3_cross(t_vec3 a, t_vec3 b);
float vec3_length(t_vec3 v);

// Ray operations
t_ray ray_create(t_vec3 origin, t_vec3 direction);
t_vec3 ray_at(const t_ray *ray, float t);

// Intersection testing (object-agnostic interface)
typedef t_hit_info (*intersect_func_t)(const t_ray *ray, const void *object_data);

// Color operations
t_color color_create(float r, float g, float b);
t_color color_add(t_color a, t_color b);
t_color color_mul(t_color c, float scalar);
t_color color_blend(t_color a, t_color b, float factor);

#endif
```

## 3. Parser Interface (rt_parser.h)

```c
#ifndef RT_PARSER_H
#define RT_PARSER_H

#include "rt_scene.h"
#include "arena.h"

// Parser result
typedef enum e_parse_result {
    PARSE_OK = 0,
    PARSE_ERROR_FILE_NOT_FOUND = -1,
    PARSE_ERROR_SYNTAX = -2,
    PARSE_ERROR_INVALID_VALUE = -3,
    PARSE_ERROR_MISSING_REQUIRED = -4,
    PARSE_ERROR_DUPLICATE = -5,
    PARSE_ERROR_MEMORY = -6
} t_parse_result;

typedef struct s_parse_error {
    t_parse_result code;
    int line;
    int column;
    char *message;
    struct s_parse_error *next;
} t_parse_error;

typedef struct s_parser_result {
    t_parse_result status;
    t_scene *scene;
    t_parse_error *errors;
} t_parser_result;

// Main parser interface - completely IO independent
t_parser_result rt_parse_scene_string(const char *content, size_t length, t_arena *arena);
t_parser_result rt_parse_scene_file(const char *filename, t_arena *arena);

// Error handling
void rt_parser_print_errors(const t_parse_error *errors);
const char *rt_parser_error_string(t_parse_result code);

#endif
```

## 4. Ray Tracing Engine (rt_engine.h)

```c
#ifndef RT_ENGINE_H
#define RT_ENGINE_H

#include "rt_scene.h"
#include "rt_math.h"
#include "arena.h"

// Rendering configuration
typedef struct s_render_config {
    int width;
    int height;
    int max_bounces;
    float epsilon;
} t_render_config;

// Pixel buffer (RGBA format)
typedef struct s_image {
    int width;
    int height;
    unsigned int *pixels;  // ARGB format for MLX
} t_image;

// Ray tracer interface
typedef struct s_raytracer t_raytracer;

// Engine creation/destruction
t_raytracer *rt_engine_create(t_arena *arena);
void rt_engine_set_scene(t_raytracer *tracer, const t_scene *scene);
void rt_engine_set_config(t_raytracer *tracer, const t_render_config *config);

// Rendering interface
t_image *rt_engine_render(t_raytracer *tracer, t_arena *arena);
t_color rt_engine_trace_ray(t_raytracer *tracer, const t_ray *ray);

// Intersection system (pluggable)
typedef struct s_intersector {
    intersect_func_t sphere_intersect;
    intersect_func_t plane_intersect;
    intersect_func_t cylinder_intersect;
} t_intersector;

t_intersector *rt_engine_get_intersector(t_raytracer *tracer);

#endif
```

## 5. Display/Window Interface (rt_window.h)

```c
#ifndef RT_WINDOW_H
#define RT_WINDOW_H

#include "rt_engine.h"
#include <stdbool.h>

// Forward declaration to avoid MLX dependency in header
typedef struct s_window t_window;

// Event handling
typedef enum e_key_event {
    KEY_ESCAPE = 53,
    KEY_Q = 12
} t_key_event;

typedef struct s_event_handlers {
    void (*on_key_press)(int keycode, void *param);
    void (*on_window_close)(void *param);
    void (*on_expose)(void *param);
    void *user_data;
} t_event_handlers;

// Window interface
t_window *rt_window_create(int width, int height, const char *title);
void rt_window_destroy(t_window *window);

// Image display
bool rt_window_display_image(t_window *window, const t_image *image);
void rt_window_set_event_handlers(t_window *window, const t_event_handlers *handlers);

// Main loop
void rt_window_run(t_window *window);
void rt_window_stop(t_window *window);

#endif
```

## 6. Main Application Interface (rt_app.h)

```c
#ifndef RT_APP_H
#define RT_APP_H

#include "rt_scene.h"
#include "rt_engine.h"
#include "rt_window.h"
#include "arena.h"

// Application state
typedef struct s_app {
    t_arena *arena;
    t_scene *scene;
    t_raytracer *engine;
    t_window *window;
    t_image *current_image;
    
    // Configuration
    t_render_config render_config;
    bool auto_render;
} t_app;

// Application lifecycle
t_app *rt_app_create(int argc, char **argv);
void rt_app_destroy(t_app *app);

// Main operations
bool rt_app_load_scene(t_app *app, const char *filename);
bool rt_app_render_scene(t_app *app);
void rt_app_run(t_app *app);

// Error handling
void rt_app_handle_error(const char *context, const char *message);

#endif
```

## Key Design Principles:

### 1. **Decoupling Strategies:**
- Each module has its own header with minimal dependencies
- Interface types are opaque (forward declarations)
- No direct MLX dependencies outside rt_window
- Arena allocator passed explicitly where needed

### 2. **Memory Management:**
- All allocations through arena
- No module owns the arena
- Clear ownership semantics
- Easy cleanup (just reset arena)

### 3. **Error Handling:**
- Each module has its own error types
- Errors propagate upward cleanly
- Detailed error context preserved
- No global error state

### 4. **Extensibility:**
- Object system supports adding new primitives
- Intersection system is pluggable
- Material system can be extended
- Parser can handle new element types

### 5. **Testability:**
- Each module can be unit tested independently
- IO separated from logic
- Mock interfaces possible
- No hidden dependencies

This architecture ensures each module can be developed, tested, and maintained independently while maintaining clean interfaces and avoiding tight coupling.
