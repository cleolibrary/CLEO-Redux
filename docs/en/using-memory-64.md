> This guide is for x64 hosts (e.g. the remastered trilogy). For the information on using the Memory class on x86 (classic era games) [click here](./using-memory.md).

# Memory Object (x64)

An intrinsic object `Memory` provides methods for accessing and manipulating the data or code in the current process. It has the following interface:

```ts
interface Memory {
    ReadFloat(address: int, vp: boolean, ib: boolean): float;
    WriteFloat(address: int, value: float, vp: boolean, ib: boolean): void;
    ReadI8(address: int, vp: boolean, ib: boolean): int;
    ReadI16(address: int, vp: boolean, ib: boolean): int;
    ReadI32(address: int, vp: boolean, ib: boolean): int;
    ReadU8(address: int, vp: boolean, ib: boolean): int;
    ReadU16(address: int, vp: boolean, ib: boolean): int;
    ReadU32(address: int, vp: boolean, ib: boolean): int;
    ReadUtf8(address: int, ib: boolean): string;
    ReadUtf16(address: int, ib: boolean): string;
    WriteI8(address: int, value: int, vp: boolean, ib: boolean): void;
    WriteI16(address: int, value: int, vp: boolean, ib: boolean): void;
    WriteI32(address: int, value: int, vp: boolean, ib: boolean): void;
    WriteU8(address: int, value: int, vp: boolean, ib: boolean): void;
    WriteU16(address: int, value: int, vp: boolean, ib: boolean): void;
    WriteU32(address: int, value: int, vp: boolean, ib: boolean): void;
    WriteUtf8(address: int, value: string, vp: boolean, ib: boolean): void;
    WriteUtf16(address: int, value: string, vp: boolean, ib: boolean): void;
    Read(address: int, size: int, vp: boolean, ib: boolean): int;
    Write(address: int, size: int, value: int, vp: boolean, ib: boolean): void;

    ToFloat(value: int): float;
    FromFloat(value: float): int;
    ToU8(value: int): int;
    ToU16(value: int): int;
    ToU32(value: int): int;
    ToI8(value: int): int;
    ToI16(value: int): int;
    ToI32(value: int): int;

    CallFunction(address: int, ib: boolean, numParams: int, ...funcParams: int[]): void;
    CallFunctionReturn(address: int, ib: boolean, numParams: int, ...funcParams: int[]): int;
    CallFunctionReturnFloat(address: int, ib: boolean, numParams: int, ...funcParams: int[]): float;

    Fn: {
        X64(address: int, ib: boolean): (...funcParams: int[]) => int;
        X64Float(address: int, ib: boolean): (...funcParams: int[]) => float;
        X64I8(address: int, ib: boolean): (...funcParams: int[]) => int;
        X64I16(address: int, ib: boolean): (...funcParams: int[]) => int;
        X64I32(address: int, ib: boolean): (...funcParams: int[]) => int;
        X64U8(address: int, ib: boolean): (...funcParams: int[]) => int;
        X64U16(address: int, ib: boolean): (...funcParams: int[]) => int;
        X64U32(address: int, ib: boolean): (...funcParams: int[]) => int;
    }
}
```

### Reading and Writing Values

Group of memory access methods (`ReadXXX`/`WriteXXX`) can be used for reading or modifying values stored in the memory. Each method is designed for a particular data type. To change a floating-point value (which occupies 4 bytes in the original game) use `Memory.WriteFloat`, e.g.:

```js
    Memory.WriteFloat(address, 1.0, false, false)
```

where `address` is a variable storing the memory location, `1.0` is the value to write, the first `false` means it's not necessary to change the memory protection with `VirtualProtect` (the address is already writable). The second `false` is the value of the `ib` flag that instructs CLEO to treat the `address` either as an absolute address (`ib` = `false`) or a relative offset to the current image base address (`ib` = `true`). Due to an ASLR feature memory addresses could change when the game runs because the base address changes. Consider the following example:

```
0x1400000000 ImageBase
...
...
0x1400000020 SomeValue
```
You want to change `SomeValue` that is currently located at `0x1400000020`. You can do it with `Memory.Write(0x1400000020, 1, 1, false, false)`. However on the next game run the memory layout might look like this:

