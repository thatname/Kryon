
#pragma once
#include "Result.h"
#include "Adapter.h"
#include "CommandBuffer.h"
#include <vector>

namespace RHI {

// 命令池标志
enum class CommandPoolFlag : uint32_t {
    None                = 0,
    Transient          = 1 << 0,    // 短暂命令池（频繁重置）
    ResetCommandBuffer = 1 << 1,    // 允许单独重置命令缓冲区
    Protected          = 1 << 2     // 受保护命令池
};

inline CommandPoolFlag operator|(CommandPoolFlag a, CommandPoolFlag b) {
    return static_cast<CommandPoolFlag>(
        static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

// 命令池描述
struct CommandPoolDesc {
    QueueType queueType;           // 队列类型
    CommandPoolFlag flags;         // 命令池标志
    uint32_t queueFamilyIndex;    // 队列族索引

    CommandPoolDesc() :
        queueType(QueueType::Graphics),
        flags(CommandPoolFlag::None),
        queueFamilyIndex(0) {}
};

// 命令缓冲区分配信息
struct CommandBufferAllocateInfo {
    CommandBufferType level;       // 命令缓冲区级别
    uint32_t count;               // 分配数量
    CommandBufferUsage usage;     // 使用标志

    CommandBufferAllocateInfo() :
        level(CommandBufferType::Graphics),
        count(1),
        usage(CommandBufferUsage::None) {}
};

// 命令池抽象基类
class ICommandPool {
public:
    virtual ~ICommandPool() = default;

    // 获取命令池描述
    virtual const CommandPoolDesc& GetDesc() const = 0;

    // 获取原生句柄
    // DirectX12: ID3D12CommandAllocator*
    // Vulkan: VkCommandPool
    // Metal: MTLCommandPool
    virtual Result<void*> GetNativeHandle() = 0;

    // 分配命令缓冲区
    virtual Result<std::vector<ICommandBuffer*>> AllocateCommandBuffers(
        const CommandBufferAllocateInfo& allocInfo) = 0;

    // 释放命令缓冲区
    virtual Result<void> FreeCommandBuffers(
        const std::vector<ICommandBuffer*>& commandBuffers) = 0;

    // 重置命令池（释放所有命令缓冲区）
    virtual Result<void> Reset() = 0;

    // 修剪未使用的命令缓冲区内存
    virtual Result<void> Trim() = 0;

protected:
    CommandPoolDesc m_desc;
};

// 用于创建命令池的工厂函数声明
using CommandPoolCreateFunc = Result<ICommandPool*> (*)(const CommandPoolDesc& desc);

} // namespace RHI
