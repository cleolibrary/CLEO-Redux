## Using FXT

### Static FXT files

Demo: https://youtu.be/ctsKy7WnY9o

CLEO Redux can load and serve static text content. Create a new file with the `.fxt` extension and put it in the `CLEO\CLEO_TEXT` folder. The file name can be any valid name. 

Each FXT file contains a list of the key-value entries in the following format:

```
<KEY1> <TEXT1>
<KEY2> <TEXT2>
...
<KEYN> <TEXTN>
```

There should be a single space character between a key and a value. The key's maximum length is 7 characters. Try using unique keys that are unlikely to clash with other entries. The text length is unlimited, however each game may impose its own limitations.

CLEO loads FXT files on startup and merges their content in a single dictionary. It also monitors the files and reloads them if any change is made.

You can also find an editor for FXT files on the cleo.li website: https://cleo.li/download.html

To display the custom content in game, use the `Text` class. The key defined in the FXT file is usually the first argument to Text commands, e.g.

```
Text.PrintHelp('KEY1') // will display <TEXT1>
```

You can find the commands available in each game in the Sanny Builder Library, e.g. for San Andreas: DE https://library.sannybuilder.com/#/sa_unreal/classes/Text


### FxtStore

Demo: https://youtu.be/FLyYyrGz1Xg

CLEO Redux provides an interface for manipulating custom text directly in JavaScript code. There is a static variable, named `FxtStore` with the following interface:

```ts
declare interface FxtStore {
  /**
   * Inserts new text content in the script's fxt storage overwriting the previous content and shadowing static fxt with the same key
   * @param key GXT key that can be used in text commands (7 characters max)
   * @param value text content
   */
  insert(key: string, value: string): void;
  /**
   * Removes the text content associated with the key in the local fxt storage
   * @param key GXT key
   */
  delete(key: string): void;
}
```

Using `FxtStore` you can create unique keys and values in the script and put it in local FXT storage. Each script owns a private storage and keys from one script will not conflict with other scripts. Also keys defined in the FxtStore will shadow the same keys defined in static FXT files. Consider the example:

custom.fxt:
```
MY_KEY Text from FXT file
```

custom.js:

```js
Text.PrintHelp('MY_KEY') // this displays "Text from FXT file"
FxtStore.insert('MY_KEY', 'Text from script');
Text.PrintHelp('MY_KEY') // this displays "Text from script"
FxtStore.delete('MY_KEY')
Text.PrintHelp('MY_KEY') // this displays "Text from FXT file" again
```

A private FXT storage is not supported in San Andreas: The Definitive Edition. Each script there modifies the global FXT storage. This behavior may change in the future.

Custom text can be constructed dynamically, e.g.:

```js
while(true) {
    wait(0);
    FxtStore.insert('TIME', 'Timestamp: ' + Date.now());
    Text.PrintHelp('TIME') // this displays "Timestamp: " and the updated timestamp value
}
```

