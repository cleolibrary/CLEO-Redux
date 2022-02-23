# ScriptObject vs Object


Sanny Builder Library defines a static class `Object` to group commands allowing to create and manipulate 3D objects in-game. At the same time JavaScript has the [native Object class](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Object) with its own methods.

To avoid mixing the two, CLEO Redux uses `ScriptObject` class instead of the Library's `Object` with [the same interface](https://library.sannybuilder.com/#/gta3/classes/Object).

```js
var x = ScriptObject.Create(modelId, x, y, z); // opcode 0107, creates a new object in the game

var x = Object.create(null); // native JavaScript code, creates a new object in JS memory
```
