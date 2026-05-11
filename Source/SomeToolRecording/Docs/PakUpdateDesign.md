# SomeTool Pak Update Design

This note records the current SomeToolPak capability and the planned update system. It is stored under the recording module only as a design record; the implementation still lives in `SomeToolPak` and `SomeToolPakEditor`.

## 中文摘要

这份文档记录 SomeToolPak 当前已经完成的能力，以及后续要补齐的 Pak 热更新设计。文档只作为设计记录存放在录制模块下，实际实现仍然属于 `SomeToolPak` 和 `SomeToolPakEditor`。

当前已经基本完成的是“Pak 处理机制”：

- 用 `PakId` 作为运行时和构建时的统一入口。
- 用 `DA_PakEntry_{PakId}` 作为 Pak 入口资产。
- 编辑器工具可以根据 Pak 入口资产生成资源列表、Cook、调用 UnrealPak，并输出 `.pak` 和 `.manifest.json`。
- 运行时可以调用 `Mount Game Pak(PakId)`，自动读取同名 manifest，找到同目录 pak，mount 后返回 Pak 入口 DataAsset。
- `ResourceRegistry` 用来管理动态软引用资源。

还没有完成的是“Pak 更新机制”：

- 还没有总表 `PakTable.json`。
- 还没有远程表和本地表对比。
- 还没有 HTTP 下载流程。
- 还没有 hash/size 校验。
- 还没有废弃 Pak 清理。
- 还没有按依赖自动 mount。
- 还没有 Base/Patch/DLC 类型和 MountOrder 策略。
- 还没有主程序兼容版本判断。

整体方向是：

```text
Pak 处理：
  PakId -> manifest -> mount -> EntryData / ResourceRegistry

Pak 更新：
  PakTable -> 对比版本/Hash/Size -> 下载/删除/校验 -> 按依赖和优先级 mount
```

## Current Scope

SomeToolPak currently covers manual Pak production and runtime mounting by `PakId`.

- `PakId` is the public identifier.
- `DA_PakEntry_{PakId}` is the content entry asset.
- `USomeToolPakPrimaryAsset` contains:
  - `EntryMap`
  - `ResourceRegistry`
  - `DependentPakIds`
- `USomeToolPakResourceRegistry` contains:
  - `Namespace`
  - `SoftObjects`
  - `SoftClasses`
- Editor UI can build:
  - `{PakId}.pak`
  - `{PakId}.manifest.json`
- The editor build path already runs:
  - resource list generation
  - Cook
  - UnrealPak
  - real-time build log display
- Runtime can call `Mount Game Pak(PakId)`.
- Mounting reads `{PakId}.manifest.json`, resolves the sibling pak file, mounts it, scans `/Game`, and returns the Pak entry asset.

Current runtime convention:

```text
Content/Paks/{PakId}.pak
Content/Paks/{PakId}.manifest.json

Saved/Paks/{PakId}.pak
Saved/Paks/{PakId}.manifest.json
```

## 当前已有功能

SomeToolPak 当前覆盖的是手动构建 Pak 和运行时按 `PakId` 挂载。

- `PakId` 是公开使用的包标识。
- `DA_PakEntry_{PakId}` 是内容入口资产。
- `USomeToolPakPrimaryAsset` 包含：
  - `EntryMap`
  - `ResourceRegistry`
  - `DependentPakIds`
- `USomeToolPakResourceRegistry` 包含：
  - `Namespace`
  - `SoftObjects`
  - `SoftClasses`
- 编辑器 UI 可以构建：
  - `{PakId}.pak`
  - `{PakId}.manifest.json`
- 编辑器构建流程已经打通：
  - 生成资源列表
  - Cook
  - UnrealPak
  - 实时构建日志显示
- 运行时可以调用 `Mount Game Pak(PakId)`。
- Mount 过程会读取 `{PakId}.manifest.json`，解析同目录下的 pak 文件，挂载后扫描 `/Game`，并返回 Pak 入口资产。

当前运行时约定目录：

```text
Content/Paks/{PakId}.pak
Content/Paks/{PakId}.manifest.json

Saved/Paks/{PakId}.pak
Saved/Paks/{PakId}.manifest.json
```

## Current Missing Pieces

The current system is not yet a full hot update system.