```
0x1500000000 ImageBase
...
...
0x1500000020 SomeValue
```

effectively breaking the script. In this case, calculate a relative offset from the image base ( `0x1500000020` - `0x1500000000` = `0x20` ), that will be permanent for the particular game version. Use `Memory.Write` as follows: `Memory.Write(0x20, 1, 1, false, true)`. CLEO will sum up the offset (`0x20`) with the current value of the image base (`0x1400000000`, `0x1500000000`, etc) and write to the correct absolute address.

For your convenience you can find the current value of the image base in the `cleo_redux.log`, e.g.:

```
09:27:35 [INFO] Image base address 0x7ff7d1f50000
```

Similarly, to read a value from the memory, use one of the `ReadXXX` methods, depending on what data type the memory address contains. For example, to read a 8-bit signed integer (also known as a `char` or `uint8`) use `Memory.ReadI8`, e.g.:

```js
    var x = Memory.ReadI8(offset, true, true)
```

variable `x` now holds a 8-bit integer value in the range (0..255). For the sake of showing possible options, this example uses `true` as the last argument, which means the default protection attribute for this address will be changed to `PAGE_EXECUTE_READWRITE` before the read.

```js
    var gravity = Memory.ReadFloat(gravityOffset, false, true);
    gravity += 0.05;
    Memory.WriteFloat(gravityOffset, gravity, false, true);
```

Finally, last two methods `Read` and `Write` is what other methods use under the hood. They have direct binding to the Rust code that reads and write the memory. In JavaScript code you can use input arguments as large as 53-bit numbers.

The `size` parameter in the `Read` method can only be `1`, `2`, `4` or `8`. CLEO treats the `value` as a signed integer stored in the little-endian format. 

In the `Write` method any `size` larger than `0` is allowed. Sizes `3`, `5`, `6`, `7` and `9` onwards can only be used together with a single byte `value`.  CLEO uses them to fill a continious block of memory starting at the `address` with the given `value` (think of it as `memset` in C++).

```js
    Memory.Write(offset, 0x90, 10, true, true) // "noping" 10 bytes of code starting from offset+image base
```

> The usage of any of the read/write methods requires the `mem` [permission](./permissions.md).

### Reading and Writing Strings

The `ReadUtf8` and `ReadUtf16` methods are used to read strings from the memory and return it as a JavaScript string. They read a character sequence until the first null terminator is found. `ReadUtf8` expects the string to be encoded in UTF-8, while `ReadUtf16` expects UTF-16. Null terminator is not included in the result. Last argument `ib` indicates whethers the `address` is an absolute address or a relative offset to the image base.

```js
    var str = Memory.ReadUtf8(0x100000, false); // read string from address 0x100000
    var str = Memory.ReadUtf8(0x100000, true); // read string from address 0x100000+IMAGE_BASE
```

The `WriteUtf8` and `WriteUtf16` methods are used to write a JavaScript string to the memory. They write any character sequence including null terminator to the memory. `WriteUtf8` encodes the string in UTF-8, while `WriteUtf16` encodes it in UTF-16. Third argument is a boolean value indicating whether the command is allowed to overwrite the memory protection. Last argument `ib` indicates whethers the `address` is an absolute address or a relative offset to the image base.

```js
    Memory.WriteUtf8(0x100000, "Hello, world!\0\0", true, false); // write string to address 0x100000
    Memory.WriteUtf8(0x100000, "Hello, world!\0\0", true, true); // write string to address 0x100000+IMAGE_BASE
```

### Casting methods

