
#pragma once
#include "Result.h"
#include <cstdint>

namespace RHI {

// 栅栏类型
enum class FenceType {
    CPUToGPU,           // CPU到GPU同步
    GPUToCPU            // GPU到CPU同步
};

// 栅栏描述
struct FenceDesc {
    FenceType type;     // 栅栏类型
    bool signaled;      // 是否已发出信号

    FenceDesc() :
        type(FenceType::CPUToGPU),
        signaled(false) {}
};

// 信号量描述
struct SemaphoreDesc {
    bool binary;        // 是否为二进制信号量
    uint64_t initialValue;  // 初始值（仅用于时间线信号量）

    SemaphoreDesc() :
        binary(true),
        initialValue(0) {}
};

// 事件描述
struct EventDesc {
    bool manualReset;   // 是否为手动重置事件

    EventDesc() :
        manualReset(false) {}
};

// 栅栏抽象基类
class IFence {
public:
    virtual ~IFence() = default;

    // 获取原生句柄
    // DirectX12: ID3D12Fence*
    // Vulkan: VkFence
    // Metal: MTLFence
    virtual Result<void*> GetNativeHandle() = 0;

    // 获取当前值
    virtual Result<uint64_t> GetValue() const = 0;

    // 设置值（仅用于CPU到GPU同步）
    virtual Result<void> Signal(uint64_t value) = 0;

    // 等待特定值
    virtual Result<void> Wait(uint64_t value, uint64_t timeout) = 0;

    // 重置栅栏
    virtual Result<void> Reset() = 0;

protected:
    FenceDesc m_desc;
};

// 信号量抽象基类
class ISemaphore {
public:
    virtual ~ISemaphore() = default;

    // 获取原生句柄
    // DirectX12: ID3D12Fence*（用作信号量）
    // Vulkan: VkSemaphore
    // Metal: MTLEvent
    virtual Result<void*> GetNativeHandle() = 0;

    // 获取当前值（仅用于时间线信号量）
    virtual Result<uint64_t> GetValue() const = 0;

    // 等待特定值（仅用于时间线信号量）
    virtual Result<void> Wait(uint64_t value, uint64_t timeout) = 0;

protected:
    SemaphoreDesc m_desc;
};

// 事件抽象基类
class IEvent {
public:
    virtual ~IEvent() = default;

    // 获取原生句柄
    // DirectX12: ID3D12Event*
    // Vulkan: VkEvent
    // Metal: MTLEvent
    virtual Result<void*> GetNativeHandle() = 0;

    // 设置事件
    virtual Result<void> Set() = 0;

    // 重置事件
    virtual Result<void> Reset() = 0;

    // 获取状态
    virtual Result<bool> GetStatus() const = 0;

protected:
    EventDesc m_desc;
};

// 用于创建同步对象的工厂函数声明
using FenceCreateFunc = Result<IFence*> (*)(const FenceDesc& desc);
using SemaphoreCreateFunc = Result<ISemaphore*> (*)(const SemaphoreDesc& desc);
using EventCreateFunc = Result<IEvent*> (*)(const EventDesc& desc);

} // namespace RHI
