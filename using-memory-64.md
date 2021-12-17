Note: This guide is for the remastered games running as 64-bit applications. For the information on using the Memory class in classic era games [click here](./using-memory.md).

## Using Memory Object

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
    WriteI8(address: int, value: int, vp: boolean, ib: boolean): void;
    WriteI16(address: int, value: int, vp: boolean, ib: boolean): void;
    WriteI32(address: int, value: int, vp: boolean, ib: boolean): void;
    WriteU8(address: int, value: int, vp: boolean, ib: boolean): void;
    WriteU16(address: int, value: int, vp: boolean, ib: boolean): void;
    WriteU32(address: int, value: int, vp: boolean, ib: boolean): void;
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

    Translate(symbol: string): int;
}
```

### Reading and Writing Values

Group of memory access methods (`ReadXXX`/`WriteXXX`) can be used for reading or modifying values stored in the memory. Each method is designed for a particular data type. To change a floating-point value (which occupies 4 bytes in the original game) use `Memory.WriteFloat`, e.g.:

```js
    Memory.WriteFloat(address, 1.0, false, false)
```

where `address` is a variable storing the memory location, `1.0` is the value to write, the first `false` means it's not necessary to change the memory protection with `VirtualProtect` (the address is already writable). The second `false` is the value of the `ib` flag that instructs CLEO to treat the `address` either as an absolute address (`ib` = `false`) or a relative offset to the current image base address (`ib` = `true`). As the definitive editions use the ASLR feature their absolute memory addresses change when the game runs because the start address changes. Consider the following example:

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

effectively breaking the script. In this case, calculate a relative offset from the image base ( `0x1500000020` - `0x1500000000` = `0x20` ), that will be permanent for the particular game version. Use Memory.Write as follows: `Memory.Write(0x20, 1, 1, false, true)`. CLEO will sum up the offset (`0x20`) with the current value of the image base (`0x1400000000`, `0x1500000000`, etc) and write to the correct absolute address.

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

The `size` parameter in the `Read` method can only be `1`, `2` or `4`. CLEO treats the `value` as a signed integer stored in the little-endian format. 

In the `Write` method any `size` larger than `0` is allowed. Sizes `3` and `5` onwards can only be used together with a single byte `value`.  CLEO uses them to fill a continious block of memory starting at the `address` with the given `value` (think of it as `memset` in C++).

```js
    Memory.Write(offset, 0x90, 10, true, true) // "noping" 10 bytes of code starting from offset+image base
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
