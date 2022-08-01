#pragma once
#define SPDLOG_WCHAR_TO_UTF8_SUPPORT
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>


namespace Q3D
{
  namespace Core
  {
      class Log
      {
      private:
          static std::shared_ptr<spdlog::logger> s_Logger;
      public:
          Log() = default;
          static void Init();
          static auto GetLogger() -> std::shared_ptr<spdlog::logger>& { return s_Logger; }
      };
  }
} 

#define Q3D_TRACE(...)    ::Q3D::Core::Log::GetLogger()->trace(__VA_ARGS__)
#define Q3D_DEBUG(...)    ::Q3D::Core::Log::GetLogger()->debug(__VA_ARGS__)
#define Q3D_INFO(...)     ::Q3D::Core::Log::GetLogger()->info(__VA_ARGS__)
#define Q3D_WARN(...)     ::Q3D::Core::Log::GetLogger()->warn(__VA_ARGS__)
#define Q3D_ERROR(...)    ::Q3D::Core::Log::GetLogger()->error(__VA_ARGS__)
#define Q3D_CRITICAL(...) ::Q3D::Core::Log::GetLogger()->critical(__VA_ARGS__)