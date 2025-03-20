
#pragma once
#include <string>

namespace RHI {

// 错误码枚举
enum class ErrorCode {
    // 成功
    Success = 0,

    // 通用错误
    Unknown = 1,                    // 未知错误
    InvalidArgument = 2,            // 无效参数
    InvalidOperation = 3,           // 无效操作
    NotImplemented = 4,             // 功能未实现
    OutOfMemory = 5,               // 内存不足
    
    // 初始化相关错误
    DeviceLost = 1000,             // 设备丢失
    DeviceNotCompatible = 1001,    // 设备不兼容
    AdapterNotFound = 1002,        // 找不到适配器
    
    // 交换链相关错误
    SwapChainCreateFailed = 2000,  // 交换链创建失败
    InvalidSurfaceFormat = 2001,   // 无效的表面格式
    InvalidPresentMode = 2002,     // 无效的呈现模式
    InvalidBufferCount = 2003,     // 无效的缓冲数量
    ResizeBuffersFailed = 2004,    // 缓冲区重置失败
    PresentFailed = 2005,          // 呈现失败
    
    // 资源相关错误
    ResourceCreateFailed = 3000,   // 资源创建失败
    ResourceMapFailed = 3001,      // 资源映射失败
    ResourceUnmapFailed = 3002,    // 资源取消映射失败
    
    // 同步相关错误
    SyncError = 4000,              // 同步错误
    TimeoutError = 4001,           // 超时错误
    
    // API特定错误
    DX12Error = 10000,             // DirectX12特定错误
    VulkanError = 20000,           // Vulkan特定错误
    MetalError = 30000             // Metal特定错误
};

// 结果包装类
template<typename T>
class Result {
public:
    // 构造成功结果
    static Result<T> Success(const T& value) {
        return Result<T>(value);
    }
    
    // 构造成功结果（void特化）
    static Result<void> Success() {
        return Result<void>();
    }
    
    // 构造错误结果
    static Result<T> Failure(ErrorCode code, const std::string& message) {
        return Result<T>(code, message);
    }
    
    // 检查是否成功
    bool IsSuccess() const { return m_errorCode == ErrorCode::Success; }
    
    // 获取错误码
    ErrorCode GetErrorCode() const { return m_errorCode; }
    
    // 获取错误信息
    const std::string& GetErrorMessage() const { return m_errorMessage; }
    
    // 获取结果值（非void类型）
    const T& GetValue() const { return m_value; }
    T& GetValue() { return m_value; }

private:
    // 成功结果构造函数
    Result(const T& value) 
        : m_errorCode(ErrorCode::Success)
        , m_value(value) {}
    
    // void特化的成功结果构造函数
    Result() 
        : m_errorCode(ErrorCode::Success) {}
    
    // 错误结果构造函数
    Result(ErrorCode code, const std::string& message)
        : m_errorCode(code)
        , m_errorMessage(message) {}

private:
    ErrorCode m_errorCode = ErrorCode::Success;
    std::string m_errorMessage;
    T m_value;
};

// void特化
template<>
class Result<void> {
public:
    static Result<void> Success() {
        return Result<void>();
    }
    
    static Result<void> Failure(ErrorCode code, const std::string& message) {
        return Result<void>(code, message);
    }
    
    bool IsSuccess() const { return m_errorCode == ErrorCode::Success; }
    ErrorCode GetErrorCode() const { return m_errorCode; }
    const std::string& GetErrorMessage() const { return m_errorMessage; }

private:
    Result() : m_errorCode(ErrorCode::Success) {}
    Result(ErrorCode code, const std::string& message)
        : m_errorCode(code)
        , m_errorMessage(message) {}

private:
    ErrorCode m_errorCode = ErrorCode::Success;
    std::string m_errorMessage;
};

} // namespace RHI
