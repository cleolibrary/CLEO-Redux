# Enums

Many commands make use of enumerated types or _enums_ for parameters with a finite range of allowed values. Each value in the range is associated with a text identifier so you don't have to memorize numbers for parameters such as weapon ids, ped types, key codes, etc. 

> Enum values can be either numbers or strings.

Enum names start with a capital letter similar to class names, e.g. `PedType`, `KeyCode`, `Button`. 

[Sanny Builder Library](https://library.sannybuilder.com/) lists all known enums for each game. It also provides a `enums.js` file with all enums exported as JavaScript objects for use in scripts. CLEO Redux automatically downloads this file along with the primary definitions file and places it in the `.config` directory.

To use an enum in a script [import](./imports.md) it like this:

```js
import { EnumName } from ".config/enums"; // replace EnumName with the actual name
```

You can also import all enums at once using the following syntax:

```js
import * as enums from ".config/enums";
```

Then you can access values in the enum as regular properties in a JavaScript object:

```js
import { KeyCode } from ".config/enums";

if (Pad.IsKeyPressed(KeyCode.A)) {
  log("A is pressed");
}
```

or

```js
import * as enums from ".config/enums";

if (Pad.IsKeyPressed(enums.KeyCode.A)) {
  log("A is pressed");
}
```

You can iterate over enum fields by using `Object.values`, `Object.keys`, or `Object.entries` functions:

```js
Object.keys(KeyCode).forEach((key) => {
  log(key);
});

Object.values(KeyCode).forEach((value) => {
  log(value);
});

Object.keys(KeyCode).forEach(([key, value]) => {
  log(key, value);
});
```


If you find an issue with an enum, a missing or incorrect value, report it in Sanny Builder Library [repo on GitHub](https://github.com/sannybuilder/library).