- No global `PakTable.json`.
- No local versus remote table comparison.
- No HTTP download pipeline.
- No hash or size verification.
- No automatic cleanup for obsolete pak files.
- No automatic recursive mount for `DependentPakIds`.
- No Base/Patch/DLC type model.
- No table-driven mount order.
- No app version compatibility gate.
- No launcher/updater process for replacing the main executable or DLLs.

## 当前缺失功能

当前系统还不是完整热更新系统。

- 没有全局 `PakTable.json`。
- 没有本地表和远程表对比。
- 没有 HTTP 下载流程。
- 没有 hash 或 size 校验。
- 没有自动清理废弃 pak 文件。
- 没有对 `DependentPakIds` 做自动递归 mount。
- 没有 Base/Patch/DLC 类型模型。
- 没有表驱动的 mount 顺序。
- 没有主程序版本兼容检查。
- 没有用于替换主程序或 DLL 的 Launcher/Updater 外部进程。

## Resource Rules

Hard references are handled by UE cook dependency collection once the entry asset is included.

Examples:

```text
Map -> Blueprint -> StaticMesh -> Material -> Texture
```

Dynamic resources must be registered explicitly.

Use `ResourceRegistry` for:

- soft object references
- soft class references
- resources selected by name
- runtime-loaded resources
- resources not reachable by hard reference from the entry map or entry asset

Do not rely on runtime string paths as the only source of truth. If a resource is loaded dynamically, it should be represented in a registry or future table rule.

## 资源规则

硬引用资源由 UE 的 Cook 依赖分析收集，前提是入口资源本身已经被纳入 Cook。

例如：

```text
Map -> Blueprint -> StaticMesh -> Material -> Texture
```

只要 `Map` 被纳入 Cook，后续硬引用链通常会被自动收集。

动态资源必须显式注册。

这些资源应该进入 `ResourceRegistry`：

- 软对象引用
- 软类引用
- 按名称选择的资源
- 运行时动态加载的资源
- 无法从入口地图或入口资产硬引用到的资源

不要把运行时字符串路径当成唯一依据。只要资源是动态加载的，就应该进入 `ResourceRegistry`，或者后续进入某种资源表规则。

## Pak Types

The update table should distinguish logical pak type from physical pak files.

```text
BasePak
  Complete content for a logical PakId version.

PatchPak
  Replacement cooked packages for existing package paths.
  Mounted with higher order than the base pak.

DlcPak
  New content, maps, language packs, voice packs, gameplay packs.
```

Important rule:

```text
Modifying an existing resource should keep the same /Game package path.
Moving a resource changes its identity and requires updating every referencing package.
```

If a resource referenced by the main package moves from:

```text
/Game/Old/A.A
```

to:

```text
/Game/New/A.A
```

then a DLC pak containing only the new path will not replace the old reference. Either keep the old path for a patch override, or also patch every package that references the old path.

## Pak 类型

更新总表需要区分逻辑 Pak 类型和物理 pak 文件。

```text
BasePak
  某个逻辑 PakId 的完整内容版本。

PatchPak
  用于替换已有资源路径的 cooked 包。
  需要用更高 MountOrder 挂载，从而覆盖 BasePak 或主包中的同路径资源。

DlcPak
  新增内容，例如新地图、新玩法、语言包、语音包。
```

重要规则：

```text
修改已有资源时，最好保持同一个 /Game 包路径。
移动资源等于改变资源身份，所有引用方也必须跟着更新。
```

如果主包引用的资源从：

```text
/Game/Old/A.A
```

移动到：

```text
/Game/New/A.A
```

那么只发布包含新路径的 DLC Pak，不能替换主包里的旧引用。要么保持旧路径做补丁覆盖，要么同时补丁更新所有引用旧路径的资源。

## Planned PakTable

`PakTable.json` should become the single source of truth for runtime resource updates.

Suggested shape:

```json
{
  "TableVersion": 1,
  "ProjectName": "P_Recording_53_AS",
  "TargetPlatform": "Win64",
  "MinAppVersion": "1.0.0",
  "MaxAppVersion": "1.0.x",
  "Paks": [
    {
      "PakId": "MapPack_001",
      "Type": "DLC",
      "Version": 3,
      "Required": false,
      "MountOnStartup": false,
      "Dependencies": ["BaseResources"],
      "Files": [
        {
          "FileName": "MapPack_001_v3_abcd1234.pak",
          "ManifestFile": "MapPack_001_v3_abcd1234.manifest.json",
          "Hash": "sha256...",
          "Size": 12345678,
          "MountOrder": 100
        }
      ]
    }
  ]
}
```

