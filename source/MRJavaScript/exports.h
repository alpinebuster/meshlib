#pragma once

#ifdef _WIN32
#   ifdef MRJavaScript_EXPORTS
#       define MRJS_API __declspec(dllexport)
#   else
#       define MRJS_API __declspec(dllimport)
#   endif
#   define MRJS_CLASS
#else
#   define MRJS_API   __attribute__((visibility("default")))
#   define MRJS_CLASS __attribute__((visibility("default")))
#endif
