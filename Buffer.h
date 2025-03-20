
#pragma once
#include "Result.h"
#include <cstdint>

namespace RHI {

// 缓冲区类型
enum class BufferType {
    Vertex,             // 顶点缓冲区
    Index,              // 索引缓冲区
    Constant,           // 常量缓冲区
    Storage,            // 存储缓冲区（结构化缓冲区）
    Indirect,           // 间接绘制缓冲区
    Staging             // 暂存缓冲区（用于传输）
};

// 缓冲区用途标志（可组合）
enum class BufferUsage : uint32_t {
    None                = 0,
    VertexBuffer        = 1 << 0,    // 顶点缓冲区
    IndexBuffer         = 1 << 1,    // 索引缓冲区
    ConstantBuffer      = 1 << 2,    // 常量缓冲区
    ShaderResource      = 1 << 3,    // 着色器资源
    UnorderedAccess     = 1 << 4,    // UAV访问
    IndirectArgs        = 1 << 5,    // 间接参数
    TransferSrc         = 1 << 6,    // 传输源
    TransferDst         = 1 << 7,    // 传输目标
};

inline BufferUsage operator|(BufferUsage a, BufferUsage b) {
    return static_cast<BufferUsage>(
        static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

inline BufferUsage operator&(BufferUsage a, BufferUsage b) {
    return static_cast<BufferUsage>(
        static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}

// 内存属性
enum class MemoryType {
    Default,            // GPU本地内存
                       // - DirectX12: D3D12_HEAP_TYPE_DEFAULT
                       // - Vulkan: VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
                       // - Metal: MTLStorageModePrivate
    
    Upload,             // CPU上传内存
                       // - DirectX12: D3D12_HEAP_TYPE_UPLOAD
                       // - Vulkan: VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
                       // - Metal: MTLStorageModeShared
    
    Readback,          // CPU回读内存
                       // - DirectX12: D3D12_HEAP_TYPE_READBACK
                       // - Vulkan: VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT
                       // - Metal: MTLStorageModeShared
    
    Custom              // 自定义内存属性
};

// 缓冲区描述
struct BufferDesc {
    BufferType type;            // 缓冲区类型
    BufferUsage usage;         // 使用标志
    MemoryType memoryType;     // 内存类型
    size_t size;              // 缓冲区大小（字节）
    size_t stride;            // 结构化缓冲区的步长（字节）
    bool allowCPUAccess;      // 是否允许CPU访问

    BufferDesc() :
        type(BufferType::Vertex),
        usage(BufferUsage::VertexBuffer),
        memoryType(MemoryType::Default),
        size(0),
        stride(0),
        allowCPUAccess(false) {}
};

// 缓冲区视图描述
struct BufferViewDesc {
    size_t offset;            // 视图起始偏移
    size_t size;             // 视图大小（字节）
    size_t stride;           // 元素步长（用于结构化缓冲区）
};

// 缓冲区抽象基类
class IBuffer {
public:
    virtual ~IBuffer() = default;

    // 获取缓冲区描述
    virtual const BufferDesc& GetDesc() const = 0;

    // 获取原生句柄
    // DirectX12: ID3D12Resource*
    // Vulkan: VkBuffer
    // Metal: id<MTLBuffer>
    virtual Result<void*> GetNativeHandle() = 0;

    // 映射缓冲区内存
    virtual Result<void*> Map() = 0;

    // 解除映射
    virtual Result<void> Unmap() = 0;

    // 更新缓冲区数据
    virtual Result<void> UpdateData(
        const void* data,
        size_t size,
        size_t offset = 0) = 0;

    // 获取顶点缓冲区视图
    // DirectX12: D3D12_VERTEX_BUFFER_VIEW
    // Vulkan: VkDescriptorBufferInfo
    // Metal: MTLVertexBufferLayoutDescriptor
    virtual Result<void*> GetVertexBufferView(
        const BufferViewDesc& desc) = 0;

    // 获取索引缓冲区视图
    // DirectX12: D3D12_INDEX_BUFFER_VIEW
    // Vulkan: VkDescriptorBufferInfo
    // Metal: MTLIndexBufferLayoutDescriptor
    virtual Result<void*> GetIndexBufferView(
        const BufferViewDesc& desc) = 0;

    // 获取常量缓冲区视图
    // DirectX12: D3D12_CONSTANT_BUFFER_VIEW_DESC
    // Vulkan: VkDescriptorBufferInfo
    // Metal: MTLBufferLayoutDescriptor
    virtual Result<void*> GetConstantBufferView(
        const BufferViewDesc& desc) = 0;

    // 获取着色器资源视图
    virtual Result<void*> GetShaderResourceView(
        const BufferViewDesc& desc) = 0;

    // 获取UAV视图
    virtual Result<void*> GetUnorderedAccessView(
        const BufferViewDesc& desc) = 0;

    // 转换缓冲区状态
    // DirectX12: D3D12_RESOURCE_STATES
    // Vulkan: VkAccessFlags
    // Metal: MTLResourceUsage
    virtual Result<void> TransitionState(uint32_t newState) = 0;

protected:
    BufferDesc m_desc;
};

// 用于创建缓冲区的工厂函数声明
using BufferCreateFunc = Result<IBuffer*> (*)(const BufferDesc& desc);

} // namespace RHI
