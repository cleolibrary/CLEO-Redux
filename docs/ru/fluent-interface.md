# Цепочки методов

<iframe width="560" height="315" src="https://www.youtube.com/embed/LLgJ0fWbklg" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

Методы конструируемых сущностей (таких как `Player`, `Car`, `Char` – любые сущности, созданные с помощью метода конструктора) поддерживают цепочку (также известную как Fluent Interface). Это позволяет писать такой код:

```js
var p = new Player(0);

p.giveWeapon(2, 100)
  .setHealth(5)
  .setCurrentWeapon(2)
  .getChar()
  .setCoordinates(1144, -600, 14)
  .setBleeding(true);
```

Посмотреть демонстрацию: https://www.youtube.com/watch?v=LLgJ0fWbklg.

Методы деструктора прерывают цепочку. Например. учитывая код:

`Char.Create(0, 0, 0, 0, 0).setCoordinates(0, 0, 0).delete()`

Цепочка не может продолжаться после метода удаления, так как символ удаляется, а его дескриптор больше не действителен.
