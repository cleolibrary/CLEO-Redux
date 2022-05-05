# C++ SDK

На этой странице описаны основные шаги, необходимые для создания новой пользовательской команды с помощью C++ SDK, которая считывает два целочисленных аргумента и возвращает их сумму.

Это руководство было проверено для Visual Studio 2019 (Community Edition) и может отличаться для других IDE и компиляторов.

## Разработка плагина

- Создайте новый проект библиотеки динамической компоновки (DLL).  В `Настройки проекта->Дополнительно` установите для `Расширение целевого файла` значение `.cleo`.

- Загрузите [`cleo_redux_sdk.h`](https://raw.githubusercontent.com/cleolibrary/CLEO-Redux/master/plugins/SDK/cleo_redux_sdk.h) и добавьте его в свой проект.

```cpp
#include "cleo_redux_sdk.h
```

Если этот заголовочный файл находится за пределами каталога вашего проекта, вам необходимо добавить папку с этим файлом в «Настройки проекта->Каталоги VC++->Включить каталоги», чтобы позволить Visual Studio обнаружить этот файл.

- В `Настройки проекта->Линкер->Вход` добавьте полный путь к [`cleo_redux.lib`](https://github.com/cleolibrary/CLEO-Redux/raw/master/plugins/SDK/cleo_redux.lib) (если вы разрабатываете 32-битный плагин) или в [`cleo_redux64.lib`](https://github.com/cleolibrary/CLEO-Redux/blob/master/plugins/SDK/cleo_redux64.lib) для 64-битного плагина.

- в `dllmain.cpp` создайте новый статический класс с функцией-конструктором.  Этот конструктор будет вызван, как только CLEO загрузит ваш плагин

```cpp
class TestPlugin {
public:
	TestPlugin() {
		Log("My Test Plugin");
	}
} TestPlugin;
```

- в конструкторе класса плагина вызовите функцию `RegisterCommand` для каждой новой команды

```cpp
class TestPlugin {
public:
	TestPlugin() {
		Log("My Test Plugin");
        RegisterCommand("INT_ADD", IntAdd);
	}

    static HandlerResult IntAdd(Context ctx) {
        return HandlerResult::CONTINUE;
    }
} TestPlugin;
```

- реализуйте обработчики для новых команд.  Каждый обработчик команд получает один входной аргумент — `Context ctx`. Этот аргумент используется для вызова других методов SDK.

```cpp
class TestPlugin {
public:
	TestPlugin() {
		Log("My Test Plugin");
        RegisterCommand("INT_ADD", IntAdd);
	}

    static HandlerResult IntAdd(Context ctx) {
        auto arg1 = GetIntParam(ctx);
        auto arg2 = GetIntParam(ctx);
        SetIntParam(ctx, arg1 + arg2);

        return HandlerResult::CONTINUE;
    }
} TestPlugin;
```

- скомпилируйте проект и поместите файл `.cleo` в папку [`CLEO_PLUGINS`](./installation-plugins.md).

- добавить определение команды в файл JSON для целевой игры (например, `gta3.json` для GTA III или `unknown_x86.json` для хоста Unknown (x86)).  Каждый `GetXXXParam`/`SetXXXParam` должен быть связан с вводом или выводом в определении команды.

```json
{
    "input": [
        { "name": "arg1", "type": "int" },
        { "name": "arg2", "type": "int" }
    ],
    "output": [
        { "name": "result", "type": "int", "source": "var_any" }
    ],
    "id": "0DDD",
    "name": "INT_ADD",
    "num_params": 3,
    "short_desc": "Adds together two integer values and writes the result into the variable",
},
```

`id` необязателен для неизвестных хостов.  Для известных и поддерживаемых игр идентификатор должен быть уникальным кодом операции, который больше нигде не используется.

Лучший способ создать правильное определение команды — использовать [Sanny Builder Library](https://library.sannybuilder.com/). Если вы планируете поделиться подключаемым модулем и сделать его доступным через Интернет, подумайте о том, чтобы связаться с сопровождающими библиотеки, чтобы ваша команда была опубликована там.

- теперь вы можете использовать новую команду в коде с помощью команды [`native`](./js-bindings.md#native)

```js
var result = native("INT_ADD", 10, 20); // 30
``` 

## Пример

См. подключаемый модуль [`IniFiles`](https://library.sannybuilder.com/#/sa_unreal/classes/IniFile), который включает полный проект для Visual Studio 2019.