By default `Read` and `Write` methods treat data as signed integer values. It can be inconvinient if the memory holds a floating-point value in IEEE 754 format or a large 32-bit signed integer (e.g. a pointer). In this case use casting methods `ToXXX`/`FromXXX`. They act similarly to [reinterpret_cast](https://docs.microsoft.com/en-us/cpp/cpp/reinterpret-cast-operator?view=msvc-160) operator in C++.

To get a quick idea what to expect from those methods see the following examples:

```js
    Memory.FromFloat(1.0) => 1065353216
    Memory.ToFloat(1065353216) => 1.0
    Memory.ToU8(-1) => 255
    Memory.ToU16(-1) => 65535
    Memory.ToU32(-1) => 4294967295
    Memory.ToI8(255) => -1
    Memory.ToI16(65535) => -1
    Memory.ToI32(4294967295) => -1
```

Alternatively, use appropriate methods to read/write the value as a float (`ReadFloat`/`WriteFloat`) or as an unsigned integer (`ReadUXXX`/`WriteUXXX`).

### Calling Foreign Functions

`Memory` object allows to invoke a foreign (native) function by its address using one of the following methods:

- `Memory.CallFunction` - calls a function at the address and discards the returned value
- `Memory.CallFunctionReturn` - calls a function and at the address and returns an integer value
- `Memory.CallFunctionReturnFloat` - calls a function and at the address and returns a floating-point value

```js
    Memory.CallFunction(0xEFFB30, true, 1, 13)
```
where `0xEFFB30` is the function offset relative to IMAGE BASE (think of it a randomized start address of the game memory), `true` is the `ib` flag (see below), `1` is the number of input arguments, and `13` are the only argument passed into the function.

The `ib` parameter in `Memory.CallFunction` has the same meaning as in memory read/write commands. When set to `true` CLEO adds the current known address of the image base to the value provided as the first argument to calculate the absolute memory address of the function. When set to `false` no changes to the first argument are made.

To pass floating-point values to the function, convert the value to integer using `Memory.FromFloat`:

```js
    Memory.CallFunction(0x1234567, true, 1, Memory.FromFloat(123.456));
```

The returned value of the function called with `Memory.CallFunction` is ignored. To read the result use `Memory.CallFunctionReturn` that has the same parameters. Use `Memory.CallFunctionReturnFloat` to call a function that returns a floating-point value.


CLEO Redux supports calling foreign functions with up to 16 parameters.

> The usage of any of the call methods requires the `mem` [permission](./permissions.md).

#### Convenience methods with Fn object

`Memory.Fn` provides convenient methods for calling different types of foreign functions.

```ts
    Fn: {
        X64(address: int, ib: boolean): (...funcParams: int[]) => int;
        X64Float(address: int, ib: boolean): (...funcParams: int[]) => float;
        X64I8(address: int, ib: boolean): (...funcParams: int[]) => int;
        X64I16(address: int, ib: boolean): (...funcParams: int[]) => int;
        X64I32(address: int, ib: boolean): (...funcParams: int[]) => int;
        X64U8(address: int, ib: boolean): (...funcParams: int[]) => int;
        X64U16(address: int, ib: boolean): (...funcParams: int[]) => int;
        X64U32(address: int, ib: boolean): (...funcParams: int[]) => int;
    }
```

These methods is designed to cover all supported return types. For example, this code

```js
    Memory.CallFunction(0xEFFB30, true, 1, 13)
```

can also be written as

```js
    Memory.Fn.X64(0xEFFB30, true)(13)
```

Note a few key differences here. First of all, `Memory.Fn` methods don't invoke a foreign function directly. Instead, they return a new JavaScript function that can be stored in a variable and reused to call the associated foreign function many times with different arguments:

```js
    var f = Memory.Fn.X64(0xEFFB30, true);
    f(13) // calls function 0xEFFB30 with the argument of 13
    f(11) // calls method 0xEFFB30 with the argument of 11
```

The second difference is that there is no `numParams` parameter. Each `Fn` method figures it out automatically.

By default a returned result is considered a 64-bit signed integer value. If the function returns another type (e.g. a boolean), use one of the methods matching the function signature:

```js
    var flag = Memory.Fn.X64U8(0x1234567, true)()
```

This code invokes a function at `0x1234567` + IMAGE_BASE with no arguments and stores the result as a 8-bit unsigned integer value. 

```js
    var float = Memory.Fn.X64Float(0x456789, true)()
```

This code invokes a function at `0x456789` + IMAGE_BASE with no arguments and stores the result as a floating-point value. 
