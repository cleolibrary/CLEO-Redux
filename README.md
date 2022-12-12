# <img src="cleo_redux.png" width="32" height="32"> CLEO Redux


[![Discord](https://img.shields.io/discord/911487285990674473?style=for-the-badge)](https://discord.gg/d5dZSfgBZr)
[![YouTube Channel](https://img.shields.io/badge/YouTube-Channel-FF0000?style=for-the-badge)](https://www.youtube.com/playlist?list=PLNxQuEFtVkeizoLEQiok7qzr1f0mcwfFb)

CLEO Redux is an experimental runtime for GTA 3D era games and, with limited functionality, [other games or applications](https://re.cleo.li/docs/en/embedding.html). It supports [JavaScript](https://re.cleo.li/docs/en/javascript.html) and [TypeScript](https://re.cleo.li/docs/en/typescript.html) languages.

Its flexible, extensible and secure environment provides rich scripting capabilities and allows easily add and remove countless mini-scripts.

A complete simple script looks like this:

```js
const VK_F4 = 115;
while (true) {
  wait(250);

  if (Pad.IsKeyPressed(VK_F4)) {
    Game.ActivateSaveMenu();
    wait(1000);
  }
}
```

To run this script, save it as a `.js` file in the `{game}/CLEO` directory and start the game.

[See more examples](https://github.com/cleolibrary/CLEO-Redux/tree/master/examples)

## Documentation

https://re.cleo.li/docs

## Installation

https://re.cleo.li/docs/en/installation.html

## Contribution

There are multiple ways to contribute to the project. We welcome any help with improving our documentation, writing new example scripts, developing plugins using [CLEO SDK](https://re.cleo.li/docs/en/using-sdk.html), sharing your ideas, or testing early builds available on our Discord.

## License

CLEO Redux is available under the [end-user license agreement](./LICENSE.txt)
