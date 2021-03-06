## Неподдерживаемые или ограниченные сценарии поддержки

Несмотря на все наши усилия, некоторые сценарии, доступные в игре, не поддерживаются или поддерживаются с ограничениями CLEO Redux. Некоторые из них обусловлены природой формата SCM или языка JavaScript или трудностями соединения JavaScript и нативного кода.

Посетите [страницу поддержки функций](https://github.com/cleolibrary/CLEO-Redux/wiki/Feature-Support-Matrix) чтобы узнать высокоуровневые фичи и статус их поддержки в разных играх.

Известно, что следующие элементы не работают, и нет конкретных сроков их исправления.

### Неподдерживаемые функции в CS

- В играх x64 (SA:DE) вы не можете читать и записывать 64-битные значения, так как скриптовый движок поддерживает только 32-битные значения. Возможно, вам придется использовать другие средства для доступа к памяти игры (например, из JavaScript).

### Неподдерживаемые функции в JS

- Команды, требующие переменной scm (например, таймеры обратного отсчета). [Проблема с отслеживанием](https://github.com/cleolibrary/CLEO-Redux/issues/10).

- Команды, неявно загружающие модели или текстуры (например, виджеты) [Проблема с отслеживанием](https://github.com/cleolibrary/CLEO-Redux/issues/12). Вы можете обойти проблему, предварительно загрузив необходимые ресурсы, например. сначала вызывая их в сценарии `.CS`.

- нельзя вызывать игровые функции, которым нужны ссылки на переменные для сохранения результата. Нет синтаксиса "take an address of the variable".
