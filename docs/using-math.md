# Using Math Object

JavaScript has a built-in `Math` object that provides common mathematical operations, such as `abs`, `sin`, `cos`, `random`, `pow`, `sqr`, etc. CLEO Redux extends this object to include extra operations supported by the game. The interface of `Math` looks as follows:

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
    clz32(x: number): number;
    imul(x: number, y: number): number;
    sign(x: number): number;
    log10(x: number): number;
    log2(x: number): number;
    log1p(x: number): number;
    expm1(x: number): number;
    cosh(x: number): number;
    sinh(x: number): number;
    tanh(x: number): number;
    acosh(x: number): number;
    asinh(x: number): number;
    atanh(x: number): number;
    hypot(...values: number[]): number;
    trunc(x: number): number;
    fround(x: number): number;
    cbrt(x: number): number;

    // GTA III, GTA Vice City, GTA SA commands
    ConvertMetersToFeet(meters: int): int;
    RandomFloatInRange(min: float, max: float): float;
    RandomIntInRange(min: int, max: int): int;

    // GTA Vice City, GTA SA commands
    GetDistanceBetweenCoords2D(fromX: float, fromY: float, toX: float, toZ: float): float;
    GetDistanceBetweenCoords3D(fromX: float, fromY: float, fromZ: float, toX: float, toY: float, toZ: float): float;

    // GTA SA commands
    GetAngleBetween2DVectors(xVector1: float, yVector1: float, xVector2: float, yVector2: float): float;
    GetHeadingFromVector2D(_p1: float, _p2: float): float;
    LimitAngle(value: float): float;
}
```

The first group includes the native constants and methods provided by the JavaScript runtime. They start with a lowercase letter, e.g. `Math.abs`. You can find the detailed documentation for these methods [here](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math).

Then the game-specific commands go. Following the naming convention, each method that is bound to a script opcode starts with a capital letter, e.g. `Math.RandomIntInRange` (opcode 0209). You can find the documentation in [Sanny Builder Library](https://library.sannybuilder.com/).


```js
    var x = Math.abs(-1); // x = 1
    var f = Math.ConvertMetersToFeet(10) // f = 32
    var pi = Math.floor(Math.PI) // pi = 3
```
