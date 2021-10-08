## Using Math Object

JavaScript has a built-in `Math` object that provides common mathematical operations, such as `abs`, `sin`, `cos`, `random`, `pow`, `sqr`, etc. CLEO Redux extends this object to include extra operations supported by the game. The interface of `Math` looks as follows:

```ts
declare class Math {
    // native code
    static readonly E: number;
    static readonly LN10: number;
    static readonly LN2: number;
    static readonly LOG2E: number;
    static readonly LOG10E: number;
    static readonly PI: number;
    static readonly SQRT1_2: number;
    static readonly SQRT2: number;
    static abs(x: number): number;
    static acos(x: number): number;
    static asin(x: number): number;
    static atan(x: number): number;
    static atan2(y: number, x: number): number;
    static ceil(x: number): number;
    static cos(x: number): number;
    static exp(x: number): number;
    static floor(x: number): number;
    static log(x: number): number;
    static max(...values: number[]): number;
    static min(...values: number[]): number;
    static pow(x: number, y: number): number;
    static random(): number;
    static round(x: number): number;
    static sin(x: number): number;
    static sqrt(x: number): number;
    static tan(x: number): number;

    // GTA III and GTA Vice City commands
    static ConvertMetresToFeet(metres: int): int;
    static RandomFloatInRange(min: float, max: float): float;
    static RandomIntInRange(min: int, max: int): int;
    // GTA Vice City-only commands
    static GetDistanceBetweenCoords2D(fromX: float, fromY: float, toX: float, toZ: float): float;
    static GetDistanceBetweenCoords3D(fromX: float, fromY: float, fromZ: float, toX: float, toY: float, toZ: float): float;
}
```

The first group includes the native constants and methods provided by the JavaScript runtime. They start with a lowercase letter, e.g. `Math.abs`. You can find the detailed documentation for these methods [here](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math).

The second group includes the game-specific methods (in this case those of GTA III). Following the naming convention, each method that is bound to a script opcode starts with a capital letter, e.g. `Math.RandomIntInRange` (opcode 0209). You can find the documentation in [Sanny Builder Library](https://library.sannybuilder.com/).


```js
    var x = Math.abs(-1); // x = 1
    var f = Math.ConvertMetresToFeet(10) // f = 32
    var pi = Math.floor(Math.PI) // pi = 3
```
