#pragma once

//std
#include <vector>
#include <array>
#include <unordered_map>
#include <variant>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

//sdl2
#include <SDL2/SDL.h>

//assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//glm
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

//spdlog
#define FMT_HEADER_ONLY
#define SPDLOG_FMT_EXTERNAL
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

//logger
#ifdef BANANA_LOG
    namespace banana
    {
        class Logger
        {
            public:
                Logger()
                {
                    m_SPD = spdlog::stdout_color_mt("stdout");
                    spdlog::set_level(spdlog::level::trace);
                    spdlog::set_pattern("%^[%T]: %v%$");
                }

                static std::shared_ptr<spdlog::logger>& ref()
                {
                    static Logger logger;
                    return logger.m_SPD;
                }

            private:
                std::shared_ptr<spdlog::logger> m_SPD;
        };
    }

    //logging macros
    #define BANANA_TRACE(...)  do { banana::Logger::ref()->trace(__VA_ARGS__); } while (0)
    #define BANANA_DEBUG(...)  do { banana::Logger::ref()->debug(__VA_ARGS__); } while (0)
    #define BANANA_INFO(...)   do { banana::Logger::ref()->info(__VA_ARGS__);  } while (0)
    #define BANANA_WARN(...)   do { banana::Logger::ref()->warn(__VA_ARGS__);  } while (0)
    #define BANANA_ERROR(...)  do { banana::Logger::ref()->error(__VA_ARGS__); } while (0)
    #define BANANA_FATAL(...)  do { banana::Logger::ref()->critical(__VA_ARGS__); std::abort(); } while (0)
#else
    #define BANANA_TRACE(...)  do { } while (0)
    #define BANANA_DEBUG(...)  do { } while (0)
    #define BANANA_INFO(...)   do { } while (0)
    #define BANANA_WARN(...)   do { } while (0)
    #define BANANA_ERROR(...)  do { } while (0)
    #define BANANA_FATAL(...)  do { std::abort(); } while (0)
#endif

//macros
namespace banana
{
    constexpr bool checkFlag(uint32_t flags, uint32_t check)
    {
        return (flags & check) == check;
    }
}