#pragma once
#include "TextureDesc.h"
#include "Result.h"
#include <vector>

namespace RHI {

// 纹理数据布局
struct TextureDataLayout {
    size_t offset;                // 数据偏移
    size_t rowPitch;             // 行间距
    size_t arrayPitch;           // 数组层间距
    size_t depthPitch;           // 深度层间距
};

// 纹理抽象基类
class ITexture {
public:
    virtual ~ITexture() = default;

    // 获取纹理描述
    virtual const TextureDesc& GetDesc() const = 0;

    // 获取原生句柄
    // DirectX12: ID3D12Resource*
    // Vulkan: VkImage
    // Metal: id<MTLTexture>
    virtual Result<void*> GetNativeHandle() = 0;

    // 更新纹理数据
    virtual Result<void> UpdateData(
        const void* data,
        const TextureDataLayout& layout,
        const TextureSubresourceRange& range) = 0;

    // 生成Mipmap
    virtual Result<void> GenerateMips(
        const TextureSubresourceRange& range) = 0;

    // 获取纹理视图（用于渲染目标）
    // DirectX12: D3D12_CPU_DESCRIPTOR_HANDLE
    // Vulkan: VkImageView
    // Metal: MTLRenderPassDescriptor
    virtual Result<void*> GetRenderTargetView(
        const TextureSubresourceRange& range) = 0;

    // 获取纹理视图（用于深度模板）
    virtual Result<void*> GetDepthStencilView(
        const TextureSubresourceRange& range) = 0;

    // 获取纹理视图（用于着色器资源）
    virtual Result<void*> GetShaderResourceView(
        const TextureSubresourceRange& range) = 0;

    // 获取纹理视图（用于UAV）
    virtual Result<void*> GetUnorderedAccessView(
        const TextureSubresourceRange& range) = 0;

    // 获取纹理大小（字节）
    virtual Result<size_t> GetTextureSize() const = 0;

    // 获取子资源布局
    virtual Result<TextureDataLayout> GetSubresourceLayout(
        uint32_t mipLevel,
        uint32_t arrayLayer) const = 0;

    // 转换纹理布局/状态
    // DirectX12: D3D12_RESOURCE_STATES
    // Vulkan: VkImageLayout
    // Metal: MTLResourceUsage
    virtual Result<void> TransitionLayout(
        uint32_t newState,
        const TextureSubresourceRange& range) = 0;

protected:
    TextureDesc m_desc;
};

// 用于创建纹理的工厂函数声明
using TextureCreateFunc = Result<ITexture*> (*)(const TextureDesc& desc);

} // namespace RHI
