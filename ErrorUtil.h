
#pragma once
#include "Result.h"
#include <string>

namespace RHI {

// 将错误码转换为可读的字符串描述
inline std::string GetErrorCodeString(ErrorCode code) {
    switch (code) {
        case ErrorCode::Success:
            return "成功";
        
        // 通用错误
        case ErrorCode::Unknown:
            return "未知错误";
        case ErrorCode::InvalidArgument:
            return "无效参数";
        case ErrorCode::InvalidOperation:
            return "无效操作";
        case ErrorCode::NotImplemented:
            return "功能未实现";
        case ErrorCode::OutOfMemory:
            return "内存不足";
        
        // 初始化相关错误
        case ErrorCode::DeviceLost:
            return "设备丢失";
        case ErrorCode::DeviceNotCompatible:
            return "设备不兼容";
        case ErrorCode::AdapterNotFound:
            return "找不到适配器";
        
        // 交换链相关错误
        case ErrorCode::SwapChainCreateFailed:
            return "交换链创建失败";
        case ErrorCode::InvalidSurfaceFormat:
            return "无效的表面格式";
        case ErrorCode::InvalidPresentMode:
            return "无效的呈现模式";
        case ErrorCode::InvalidBufferCount:
            return "无效的缓冲数量";
        case ErrorCode::ResizeBuffersFailed:
            return "缓冲区重置失败";
        case ErrorCode::PresentFailed:
            return "呈现失败";
        
        // 资源相关错误
        case ErrorCode::ResourceCreateFailed:
            return "资源创建失败";
        case ErrorCode::ResourceMapFailed:
            return "资源映射失败";
        case ErrorCode::ResourceUnmapFailed:
            return "资源取消映射失败";
        
        // 同步相关错误
        case ErrorCode::SyncError:
            return "同步错误";
        case ErrorCode::TimeoutError:
            return "超时错误";
        
        // API特定错误
        case ErrorCode::DX12Error:
            return "DirectX12错误";
        case ErrorCode::VulkanError:
            return "Vulkan错误";
        case ErrorCode::MetalError:
            return "Metal错误";
        
        default:
            return "未定义错误码: " + std::to_string(static_cast<int>(code));
    }
}

// 错误处理宏
#define RHI_RETURN_IF_FAILED(result) \
    do { \
        auto&& _result = (result); \
        if (!_result.IsSuccess()) { \
            return std::move(_result); \
        } \
    } while (0)

#define RHI_RETURN_IF_FALSE(condition, code, message) \
    do { \
        if (!(condition)) { \
            return Result<void>::Failure(code, message); \
        } \
    } while (0)

// 错误结果构建辅助函数
template<typename T>
inline Result<T> MakeErrorResult(ErrorCode code, const std::string& message) {
    return Result<T>::Failure(code, message);
}

template<typename T>
inline Result<T> MakeSuccessResult(const T& value) {
    return Result<T>::Success(value);
}

inline Result<void> MakeSuccessResult() {
    return Result<void>::Success();
}

// 错误结果链式处理辅助函数
template<typename T, typename Func>
inline auto Then(const Result<T>& result, Func&& func) 
    -> decltype(func(result.GetValue()))
{
    if (!result.IsSuccess()) {
        return Result<typename std::decay<
            decltype(func(result.GetValue()).GetValue())
        >::type>::Failure(result.GetErrorCode(), result.GetErrorMessage());
    }
    return func(result.GetValue());
}

} // namespace RHI
