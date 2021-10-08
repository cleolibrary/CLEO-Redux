## Using Memory class

Static class `Memory` provides methods for accessing and manipulating the data or code in the current process. It has the following interface:

```ts
class Memory {
    static ReadFloat(address: int, vp: boolean): float;
    static WriteFloat(address: int, value: float, vp: boolean): void;
    static ReadI8(address: int, vp: boolean): int;
    static ReadI16(address: int, vp: boolean): int;
    static ReadI32(address: int, vp: boolean): int;
    static ReadU8(address: int, vp: boolean): int;
    static ReadU16(address: int, vp: boolean): int;
    static ReadU32(address: int, vp: boolean): int;
    static WriteI8(address: int, value: int, vp: boolean): void;
    static WriteI16(address: int, value: int, vp: boolean): void;
    static WriteI32(address: int, value: int, vp: boolean): void;
    static WriteU8(address: int, value: int, vp: boolean): void;
    static WriteU16(address: int, value: int, vp: boolean): void;
    static WriteU32(address: int, value: int, vp: boolean): void;
    static Read(address: int, size: int, vp: boolean): int;
    static Write(address: int, size: int, value: int, vp: boolean): void;

    static ToFloat(value: int): float;
    static FromFloat(value: float): int;
    static ToU8(value: int): int;
    static ToU16(value: int): int;
    static ToU32(value: int): int;
    static ToI8(value: int): int;
    static ToI16(value: int): int;
    static ToI32(value: int): int;
}
```

### Reading and Writing Values

First group of methods (`ReadXXX`/`WriteXXX`) can be used for changing values stored in the memory. Each method is designed for a particular data type. To change a floating-point value (which occupies 4 bytes in the original game) use `Memory.WriteFloat`, e.g.:

```js
    Memory.WriteFloat(address, 1.0, false)
```

where `address` is a variable storing the memory location, `1.0` is the value to write and `false` means it's not necessary to change the memory protection with `VirtualProtect` (the address is already writable). 

Similarly, to read a value from the memory, use one of the `ReadXXX` methods, depending on what data type the memory address contains. For example, to read a  8-bit signed integer (also known as a `char` or `uint8`) use `Memory.ReadI8`, e.g.:

```js
    var x = Memory.ReadI8(address, true)
```

variable `x` now holds a 8-bit integer value in the range (0..255). For the sake of showing possible options, this example uses `true` as the last argument, which means the default protection attribute for this address will be changed to `PAGE_EXECUTE_READWRITE` before the read.

```js
    var gravity = Memory.ReadFloat(gravityAddress, false);
    gravity += 0.05;
    Memory.WriteFloat(gravityAddress, gravity, false);
```

Finally, last two methods `Read` and `Write` is what other methods use under the hood. They have direct binding to opcodes [0A8D READ_MEMORY](https://library.sannybuilder.com/#/gta3/CLEO/0A8D) and [0A8C WRITE_MEMORY](https://library.sannybuilder.com/#/gta3/CLEO/0A8C) and produce the same result. 

The `size` parameter in the `Read` method can only be `1`, `2` or `4`. CLEO treats the `value` as a signed integer stored in the little-endian format. 

In the `Write` method any `size` larger than `0` is allowed. Sizes `3` and `5` onwards can only be used together with a single byte `value`.  CLEO uses them to fill a continious block of memory starting at the `address` with the given `value` (think of it as `memset` in C++).

```js
    Memory.Write(addr, 0x90, 10, true) // "noping" 10 bytes of code starting from addr
```

**Note that usage of any of the read/write methods requires the `mem` [permission](README.md#Permissions)**.


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