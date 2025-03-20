
#pragma once
#include <cstdint>
#include "Format.h"
#include "Result.h"

namespace RHI {

// 定义交换链相关的枚举和结构体
enum class PresentMode {
    Immediate,      // 立即显示，可能会撕裂 
                   // - Vulkan: VK_PRESENT_MODE_IMMEDIATE_KHR
                   // - DX12: DXGI_SWAP_EFFECT_SEQUENTIAL
                   // - Metal: MTLPresentModeImmediate
    
    Fifo,          // 垂直同步 
                   // - Vulkan: VK_PRESENT_MODE_FIFO_KHR
                   // - DX12: DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL with vsync
                   // - Metal: MTLPresentModeFilfo
    
    Mailbox,       // 三重缓冲 
                   // - Vulkan: VK_PRESENT_MODE_MAILBOX_KHR
                   // - DX12: DXGI_SWAP_EFFECT_FLIP_DISCARD with extra buffer
                   // - Metal: MTLPresentModeMailbox
    
    FifoRelaxed    // 自适应垂直同步
                   // - Vulkan: VK_PRESENT_MODE_FIFO_RELAXED_KHR
                   // - DX12: 通过DXGI_PRESENT_ALLOW_TEARING实现
                   // - Metal: 通过CADisplayLink实现
};

struct SwapChainDesc {
    uint32_t width;                 // 交换链宽度
    uint32_t height;                // 交换链高度
    uint32_t bufferCount;          // 缓冲数量（通常为2或3）
    Format format;                  // 颜色格式
    PresentMode presentMode;        // 呈现模式
    bool isVSync;                   // 是否开启垂直同步
    bool isHDR;                     // 是否支持HDR
    uint32_t refreshRate;           // 刷新率（以Hz为单位）

    SwapChainDesc() :
        width(0),
        height(0),
        bufferCount(2),
        format(Format::BGRA8_UNORM),
        presentMode(PresentMode::Fifo),
        isVSync(true),
        isHDR(false),
        refreshRate(60) {}
};

struct PresentInfo {
    uint32_t backBufferIndex;       // 当前后缓冲区索引
    bool waitForVBlank;             // 是否等待垂直同步
    
    PresentInfo() :
        backBufferIndex(0),
        waitForVBlank(true) {}
};

// 交换链抽象基类
class ISwapChain {
public:
    virtual ~ISwapChain() = default;

    // 初始化交换链
    virtual Result<void> Initialize(const SwapChainDesc& desc) = 0;

    // 清理资源
    virtual Result<void> Cleanup() = 0;

    // 重置交换链（例如窗口大小改变时）
    virtual Result<void> Resize(uint32_t width, uint32_t height) = 0;

    // 获取当前后缓冲区索引
    virtual Result<uint32_t> GetCurrentBackBufferIndex() const = 0;

    // 获取交换链中的缓冲区数量
    virtual Result<uint32_t> GetBufferCount() const = 0;

    // 获取交换链描述信息
    virtual const SwapChainDesc& GetDesc() const = 0;

    // 呈现画面
    virtual Result<void> Present(const PresentInfo& presentInfo) = 0;

    // 等待之前的呈现完成
    virtual Result<void> WaitForPresent() = 0;

    // 获取是否支持特定的呈现模式
    virtual Result<bool> IsPresentModeSupported(PresentMode mode) const = 0;

    // 获取当前后缓冲区的本地句柄
    virtual Result<void*> GetCurrentBackBufferHandle() = 0;

    // 获取交换链的本地句柄
    virtual Result<void*> GetNativeHandle() = 0;

protected:
    SwapChainDesc m_desc;
};

// 用于创建特定API实现的工厂函数声明
using SwapChainCreateFunc = Result<ISwapChain*> (*)(void* nativeWindowHandle);

} // namespace RHI