Recommended file naming:

```text
{PakId}_v{Version}_{HashPrefix}.pak
{PakId}_v{Version}_{HashPrefix}.manifest.json
```

Do not overwrite old pak files on the CDN. Update `PakTable.json` to point to the new files.

## 计划中的 PakTable

`PakTable.json` 应该成为运行时资源更新的唯一依据。

建议结构：

```json
{
  "TableVersion": 1,
  "ProjectName": "P_Recording_53_AS",
  "TargetPlatform": "Win64",
  "MinAppVersion": "1.0.0",
  "MaxAppVersion": "1.0.x",
  "Paks": [
    {
      "PakId": "MapPack_001",
      "Type": "DLC",
      "Version": 3,
      "Required": false,
      "MountOnStartup": false,
      "Dependencies": ["BaseResources"],
      "Files": [
        {
          "FileName": "MapPack_001_v3_abcd1234.pak",
          "ManifestFile": "MapPack_001_v3_abcd1234.manifest.json",
          "Hash": "sha256...",
          "Size": 12345678,
          "MountOrder": 100
        }
      ]
    }
  ]
}
```

推荐文件命名：

```text
{PakId}_v{Version}_{HashPrefix}.pak
{PakId}_v{Version}_{HashPrefix}.manifest.json
```

CDN 上不要直接覆盖旧 pak 文件。应该生成新文件名，然后只更新 `PakTable.json` 指向新的文件。

## Runtime Update Flow

The game process can update resource paks because it is not replacing the running executable or loaded DLLs.

Planned flow:

```text
1. Read local PakTable.
2. Download remote PakTable.
3. Check app version compatibility.
4. Compare PakId, Version, Hash, and Size.
5. Download missing or outdated pak files to a temporary path.
6. Verify hash and size.
7. Move verified files into Saved/Paks.
8. Remove local pak files that are no longer referenced by the remote table.
9. Mount required paks by dependency order and MountOrder.
10. Save the new local PakTable.
```

Temporary download path:

```text
Saved/Paks/Downloading/{FileName}.tmp
```

Installed path:

```text
Saved/Paks/{FileName}
Saved/Paks/{ManifestFile}
```

## 运行时更新流程

游戏进程可以更新资源 Pak，因为它不需要替换正在运行的 exe 或已加载 DLL。

计划流程：

```text
1. 读取本地 PakTable。
2. 下载远程 PakTable。
3. 检查主程序版本是否兼容。
4. 对比 PakId、Version、Hash、Size。
5. 将缺失或过期的 pak 文件下载到临时路径。
6. 校验 hash 和 size。
7. 将校验通过的文件移动到 Saved/Paks。
8. 删除远程表不再引用的本地 pak 文件。
9. 按依赖顺序和 MountOrder 挂载需要的 pak。
10. 保存新的本地 PakTable。
```

临时下载路径：

```text
Saved/Paks/Downloading/{FileName}.tmp
```

安装后的路径：

```text
Saved/Paks/{FileName}
Saved/Paks/{ManifestFile}
```

## CDN Requirements

The CDN only needs to serve static files over HTTPS.

Recommended layout:

```text
https://cdn.example.com/P_Recording_53_AS/Win64/PakTable.json
https://cdn.example.com/P_Recording_53_AS/Win64/Paks/MapPack_001_v3_abcd1234.pak
https://cdn.example.com/P_Recording_53_AS/Win64/Paks/MapPack_001_v3_abcd1234.manifest.json
```

Useful CDN features:

- HTTPS
- large file support
- Range requests for resume support
- custom domain
- stable cache behavior
- optional token or signed URL access

Suggested cache policy:

```text
PakTable.json:
  Cache-Control: no-cache

.pak and .manifest.json with version/hash in file name:
  Cache-Control: public, max-age=31536000, immutable
```

Possible providers:

- Tencent Cloud COS + CDN
- Aliyun OSS + CDN
- Cloudflare R2 + CDN
- AWS S3 + CloudFront
- DigitalOcean Spaces CDN

## CDN 要求

CDN 只需要能通过 HTTPS 稳定提供静态文件下载。

推荐目录：

```text
https://cdn.example.com/P_Recording_53_AS/Win64/PakTable.json
https://cdn.example.com/P_Recording_53_AS/Win64/Paks/MapPack_001_v3_abcd1234.pak
https://cdn.example.com/P_Recording_53_AS/Win64/Paks/MapPack_001_v3_abcd1234.manifest.json
```

