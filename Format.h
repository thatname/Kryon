
#pragma once

namespace RHI {

/// @brief RHI格式枚举
/// 包含DirectX12、Vulkan和Metal支持的所有主要格式
enum class Format {
    // 8位标准格式
    R8_UNORM,           // DX12: DXGI_FORMAT_R8_UNORM
                        // Vulkan: VK_FORMAT_R8_UNORM
                        // Metal: MTLPixelFormatR8Unorm

    R8_SNORM,           // DX12: DXGI_FORMAT_R8_SNORM
                        // Vulkan: VK_FORMAT_R8_SNORM
                        // Metal: MTLPixelFormatR8Snorm

    R8_UINT,            // DX12: DXGI_FORMAT_R8_UINT
                        // Vulkan: VK_FORMAT_R8_UINT
                        // Metal: MTLPixelFormatR8Uint

    R8_SINT,            // DX12: DXGI_FORMAT_R8_SINT
                        // Vulkan: VK_FORMAT_R8_SINT
                        // Metal: MTLPixelFormatR8Sint

    // 8位双通道格式
    RG8_UNORM,          // DX12: DXGI_FORMAT_R8G8_UNORM
                        // Vulkan: VK_FORMAT_R8G8_UNORM
                        // Metal: MTLPixelFormatRG8Unorm

    RG8_SNORM,          // DX12: DXGI_FORMAT_R8G8_SNORM
                        // Vulkan: VK_FORMAT_R8G8_SNORM
                        // Metal: MTLPixelFormatRG8Snorm

    RG8_UINT,           // DX12: DXGI_FORMAT_R8G8_UINT
                        // Vulkan: VK_FORMAT_R8G8_UINT
                        // Metal: MTLPixelFormatRG8Uint

    RG8_SINT,           // DX12: DXGI_FORMAT_R8G8_SINT
                        // Vulkan: VK_FORMAT_R8G8_SINT
                        // Metal: MTLPixelFormatRG8Sint

    // 8位四通道格式
    RGBA8_UNORM,        // DX12: DXGI_FORMAT_R8G8B8A8_UNORM
                        // Vulkan: VK_FORMAT_R8G8B8A8_UNORM
                        // Metal: MTLPixelFormatRGBA8Unorm

    RGBA8_SNORM,        // DX12: DXGI_FORMAT_R8G8B8A8_SNORM
                        // Vulkan: VK_FORMAT_R8G8B8A8_SNORM
                        // Metal: MTLPixelFormatRGBA8Snorm

    RGBA8_UINT,         // DX12: DXGI_FORMAT_R8G8B8A8_UINT
                        // Vulkan: VK_FORMAT_R8G8B8A8_UINT
                        // Metal: MTLPixelFormatRGBA8Uint

    RGBA8_SINT,         // DX12: DXGI_FORMAT_R8G8B8A8_SINT
                        // Vulkan: VK_FORMAT_R8G8B8A8_SINT
                        // Metal: MTLPixelFormatRGBA8Sint

    RGBA8_SRGB,         // DX12: DXGI_FORMAT_R8G8B8A8_UNORM_SRGB
                        // Vulkan: VK_FORMAT_R8G8B8A8_SRGB
                        // Metal: MTLPixelFormatRGBA8Unorm_sRGB

    BGRA8_UNORM,        // DX12: DXGI_FORMAT_B8G8R8A8_UNORM
                        // Vulkan: VK_FORMAT_B8G8R8A8_UNORM
                        // Metal: MTLPixelFormatBGRA8Unorm

    BGRA8_SRGB,         // DX12: DXGI_FORMAT_B8G8R8A8_UNORM_SRGB
                        // Vulkan: VK_FORMAT_B8G8R8A8_SRGB
                        // Metal: MTLPixelFormatBGRA8Unorm_sRGB

    // 16位格式
    R16_UNORM,          // DX12: DXGI_FORMAT_R16_UNORM
                        // Vulkan: VK_FORMAT_R16_UNORM
                        // Metal: MTLPixelFormatR16Unorm

