# Prerequisites

When JavaScript is enabled CLEO Redux needs commands definitions from [Sanny Builder Library](https://library.sannybuilder.com). They bring in the type information and convenient classes wrapping all available scripting commands.

On the first run CLEO tries to download a definition file (see the table below) and put it into your local `CLEO/.config` directory. If that did not happen, or you don't want to let CLEO make network calls, manually download the required file and place it in the `CLEO/.config` directory.

| Game                                | File                                                                                                 | Minimum Required Version |
| ----------------------------------- | ---------------------------------------------------------------------------------------------------- | ------------------------ |
| GTA III, re3                        | [gta3.json](https://github.com/sannybuilder/library/blob/master/gta3/gta3.json)                      | `0.218`                  |
| GTA VC, reVC                        | [vc.json](https://github.com/sannybuilder/library/blob/master/vc/vc.json)                            | `0.220`                  |
| GTA San Andreas (Classic) 1.0       | [sa.json](https://github.com/sannybuilder/library/blob/master/sa/sa.json)                            | `0.245`                  |
| GTA IV                              | [gta_iv.json](https://github.com/sannybuilder/library/blob/master/gta_iv/gta_iv.json)                | `0.34`                   |
| GTA III: The Definitive Edition     | [gta3_unreal.json](https://github.com/sannybuilder/library/blob/master/gta3_unreal/gta3_unreal.json) | `0.213`                  |
| Vice City: The Definitive Edition   | [vc_unreal.json](https://github.com/sannybuilder/library/blob/master/vc_unreal/vc_unreal.json)       | `0.215`                  |
| San Andreas: The Definitive Edition | [sa_unreal.json](https://github.com/sannybuilder/library/blob/master/sa_unreal/sa_unreal.json)       | `0.220`                  |
| Unknown (32-bit)                    | [unknown_x86.json](https://github.com/sannybuilder/library/blob/master/unknown_x86/unknown_x86.json) | `0.203`                  |
| Unknown (64-bit)                    | [unknown_x64.json](https://github.com/sannybuilder/library/blob/master/unknown_x64/unknown_x64.json) | `0.207`                  |