
#pragma once
#include "Result.h"
#include <cstdint>

namespace RHI {

// 内存类型
enum class MemoryType {
    Default,            // GPU本地内存（最佳性能）
                       // - DirectX12: D3D12_HEAP_TYPE_DEFAULT
                       // - Vulkan: DEVICE_LOCAL_BIT
                       // - Metal: MTLStorageModePrivate
    
    Upload,             // CPU上传内存
                       // - DirectX12: D3D12_HEAP_TYPE_UPLOAD
                       // - Vulkan: HOST_VISIBLE_BIT
                       // - Metal: MTLStorageModeShared
    
    Readback,          // CPU回读内存
                       // - DirectX12: D3D12_HEAP_TYPE_READBACK
                       // - Vulkan: HOST_VISIBLE_BIT | HOST_CACHED_BIT
                       // - Metal: MTLStorageModeShared
    
    Custom              // 自定义内存类型（用于特殊需求）
};

// 内存属性标志（可组合）
enum class MemoryPropertyFlag : uint32_t {
    None                = 0,
    DeviceLocal         = 1 << 0,    // GPU本地内存
    HostVisible         = 1 << 1,    // CPU可见
    HostCoherent       = 1 << 2,    // CPU访问无需显式刷新
    HostCached         = 1 << 3,    // CPU缓存优化
    LazilyAllocated    = 1 << 4,    // 延迟分配
    Protected          = 1 << 5,    // 受保护内存
};

inline MemoryPropertyFlag operator|(MemoryPropertyFlag a, MemoryPropertyFlag b) {
    return static_cast<MemoryPropertyFlag>(
        static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

// 内存分配信息
struct MemoryAllocationInfo {
    size_t size;                   // 分配大小
    size_t alignment;              // 对齐要求
    MemoryType type;               // 内存类型
    MemoryPropertyFlag properties; // 内存属性
    bool dedicated;                // 是否专用分配
};

// 内存统计信息
struct MemoryStats {
    size_t totalSize;              // 总大小
    size_t usedSize;               // 已使用大小
    size_t largestFreeBlock;       // 最大空闲块
    size_t freeCount;              // 空闲块数量
    float fragmentation;           // 碎片化程度（0-1）
};

// 内存描述
struct MemoryDesc {
    MemoryType type;               // 内存类型
    MemoryPropertyFlag properties; // 内存属性
    size_t size;                  // 内存大小
    size_t alignment;             // 对齐要求
    bool dedicated;               // 是否专用内存

    MemoryDesc() :
        type(MemoryType::Default),
        properties(MemoryPropertyFlag::None),
        size(0),
        alignment(0),
        dedicated(false) {}
};

// 内存抽象基类
class IMemory {
public:
    virtual ~IMemory() = default;

    // 获取内存描述
    virtual const MemoryDesc& GetDesc() const = 0;

    // 获取原生句柄
    // DirectX12: ID3D12Heap*
    // Vulkan: VkDeviceMemory
    // Metal: id<MTLHeap>
    virtual Result<void*> GetNativeHandle() = 0;

    // 分配内存
    virtual Result<void*> Allocate(const MemoryAllocationInfo& info) = 0;

    // 释放内存
    virtual Result<void> Free(void* allocation) = 0;

    // 映射内存
    virtual Result<void*> Map(
        void* allocation,
        size_t offset,
        size_t size) = 0;

    // 解除映射
    virtual Result<void> Unmap(void* allocation) = 0;

    // 刷新映射范围（使CPU写入对GPU可见）
    virtual Result<void> FlushMappedRange(
        void* allocation,
        size_t offset,
        size_t size) = 0;

    // 使映射范围失效（使GPU写入对CPU可见）
    virtual Result<void> InvalidateMappedRange(
        void* allocation,
        size_t offset,
        size_t size) = 0;

    // 获取分配信息
    virtual Result<MemoryAllocationInfo> GetAllocationInfo(
        void* allocation) const = 0;

    // 获取内存统计信息
    virtual Result<MemoryStats> GetStats() const = 0;

    // 检查内存类型是否支持指定属性
    virtual Result<bool> IsMemoryTypeSupported(
        MemoryType type,
        MemoryPropertyFlag properties) const = 0;

    // 获取最佳内存类型
    virtual Result<MemoryType> GetBestMemoryType(
        MemoryPropertyFlag requiredProperties,
        MemoryPropertyFlag preferredProperties) const = 0;

    // 合并空闲块（碎片整理）
    virtual Result<void> Defragment() = 0;

    // 设置内存优先级（影响驻留策略）
    virtual Result<void> SetPriority(uint32_t priority) = 0;

    // 使内存驻留（确保在GPU内存中）
    virtual Result<void> MakeResident() = 0;

    // 解除内存驻留
    virtual Result<void> Evict() = 0;

protected:
    MemoryDesc m_desc;
};

// 用于创建内存的工厂函数声明
using MemoryCreateFunc = Result<IMemory*> (*)(const MemoryDesc& desc);

} // namespace RHI
