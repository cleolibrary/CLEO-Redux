# Plugins

Plugins are optional programs adding extra scripting commands with the help of [CLEO Redux SDK](./using-sdk.md). A plugin file has a `.cleo` extension and should be copied to the `CLEO\CLEO_PLUGINS` directory.

## List of plugins

| Name                                                                      | Description                                                  | Link                                                                          |
| ------------------------------------------------------------------------- | ------------------------------------------------------------ | ----------------------------------------------------------------------------- |
| [IniFiles](https://library.sannybuilder.com/#/unknown_x86/ini)            | Reading from and writing to INI files                        | [src](https://github.com/cleolibrary/CLEO-Redux/tree/master/plugins/IniFiles) |
| [Dylib](https://library.sannybuilder.com/#/unknown_x86/dylib)             | Loading DLL files and importing functions                    | [src](https://github.com/cleolibrary/CLEO-Redux/tree/master/plugins/Dylib)    |
| [Input](https://library.sannybuilder.com/#/unknown_x86/input)             | Checking for keyboard and mouse input, emulating key presses | [src](https://github.com/cleolibrary/CLEO-Redux/tree/master/plugins/Input)                                                                |
| [ImGuiRedux](https://library.sannybuilder.com/#/unknown_x86/imgui)        | Dear ImGui bindings                                          | [GitHub repo](https://github.com/user-grinch/ImGuiRedux)                      |
| [MemoryOperations](https://library.sannybuilder.com/#/unknown_x86/memops) | Low-level memory operations                                  | [GitHub repo](https://github.com/cleolibrary/CLEO-REDUX-PLUGINS)              |

Plugins are included in the CLEO Redux installer. You can opt out of some of them by unchecking the corresponding checkbox in the installer.