# Memory Object

> This guide is for x86 hosts (such as classic era games). For the information on using the Memory class on x64 hosts (such as the Definitive edition) [click here](./using-memory-64.md).

- [Reading and Writing Numbers](#reading-and-writing-numbers)
- [Reading and Writing Strings](#reading-and-writing-strings)
- [Casting methods](#casting-methods)
- [Calling Foreign Functions](#calling-foreign-functions)
  - [Convenience methods with Fn object](#convenience-methods-with-fn-object)
- [Finding Memory Addresses in re3 and reVC](#finding-memory-addresses-in-re3-and-revc)
- [Allocating and Freeing Memory](#allocating-and-freeing-memory)

An intrinsic object `Memory` provides methods for accessing and manipulating the data or code in the current process. It has the following interface:

```ts
interface Memory {
  ReadFloat(address: int, vp?: boolean): float;
  WriteFloat(address: int, value: float, vp?: boolean): void;
  ReadI8(address: int, vp?: boolean): int;
  ReadI16(address: int, vp?: boolean): int;
  ReadI32(address: int, vp?: boolean): int;
  ReadU8(address: int, vp?: boolean): int;
  ReadU16(address: int, vp?: boolean): int;
  ReadU32(address: int, vp?: boolean): int;
  ReadUtf8(address: int): string;
  ReadUtf16(address: int): string;
  WriteI8(address: int, value: int, vp?: boolean): void;
  WriteI16(address: int, value: int, vp?: boolean): void;
  WriteI32(address: int, value: int, vp?: boolean): void;
  WriteU8(address: int, value: int, vp?: boolean): void;
  WriteU16(address: int, value: int, vp?: boolean): void;
  WriteU32(address: int, value: int, vp?: boolean): void;
  WriteUtf8(address: int, value: string, vp?: boolean): void;
  WriteUtf16(address: int, value: string, vp?: boolean): void;
  Read(address: int, size: int, vp?: boolean): int;
  Write(address: int, size: int, value: int, vp?: boolean): void;

  ToFloat(value: int): float;
  FromFloat(value: float): int;
  ToU8(value: int): int;
  ToU16(value: int): int;
  ToU32(value: int): int;
  ToI8(value: int): int;
  ToI16(value: int): int;
  ToI32(value: int): int;

  Translate(symbol: string): int;

  CallFunction(address: int, numParams: int, pop: int, ...funcParams: int[]): void;
  CallFunctionReturn(address: int, numParams: int, pop: int, ...funcParams: int[]): int;
  CallFunctionReturnFloat(address: int, numParams: int, pop: int, ...funcParams: int[]): float;
  CallMethod(address: int, struct: int, numParams: int, pop: int, ...funcParams: int[]): void;
  CallMethodReturn(address: int, struct: int, numParams: int, pop: int, ...funcParams: int[]): int;
  CallMethodReturnFloat(address: int, struct: int, numParams: int, pop: int, ...funcParams: int[]): float;

  Allocate(size: int): int;
  Free(address: int): void;

  Fn: {
    Cdecl(address: int): (...funcParams: int[]) => int;
    CdeclFloat(address: int): (...funcParams: int[]) => float;
    CdeclI8(address: int): (...funcParams: int[]) => int;
    CdeclI16(address: int): (...funcParams: int[]) => int;
    CdeclI32(address: int): (...funcParams: int[]) => int;
    CdeclU8(address: int): (...funcParams: int[]) => int;
    CdeclU16(address: int): (...funcParams: int[]) => int;
    CdeclU32(address: int): (...funcParams: int[]) => int;

    Stdcall(address: int): (...funcParams: int[]) => int;
    StdcallFloat(address: int): (...funcParams: int[]) => float;
    StdcallI8(address: int): (...funcParams: int[]) => int;
    StdcallI16(address: int): (...funcParams: int[]) => int;
    StdcallI32(address: int): (...funcParams: int[]) => int;
    StdcallU8(address: int): (...funcParams: int[]) => int;
    StdcallU16(address: int): (...funcParams: int[]) => int;
    StdcallU32(address: int): (...funcParams: int[]) => int;

    Thiscall(address: int, struct: int): (...funcParams: int[]) => int;
    ThiscallFloat(address: int, struct: int): (...funcParams: int[]) => float;
    ThiscallI8(address: int, struct: int): (...funcParams: int[]) => int;
    ThiscallI16(address: int, struct: int): (...funcParams: int[]) => int;
    ThiscallI32(address: int, struct: int): (...funcParams: int[]) => int;
    ThiscallU8(address: int, struct: int): (...funcParams: int[]) => int;
    ThiscallU16(address: int, struct: int): (...funcParams: int[]) => int;
    ThiscallU32(address: int, struct: int): (...funcParams: int[]) => int;
  };
}
```

### Reading and Writing Numbers

A group of memory access methods (`ReadXXX`/`WriteXXX`) can be used for reading or modifying numbers stored in the memory. Each method is designed for a particular data type. For example, to change a floating-point number (which occupies 4 bytes in the original game) use `Memory.WriteFloat`:

```js
Memory.WriteFloat(address, 1.0, false);
```

where `address` is a variable storing the memory location, `1.0` is the value to write and `false` means it's not necessary to change the memory protection with `VirtualProtect` (the address is already writable).

Similarly, to read a number from the memory, use one of the `ReadXXX` methods, depending on what data type the memory address contains. For example, to read a 8-bit signed integer (also known as a `char` or `uint8`) use `Memory.ReadI8`:

```js
var x = Memory.ReadI8(address, true);
```

variable `x` now holds a 8-bit integer value in the range (0..255). For the sake of showing possible options, this example uses `true` as the last argument, which means the default protection attribute for this address will be changed to `PAGE_EXECUTE_READWRITE` before the read.

```js
var gravity = Memory.ReadFloat(gravityAddress, false);
gravity += 0.05;
Memory.WriteFloat(gravityAddress, gravity, false);
```

Finally, last two methods `Read` and `Write` is what other methods use under the hood. They have direct binding to opcodes [0A8D READ_MEMORY](https://library.sannybuilder.com/#/gta3/CLEO/0A8D) and [0A8C WRITE_MEMORY](https://library.sannybuilder.com/#/gta3/CLEO/0A8C) and produce the same result.

The `size` parameter in the `Read` method can only be `1`, `2` or `4`. CLEO treats the `value` as a signed integer stored in the little-endian format.

In the `Write` method any `size` larger than `0` is allowed. Sizes `3` and `5` onwards can only be used together with a single byte `value`. CLEO uses them to fill a continious block of memory starting at the `address` with the given `value` (think of it as `memset` in C++).

```js
Memory.Write(addr, 0x90, 10, true); // "noping" 10 bytes of code starting from addr
```

> The usage of any of the read/write methods requires the `mem` [permission](./permissions.md).

### Reading and Writing Strings

The `ReadUtf8` and `ReadUtf16` methods are used to read strings from the memory and return it as a JavaScript string. They read the character sequence until the first null terminator is found. `ReadUtf8` expects the string to be encoded in UTF-8, while `ReadUtf16` expects UTF-16. Null terminator is not included in the result.

```js
var str = Memory.ReadUtf8(address);
var str = Memory.ReadUtf16(address);
```

The `WriteUtf8` and `WriteUtf16` methods are used to write a JavaScript string to the memory. They write any character sequence including null terminator to the memory. `WriteUtf8` encodes the string in UTF-8, while `WriteUtf16` encodes it in UTF-16. Last argument is a boolean value indicating whether the command is allowed to overwrite the memory protection.

```js
Memory.WriteUtf8(address, "Hello, world!\0", true);
Memory.WriteUtf16(address, "Hello, world!\0", true);
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

- `Memory.CallMethod` - calls a class instance method and discards the returned value
- `Memory.CallMethodReturn` - calls a class instance method and returns an integer value
- `Memory.CallMethodReturnFloat` - calls a class instance method and returns a floating-point value

```js
Memory.CallFunction(0x1234567, 2, 0, 1000, 2000);
```

where `0x1234567` is the address of the function, `2` is the number of arguments, `0` is the `pop` parameter (see below), `1000` and `2000` are the two arguments passed into the function.

> Legacy SCM implementation of the call commands require the arguments of the invoked function to be listed in reverse order. That's it, you would see the same call in SCM as:
>
> ```
> 0AA5: call 0x1234567 num_params 2 pop 0 2000 1000
> ```
>
> where `2000` is the second argument passed to the function located at 0x1234567 and `1000` is the first one. In JS code all input arguments go in the direct order.

The third parameter (`pop`) in `Memory.CallFunction` defines the calling convention. When it is set to `0`, the function is called using the [stdcall](https://en.wikipedia.org/wiki/X86_calling_conventions#stdcall) convention. When it is set to the same value as `numParam`, the function is called using the [cdecl](https://en.wikipedia.org/wiki/X86_calling_conventions#cdecl) convention. Any other value breaks the code.

`Memory.CallFunctionReturn` has the same interface but additionally it writes the result of the function to a variable.

`Memory.CallMethod` invokes a method of an object:

```js
Memory.CallMethod(0x2345678, 0x7001234, 2, 0, 1000, 2000);
```

The second parameter (`0x7001234`) is the object address. The `pop` parameter is always `0` (the method uses the [thiscall](https://en.wikipedia.org/wiki/X86_calling_conventions#thiscall) convention).

To call the method and get the result out of it, use `Memory.CallMethodReturn`.

> Input arguments are treated as 32-bit signed integers. If you need to provide a floating-point number, use `Memory.FromFloat`, e.g.
> ```js
> Memory.CallFunction(0x1234567, 1, 1, Memory.FromFloat(123.456));
> ```

CLEO Redux supports calling foreign functions with up to 16 parameters.

> The usage of any of the call methods requires the `mem` [permission](./permissions.md).

#### Convenience methods with Fn object

`Memory.Fn` provides a lot of convenient methods for calling different types of foreign functions.

```ts
Fn: {
        Cdecl(address: int): (...funcParams: int[]) => int;
        CdeclFloat(address: int): (...funcParams: int[]) => float;
        CdeclI8(address: int): (...funcParams: int[]) => int;
        CdeclI16(address: int): (...funcParams: int[]) => int;
        CdeclI32(address: int): (...funcParams: int[]) => int;
        CdeclU8(address: int): (...funcParams: int[]) => int;
        CdeclU16(address: int): (...funcParams: int[]) => int;
        CdeclU32(address: int): (...funcParams: int[]) => int;

        Stdcall(address: int): (...funcParams: int[]) => int;
        StdcallFloat(address: int): (...funcParams: int[]) => float;
        StdcallI8(address: int): (...funcParams: int[]) => int;
        StdcallI16(address: int): (...funcParams: int[]) => int;
        StdcallI32(address: int): (...funcParams: int[]) => int;
        StdcallU8(address: int): (...funcParams: int[]) => int;
        StdcallU16(address: int): (...funcParams: int[]) => int;
        StdcallU32(address: int): (...funcParams: int[]) => int;

        Thiscall(address: int, struct: int): (...funcParams: int[]) => int;
        ThiscallFloat(address: int, struct: int): (...funcParams: int[]) => float;
        ThiscallI8(address: int, struct: int): (...funcParams: int[]) => int;
        ThiscallI16(address: int, struct: int): (...funcParams: int[]) => int;
        ThiscallI32(address: int, struct: int): (...funcParams: int[]) => int;
        ThiscallU8(address: int, struct: int): (...funcParams: int[]) => int;
        ThiscallU16(address: int, struct: int): (...funcParams: int[]) => int;
        ThiscallU32(address: int, struct: int): (...funcParams: int[]) => int;
    }
```

These methods is designed to cover all possible function signatures. For example, this code

```js
Memory.CallMethod(0x2345678, 0x7001234, 2, 0, 1000, 2000);
```

can also be written as

```js
Memory.Fn.Thiscall(0x2345678, 0x7001234)(1000, 2000);
```

Note a few key differences here. First of all, `Memory.Fn` methods don't invoke a foreign function directly. Instead, they return a new JavaScript function that can be stored in a variable and reused to call the associated foreign function many times with different arguments:

```js
var myMethod = Memory.Fn.Thiscall(0x2345678, 0x7001234);
myMethod(1000, 2000); // calls method 0x2345678 with arguments 1000 and 2000
myMethod(3000, 5000); // calls method 0x2345678 with arguments 3000 and 5000
```

The second difference is that there are no `numParams` and `pop` parameters. Each `Fn` method figures them out automatically.

By default a returned result is considered a 32-bit signed integer value. If the function returns another type (a floating-point value, or a signed integer), use one of the methods matching the function signature, e.g.:

```js
var flag = Memory.Fn.CdeclU8(0x1234567)();
```

This code invokes a `cdecl` function at `0x1234567` with no arguments and stores the result as a 8-bit unsigned integer value.

### Finding Memory Addresses in re3 and reVC

Since `re3` and `reVC` use address space layout randomization (ASLR) feature, it can be difficult to locate needed addresses. CLEO Redux provides a helper function `Memory.Translate` that accepts a name of the function or variable and returns its current address. If the requested symbol is not found, the result is 0.

```js
var addr = Memory.Translate("CTheScripts::MainScriptSize");

// check if address is not zero
if (addr) {
  showTextBox("MainScriptSize = " + Memory.ReadI32(addr, 0));
}
```

At the moment `Memory.Translate` should only be used in `re3` and `reVC`. In other games you will be getting `0` as a result most of the time.

### Allocating and Freeing Memory

To allocate a block of memory in the current process use `Memory.Allocate` method. It accepts the size of the block in bytes and returns the address of the allocated memory. Memory is guaranteed to be zero-initialized.

```js
var addr = Memory.Allocate(1024); // allocate 1KB of memory
```

To free previously allocated memory use `Memory.Free` method. It accepts the address of the memory block to free.

```js
Memory.Free(addr);
```
