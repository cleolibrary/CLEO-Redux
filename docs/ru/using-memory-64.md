Примечание. Это руководство предназначено для обновленных игр, работающих как 64-разрядные приложения. Для получения информации об использовании класса Memory в играх классической эпохи [нажмите здесь](./using-memory.md).

## Использование объекта памяти

Внутренний объект `Memory` предоставляет методы для доступа и управления данными или кодом в текущем процессе. Он имеет следующий интерфейс:

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

### Чтение и запись значений

Группа методов доступа к памяти (`ReadXXX`/`WriteXXX`) может использоваться для чтения или изменения значений, хранящихся в памяти. Каждый метод предназначен для определенного типа данных. Чтобы изменить значение с плавающей запятой (которое в исходной игре занимает 4 байта), используйте `Memory.WriteFloat`, например:

```js
    Memory.WriteFloat(address, 1.0, false, false)
```

Где `address` — это переменная, хранящая адрес памяти, `1.0` — это значение для записи, первое «false» означает, что нет необходимости изменять защиту памяти с помощью `VirtualProtect` (адрес уже доступен для записи). Второй `false` — это значение флага `ib`, который предписывает CLEO рассматривать `address` либо как абсолютный адрес (`ib` = `false`), либо как относительное смещение к текущему базовому адресу образа (`ib` = `true`). Поскольку в окончательных версиях используется функция ASLR, их абсолютные адреса памяти меняются при запуске игры из-за изменения начального адреса. Рассмотрим следующий пример:

```
0x1400000000 ImageBase
...
...
0x1400000020 SomeValue
```
Вы хотите изменить `SomeValue`, которое в настоящее время находится по адресу `0x1400000020`. Вы можете сделать это с помощью `Memory.Write(0x1400000020, 1, 1, false, false)`. Однако при следующем запуске игры расположение памяти может выглядеть так:

```
0x1500000000 ImageBase
...
...
0x1500000020 SomeValue
```

Эффективно ломая сценарий. В этом случае рассчитайте относительное смещение от базы изображения (`0x1500000020` - `0x1500000000` = `0x20`), которое будет постоянным для конкретной версии игры. Используйте Memory.Write следующим образом: `Memory.Write(0x20, 1, 1, false, true)`. CLEO суммирует смещение (`0x20`) с текущим значением базы изображения (`0x1400000000`, `0x1500000000` и т. д.) и записывает по правильному абсолютному адресу.

Для вашего удобства вы можете узнать текущее значение базы образа в `cleo_redux.log`, например:

```
09:27:35 [INFO] Image base address 0x7ff7d1f50000
```

Точно так же, чтобы прочитать значение из памяти, используйте один из методов `ReadXXX`, в зависимости от того, какой тип данных содержит адрес памяти. Например, чтобы прочитать 8-битное целое число со знаком (также известное как `char` или `uint8`), используйте `Memory.ReadI8`, например:

```js
    var x = Memory.ReadI8(offset, true, true)
```

Переменная `x` теперь содержит 8-битное целое число в диапазоне (0..255). Чтобы показать возможные варианты, в этом примере в качестве последнего аргумента используется `true`, что означает, что атрибут защиты по умолчанию для этого адреса будет изменен на `PAGE_EXECUTE_READWRITE` перед чтением.

```js
    var gravity = Memory.ReadFloat(gravityOffset, false, true);
    gravity += 0.05;
    Memory.WriteFloat(gravityOffset, gravity, false, true);
```

Наконец, последние два метода `Read` и `Write` — это то, что другие методы используют под капотом. Они имеют прямую привязку к коду Rust, который читает и записывает память. В коде JavaScript вы можете использовать входные аргументы размером до 53-битных чисел.

