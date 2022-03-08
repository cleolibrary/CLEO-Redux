# Troubleshooting

## CLEO does not work with re3 or reVC

{{#include ./re3-reVC-notes.md}}

## Краш игры с CLEO на San Andreas: The Definitive Edition

- Убедитесь, что вы установили 64-битную версию Ultimate ASI Loader ([прямая ссылка на последний релиз](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases/download/x64-latest/version.zip)).
  - Поместите `version.dll` в `GTA San Andreas - Definitive Edition\Gameface\Binaries\Win64`
- убедитесь, что у вас установлена последняя версия CLEO Redux (0.8.2 и выше)
- удалить файлы конфигурации из `Documents\Rockstar Games\GTA San Andreas Definitive Edition\Config\WindowsNoEditor`
- запустить игру (или Rockstar Games Launcher) от имени администратора

Если CLEO не может создавать файлы в `GTA San Andreas - Definitive Edition\Gameface\Binaries\Win64`, он будет использовать другой каталог в `C:\Users\<ваше_имя>\AppData\Roaming\CLEO Redux`. Там должен быть `cleo_redux.log` и папка CLEO, куда попадают все ваши скрипты.
