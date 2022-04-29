# Пользовательские команды

> Примечание: Следующие команды предназначены только для классических игр. Для The Definitive Edition [проверьте эту информацию](the-definitive-edition-faq.md#can-i-use-cleo-opcodes).

CLEO Redux поддерживает все оригинальные опкоды, доступные в данной игре.  Помимо них, он добавляет несколько новых команд, перечисленных ниже.  Обратите внимание, что они строго соответствуют опкодам библиотеки CLEO.

- 0A8C [WRITE_MEMORY](https://library.sannybuilder.com/#/gta3/CLEO/0A8C) (**НЕБЕЗОПАСНО** - требует `mem` разрешение)
- 0A8D [READ_MEMORY](https://library.sannybuilder.com/#/gta3/CLEO/0A8D) (**НЕБЕЗОПАСНО** - требует `mem` разрешение)
- 0A8E [INT_ADD](https://library.sannybuilder.com/#/gta3/CLEO/0A8E)
- 0A8F [INT_SUB](https://library.sannybuilder.com/#/gta3/CLEO/0A8F)
- 0A90 [INT_MUL](https://library.sannybuilder.com/#/gta3/CLEO/0A90)
- 0A91 [INT_DIV](https://library.sannybuilder.com/#/gta3/CLEO/0A91)
- 0A93 [TERMINATE_THIS_CUSTOM_SCRIPT](https://library.sannybuilder.com/#/gta3/CLEO/0A93)
- 0AA5 [CALL_FUNCTION](https://library.sannybuilder.com/#/gta3/CLEO/0AA5) (**НЕБЕЗОПАСНО** - требует `mem` разрешение)
- 0AA6 [CALL_FUNCTION_RETURN](https://library.sannybuilder.com/#/gta3/CLEO/0AA6) (**НЕБЕЗОПАСНО** - требует `mem` разрешение)
- 0AA7 [CALL_METHOD](https://library.sannybuilder.com/#/gta3/CLEO/0AA7) (**НЕБЕЗОПАСНО** - требует `mem` разрешение)
- 0AA8 [CALL_METHOD_RETURN](https://library.sannybuilder.com/#/gta3/CLEO/0AA8) (**НЕБЕЗОПАСНО** - требует `mem` разрешение)
- 0AB0 [IS_KEY_PRESSED](https://library.sannybuilder.com/#/gta3/CLEO/0AB0)

Этот список может быть неполным, поскольку существуют специальные плагины с дополнительными командами (см. [Использование SDK](./using-sdk.md)).  Обратитесь к [библиотеке Sanny Builder](https://library.sannybuilder.com) для получения полного списка доступных команд для каждой игры.
