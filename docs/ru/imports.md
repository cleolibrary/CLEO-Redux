# Импорт

Вы можете импортировать другие файлы сценариев в свой код, чтобы сделать код модульным и использовать общую логику. Среда выполнения поддерживает оператор импорта, как описано в [этой статье](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Statements/import).

Чтобы избежать запуска включенных файлов `.js` как отдельных скриптов, либо поместите их в отдельную папку (например, `CLEO/includes/`), либо используйте расширение `.mjs`.

```js
// импортирует экспорт по умолчанию из other.js или other.mjs, расположенных в том же каталоге
import func from "./other"; 

// импортирует именованный экспорт PedType из types.js или types.mjs, расположенных в каталоге CLEO/includes
import { PedType } from "./includes/types"; 

// импортирует cars.json как значение JavaScript (массив, объект).
import data from "./vehicles.json";
```

В настоящее время поддерживается только импорт файлов `.js` (`.mjs`) и `.json`.
