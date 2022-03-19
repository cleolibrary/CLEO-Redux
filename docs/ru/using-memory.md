Примечание. Это руководство предназначено для игр классической эпохи. Для получения информации об использовании класса Memory в Definitive Edition [нажмите здесь](./using-memory-64.md).

## Использование объекта памяти

Внутренний объект `Memory` предоставляет методы для доступа и управления данными или кодом в текущем процессе. Он имеет следующий интерфейс:

```ts
interface Memory {
    ReadFloat(address: int, vp: boolean): float;
    WriteFloat(address: int, value: float, vp: boolean): void;
    ReadI8(address: int, vp: boolean): int;
    ReadI16(address: int, vp: boolean): int;
    ReadI32(address: int, vp: boolean): int;
    ReadU8(address: int, vp: boolean): int;
    ReadU16(address: int, vp: boolean): int;
    ReadU32(address: int, vp: boolean): int;
    WriteI8(address: int, value: int, vp: boolean): void;
    WriteI16(address: int, value: int, vp: boolean): void;
    WriteI32(address: int, value: int, vp: boolean): void;
    WriteU8(address: int, value: int, vp: boolean): void;
    WriteU16(address: int, value: int, vp: boolean): void;
    WriteU32(address: int, value: int, vp: boolean): void;
    Read(address: int, size: int, vp: boolean): int;
    Write(address: int, size: int, value: int, vp: boolean): void;

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
    CallMethod(address: int, struct: int, numParams: int, pop: int, ...funcParams: int[]): void;
    CallMethodReturn(address: int, struct: int, numParams: int, pop: int, ...funcParams: int[]): int;
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
}
```

### Чтение и запись значений

Группа методов доступа к памяти (`ReadXXX`/`WriteXXX`) может использоваться для чтения или изменения значений, хранящихся в памяти. Каждый метод предназначен для определенного типа данных. Чтобы изменить значение с плавающей запятой (которое в исходной игре занимает 4 байта), используйте `Memory.WriteFloat`, например:

```js
    Memory.WriteFloat(address, 1.0, false)
```

Где `address` — это переменная, хранящая адрес памяти, `1.0` — это значение для записи, а `false` означает, что нет необходимости изменять защиту памяти с помощью  `VirtualProtect` (адрес уже доступен для записи). 

Точно так же, чтобы прочитать значение из памяти, используйте один из методов `ReadXXX`, в зависимости от того, какой тип данных содержит адрес памяти. Например, чтобы прочитать 8-битное целое число со знаком (также известное как `char` или `uint8`), используйте `Memory.ReadI8`, например:

```js
    var x = Memory.ReadI8(address, true)
```

переменная `x` теперь содержит 8-битное целое значение в диапазоне (0..255). Чтобы показать возможные варианты, в этом примере в качестве последнего аргумента используется `true`, что означает, что атрибут защиты по умолчанию для этого адреса будет изменен на `PAGE_EXECUTE_READWRITE` перед чтением.

```js
    var gravity = Memory.ReadFloat(gravityAddress, false);
    gravity += 0.05;
    Memory.WriteFloat(gravityAddress, gravity, false);
```

