
#pragma once
#include "Format.h"
#include "Result.h"
#include <cstdint>
#include <vector>

namespace RHI {

// 着色器阶段标志
enum class ShaderStageFlag : uint32_t {
    None                = 0,
    Vertex             = 1 << 0,
    Hull               = 1 << 1,    // DX12术语，对应Vulkan的TessControl
    Domain             = 1 << 2,    // DX12术语，对应Vulkan的TessEval
    Geometry           = 1 << 3,
    Pixel              = 1 << 4,    // DX12术语，对应Vulkan的Fragment
    Compute            = 1 << 5,
    All                = 0x3F
};

inline ShaderStageFlag operator|(ShaderStageFlag a, ShaderStageFlag b) {
    return static_cast<ShaderStageFlag>(
        static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

// 顶点属性描述
struct VertexAttribute {
    uint32_t location;     // 着色器中的位置
    Format format;         // 数据格式
    uint32_t offset;       // 在顶点中的偏移
    uint32_t binding;      // 绑定点
};

// 顶点绑定描述
struct VertexBinding {
    uint32_t binding;      // 绑定点
    uint32_t stride;       // 顶点步长
    bool instanceDivisor;  // 是否用于实例化
};

// 光栅化状态
struct RasterizationState {
    bool depthClampEnable;         // 深度钳制
    bool rasterizerDiscardEnable;  // 放弃光栅化
    bool depthBiasEnable;          // 深度偏移
    float depthBiasConstant;       // 恒定深度偏移
    float depthBiasClamp;          // 深度偏移钳制
    float depthBiasSlope;          // 深度偏移斜率
    float lineWidth;               // 线宽

    enum class FillMode {
        Solid,
        Wireframe,
        Point
    } fillMode;

    enum class CullMode {
        None,
        Front,
        Back
    } cullMode;

    enum class FrontFace {
        CounterClockwise,
        Clockwise
    } frontFace;

    RasterizationState() :
        depthClampEnable(false),
        rasterizerDiscardEnable(false),
        depthBiasEnable(false),
        depthBiasConstant(0.0f),
        depthBiasClamp(0.0f),
        depthBiasSlope(0.0f),
        lineWidth(1.0f),
        fillMode(FillMode::Solid),
        cullMode(CullMode::Back),
        frontFace(FrontFace::CounterClockwise) {}
};

// 深度模板状态
struct DepthStencilState {
    bool depthTestEnable;          // 深度测试
    bool depthWriteEnable;         // 深度写入
    bool stencilTestEnable;        // 模板测试

    enum class CompareOp {
        Never,
        Less,
        Equal,
        LessOrEqual,
        Greater,
        NotEqual,
        GreaterOrEqual,
        Always
    } depthCompareOp;

    struct StencilOpState {
        enum class Op {
            Keep,
            Zero,
            Replace,
            IncrementClamp,
            DecrementClamp,
            Invert,
            IncrementWrap,
            DecrementWrap
        };

        Op failOp;                 // 模板测试失败操作
        Op passOp;                 // 模板测试通过操作
        Op depthFailOp;            // 深度测试失败操作
        CompareOp compareOp;       // 比较操作
        uint32_t compareMask;      // 比较掩码
        uint32_t writeMask;        // 写入掩码
        uint32_t reference;        // 参考值
    };

    StencilOpState front;          // 正面模板操作
    StencilOpState back;           // 背面模板操作

    DepthStencilState() :
        depthTestEnable(true),
        depthWriteEnable(true),
        stencilTestEnable(false),
        depthCompareOp(CompareOp::Less) {}
};

// 混合状态
struct BlendState {
    bool logicOpEnable;            // 逻辑操作启用
    bool blendEnable;              // 混合启用

    enum class BlendFactor {
        Zero,
        One,
        SrcColor,
        OneMinusSrcColor,
        DstColor,
        OneMinusDstColor,
        SrcAlpha,
        OneMinusSrcAlpha,
        DstAlpha,
        OneMinusDstAlpha,
        ConstantColor,
        OneMinusConstantColor,
        ConstantAlpha,
        OneMinusConstantAlpha,
        SrcAlphaSaturate
    };

    enum class BlendOp {
        Add,
        Subtract,
        ReverseSubtract,
        Min,
        Max
    };

    enum class LogicOp {
        Clear,
        And,
        AndReverse,
        Copy,
        AndInverted,
        NoOp,
        Xor,
        Or,
        Nor,
        Equivalent,
        Invert,
        OrReverse,
        CopyInverted,
        OrInverted,
        Nand,
        Set
    };

    BlendFactor srcColorBlendFactor;
    BlendFactor dstColorBlendFactor;
    BlendOp colorBlendOp;
    BlendFactor srcAlphaBlendFactor;
    BlendFactor dstAlphaBlendFactor;
    BlendOp alphaBlendOp;
    LogicOp logicOp;
    uint32_t colorWriteMask;

    BlendState() :
        logicOpEnable(false),
        blendEnable(false),
        srcColorBlendFactor(BlendFactor::One),
        dstColorBlendFactor(BlendFactor::Zero),
        colorBlendOp(BlendOp::Add),
        srcAlphaBlendFactor(BlendFactor::One),
        dstAlphaBlendFactor(BlendFactor::Zero),
        alphaBlendOp(BlendOp::Add),
        logicOp(LogicOp::Copy),
        colorWriteMask(0xF) {}
};

// 管线布局描述
struct PipelineLayoutDesc {
    std::vector<void*> descriptorSetLayouts;  // 描述符集布局
    std::vector<void*> pushConstantRanges;    // 推送常量范围
};

// 管线状态描述基类
struct PipelineStateDesc {
    void* pipelineLayout;          // 管线布局
    void* renderPass;              // 渲染通道（仅图形管线）
    uint32_t subpass;              // 子通道索引（仅图形管线）
};

// 图形管线状态描述
struct GraphicsPipelineStateDesc : public PipelineStateDesc {
    std::vector<VertexAttribute> vertexAttributes;  // 顶点属性
    std::vector<VertexBinding> vertexBindings;      // 顶点绑定
    RasterizationState rasterizationState;          // 光栅化状态
    DepthStencilState depthStencilState;           // 深度模板状态
    std::vector<BlendState> blendStates;           // 每个渲染目标的混合状态
    void* vertexShader;                            // 顶点着色器
    void* pixelShader;                             // 像素着色器
    void* geometryShader;                          // 几何着色器
    void* hullShader;                              // 曲面细分控制着色器
    void* domainShader;                            // 曲面细分评估着色器
    uint32_t sampleCount;                          // 多重采样数
    bool alphaToCoverageEnable;                    // Alpha到覆盖率启用
};

// 计算管线状态描述
struct ComputePipelineStateDesc : public PipelineStateDesc {
    void* computeShader;           // 计算着色器
};

// 管线状态对象抽象基类
class IPipelineState {
public:
    virtual ~IPipelineState() = default;

    // 获取原生句柄
    // DirectX12: ID3D12PipelineState*
    // Vulkan: VkPipeline
    // Metal: id<MTLRenderPipelineState>/id<MTLComputePipelineState>
    virtual Result<void*> GetNativeHandle() = 0;

    // 获取管线布局
    virtual Result<void*> GetPipelineLayout() const = 0;

    // 获取着色器
    virtual Result<void*> GetShader(ShaderStageFlag stage) const = 0;

protected:
    PipelineStateDesc m_desc;
};

// 用于创建管线状态对象的工厂函数声明
using GraphicsPipelineStateCreateFunc = Result<IPipelineState*> (*)(const GraphicsPipelineStateDesc& desc);
using ComputePipelineStateCreateFunc = Result<IPipelineState*> (*)(const ComputePipelineStateDesc& desc);

} // namespace RHI
