# Rust SDK

Rust SDK использует интерфейс, аналогичный интерфейсу C++, с некоторыми дополнительными методами переноса, позволяющими легко конвертировать типы C и Rust. Заголовочный файл доступен в виде [crate](https://crates.io/crates/cleo_redux_sdk) на crates.io.  См. документацию [здесь](https://docs.rs/cleo_redux_sdk/latest/).

## Пример

Рассмотрим плагин `Dylib`.  Он добавляет класс DynamicLibrary со следующими методами:

```ts
declare class DynamicLibrary {
    constructor(handle: number);
    static Load(libraryFileName: string): DynamicLibrary | undefined;
    free(): void;
    getProcedure(procName: string): int | undefined;
}
```

[Дополнительная информация](https://library.sannybuilder.com/#/sa_unreal/classes/DynamicLibrary) в библиотеке Sanny Builder.  Для использования класса `DynamicLibrary` требуется `dll` [разрешение](./permissions.md).
