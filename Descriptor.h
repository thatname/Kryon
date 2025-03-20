
#pragma once
#include "Result.h"
#include <cstdint>
#include <vector>

namespace RHI {

// 描述符类型
enum class DescriptorType {
    UniformBuffer,          // 常量缓冲区视图
    StorageBuffer,          // 存储缓冲区视图
    Texture,                // 纹理视图
    StorageTexture,        // 存储纹理视图
    Sampler,               // 采样器
    InputAttachment        // 输入附件
};

// 描述符标志
enum class DescriptorFlag : uint32_t {
    None                = 0,
    UpdateAfterBind     = 1 << 0,    // 绑定后更新
    PartiallyBound     = 1 << 1,    // 部分绑定
    VariableDescriptors = 1 << 2     // 可变数量描述符
};

// 描述符范围
struct DescriptorRange {
    DescriptorType type;         // 描述符类型
    uint32_t baseRegister;       // 基础寄存器
    uint32_t registerSpace;      // 寄存器空间
    uint32_t count;             // 描述符数量
    ShaderStageFlag stages;     // 可见的着色器阶段
    DescriptorFlag flags;       // 描述符标志
};

// 描述符集布局描述
struct DescriptorSetLayoutDesc {
    std::vector<DescriptorRange> ranges;  // 描述符范围
    bool pushDescriptor;                  // 是否为推送描述符
};

// 描述符池大小
struct DescriptorPoolSize {
    DescriptorType type;         // 描述符类型
    uint32_t count;             // 描述符数量
};

// 描述符池描述
struct DescriptorPoolDesc {
    uint32_t maxSets;           // 最大描述符集数量
    std::vector<DescriptorPoolSize> poolSizes;  // 池大小
    bool freeDescriptorSet;     // 是否支持释放单个描述符集
};

// 描述符写入
struct DescriptorWrite {
    uint32_t dstSet;            // 目标描述符集
    uint32_t dstBinding;        // 目标绑定点
    uint32_t dstArrayElement;   // 目标数组元素
    DescriptorType type;        // 描述符类型
    void* bufferInfo;           // 缓冲区信息
    void* imageInfo;            // 图像信息
    void* texelBufferView;      // 纹素缓冲区视图
};

// 描述符集布局抽象基类
class IDescriptorSetLayout {
public:
    virtual ~IDescriptorSetLayout() = default;

    // 获取原生句柄
    // DirectX12: D3D12_ROOT_PARAMETER*
    // Vulkan: VkDescriptorSetLayout
    // Metal: MTLArgumentEncoder
    virtual Result<void*> GetNativeHandle() = 0;

    // 获取描述符集布局描述
    virtual const DescriptorSetLayoutDesc& GetDesc() const = 0;

protected:
    DescriptorSetLayoutDesc m_desc;
};

// 描述符池抽象基类
class IDescriptorPool {
public:
    virtual ~IDescriptorPool() = default;

    // 获取原生句柄
    // DirectX12: ID3D12DescriptorHeap*
    // Vulkan: VkDescriptorPool
    // Metal: MTLHeap
    virtual Result<void*> GetNativeHandle() = 0;

    // 分配描述符集
    virtual Result<class IDescriptorSet*> AllocateDescriptorSet(
        IDescriptorSetLayout* layout) = 0;

    // 释放描述符集
    virtual Result<void> FreeDescriptorSet(
        class IDescriptorSet* descriptorSet) = 0;

    // 重置描述符池
    virtual Result<void> Reset() = 0;

protected:
    DescriptorPoolDesc m_desc;
};

// 描述符集抽象基类
class IDescriptorSet {
public:
    virtual ~IDescriptorSet() = default;

    // 获取原生句柄
    // DirectX12: D3D12_GPU_DESCRIPTOR_HANDLE
    // Vulkan: VkDescriptorSet
    // Metal: MTLArgumentBuffer
    virtual Result<void*> GetNativeHandle() = 0;

    // 更新描述符
    virtual Result<void> UpdateDescriptor(
        const std::vector<DescriptorWrite>& writes) = 0;

    // 获取描述符集布局
    virtual Result<IDescriptorSetLayout*> GetLayout() const = 0;
};

// 用于创建描述符相关对象的工厂函数声明
using DescriptorSetLayoutCreateFunc = Result<IDescriptorSetLayout*> (*)(const DescriptorSetLayoutDesc& desc);
using DescriptorPoolCreateFunc = Result<IDescriptorPool*> (*)(const DescriptorPoolDesc& desc);

} // namespace RHI
