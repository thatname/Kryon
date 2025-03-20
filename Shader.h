
#pragma once
#include "Result.h"
#include "Descriptor.h"
#include "Pipeline.h"
#include <string>
#include <vector>
#include <cstdint>

namespace RHI {

// 着色器类型
enum class ShaderType {
    Vertex,             // 顶点着色器
    Pixel,              // 像素着色器
    Geometry,           // 几何着色器
    Hull,               // 曲面细分控制着色器
    Domain,             // 曲面细分评估着色器
    Compute             // 计算着色器
};

// 着色器语言
enum class ShaderLanguage {
    HLSL,               // DirectX着色器语言
    GLSL,               // OpenGL着色器语言
    MSL,                // Metal着色器语言
    SPIR_V              // Vulkan着色器中间语言
};

// 着色器编译选项
struct ShaderCompileOptions {
    ShaderLanguage language;        // 着色器语言
    std::string entryPoint;        // 入口点
    std::string target;            // 目标版本
    bool debug;                    // 是否包含调试信息
    bool optimize;                 // 是否优化
    std::vector<std::string> defines;  // 预处理定义
    std::string includeDir;        // 包含文件目录

    ShaderCompileOptions() :
        language(ShaderLanguage::HLSL),
        entryPoint("main"),
        debug(false),
        optimize(true) {}
};

// 着色器资源类型
enum class ShaderResourceType {
    UniformBuffer,      // 常量缓冲区
    StorageBuffer,      // 存储缓冲区
    Texture,            // 纹理
    Sampler,           // 采样器
    StorageImage,      // 存储图像
    InputAttachment    // 输入附件
};

// 着色器资源描述
struct ShaderResourceDesc {
    std::string name;              // 资源名称
    ShaderResourceType type;       // 资源类型
    uint32_t set;                 // 描述符集索引
    uint32_t binding;             // 绑定点
    uint32_t arraySize;           // 数组大小
    ShaderStageFlag stages;       // 使用的着色器阶段
};

// 着色器反射信息
struct ShaderReflection {
    std::vector<ShaderResourceDesc> resources;     // 资源列表
    std::vector<VertexAttribute> vertexAttributes; // 顶点属性（仅顶点着色器）
    std::vector<void*> pushConstantRanges;        // 推送常量范围
};

// 着色器描述
struct ShaderDesc {
    ShaderType type;               // 着色器类型
    ShaderLanguage language;       // 着色器语言
    std::vector<uint8_t> code;    // 着色器代码
    std::string entryPoint;       // 入口点名称

    ShaderDesc() :
        type(ShaderType::Vertex),
        language(ShaderLanguage::HLSL),
        entryPoint("main") {}
};

// 着色器抽象基类
class IShader {
public:
    virtual ~IShader() = default;

    // 获取着色器描述
    virtual const ShaderDesc& GetDesc() const = 0;

    // 获取原生句柄
    // DirectX12: ID3DBlob*
    // Vulkan: VkShaderModule
    // Metal: id<MTLFunction>
    virtual Result<void*> GetNativeHandle() = 0;

    // 获取反射信息
    virtual Result<ShaderReflection> GetReflection() const = 0;

    // 编译着色器
    static Result<IShader*> Compile(
        const std::string& source,
        const ShaderCompileOptions& options);

    // 从字节码创建着色器
    static Result<IShader*> CreateFromBytecode(
        const std::vector<uint8_t>& bytecode,
        ShaderType type);

protected:
    ShaderDesc m_desc;
};

// 用于创建着色器的工厂函数声明
using ShaderCreateFunc = Result<IShader*> (*)(const ShaderDesc& desc);

} // namespace RHI
