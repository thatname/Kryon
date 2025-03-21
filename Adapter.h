
#pragma once
#include "Result.h"
#include "Format.h"
#include <string>
#include <vector>
#include <cstdint>

namespace RHI {

// 适配器类型
enum class AdapterType {
    Discrete,           // 独立显卡
    Integrated,         // 集成显卡
    Software,           // 软件渲染器
    CPU,                // CPU渲染器
    Unknown             // 未知类型
};

// 队列类型
enum class QueueType {
    Graphics,           // 图形队列
    Compute,            // 计算队列
    Transfer,           // 传输队列
    Present            // 显示队列
};

// 队列族属性
struct QueueFamilyProperties {
    QueueType type;                // 队列类型
    uint32_t queueCount;          // 队列数量
    uint32_t timestampValidBits;  // 时间戳有效位
    uint32_t minImageTransferGranularity[3];  // 最小图像传输粒度
    bool graphicsSupport;         // 支持图形操作
    bool computeSupport;          // 支持计算操作
    bool transferSupport;         // 支持传输操作
    bool sparseSupport;           // 支持稀疏资源
    bool protectedSupport;        // 支持受保护内存
};

// 设备限制
struct DeviceLimits {
    uint32_t maxImageDimension1D;
    uint32_t maxImageDimension2D;
    uint32_t maxImageDimension3D;
    uint32_t maxImageDimensionCube;
    uint32_t maxImageArrayLayers;
    uint32_t maxTexelBufferElements;
    uint32_t maxUniformBufferRange;
    uint32_t maxStorageBufferRange;
    uint32_t maxPushConstantsSize;
    uint32_t maxMemoryAllocationCount;
    uint32_t maxSamplerAllocationCount;
    uint32_t maxBoundDescriptorSets;
    uint32_t maxPerStageDescriptorSamplers;
    uint32_t maxPerStageDescriptorUniformBuffers;
    uint32_t maxPerStageDescriptorStorageBuffers;
    uint32_t maxPerStageDescriptorSampledImages;
    uint32_t maxPerStageDescriptorStorageImages;
    uint32_t maxPerStageResources;
    uint32_t maxDescriptorSetSamplers;
    uint32_t maxDescriptorSetUniformBuffers;
    uint32_t maxDescriptorSetStorageBuffers;
    uint32_t maxDescriptorSetSampledImages;
    uint32_t maxDescriptorSetStorageImages;
    uint64_t maxGeometryShaderInvocations;
    uint32_t maxGeometryInputComponents;
    uint32_t maxGeometryOutputComponents;
    uint32_t maxGeometryOutputVertices;
    uint32_t maxGeometryTotalOutputComponents;
    uint32_t maxFragmentInputComponents;
    uint32_t maxFragmentOutputAttachments;
    uint32_t maxComputeSharedMemorySize;
    uint32_t maxComputeWorkGroupCount[3];
    uint32_t maxComputeWorkGroupInvocations;
    uint32_t maxComputeWorkGroupSize[3];
    uint32_t maxViewports;
    uint32_t maxViewportDimensions[2];
};

// 设备特性
struct DeviceFeatures {
    bool robustBufferAccess;
    bool fullDrawIndexUint32;
    bool imageCubeArray;
    bool independentBlend;
    bool geometryShader;
    bool tessellationShader;
    bool sampleRateShading;
    bool dualSrcBlend;
    bool logicOp;
    bool multiDrawIndirect;
    bool drawIndirectFirstInstance;
    bool depthClamp;
    bool depthBiasClamp;
    bool fillModeNonSolid;
    bool depthBounds;
    bool wideLines;
    bool largePoints;
    bool alphaToOne;
    bool multiViewport;
    bool samplerAnisotropy;
    bool textureCompressionBC;
    bool textureCompressionETC2;
    bool textureCompressionASTC_LDR;
    bool occlusionQueryPrecise;
    bool pipelineStatisticsQuery;
    bool vertexPipelineStoresAndAtomics;
    bool fragmentStoresAndAtomics;
    bool shaderTessellationAndGeometryPointSize;
    bool shaderImageGatherExtended;
    bool shaderStorageImageExtendedFormats;
    bool shaderStorageImageMultisample;
    bool shaderUniformBufferArrayDynamicIndexing;
    bool shaderSampledImageArrayDynamicIndexing;
    bool shaderStorageBufferArrayDynamicIndexing;
    bool shaderStorageImageArrayDynamicIndexing;
};

// 适配器信息
struct AdapterInfo {
    std::string name;              // 适配器名称
    std::string vendor;            // 厂商名称
    uint32_t vendorId;            // 厂商ID
    uint32_t deviceId;            // 设备ID
    AdapterType type;             // 适配器类型
    uint64_t dedicatedVideoMemory; // 专用显存大小
    uint64_t dedicatedSystemMemory;// 专用系统内存大小
    uint64_t sharedSystemMemory;   // 共享系统内存大小
    DeviceLimits limits;          // 设备限制
    DeviceFeatures features;      // 设备特性
};

// 适配器抽象基类
class IAdapter {
public:
    virtual ~IAdapter() = default;

    // 获取原生句柄
    // DirectX12: IDXGIAdapter*
    // Vulkan: VkPhysicalDevice
    // Metal: id<MTLDevice>
    virtual Result<void*> GetNativeHandle() = 0;

    // 获取适配器信息
    virtual const AdapterInfo& GetAdapterInfo() const = 0;

    // 获取队列族属性
    virtual Result<std::vector<QueueFamilyProperties>> GetQueueFamilyProperties() const = 0;

    // 检查表面支持
    virtual Result<bool> CheckPresentSupport(
        uint32_t queueFamilyIndex,
        void* surface) const = 0;

    // 获取内存属性
    virtual Result<void> GetMemoryProperties(
        uint32_t* memoryTypeCount,
        void* memoryTypes,
        uint32_t* memoryHeapCount,
        void* memoryHeaps) const = 0;

    // 获取格式属性
    virtual Result<void> GetFormatProperties(
        Format format,
        void* formatProperties) const = 0;

    // 检查特性支持
    virtual bool CheckFeatureSupport(
        const std::string& featureName) const = 0;

    // 创建逻辑设备
    virtual Result<class IDevice*> CreateDevice(
        const class DeviceDesc& desc) = 0;
};

// 用于枚举适配器的函数声明
using EnumerateAdaptersFunc = Result<std::vector<IAdapter*>> (*)();

} // namespace RHI
