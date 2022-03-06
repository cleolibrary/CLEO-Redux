# Prerequisites

When JavaScript is enabled CLEO Redux needs commands definitions from [Sanny Builder Library](https://library.sannybuilder.com). They bring in the type information and convenient classes wrapping all available scripting commands.

On the first run CLEO tries to download a definition file (see the table below) and put it into your local `CLEO/.config` directory. If that did not happen, or you don't want to let CLEO make network calls, manually download the required file and place it in the `CLEO/.config` directory.

| Game                                | File                                                                                                 | Minimum Required Version |
| ----------------------------------- | ---------------------------------------------------------------------------------------------------- | ------------------------ |
| GTA III, re3                        | [gta3.json](https://github.com/sannybuilder/library/blob/master/gta3/gta3.json)                      | `0.208`                  |
| GTA VC, reVC                        | [vc.json](https://github.com/sannybuilder/library/blob/master/vc/vc.json)                            | `0.210`                  |
| GTA San Andreas (Classic) 1.0       | [sa.json](https://github.com/sannybuilder/library/blob/master/sa/sa.json)                            | `0.210`                  |
| GTA III: The Definitive Edition     | [gta3_unreal.json](https://github.com/sannybuilder/library/blob/master/gta3_unreal/gta3_unreal.json) | `0.210`                  |
| Vice City: The Definitive Edition   | [vc_unreal.json](https://github.com/sannybuilder/library/blob/master/vc_unreal/vc_unreal.json)       | `0.212`                  |
| San Andreas: The Definitive Edition | [sa_unreal.json](https://github.com/sannybuilder/library/blob/master/sa_unreal/sa_unreal.json)       | `0.216`                  |
