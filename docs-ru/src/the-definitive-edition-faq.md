Здесь вы можете найти ответы на часто задаваемые вопросы о поддержке ремастера The Trilogy.

- [Какие версии поддерживаются?](#какие-версии-поддерживаются)
- [Как установить CLEO Redux в The Definitive Edition?](#как-установить-cleo-redux-в-the-definitive-edition)
- [Что делать, если я не могу найти каталог CLEO?](#что-делать-если-я-не-могу-найти-каталог-cleo)
- [Как удалить CLEO Redux?](#как-удалить-cleo-redux)
- [Есть ли отличия от поддержки классических игр?](#есть-ли-отличия-от-поддержки-классических-игр)
- [Могу ли я использовать оригинальные опкоды?](#могу-ли-я-использовать-оригинальные-опкоды)
- [Как узнать, какие команды можно использовать в JavaScript?](#как-узнать-какие-команды-можно-использовать-в-javascript)
- [Могу ли я использовать опкоды CLEO?](#могу-ли-я-использовать-опкоды-cleo)
- [Можно ли работать с памятью игры или вызывать функции игры?](#можно-ли-работать-с-памятью-игры-или-вызывать-функции-игры)
- [Как компилировать CLEO-скрипты с помощью Sanny Builder?](#как-компилировать-cleo-скрипты-с-помощью-sanny-builder)
- [Я не могу найти здесь ответ на свой вопрос, куда мне обратиться?](#я-не-могу-найти-здесь-ответ-на-свой-вопрос-куда-мне-обратиться)

### Какие версии поддерживаются?

- GTA III: The Definitive Edition **1.0.0.14718** 
- GTA Vice City: The Definitive Edition **1.0.0.14718** 
- San Andreas: The Definitive Edition **1.0.0.14296**, **1.0.0.14388**, **1.0.0.14718** 

### Как установить CLEO Redux в The Definitive Edition?

- Загрузите и установите [Ultimate ASI Loader x64](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases/download/x64-latest/version.zip) от [ThirteenAG](https://github.com/ThirteenAG) (поместите `version.dll` в каталог `Gameface\Binaries\Win64`).

- Скопируйте `cleo_redux64.asi` в тот же каталог.

- Запустите игру один раз, и вы должны создать новый каталог CLEO в том же каталоге. Если этого не произошло, проверьте ниже.

### Что делать, если я не могу найти каталог CLEO?

У многих людей запуск игры с установленным CLEO Redux приводит к немедленному вылету. Это происходит, если в текущем каталоге (`Win64`) нет прав на запись. Чтобы исправить эту проблему, CLEO использует альтернативный путь в `C:\Users\<Ваше_имя_пользователя>\AppData\Roaming\CLEO Redux`. Там можно найти `cleo_redux.log` и каталог `CLEO`. См. также [руководство по устранению неполадок](TROUBLESHOOTING.md).

### Как удалить CLEO Redux?

- Удалите `cleo_redux64.asi`.
- Удалите папку `CLEO` (необязательно).
- Удалите `cleo_redux.log` (необязательно)

### Есть ли отличия от поддержки классических игр?

Есть. CLEO не отображает версию в меню игры. Также CLEO может запускать только JS-скрипты в GTA III и GTA VC. В San Andreas поддерживаются как скрипты CS, так и JS.

### Могу ли я использовать оригинальные опкоды?

Да, ты можешь. Обратитесь к Sanny Builder Library: https://library.sannybuilder.com/#/sa_unreal. Обратите внимание, что некоторые коды операций были изменены по сравнению с классическими играми, поэтому не ожидайте, что все будет работать так же, как в классических играх. Если вы столкнулись с проблемой, найдите помощь в [нашем Discord](https://discord.gg/d5dZSfgBZr).

### Как узнать, какие команды можно использовать в JavaScript?

После каждого запуска игры CLEO создает файл d.ts в каталоге CLEO\.config. Он называется gta3.d.ts, vc.d.ts или sa.d.ts в зависимости от игры. В этом файле перечислены все поддерживаемые функции и методы, которые вы можете использовать в коде JavaScript.

Чтобы включить автозаполнение в VS Code, включите в свой JS-скрипт следующую строку:

```js
/// <reference path=".config/sa.d.ts" />
```

Обновите имя файла соответственно в зависимости от того, для какой игры предназначен ваш скрипт.

### Могу ли я использовать опкоды CLEO?

Опкоды из библиотеки CLEO (CLEO 4 или CLEO для GTA III и Vice City) не поддерживаются. Но CLEO Redux добавляет свои новые опкоды для некоторых операций.

  - 0C00 [IS_KEY_PRESSED](https://library.sannybuilder.com/#/sa_unreal/CLEO/0C00)
  - 0C01 [INT_ADD](https://library.sannybuilder.com/#/sa_unreal/CLEO/0C01)
  - 0C02 [INT_SUB](https://library.sannybuilder.com/#/sa_unreal/CLEO/0C02)
  - 0C03 [INT_MUL](https://library.sannybuilder.com/#/sa_unreal/CLEO/0C03)
  - 0C04 [INT_DIV](https://library.sannybuilder.com/#/sa_unreal/CLEO/0C04)
  - 0C05 [TERMINATE_THIS_CUSTOM_SCRIPT](https://library.sannybuilder.com/#/sa_unreal/CLEO/0C05)
  - 0C06 [WRITE_MEMORY](https://library.sannybuilder.com/#/sa_unreal/CLEO/0C06) (**UNSAFE** - требует `mem` разрешение)
  - 0C07 [READ_MEMORY](https://library.sannybuilder.com/#/sa_unreal/CLEO/0C07) (**UNSAFE** - требует `mem` разрешение)
  - 0C08 [CALL_FUNCTION](https://library.sannybuilder.com/#/sa_unreal/CLEO/0C08) (**UNSAFE** - требует `mem` разрешение)
  - 0C09 [CALL_FUNCTION_RETURN](https://library.sannybuilder.com/#/sa_unreal/CLEO/0C09) (**UNSAFE** - требует `mem` разрешение)

Обратите внимание, что Sanny Builder еще не поддерживает эти новые коды операций «из коробки». Чтобы включить новые коды операций в ваших сценариях CS, добавьте следующие строки поверх вашего сценария:

```
{$O 0C00=1,  is_key_pressed %1d% }
{$O 0C01=3,%3d% = %1d% + %2d% }
{$O 0C02=3,%3d% = %1d% - %2d% }
{$O 0C03=3,%3d% = %1d% * %2d% }
{$O 0C04=3,%3d% = %1d% / %2d% }
{$O 0C05=0,terminate_this_custom_script }
{$O 0C06=5,write_memory %1d% size %2d% value %3d% virtual_protect %4d% ib %5d% }
{$O 0C07=5,%5d% = read_memory %1d% size %2d% virtual_protect %3d% ib %4d% }
{$O 0C08=-1,call_function %1d% ib %2d% num_params %3d%}
{$O 0C09=-1,call_function_return %1d% ib %2d% num_params %3d%}
```

### Можно ли работать с памятью игры или вызывать функции игры?

Да, проверьте [Руководство по использованию памяти](using-memory-64.md).

### Как компилировать CLEO-скрипты с помощью Sanny Builder?

Используйте режим SA Mobile для компиляции CLEO-скриптов для San Andreas: The Definitive Edition. Обратите внимание, что CLEO Redux не поддерживает CS-скрипты в GTA III: DE и VC: DE. JS-скрипты поддерживаются во всех играх.

### Я не могу найти здесь ответ на свой вопрос, куда мне обратиться?

- Проверьте основной [файл readme](readme.md).
- Ознакомьтесь с [руководством по устранению неполадок](TROUBLESHOOTING.md).
- Проверьте [вопросы GitHub](https://github.com/cleolibrary/CLEO-Redux/issues).
- Проверьте [страницу поддержки функций](https://github.com/cleolibrary/CLEO-Redux/wiki/Feature-Support-Matrix).
- Задать вопрос в [нашем Discord](https://discord.gg/d5dZSfgBZr).
