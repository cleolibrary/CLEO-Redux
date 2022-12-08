# Custom Text (FXT)

CLEO Redux supports custom text content without the need to edit game files.

## Static FXT files

<iframe width="560" height="315" src="https://www.youtube.com/embed/ctsKy7WnY9o" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

CLEO Redux can load and serve static text content. Create a new file with the `.fxt` extension and put it in the `CLEO\CLEO_TEXT` [folder](./cleo-directory.md). The file name can be any valid name.

Each FXT file contains a list of the key-value entries in the following format:

```
<KEY1> <TEXT1>
<KEY2> <TEXT2>
...
<KEYN> <TEXTN>
```

There should be a single space character between a key and a value. The key's maximum length is 7 characters. Try using unique keys that are unlikely to clash with other entries. The text length is unlimited, however each game may impose its own limitations.

CLEO loads FXT files on startup and merges their content in a single dictionary. It also monitors the files and reloads them if any change is made.

You can also download an editor for FXT files from the [CLEO library website](https://cleo.li/download.html).

To display the custom content in game, use the `Text` class. The key defined in the FXT file is usually the first argument to the `Text` class methods, e.g.

```
Text.PrintHelp('KEY1') // displays <TEXT1>
```

You can find the commands available in each game in the Sanny Builder Library, e.g. [for San Andreas: DE](https://library.sannybuilder.com/#/sa_unreal/classes/Text).

> CLEO Redux only supports texts encoded in UTF-8. It means that any non-standard encoding (e.g. for Russian localization by 1C) most likely will not work.

## FxtStore

<iframe width="560" height="315" src="https://www.youtube.com/embed/FLyYyrGz1Xg" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

CLEO Redux provides an interface for manipulating custom text directly in JavaScript code. There is a static variable, named `FxtStore` with the following interface:

```ts
declare interface FxtStore {
  /**
   * Inserts new text content in the script's fxt storage overwriting the previous content and shadowing static fxt with the same key
   * @param key GXT key that can be used in text commands (7 characters max)
   * @param value text content
   * @param [isGlobal] if true, the text affects global FXT storage
   */
  insert(key: string, value: string, isGlobal?: boolean): void;
  /**
   * Removes the text content associated with the key in the local fxt storage
   * @param key GXT key
   * @param [isGlobal] if true, the text affects global FXT storage
   */
  delete(key: string, isGlobal?: boolean): void;
}
```

Using `FxtStore` you can create unique keys and values in the script and put it in local FXT storage. Each script owns a private storage and keys from one script will not conflict with other scripts. Also keys defined in the FxtStore shadow the same keys defined in static FXT files. Consider the example:

custom.fxt:

```
MY_KEY Text from FXT file
```

custom.js:

```js
Text.PrintHelp("MY_KEY"); // this displays "Text from FXT file"
FxtStore.insert("MY_KEY", "Text from script");
Text.PrintHelp("MY_KEY"); // this displays "Text from script"
FxtStore.delete("MY_KEY");
Text.PrintHelp("MY_KEY"); // this displays "Text from FXT file" again
```

> The private FXT storage is not supported in The Trilogy, Bully and GTA IV. Each script there modifies the global FXT storage. This behavior may change in the future.

`insert` and `delete` methods can be forced to change global FXT keys even when the current host supports a private storage. By setting the last argument `isGlobal` to `true` you can mutate (add or delete) keys in the global storage. It might be helpful to deal with those keys that the game uses after procesing all scripts in a given frame (e.g. in delayed messages or HUD elements text) when the script's private storage is not available.

Custom text can be constructed dynamically, e.g.:

```js
while (true) {
  wait(0);
  FxtStore.insert("TIME", "Timestamp: " + Date.now());
  Text.PrintHelp("TIME"); // this displays "Timestamp: " and the updated timestamp value
}
```