Параметр `size` в методе `Read` может быть только `1`, `2`, `4` или `8. CLEO обрабатывает `value` как целое число со знаком, хранящееся в формате с прямым порядком байтов. 

В методе `Write` допускается любой `size` больше `0`. Размеры «`3`, `5`, `6`, `7` и `9` и далее могут использоваться только вместе с одним байтом `value`. CLEO использует их для заполнения непрерывного блока памяти, начиная с `address`, заданным `value` (подумайте об этом как о `memset` в C++).

```js
    Memory.Write(offset, 0x90, 10, true, true) // "noping" 10 байт кода, начиная с базы смещения+изображения
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

В качестве альтернативы используйте соответствующие методы для чтения/записи значения в виде числа с плавающей запятой (`ReadFloat`/`WriteFloat`) или целого числа без знака (`ReadUCX`/`WriteUXXX`).

### Вызов внешних функций

Объект `Memory` позволяет вызвать чужую (собственную) функцию по ее адресу одним из следующих способов:

- `Memory.CallFunction`
- `Memory.CallFunctionReturn`
- `Memory.CallFunctionReturnFloat`

```js
    Memory.CallFunction(0xEFFB30, true, 1, 13)
```
Где `0xEFFB30` — это смещение функции относительно IMAGE BASE (представьте себе, что это случайный начальный адрес игровой памяти), `true` — это флаг `ib` (см. ниже), `1` – количество входных аргументов, и `13` — единственный аргумент, передаваемый в функцию.

Параметр `ib` в `Memory.CallFunction` имеет то же значение, что и в командах чтения/записи памяти. При значении `true` CLEO добавляет текущий известный адрес базы образа к значению, указанному в качестве первого аргумента, для вычисления абсолютного адреса памяти функции. Если установлено значение `false`, первый аргумент не изменяется.

Чтобы передать функции значения с плавающей запятой, преобразуйте значение в целое число, используя `Memory.FromFloat`:

```js
    Memory.CallFunction(0x1234567, true, 1, Memory.FromFloat(123.456));
```

Возвращаемое значение функции, вызванной с помощью `Memory.CallFunction`, игнорируется. Чтобы прочитать результат, используйте `Memory.CallFunctionReturn` с теми же параметрами. Используйте `Memory.CallFunctionReturnFloat` для вызова функции, которая возвращает значение с плавающей запятой.


CLEO Redux поддерживает вызов сторонних функций с параметрами до 16.

**Обратите внимание, что для использования любого из методов вызова требуется `mem` [разрешение](readme.md#разрешения)**.

#### Удобные методы с объектом Fn

`Memory.Fn` предоставляет удобные методы для вызова различных типов внешних функций.

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

Эти методы предназначены для охвата всех поддерживаемых типов возврата. Например, этот код:

```js
    Memory.CallFunction(0xEFFB30, true, 1, 13)
```

Также можно записать как:

```js
    Memory.Fn.X64(0xEFFB30, true)(13)
```

Обратите внимание на несколько ключевых отличий. Прежде всего, методы `Memory.Fn` не вызывают внешнюю функцию напрямую. Вместо этого они возвращают новую функцию JavaScript, которую можно сохранить в переменной и повторно использовать для многократного вызова связанной внешней функции с разными аргументами:

```js
    var f = Memory.Fn.X64(0xEFFB30, true);
    f(13) // вызывает функцию 0xEFFB30 с аргументом 13
    f(11) // вызывает метод 0xEFFB30 с аргументом 11
```

Второе отличие состоит в том, что здесь нет параметра `numParams`. Каждый метод `Fn` вычисляет это автоматически.

По умолчанию возвращаемый результат считается 64-битным целым числом со знаком. Если функция возвращает другой тип (например, логическое значение), используйте один из методов, соответствующих сигнатуре функции:

```js
    var flag = Memory.Fn.X64U8(0x1234567, true)()
```

Этот код вызывает функцию по адресу `0x1234567` + IMAGE_BASE без аргументов и сохраняет результат как 8-битное целое число без знака.

```js
    var float = Memory.Fn.X64Float(0x456789, true)()
```

Этот код вызывает функцию по адресу `0x456789` + IMAGE_BASE без аргументов и сохраняет результат как значение с плавающей запятой.
