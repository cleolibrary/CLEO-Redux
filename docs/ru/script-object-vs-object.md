# Сравнение ScriptObject и Object

Библиотека Sanny Builder определяет статический класс `Object` для группировки команд, позволяющих создавать и управлять трехмерными объектами в игре. В то же время в JavaScript есть [собственный класс Object](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Object) со своими методами.

Чтобы не смешивать их, CLEO Redux использует класс `ScriptObject` вместо класса `Object` из библиотеки с [тем же интерфейсом](https://library.sannybuilder.com/#/gta3/classes/Object).

```js
// код операции 0107, создает новый объект в игре
var x = ScriptObject.Create(modelId, x, y, z); 

// собственный код JavaScript, создает новый объект в памяти JS
var x = Object.create(null); 
```