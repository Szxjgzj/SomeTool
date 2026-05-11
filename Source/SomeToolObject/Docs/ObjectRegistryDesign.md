# SomeToolObject Runtime Registry Design

## Goal

`SomeToolObject` is reserved for runtime UObject and Actor lifetime helpers.

The first planned system is a World-level runtime registry. It should reduce direct long-lived references between gameplay systems and short-lived world objects.

## Core Rule

Persistent systems should not strongly own objects that belong to an unloadable Level.

Use this model instead:

```text
Runtime object -> registers itself to a World registry
Runtime object -> unregisters itself during shutdown/end play
Other systems  -> query the registry when they need current objects
Registry       -> stores weak references
```

## Target Scope

The registry is for runtime instances:

```text
Actor
ActorComponent
UserWidget
temporary UObject business objects
```

It is not meant to replace asset/resource management:

```text
DataAsset
Blueprint class assets
texture/material/static mesh assets
pak resource soft references
```

Assets should stay in `SomeToolPak` / `ResourceRegistry` / UE AssetManager style systems.

## Recommended Lifetime Owner

Use `UWorldSubsystem` as the default owner.

Reason:

```text
World subsystem lifetime follows the current World
OpenLevel creates a new World context
Unloadable Level objects should not be owned by GameInstance-level systems
```

Avoid using `GameInstanceSubsystem` for direct Actor references unless the references are weak and aggressively cleaned.

## Registration Model

Planned object-side pattern:

```text
BeginPlay / Initialize:
  RegisterSelf

EndPlay / Deinitialize:
  UnregisterSelf
  clear timers
  unbind delegates
  cancel async callbacks
```

Registry-side storage:

```text
FName Id -> TWeakObjectPtr<UObject>
FName Tag -> TArray<TWeakObjectPtr<UObject>>
UClass/Interface -> TArray<TWeakObjectPtr<UObject>>
```

All query functions should remove invalid weak references opportunistically.

## Query Model

External systems should prefer short-lived lookups:

```text
Find current object by Id
Get current objects by Tag
Get current objects implementing Interface
```

External systems should not cache strong Actor references across map or level boundaries.

If a system must cache a result, it should use weak references or stable data IDs.

## Blueprint Use

Desired Blueprint-facing API:

```text
Register Runtime Object
Unregister Runtime Object
Find Runtime Object
Get Runtime Objects By Tag
Get Runtime Objects By Class
Get Runtime Objects By Interface
Clear Invalid Runtime Object References
```

Optional object interface:

```text
SomeToolRuntimeRegistryItem
  Get Registry Id
  Get Registry Tags
```

## Open Questions

Keep these undecided until implementation:

```text
Whether registration is explicit through Blueprint nodes or automatic through an interface/component
Whether Id must be globally unique inside a World
Whether tag queries should use FName or GameplayTag
Whether widgets should live in the same registry or a separate UI registry
```

## Practical Rule

The registry should make this pattern easy:

```text
Actor can reference services.
Services should not strongly own unloadable Actor instances.
```
