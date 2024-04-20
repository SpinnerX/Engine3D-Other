#pragma once
#include <memory>
#include <Engine3D/Core/core.h>
#include <spdlog/spdlog.h>
#include <fmt/core.h>
#include <spdlog/fmt/ostr.h>
#include <cstdarg>

namespace Engine3D{
    class EngineLogger{
    public:
        EngineLogger();
        ~EngineLogger();

        //! @note Instantiating our logger through this Init function
        static void Init();

        //! @note Checking if our logger is already instantiated by the engine, though should not be called but just checking in case it isn't.
        static bool isLoggerInit() {
            return (coreLogger == nullptr || clientLogger == nullptr);
        }

        inline static Ref<spdlog::logger>& GetCoreLogger(){
            if(EngineLogger::isLoggerInit()){
                spdlog::log(spdlog::level::critical, "EngineLogger::Init() needs to be called!\n");
                std::terminate();
            }

            return coreLogger;
        }

        inline static Ref<spdlog::logger>& GetClientLogger() {
            if(EngineLogger::isLoggerInit()){
                spdlog::log(spdlog::level::critical, "EngineLogger::Init() needs to be called!\n");
                std::terminate();
            }
            
            return clientLogger;
        }

    private:
        static Ref<spdlog::logger> coreLogger;
        static Ref<spdlog::logger> clientLogger;
    };
};

template<typename... T>
inline void coreLogTrace2(fmt::format_string<T...> fmt, T&&... args) {
    Engine3D::EngineLogger::GetCoreLogger()->trace(fmt, std::forward<T>(args)...);
}

template<typename... T>
inline void coreLogTrace(fmt::format_string<T...> fmt, T&&... args) {
    Engine3D::EngineLogger::GetCoreLogger()->trace(fmt, std::forward<T>(args)...);
}

template<typename... T>
inline void coreLogInfo(fmt::format_string<T...> fmt, T&&... args) {
    Engine3D::EngineLogger::GetCoreLogger()->info(fmt, std::forward<T>(args)...);
}

template<typename... T>
inline void coreLogWarn(fmt::format_string<T...> fmt, T &&...args) {
    Engine3D::EngineLogger::GetCoreLogger()->warn(fmt, std::forward<T>(args)...);
}

template<typename... T>
inline void coreLogError(fmt::format_string<T...> fmt, T &&...args) {
    Engine3D::EngineLogger::GetCoreLogger()->error(fmt, std::forward<T>(args)...);
}

template<typename... T>
inline void coreLogFatal(fmt::format_string<T...> fmt, T &&...args) {
    Engine3D::EngineLogger::GetCoreLogger()->critical(fmt, std::forward<T>(args)...);
}

// ------------ Client logs ------------
template<typename... T>
inline void clientLogTrace(fmt::format_string<T...> fmt, T &&...args) {
    Engine3D::EngineLogger::GetClientLogger()->trace(fmt, std::forward<T>(args)...);
}

template<typename... T>
inline void clientLogInfo(fmt::format_string<T...> fmt, T &&...args) {
    Engine3D::EngineLogger::GetClientLogger()->info(fmt, std::forward<T>(args)...);
}

template<typename... T>
inline void clientLogWarn(fmt::format_string<T...> fmt, T &&...args) {
    Engine3D::EngineLogger::GetClientLogger()->warn(fmt, std::forward<T>(args)...);
}

template<typename... T>
inline void clientLogError(fmt::format_string<T...> fmt, T &&...args) {
    Engine3D::EngineLogger::GetClientLogger()->error(fmt, std::forward<T>(args)...);
}

template<typename... T>
inline void clientLogFatal(fmt::format_string<T...> fmt, T &&...args) {
    Engine3D::EngineLogger::GetClientLogger()->critical(fmt, std::forward<T>(args)...);
}