    R16_SNORM,          // DX12: DXGI_FORMAT_R16_SNORM
                        // Vulkan: VK_FORMAT_R16_SNORM
                        // Metal: MTLPixelFormatR16Snorm

    R16_UINT,           // DX12: DXGI_FORMAT_R16_UINT
                        // Vulkan: VK_FORMAT_R16_UINT
                        // Metal: MTLPixelFormatR16Uint

    R16_SINT,           // DX12: DXGI_FORMAT_R16_SINT
                        // Vulkan: VK_FORMAT_R16_SINT
                        // Metal: MTLPixelFormatR16Sint

    R16_FLOAT,          // DX12: DXGI_FORMAT_R16_FLOAT
                        // Vulkan: VK_FORMAT_R16_SFLOAT
                        // Metal: MTLPixelFormatR16Float

    RG16_UNORM,         // DX12: DXGI_FORMAT_R16G16_UNORM
                        // Vulkan: VK_FORMAT_R16G16_UNORM
                        // Metal: MTLPixelFormatRG16Unorm

    RG16_SNORM,         // DX12: DXGI_FORMAT_R16G16_SNORM
                        // Vulkan: VK_FORMAT_R16G16_SNORM
                        // Metal: MTLPixelFormatRG16Snorm

    RG16_UINT,          // DX12: DXGI_FORMAT_R16G16_UINT
                        // Vulkan: VK_FORMAT_R16G16_UINT
                        // Metal: MTLPixelFormatRG16Uint

    RG16_SINT,          // DX12: DXGI_FORMAT_R16G16_SINT
                        // Vulkan: VK_FORMAT_R16G16_SINT
                        // Metal: MTLPixelFormatRG16Sint

    RG16_FLOAT,         // DX12: DXGI_FORMAT_R16G16_FLOAT
                        // Vulkan: VK_FORMAT_R16G16_SFLOAT
                        // Metal: MTLPixelFormatRG16Float

    RGBA16_UNORM,       // DX12: DXGI_FORMAT_R16G16B16A16_UNORM
                        // Vulkan: VK_FORMAT_R16G16B16A16_UNORM
                        // Metal: MTLPixelFormatRGBA16Unorm

    RGBA16_SNORM,       // DX12: DXGI_FORMAT_R16G16B16A16_SNORM
                        // Vulkan: VK_FORMAT_R16G16B16A16_SNORM
                        // Metal: MTLPixelFormatRGBA16Snorm

    RGBA16_UINT,        // DX12: DXGI_FORMAT_R16G16B16A16_UINT
                        // Vulkan: VK_FORMAT_R16G16B16A16_UINT
                        // Metal: MTLPixelFormatRGBA16Uint

    RGBA16_SINT,        // DX12: DXGI_FORMAT_R16G16B16A16_SINT
                        // Vulkan: VK_FORMAT_R16G16B16A16_SINT
                        // Metal: MTLPixelFormatRGBA16Sint

    RGBA16_FLOAT,       // DX12: DXGI_FORMAT_R16G16B16A16_FLOAT
                        // Vulkan: VK_FORMAT_R16G16B16A16_SFLOAT
                        // Metal: MTLPixelFormatRGBA16Float

    // 32位格式
    R32_UINT,           // DX12: DXGI_FORMAT_R32_UINT
                        // Vulkan: VK_FORMAT_R32_UINT
                        // Metal: MTLPixelFormatR32Uint

    R32_SINT,           // DX12: DXGI_FORMAT_R32_SINT
                        // Vulkan: VK_FORMAT_R32_SINT
                        // Metal: MTLPixelFormatR32Sint

    R32_FLOAT,          // DX12: DXGI_FORMAT_R32_FLOAT
                        // Vulkan: VK_FORMAT_R32_SFLOAT
                        // Metal: MTLPixelFormatR32Float

    RG32_UINT,          // DX12: DXGI_FORMAT_R32G32_UINT
                        // Vulkan: VK_FORMAT_R32G32_UINT
                        // Metal: MTLPixelFormatRG32Uint

