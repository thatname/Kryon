
#pragma once
#include "Result.h"
#include "Format.h"
#include <cstdint>

namespace RHI {

// 命令缓冲区类型
enum class CommandBufferType {
    Graphics,           // 图形命令（包含所有类型命令）
    Compute,            // 仅计算命令
    Transfer,          // 仅传输命令
    Bundle             // 命令包（二级命令缓冲区）
};

// 命令缓冲区用途标志（可组合）
enum class CommandBufferUsage : uint32_t {
    None                = 0,
    OneTimeSubmit       = 1 << 0,    // 一次性提交
    RenderPassContinue  = 1 << 1,    // 继续渲染通道
    SimultaneousUse     = 1 << 2,    // 可同时使用
};

inline CommandBufferUsage operator|(CommandBufferUsage a, CommandBufferUsage b) {
    return static_cast<CommandBufferUsage>(
        static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

// 资源屏障类型
enum class BarrierType {
    Transition,         // 资源状态转换
    UAV,               // UAV访问同步
    Aliasing,          // 资源别名同步
    Global             // 全局内存屏障
};

// 资源屏障描述
struct BarrierDesc {
    BarrierType type;              // 屏障类型
    void* resource;                // 资源指针
    uint32_t stateBefore;          // 转换前状态
    uint32_t stateAfter;           // 转换后状态
};

// 渲染通道描述
struct RenderPassDesc {
    uint32_t colorAttachmentCount;  // 颜色附件数量
    void* colorAttachments;         // 颜色附件数组
    void* depthStencilAttachment;   // 深度模板附件
};

// 视口描述
struct Viewport {
    float x;
    float y;
    float width;
    float height;
    float minDepth;
    float maxDepth;
};

// 裁剪矩形
struct Scissor {
    int32_t x;
    int32_t y;
    uint32_t width;
    uint32_t height;
};

// 命令缓冲区描述
struct CommandBufferDesc {
    CommandBufferType type;        // 命令缓冲区类型
    CommandBufferUsage usage;      // 使用标志
    bool isSecondary;             // 是否为二级命令缓冲区

    CommandBufferDesc() :
        type(CommandBufferType::Graphics),
        usage(CommandBufferUsage::None),
        isSecondary(false) {}
};

// 命令缓冲区抽象基类
class ICommandBuffer {
public:
    virtual ~ICommandBuffer() = default;

    // 获取命令缓冲区描述
    virtual const CommandBufferDesc& GetDesc() const = 0;

    // 获取原生句柄
    // DirectX12: ID3D12GraphicsCommandList*
    // Vulkan: VkCommandBuffer
    // Metal: id<MTLCommandBuffer>
    virtual Result<void*> GetNativeHandle() = 0;

    // 开始记录命令
    virtual Result<void> Begin() = 0;

    // 结束记录命令
    virtual Result<void> End() = 0;

    // 重置命令缓冲区
    virtual Result<void> Reset() = 0;

    // 开始渲染通道
    virtual Result<void> BeginRenderPass(const RenderPassDesc& desc) = 0;

    // 结束渲染通道
    virtual Result<void> EndRenderPass() = 0;

    // 设置视口
    virtual Result<void> SetViewport(const Viewport& viewport) = 0;

    // 设置裁剪矩形
    virtual Result<void> SetScissor(const Scissor& scissor) = 0;

    // 设置管线状态
    virtual Result<void> SetPipelineState(void* pipelineState) = 0;

    // 设置描述符集
    virtual Result<void> SetDescriptorSet(
        uint32_t set,
        void* descriptorSet) = 0;

    // 设置顶点缓冲区
    virtual Result<void> SetVertexBuffer(
        uint32_t slot,
        void* vertexBufferView) = 0;

    // 设置索引缓冲区
    virtual Result<void> SetIndexBuffer(void* indexBufferView) = 0;

    // 设置推送常量
    virtual Result<void> PushConstants(
        void* layout,
        uint32_t offset,
        uint32_t size,
        const void* data) = 0;

    // 绘制
    virtual Result<void> Draw(
        uint32_t vertexCount,
        uint32_t instanceCount,
        uint32_t firstVertex,
        uint32_t firstInstance) = 0;

    // 索引绘制
    virtual Result<void> DrawIndexed(
        uint32_t indexCount,
        uint32_t instanceCount,
        uint32_t firstIndex,
        int32_t vertexOffset,
        uint32_t firstInstance) = 0;

    // 间接绘制
    virtual Result<void> DrawIndirect(
        void* argumentBuffer,
        uint32_t offset,
        uint32_t drawCount,
        uint32_t stride) = 0;

    // 调度计算
    virtual Result<void> Dispatch(
        uint32_t groupCountX,
        uint32_t groupCountY,
        uint32_t groupCountZ) = 0;

    // 间接调度计算
    virtual Result<void> DispatchIndirect(
        void* argumentBuffer,
        uint32_t offset) = 0;

    // 复制缓冲区
    virtual Result<void> CopyBuffer(
        void* srcBuffer,
        void* dstBuffer,
        uint32_t regionCount,
        void* regions) = 0;

    // 复制纹理
    virtual Result<void> CopyTexture(
        void* srcTexture,
        void* dstTexture,
        uint32_t regionCount,
        void* regions) = 0;

    // 资源屏障
    virtual Result<void> ResourceBarrier(
        uint32_t barrierCount,
        const BarrierDesc* barriers) = 0;

    // 执行命令包（二级命令缓冲区）
    virtual Result<void> ExecuteBundle(ICommandBuffer* bundle) = 0;

protected:
    CommandBufferDesc m_desc;
};

// 用于创建命令缓冲区的工厂函数声明
using CommandBufferCreateFunc = Result<ICommandBuffer*> (*)(const CommandBufferDesc& desc);

} // namespace RHI