Наконец, последние два метода `Read` и `Write` — это то, что другие методы используют под капотом. Они имеют прямую привязку к опкодам [0A8D READ_MEMORY](https://library.sannybuilder.com/#/gta3/CLEO/0A8D) и [0A8C WRITE_MEMORY](https://library.sannybuilder.com/#/gta3/CLEO/0A8C) и дают тот же результат. 

Параметр `size` в методе `Read` может быть только `1`, `2` или `4`. CLEO обрабатывает `value` как целое число со знаком, хранящееся в формате с прямым порядком байтов.

В методе `Write` допускается любой `size` больше `0`. Размеры `3` и `5` и далее могут использоваться только вместе с одним байтом `value`. CLEO использует их для заполнения непрерывного блока памяти, начиная с `address`, с заданным `value` (подумайте об этом как о `memset` в C++).

```js
    Memory.Write(addr, 0x90, 10, true) // "noping" 10 байт кода, начиная с адреса
```

**Обратите внимание, что для использования любого из методов чтения/записи требуется `mem` [разрешение](readme.md#разрешения)**.


### Метод приведения типов

По умолчанию методы `Read` и `Write` обрабатывают данные как целочисленные значения со знаком. Это может быть неудобно, если память содержит значение с плавающей запятой в формате IEEE 754 или большое 32-битное целое число со знаком (например, указатель). В этом случае используйте методы приведения `ToXXX`/`FromXXX`. Они действуют аналогично оператору [reinterpret_cast](https://docs.microsoft.com/en-us/cpp/cpp/reinterpret-cast-operator?view=msvc-160) в C++.

Чтобы получить представление о том, чего ожидать от этих методов, см. следующие примеры:

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

В качестве альтернативы используйте соответствующие методы для чтения/записи значения в виде числа с плавающей запятой (`ReadFloat`/`WriteFloat`) или целого числа без знака (`ReadUXXX`/`WriteUXXX`).


### Вызов внешних функций

Объект `Memory` позволяет вызвать чужую (собственную) функцию по ее адресу одним из следующих способов:

- `Memory.CallFunction` - привязывается к [0AA5 CALL_FUNCTION](https://library.sannybuilder.com/#/gta3/CLEO/0AA5)
- `Memory.CallFunctionReturn` - привязывается к [0AA7 CALL_FUNCTION_RETURN](https://library.sannybuilder.com/#/gta3/CLEO/0AA7)
- `Memory.CallMethod` - привязывается к [CALL_METHOD](https://library.sannybuilder.com/#/gta3/CLEO/0AA6)
- `Memory.CallMethodReturn` - привязывается к [CALL_METHOD_RETURN](https://library.sannybuilder.com/#/gta3/CLEO/0AA8)


```js
    Memory.CallFunction(0x1234567, 2, 0, 1000, 2000)
```
Где `0x1234567` — адрес функции, `2` — количество аргументов, `0` — параметр `pop` (см. ниже), `1000` и `2000` — два аргумента, переданных в функцию.

Обратите внимание, что устаревшая реализация команд вызова SCM требует, чтобы аргументы вызываемой функции были перечислены в обратном порядке. Вот и все, вы увидите тот же вызов в SCM, что и:

```
0AA5: call 0x1234567 num_params 2 pop 0 2000 1000
```
Где `2000` — второй аргумент, передаваемый функции, расположенной по адресу 0x1234567, а `1000` — первый.


Третий параметр (`pop`) в `Memory.CallFunction` определяет соглашение о вызовах. Если установлено значение `0`, функция вызывается с использованием соглашения [stdcall](https://en.wikipedia.org/wiki/X86_calling_conventions#stdcall). Когда для него установлено то же значение, что и для `numParam`, функция вызывается с использованием соглашения [cdecl](https://en.wikipedia.org/wiki/X86_calling_conventions#cdecl). Любое другое значение нарушает код.

`Memory.CallFunctionReturn` имеет тот же интерфейс, но дополнительно записывает результат функции в переменную.

`Memory.CallMethod` вызывает метод объекта:

```js
    Memory.CallMethod(0x2345678, 0x7001234, 2, 0, 1000, 2000)
```

Второй параметр (`0x7001234`) — это адрес объекта. Параметр `pop` всегда равен `0` (метод использует соглашение [thiscall](https://en.wikipedia.org/wiki/X86_calling_conventions#thiscall)).

Чтобы вызвать метод и получить от него результат, используйте `Memory.CallMethodReturn`.

Обратите внимание, что все аргументы читаются как 32-битные целые числа со знаком. Если вам нужно предоставить аргумент типа float, используйте `Memory.FromFloat`, например:

```js
    Memory.CallFunction(0x1234567, 1, 1, Memory.FromFloat(123.456))
```

CLEO Redux поддерживает вызов сторонних функций с параметрами до 16.

**Обратите внимание, что для использования любого из методов вызова требуется `mem` [разрешение](readme.md#разрешения)**.

#### Удобные методы с объектом Fn

`Memory.Fn` предоставляет множество удобных методов для вызова различных типов внешних функций.

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

Эти методы предназначены для охвата всех возможных сигнатур функций. Например, этот код:

```js
    Memory.CallMethod(0x2345678, 0x7001234, 2, 0, 1000, 2000)
```

Также можно записать как:

```js
    Memory.Fn.Thiscall(0x2345678, 0x7001234)(1000, 2000)
```

Обратите внимание на несколько ключевых отличий. Прежде всего, методы `Memory.Fn` не вызывают внешнюю функцию напрямую. Вместо этого они возвращают новую функцию JavaScript, которую можно сохранить в переменной и повторно использовать для многократного вызова связанной внешней функции с разными аргументами:

```js
    var myMethod = Memory.Fn.Thiscall(0x2345678, 0x7001234);
    myMethod(1000, 2000); // вызывает метод 0x2345678 с аргументами 1000 и 2000
    myMethod(3000, 5000); // вызывает метод 0x2345678 с аргументами 3000 и 5000
```

Второе отличие состоит в том, что отсутствуют параметры `numParams` и `pop`. Каждый метод `Fn` вычисляет их автоматически.

По умолчанию возвращаемый результат считается 32-битным целым числом со знаком. Если функция возвращает другой тип (значение с плавающей запятой или целое число со знаком), используйте один из методов, соответствующих сигнатуре функции, например:

```js
    var flag = Memory.Fn.CdeclU8(0x1234567)()
```

Этот код вызывает функцию `cdecl` по адресу `0x1234567` без аргументов и сохраняет результат в виде 8-битного целого числа без знака. 


### Поиск адресов памяти в re3 и reVC

Поскольку `re3` и `reVC` используют функцию рандомизации адресного пространства (ASLR), может быть трудно найти нужные адреса. CLEO Redux предоставляет вспомогательную функцию `Memory.Translate` которая принимает имя функции или переменной и возвращает ее текущий адрес. Если запрошенный символ не найден, результат равен 0.

```js
    var addr = Memory.Translate("CTheScripts::MainScriptSize");

    // проверить, не равен ли адрес нулю
    if (addr) {
        showTextBox("MainScriptSize = " + Memory.ReadI32(addr, 0))
    }
```

На данный момент `Memory.Translate` следует использовать только в `re3` и `reVC`. В других играх в большинстве случаев вы будете получать `0`.