    RG32_SINT,          // DX12: DXGI_FORMAT_R32G32_SINT
                        // Vulkan: VK_FORMAT_R32G32_SINT
                        // Metal: MTLPixelFormatRG32Sint

    RG32_FLOAT,         // DX12: DXGI_FORMAT_R32G32_FLOAT
                        // Vulkan: VK_FORMAT_R32G32_SFLOAT
                        // Metal: MTLPixelFormatRG32Float

    RGB32_UINT,         // DX12: DXGI_FORMAT_R32G32B32_UINT
                        // Vulkan: VK_FORMAT_R32G32B32_UINT
                        // Metal: 不支持

    RGB32_SINT,         // DX12: DXGI_FORMAT_R32G32B32_SINT
                        // Vulkan: VK_FORMAT_R32G32B32_SINT
                        // Metal: 不支持

    RGB32_FLOAT,        // DX12: DXGI_FORMAT_R32G32B32_FLOAT
                        // Vulkan: VK_FORMAT_R32G32B32_SFLOAT
                        // Metal: 不支持

    RGBA32_UINT,        // DX12: DXGI_FORMAT_R32G32B32A32_UINT
                        // Vulkan: VK_FORMAT_R32G32B32A32_UINT
                        // Metal: MTLPixelFormatRGBA32Uint

    RGBA32_SINT,        // DX12: DXGI_FORMAT_R32G32B32A32_SINT
                        // Vulkan: VK_FORMAT_R32G32B32A32_SINT
                        // Metal: MTLPixelFormatRGBA32Sint

    RGBA32_FLOAT,       // DX12: DXGI_FORMAT_R32G32B32A32_FLOAT
                        // Vulkan: VK_FORMAT_R32G32B32A32_SFLOAT
                        // Metal: MTLPixelFormatRGBA32Float

    // 特殊打包格式
    RGB10A2_UNORM,      // DX12: DXGI_FORMAT_R10G10B10A2_UNORM
                        // Vulkan: VK_FORMAT_A2B10G10R10_UNORM_PACK32
                        // Metal: MTLPixelFormatRGB10A2Unorm

    RGB10A2_UINT,       // DX12: DXGI_FORMAT_R10G10B10A2_UINT
                        // Vulkan: VK_FORMAT_A2B10G10R10_UINT_PACK32
                        // Metal: MTLPixelFormatRGB10A2Uint

    RG11B10_FLOAT,      // DX12: DXGI_FORMAT_R11G11B10_FLOAT
                        // Vulkan: VK_FORMAT_B10G11R11_UFLOAT_PACK32
                        // Metal: MTLPixelFormatRG11B10Float

    RGB9E5_FLOAT,       // DX12: DXGI_FORMAT_R9G9B9E5_SHAREDEXP
                        // Vulkan: VK_FORMAT_E5B9G9R9_UFLOAT_PACK32
                        // Metal: MTLPixelFormatRGB9E5Float

    // 深度模板格式
    D16_UNORM,          // DX12: DXGI_FORMAT_D16_UNORM
                        // Vulkan: VK_FORMAT_D16_UNORM
                        // Metal: MTLPixelFormatDepth16Unorm

    D24_UNORM_S8_UINT,  // DX12: DXGI_FORMAT_D24_UNORM_S8_UINT
                        // Vulkan: VK_FORMAT_D24_UNORM_S8_UINT
                        // Metal: MTLPixelFormatDepth24Unorm_Stencil8

    D32_FLOAT,          // DX12: DXGI_FORMAT_D32_FLOAT
                        // Vulkan: VK_FORMAT_D32_SFLOAT
                        // Metal: MTLPixelFormatDepth32Float

    D32_FLOAT_S8_UINT,  // DX12: DXGI_FORMAT_D32_FLOAT_S8X24_UINT
                        // Vulkan: VK_FORMAT_D32_SFLOAT_S8_UINT
                        // Metal: MTLPixelFormatDepth32Float_Stencil8

    // BC压缩纹理格式
    BC1_RGBA_UNORM,     // DX12: DXGI_FORMAT_BC1_UNORM
                        // Vulkan: VK_FORMAT_BC1_RGBA_UNORM_BLOCK
                        // Metal: MTLPixelFormatBC1_RGBA

