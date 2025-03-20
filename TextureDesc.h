
#pragma once
#include "Format.h"
#include <cstdint>

namespace RHI {

// 纹理类型
enum class TextureType {
    Texture1D,          // 1D纹理
    Texture2D,          // 2D纹理
    Texture3D,          // 3D纹理
    TextureCube,        // 立方体纹理
    Texture1DArray,     // 1D纹理数组
    Texture2DArray,     // 2D纹理数组
    TextureCubeArray    // 立方体纹理数组
};

// 纹理用途标志（可组合）
enum class TextureUsage : uint32_t {
    None                = 0,
    ShaderResource      = 1 << 0,    // 着色器资源
    RenderTarget        = 1 << 1,    // 渲染目标
    DepthStencil        = 1 << 2,    // 深度模板
    UnorderedAccess     = 1 << 3,    // UAV访问
    TransferSrc         = 1 << 4,    // 传输源
    TransferDst         = 1 << 5,    // 传输目标
};

inline TextureUsage operator|(TextureUsage a, TextureUsage b) {
    return static_cast<TextureUsage>(
        static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

inline TextureUsage operator&(TextureUsage a, TextureUsage b) {
    return static_cast<TextureUsage>(
        static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}

// 采样器地址模式
enum class AddressMode {
    Repeat,             // 重复
    MirrorRepeat,      // 镜像重复
    ClampToEdge,       // 钳制到边缘
    ClampToBorder,     // 钳制到边界
    MirrorClampToEdge  // 镜像钳制到边缘
};

// 采样器过滤模式
enum class FilterMode {
    Nearest,                // 最近点
    Linear,                 // 线性
    NearestMipmapNearest,  // 最近点mipmap最近点
    LinearMipmapNearest,   // 线性mipmap最近点
    NearestMipmapLinear,   // 最近点mipmap线性
    LinearMipmapLinear     // 线性mipmap线性
};

// 采样器描述
struct SamplerDesc {
    FilterMode magFilter;           // 放大过滤
    FilterMode minFilter;           // 缩小过滤
    FilterMode mipmapMode;         // Mipmap过滤
    AddressMode addressU;          // U方向寻址模式
    AddressMode addressV;          // V方向寻址模式
    AddressMode addressW;          // W方向寻址模式
    float mipLodBias;              // Mip级别偏移
    float maxAnisotropy;           // 最大各向异性
    float minLod;                  // 最小LOD
    float maxLod;                  // 最大LOD
    float borderColor[4];          // 边界颜色

    SamplerDesc() :
        magFilter(FilterMode::Linear),
        minFilter(FilterMode::Linear),
        mipmapMode(FilterMode::LinearMipmapLinear),
        addressU(AddressMode::Repeat),
        addressV(AddressMode::Repeat),
        addressW(AddressMode::Repeat),
        mipLodBias(0.0f),
        maxAnisotropy(1.0f),
        minLod(0.0f),
        maxLod(1000.0f),
        borderColor{0.0f, 0.0f, 0.0f, 0.0f} {}
};

// 纹理描述
struct TextureDesc {
    TextureType type;              // 纹理类型
    Format format;                 // 纹理格式
    uint32_t width;               // 宽度
    uint32_t height;              // 高度
    uint32_t depth;               // 深度（3D纹理）
    uint32_t mipLevels;           // mip级别数
    uint32_t arraySize;           // 数组大小
    uint32_t sampleCount;         // 采样数（多重采样）
    TextureUsage usage;           // 使用标志
    bool isCubeCompatible;        // 是否可用作立方体纹理
    SamplerDesc samplerDesc;      // 采样器描述

    TextureDesc() :
        type(TextureType::Texture2D),
        format(Format::RGBA8_UNORM),
        width(1),
        height(1),
        depth(1),
        mipLevels(1),
        arraySize(1),
        sampleCount(1),
        usage(TextureUsage::ShaderResource),
        isCubeCompatible(false) {}
};

// 纹理子资源范围
struct TextureSubresourceRange {
    uint32_t baseMipLevel;        // 基础mip级别
    uint32_t mipLevelCount;       // mip级别数量
    uint32_t baseArrayLayer;      // 基础数组层
    uint32_t arrayLayerCount;     // 数组层数量

    TextureSubresourceRange() :
        baseMipLevel(0),
        mipLevelCount(1),
        baseArrayLayer(0),
        arrayLayerCount(1) {}
};

} // namespace RHI
