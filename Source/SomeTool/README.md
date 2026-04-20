# SomeTool Module Layout

`SomeTool` 现在保留为通用运行时工具模块，按业务域整理为以下目录：

- `Public/Blueprint`, `Private/Blueprint`
  - `UBlueprintObject`
  - 提供可在蓝图中使用的 `UObject` 基类，适合绑定到真实 world 上下文后执行潜伏节点。
- `Public/Gameplay`, `Private/Gameplay`
  - `ANoSkelCharacter`
  - 保留 `ACharacter` 的移动与碰撞能力，但不创建默认骨骼网格组件。
- `Public/Geometry`, `Private/Geometry`
  - `UGeometryInstance`
  - 负责形状采样与实例布点。
- `Public/Math`, `Private/Math`
  - `UFunctionLibrary`
  - 放置贝塞尔与形状采样等通用数学/空间工具。

## About UObject + Delay In Editor

让 `UObject` 支持 `Delay` 在编辑器里不是完全没意义，但前提很严格：

- 对象必须能拿到一个真实且会持续 Tick 的 `World`。
- 这更适合 `PIE`、运行时对象、Editor Utility、预览世界等 world-backed 场景。
- 对普通资源对象、配置对象、纯编辑器数据对象来说，`Delay` 通常没有稳定意义。

因此，`UBlueprintObject` 更应该被视为“需要 world 上下文的蓝图对象基类”，而不是“任何 UObject 都能安全跑潜伏节点”的通用解法。
