
#pragma once
#include "Result.h"
#include "Adapter.h"
#include "CommandBuffer.h"
#include <vector>

namespace RHI {

// 队列描述
struct QueueDesc {
    QueueType type;              // 队列类型
    uint32_t queueFamilyIndex;  // 队列族索引
    uint32_t queueIndex;        // 队列索引
    bool enableTimeQueries;      // 是否启用时间查询
};

// 设备描述
struct DeviceDesc {
    std::vector<QueueDesc> queues;           // 队列描述列表
    DeviceFeatures enabledFeatures;          // 启用的特性
    std::vector<std::string> extensions;     // 启用的扩展
    std::vector<std::string> layers;         // 启用的层
    bool enableDebugMarkers;                 // 是否启用调试标记
};

// 命令队列抽象基类
class IQueue {
public:
    virtual ~IQueue() = default;

    // 获取原生句柄
    // DirectX12: ID3D12CommandQueue*
    // Vulkan: VkQueue
    // Metal: id<MTLCommandQueue>
    virtual Result<void*> GetNativeHandle() = 0;

    // 提交命令缓冲区
    virtual Result<void> Submit(
        const std::vector<ICommandBuffer*>& commandBuffers,
        const std::vector<ISemaphore*>& waitSemaphores,
        const std::vector<ISemaphore*>& signalSemaphores,
        IFence* fence) = 0;

    // 等待队列空闲
    virtual Result<void> WaitIdle() = 0;

    // 呈现
    virtual Result<void> Present(
        class ISwapChain* swapChain,
        uint32_t imageIndex,
        const std::vector<ISemaphore*>& waitSemaphores) = 0;

protected:
    QueueDesc m_desc;
};

// 设备抽象基类
class IDevice {
public:
    virtual ~IDevice() = default;

    // 获取原生句柄
    // DirectX12: ID3D12Device*
    // Vulkan: VkDevice
    // Metal: id<MTLDevice>
    virtual Result<void*> GetNativeHandle() = 0;

    // 获取命令队列
    virtual Result<IQueue*> GetQueue(QueueType type, uint32_t index) = 0;

    // 创建命令池
    virtual Result<class ICommandPool*> CreateCommandPool(
        QueueType type,
        bool transient = false) = 0;

    // 创建交换链
    virtual Result<class ISwapChain*> CreateSwapChain(
        const class SwapChainDesc& desc) = 0;

    // 创建缓冲区
    virtual Result<class IBuffer*> CreateBuffer(
        const class BufferDesc& desc) = 0;

    // 创建纹理
    virtual Result<class ITexture*> CreateTexture(
        const class TextureDesc& desc) = 0;

    // 创建着色器
    virtual Result<class IShader*> CreateShader(
        const class ShaderDesc& desc) = 0;

    // 创建管线状态
    virtual Result<class IPipelineState*> CreatePipelineState(
        const class PipelineStateDesc& desc) = 0;

    // 创建描述符集布局
    virtual Result<class IDescriptorSetLayout*> CreateDescriptorSetLayout(
        const class DescriptorSetLayoutDesc& desc) = 0;

    // 创建描述符池
    virtual Result<class IDescriptorPool*> CreateDescriptorPool(
        const class DescriptorPoolDesc& desc) = 0;

    // 创建栅栏
    virtual Result<class IFence*> CreateFence(
        const class FenceDesc& desc) = 0;

    // 创建信号量
    virtual Result<class ISemaphore*> CreateSemaphore(
        const class SemaphoreDesc& desc) = 0;

    // 创建事件
    virtual Result<class IEvent*> CreateEvent(
        const class EventDesc& desc) = 0;

    // 分配内存
    virtual Result<class IMemory*> AllocateMemory(
        const class MemoryDesc& desc) = 0;

    // 等待设备空闲
    virtual Result<void> WaitIdle() = 0;

protected:
    DeviceDesc m_desc;
};

// 用于创建设备的工厂函数声明
using DeviceCreateFunc = Result<IDevice*> (*)(IAdapter* adapter, const DeviceDesc& desc);

} // namespace RHI
