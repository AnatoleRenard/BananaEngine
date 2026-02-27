#pragma once

#ifdef BANANA_USE_3D
    #ifdef BANANA_USE_VULKAN
        #error "Vulkan not implemented yet!"
    #else
        #include "OpenGL not implemented yet!"
    #endif
#endif

#ifdef BANANA_USE_2D
    //#error "2D not implemented yet!"
    #include "Input.hpp"
#endif