有用的 CDN 能力：

- HTTPS
- 大文件支持
- Range 请求，用于断点续传
- 自定义域名
- 稳定缓存策略
- 可选 Token 或签名 URL 防盗链

建议缓存策略：

```text
PakTable.json:
  Cache-Control: no-cache

带版本/hash 文件名的 .pak 和 .manifest.json:
  Cache-Control: public, max-age=31536000, immutable
```

可选服务：

- 腾讯云 COS + CDN
- 阿里云 OSS + CDN
- Cloudflare R2 + CDN
- AWS S3 + CloudFront
- DigitalOcean Spaces CDN

## Download Implementation Options

Recommended first implementation:

```text
FHttpModule + custom SomeToolPak update subsystem
```

Reasons:

- Fits the current `PakId` model.
- Small enough to control.
- Can write exactly the table format we need.
- UE 5.3 HTTP requests support progress callbacks and response streaming.

Other options:

```text
ChunkDownloader
  UE built-in plugin for chunk pak download and mount.
  Useful, but its chunk model is not the same as the current PakId model.

BuildPatchServices
  Heavy system similar to launcher patching.
  Better suited for an external updater or main program distribution.
```

## 下载实现方案

第一版推荐：

```text
FHttpModule + 自定义 SomeToolPak 更新子系统
```

原因：

- 贴合当前 `PakId` 模型。
- 足够轻，方便控制。
- 可以完全按需要设计 `PakTable`。
- UE 5.3 HTTP 请求支持进度回调和响应流式写入。

其他方案：

```text
ChunkDownloader
  UE 内置插件，用于 chunk pak 下载和 mount。
  可以用，但它的 chunk 模型和当前 PakId 模型不完全一致。

BuildPatchServices
  更重，接近 Launcher 补丁系统。
  更适合外部更新器或主程序分发。
```

## Main Program Updates

Pak update should not replace the running executable or loaded DLLs.

Use a separate process for main program updates:

```text
Launcher.exe or Updater.exe
Game/
  P_Recording_53_AS-Win64-Shipping.exe
  Engine/
  Content/
  Plugins/
```

Responsibilities:

```text
Game process:
  Resource Pak updates, PakTable, MountPak.

Launcher or Updater process:
  Main executable, DLLs, plugins, full package replacement.
```

The game can detect an incompatible `PakTable` and launch the updater:

```text
Game detects app version mismatch
-> starts Updater.exe
-> exits
-> Updater waits for game exit
-> replaces files
-> restarts game
```

## 主程序更新

Pak 更新不应该负责替换正在运行的 exe 或已加载 DLL。

主程序更新应该交给单独进程：

```text
Launcher.exe 或 Updater.exe
Game/
  P_Recording_53_AS-Win64-Shipping.exe
  Engine/
  Content/
  Plugins/
```

职责划分：

```text
Game 进程：
  资源 Pak 更新、PakTable、MountPak。

Launcher 或 Updater 进程：
  主程序、DLL、插件、完整包体替换。
```

游戏可以检测到不兼容的 `PakTable` 后拉起更新器：

```text
Game 检测到主程序版本不匹配
-> 启动 Updater.exe
-> Game 自己退出
-> Updater 等待 Game 完全退出
-> 替换文件
-> 重启 Game
```

## Suggested Implementation Order

1. Add `PakTable.json` structs and parser.
2. Generate or update `PakTable.json` from the editor build UI.
3. Add hash and size to built pak outputs.
4. Add runtime local table read and local file verification.
5. Add dependency-aware mount by table.
6. Add HTTP download of remote table and pak files.
7. Add obsolete file cleanup.
8. Add PatchPak/BasePak/DlcPak mount-order policy.
9. Add UI callbacks for download progress and errors.
10. Add external updater design for main program replacement.

## 建议实现顺序

1. 增加 `PakTable.json` 结构体和解析。
2. 在编辑器构建 UI 中生成或更新 `PakTable.json`。
3. 为构建出来的 pak 输出 hash 和 size。
4. 增加运行时本地表读取和本地文件校验。
5. 增加按依赖 mount 的能力。
6. 增加远程表和 pak 文件 HTTP 下载。
7. 增加废弃文件清理。
8. 增加 PatchPak/BasePak/DlcPak 的 MountOrder 策略。
9. 增加下载进度和错误回调。
10. 增加主程序外部更新器设计。
