# Fluent Interface

<iframe width="560" height="315" src="https://www.youtube.com/embed/LLgJ0fWbklg" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

Methods on constructible entities (such as `Player`, `Car`, `Char` -- any entities created via a constructor method) support chaining (also known as Fluent Interface). It allows to write code like this:

```js
var p = new Player(0);

p.giveWeapon(2, 100)
  .setHealth(5)
  .setCurrentWeapon(2)
  .getChar()
  .setCoordinates(1144, -600, 14)
  .setBleeding(true);
```

Destructor methods interrupt the chain. E.g. given the code:

`Char.Create(0, 0, 0, 0, 0).setCoordinates(0, 0, 0).delete()`

the chain can not continue after delete method as the character gets removed and its handle is not longer valid.
