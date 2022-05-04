# Встраивание на пользовательских хостах

> Над этой документацией ведется работа.

CLEO Redux может встраивать и запускать JS-скрипты на неизвестном (т.е. не [поддерживаемом официально](./introduction.md#supported-releases)) хосте.  *Хост* — это приложение, в котором загружается или внедряется процесс cleo_redux.asi или cleo_redux64.asi и в котором работает среда выполнения CLEO. Эта функция является экспериментальной и может быть изменена в любой момент.

[Демонстрация на YouTube](https://www.youtube.com/watch?v=rk2LvDt7UkI).

## Загрузка в пользовательский процесс

Существует несколько способов загрузки файла ASI в целевой процесс. [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases) — один из них. Или используйте любой [DLL-инжектор](https://github.com/search?q=dll+injector), доступный на GitHub. При необходимости хост может загрузить файл CLEO ASI как динамическую библиотеку.

## Запускаем среду выполнения CLEO

Чтобы запустить среду выполнения на неизвестном хосте сразу после загрузки, откройте [файл конфигурации](./config.md) и установите `EnableSelfHost` на `1|.  При загрузке в качестве собственного хоста CLEO Redux сканирует [директорию CLEO](./cleo-directory.md) на наличие плагинов и скриптов и запускает их.

### Ручное управление средой выполнения

Хост может запускать среду выполнения и продвигать ее основной цикл с помощью методов SDK `RuntimeInit` и |RuntimeNextTick`.

Вот как это можно реализовать на Rust:

```toml
[dependencies]
ctor = "0.1.21"
cleo_redux_sdk = "0.0.6"
```

```rust
use std::time;
use ctor::*;
use cleo_redux_sdk;

#[cfg_attr(target_arch = "x86", link(name = "cleo_redux"))]
#[cfg_attr(target_arch = "x86_64", link(name = "cleo_redux64"))]

#[ctor]
fn init() {
    use std::thread;

    // загружаем CLEO-скрипты, FXT, включаем файловый наблюдатель
    cleo_redux_sdk::runtime_init();

    // переменные времени инициализации
    const FPS: i32 = 30;
    let time_step = 1000 / FPS;
    let started = time::Instant::now();

    thread::spawn(move || loop {
        let current_time = started.elapsed().as_millis() as u32;

        // продвигаем основной цикл, предоставляя текущее время и временной шаг
        // текущее время используется для определения того, должен ли скрипт "просыпаться" после команды ожидания.
        // временной шаг используется для увеличения переменных TIMERA и TIMERB
        cleo_redux_sdk::runtime_next_tick(current_time, time_step);


        // пауза по крайней мере на временной шаг (в миллисекундах) 
        thread::sleep(time::Duration::from_millis(time_step as u64));
    });
}
```

## Доступные команды

В автономном режиме CLEO Redux поддерживает собственные [переменные](./js-bindings.md) и команды, созданные с помощью [SDK](./using-sdk.md). Он использует определения команд для неизвестного хоста из библиотеки Sanny Builder (доступно для [32-разрядных](https://library.sannybuilder.com/#/unknown_x86) и [64-разрядных](https://library.sannybuilder.com/#/unknown_x64)). CLEO Redux автоматически загружает необходимые файлы при [первом запуске](./prerequisites.md).

Вы можете использовать все стандартные функции JavaScript.  Список доступных команд можно увидеть в автоматически сгенерированном файле `.config/unknown.d.ts`.
