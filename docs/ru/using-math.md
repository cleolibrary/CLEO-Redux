## Использование математических объектов

В JavaScript есть встроенный объект `Math`, который обеспечивает общие математические операции, такие как `abs`, `sin`, `cos`, `random`, `pow`, `sqr` и т. д. CLEO Redux расширяет этот объект до включать дополнительные операции, поддерживаемые игрой. Интерфейс `Math` выглядит следующим образом:

```ts
interface Math {
    // native code
    readonly E: number;
    readonly LN10: number;
    readonly LN2: number;
    readonly LOG2E: number;
    readonly LOG10E: number;
    readonly PI: number;
    readonly SQRT1_2: number;
    readonly SQRT2: number;
    abs(x: number): number;
    acos(x: number): number;
    asin(x: number): number;
    atan(x: number): number;
    atan2(y: number, x: number): number;
    ceil(x: number): number;
    cos(x: number): number;
    exp(x: number): number;
    floor(x: number): number;
    log(x: number): number;
    max(...values: number[]): number;
    min(...values: number[]): number;
    pow(x: number, y: number): number;
    random(): number;
    round(x: number): number;
    sin(x: number): number;
    sqrt(x: number): number;
    tan(x: number): number;

    // GTA III, GTA Vice City, GTA SA команды
    ConvertMetersToFeet(meters: int): int;
    RandomFloatInRange(min: float, max: float): float;
    RandomIntInRange(min: int, max: int): int;

    // GTA Vice City, GTA SA команды
    GetDistanceBetweenCoords2D(fromX: float, fromY: float, toX: float, toZ: float): float;
    GetDistanceBetweenCoords3D(fromX: float, fromY: float, fromZ: float, toX: float, toY: float, toZ: float): float;

    // GTA SA команды
    GetAngleBetween2DVectors(xVector1: float, yVector1: float, xVector2: float, yVector2: float): float;
    GetHeadingFromVector2D(_p1: float, _p2: float): float;
    LimitAngle(value: float): float;
}
```

Первая группа включает собственные константы и методы, предоставляемые средой выполнения JavaScript. Они начинаются со строчной буквы, например. `Math.abs`. Вы можете найти подробную документацию по этим методам [здесь](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math).

Затем идут специфичные для игры команды. Согласно соглашению об именах, каждый метод, привязанный к коду операции скрипта, начинается с заглавной буквы, например `Math.RandomIntInRange` (код операции 0209). Вы можете найти документацию в [Sanny Builder Library](https://library.sannybuilder.com/).


```js
    var x = Math.abs(-1); // x = 1
    var f = Math.ConvertMetersToFeet(10) // f = 32
    var pi = Math.floor(Math.PI) // pi = 3
```
