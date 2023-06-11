# Definitions

Due to the dynamic nature of JavaScript CLEO Redux needs to know an interface of each native command, i.e. a number of input arguments and returned values and their types. [Sanny Builder Library](https://library.sannybuilder.com) serves as the source of command definitions for CLEO Redux.

At start CLEO validates that a definition file is present and correct and if not tries to download it from GitHub (see the table below) into your local `CLEO/.config` directory. If that did not happen, or you don't want to let CLEO make network calls, manually download the required file and place it in the `CLEO/.config` directory.

| Game                                | File                                                                                                 | Minimum Required Version |
| ----------------------------------- | ---------------------------------------------------------------------------------------------------- | ------------------------ |
| GTA III, re3                        | [gta3.json](https://github.com/sannybuilder/library/blob/master/gta3/gta3.json)                      | `0.262`                  |
| GTA VC, reVC                        | [vc.json](https://github.com/sannybuilder/library/blob/master/vc/vc.json)                            | `0.268`                  |
| GTA San Andreas (Classic) 1.0       | [sa.json](https://github.com/sannybuilder/library/blob/master/sa/sa.json)                            | `0.313`                  |
| GTA III: The Definitive Edition     | [gta3_unreal.json](https://github.com/sannybuilder/library/blob/master/gta3_unreal/gta3_unreal.json) | `0.227`                  |
| Vice City: The Definitive Edition   | [vc_unreal.json](https://github.com/sannybuilder/library/blob/master/vc_unreal/vc_unreal.json)       | `0.233`                  |
| San Andreas: The Definitive Edition | [sa_unreal.json](https://github.com/sannybuilder/library/blob/master/sa_unreal/sa_unreal.json)       | `0.262`                  |
| GTA IV                              | [gta_iv.json](https://github.com/sannybuilder/library/blob/master/gta_iv/gta_iv.json)                | `0.78`                   |
| Unknown (32-bit)                    | [unknown_x86.json](https://github.com/sannybuilder/library/blob/master/unknown_x86/unknown_x86.json) | `0.223`                  |
| Unknown (64-bit)                    | [unknown_x64.json](https://github.com/sannybuilder/library/blob/master/unknown_x64/unknown_x64.json) | `0.226`                  |
| Bully: Scholarship Edition          | [bully.json](https://github.com/sannybuilder/library/blob/master/bully/bully.json)                   | `0.41`                   |

CLEO Redux uses compound definitions (a combination of the primary JSON file for the current game and a JSON file for the Unknown host). It lets SDK commands to work in JS scripts regardless of them being defined or not in the primary JSON file. You should notice that during updates CLEO downloads both `<game>.json` and `unknown.json` as well as the accompanying `enums.js` files. It should not affect any existing scripts.