    BC1_RGBA_SRGB,      // DX12: DXGI_FORMAT_BC1_UNORM_SRGB
                        // Vulkan: VK_FORMAT_BC1_RGBA_SRGB_BLOCK
                        // Metal: MTLPixelFormatBC1_RGBA_sRGB

    BC2_UNORM,          // DX12: DXGI_FORMAT_BC2_UNORM
                        // Vulkan: VK_FORMAT_BC2_UNORM_BLOCK
                        // Metal: MTLPixelFormatBC2_RGBA

    BC2_SRGB,           // DX12: DXGI_FORMAT_BC2_UNORM_SRGB
                        // Vulkan: VK_FORMAT_BC2_SRGB_BLOCK
                        // Metal: MTLPixelFormatBC2_RGBA_sRGB

    BC3_UNORM,          // DX12: DXGI_FORMAT_BC3_UNORM
                        // Vulkan: VK_FORMAT_BC3_UNORM_BLOCK
                        // Metal: MTLPixelFormatBC3_RGBA

    BC3_SRGB,           // DX12: DXGI_FORMAT_BC3_UNORM_SRGB
                        // Vulkan: VK_FORMAT_BC3_SRGB_BLOCK
                        // Metal: MTLPixelFormatBC3_RGBA_sRGB

    BC4_UNORM,          // DX12: DXGI_FORMAT_BC4_UNORM
                        // Vulkan: VK_FORMAT_BC4_UNORM_BLOCK
                        // Metal: MTLPixelFormatBC4_RUnorm

    BC4_SNORM,          // DX12: DXGI_FORMAT_BC4_SNORM
                        // Vulkan: VK_FORMAT_BC4_SNORM_BLOCK
                        // Metal: MTLPixelFormatBC4_RSnorm

    BC5_UNORM,          // DX12: DXGI_FORMAT_BC5_UNORM
                        // Vulkan: VK_FORMAT_BC5_UNORM_BLOCK
                        // Metal: MTLPixelFormatBC5_RGUnorm

    BC5_SNORM,          // DX12: DXGI_FORMAT_BC5_SNORM
                        // Vulkan: VK_FORMAT_BC5_SNORM_BLOCK
                        // Metal: MTLPixelFormatBC5_RGSnorm

    BC6H_UF16,          // DX12: DXGI_FORMAT_BC6H_UF16
                        // Vulkan: VK_FORMAT_BC6H_UFLOAT_BLOCK
                        // Metal: MTLPixelFormatBC6H_RGBUfloat

    BC6H_SF16,          // DX12: DXGI_FORMAT_BC6H_SF16
                        // Vulkan: VK_FORMAT_BC6H_SFLOAT_BLOCK
                        // Metal: MTLPixelFormatBC6H_RGBFloat

    BC7_UNORM,          // DX12: DXGI_FORMAT_BC7_UNORM
                        // Vulkan: VK_FORMAT_BC7_UNORM_BLOCK
                        // Metal: MTLPixelFormatBC7_RGBAUnorm

    BC7_SRGB,           // DX12: DXGI_FORMAT_BC7_UNORM_SRGB
                        // Vulkan: VK_FORMAT_BC7_SRGB_BLOCK
                        // Metal: MTLPixelFormatBC7_RGBAUnorm_sRGB

    // ASTC压缩纹理格式（仅Vulkan和Metal支持）
    ASTC_4x4_UNORM,     // DX12: 不支持
                        // Vulkan: VK_FORMAT_ASTC_4x4_UNORM_BLOCK
                        // Metal: MTLPixelFormatASTC_4x4_LDR

    ASTC_4x4_SRGB,      // DX12: 不支持
                        // Vulkan: VK_FORMAT_ASTC_4x4_SRGB_BLOCK
                        // Metal: MTLPixelFormatASTC_4x4_sRGB

    // 特殊值
    UNKNOWN,            // 未知或不支持的格式

    MAX_FORMAT          // 用于遍历的辅助值
};

} // namespace RHI
