# First steps

Since [available commands](./api.md) vary from game to game for the purpose of this tutorial we will be using CLEO's built-in commands such as [`log`](./log.md) command that is available everywhere.

Once you have CLEO Redux [installed](./installation.md) run the game once to make sure CLEO is loading. You can verify it by having `cleo_redux.log` created in the game root folder. If there are no errors in the log you can start adding new scripts.

Go to the [CLEO directory](./cleo-directory.md) and create a new file named `intro.js`. This will be a text file and you can edit it in any text editor. We recommend using VS Code as the most advanced choice available today, but other editors, even Notepad, would work too. Open `intro.js` and add two lines:

```js
// intro script, revision 1
log("Hello world");
```

Lines starting with `//` are comments and ignored by the game. The only meaningful line is the second that instructs JavaScript runtime to print a message in the log file.

Now save the file and run the game. Start a new game or load a save file, play a few seconds and then go to `cleo_redux.log` (do not exit the game yet). You should now see a new line like:

```log
10:12:19 [INFO] ["intro"] "Hello world"
```

If you can't find this line, try to read through other messages, they might point you out the issue.

If you see the message, open `intro.js` again and change "Hello world" to another text. Save the file and go back to game. Play, then switch back to `cleo_redux.log`. Notice how the log now contains the new message. The script was reloaded on the fly as you saved it and the game now runs an updated version of it. This is called [hot reloading](./other-features.md#hot-reload).

## Concurrency

There is so little fun in a single script, so let's explore another important aspect. CLEO Redux can load and run many scripts concurrently. But they do not run in parallel, or at the same time. Instead there is a queue of scripts to execute them sequentually on each game iteration. This happens to minimize number of issues caused by accessing shared resources from multiple parallel scripts. The game's main loop is also locked while scripts get processed.

When the script is ready to return control to the main script or another script in the queue, it must call the `wait(n)` command where `n` is a number greater than or equal to zero. This command pauses the current script for at least `n` milliseconds:

```js
wait(250); // pause current script and wake up after 250 milliseconds
```

Low values (such as `0` or generally anything lower than `16`) essentially make the script run on each tick of the game's main loop.

Let's create another JS file in the CLEO directory and call it `second.js`. Add the following lines:

```js
wait(1000);
log("This is the second script");
```

Save the file and re-run the game. You should now see two lines in the `cleo_redux.log`:

```log
10:12:19 [INFO] ["intro"] "Hello world"
10:12:20 [INFO] ["second"] "This is the second script"
```

Notice that there is a difference in one second between two messages. Try different combinations of `log` and `wait` commands in both scripts and see the results. Do they match your expectations?

## Variables

Variables keep your script's state and intermediate results. Each variable has a unique name and a type and can be either mutable or immutable. Mutable variables are created with `var` or `let` keywords. Immutable variables (or constants) are created with a `const` keyword.

```js
let x = 5;
let name = "CJ";
const z = -100;
```

Constants can not be reassigned to another value. The following code will throw an error:

```js
const z = -100;
z = -200;
```

On the other side `var` or `let` variables can get new values. Those values can be of a different type, e.g. you can reuse same variable for different types of data:

```js
let temp;

temp = 1; // number
temp = "str"; // string
temp = {}; // object
temp = []; // array
```

Use operator `typeof` to find the type of the variable at any given moment:

```js
let temp;

temp = 1;
log(typeof temp); // prints "number" in cleo_redux.log
temp = "str";
log(typeof temp); // prints "string" in cleo_redux.log
temp = {};
log(typeof temp); // prints "object" in cleo_redux.log
temp = [];
log(typeof temp); // prints "object" in cleo_redux.log*
```

> *`typeof` returns "object" for an array (`[]`). This is a very well known quirk in the language. You can [read more about it here](https://web.mit.edu/jwalden/www/isArray.html) and find other means of differenting between arrays and plain objects.

## Control Flow

### Conditions

So far we have been running commands in the script in a sequence from top to bottom. The runtime executed the first line, then proceed to the second line if there was one, then to the third line, etc. But what if we want to execute a command only when some condition is met, lets say a button is pressed? We can use conditions.

In JavaScript an `if` statement allows to conditionally execute a branch of code if the condition is met. For example, when you write:

```js
if (true) {
  log("this is always printed");
}
```

You always get the log line printed since the condition in `if` always evaluates to true. Likewise

```js
if (false) {
  log("this will never be printed");
}
```

when the condition evaluates to `false` inside the if block does not run so you won't see the log messages.

You can have any expression in the `if` statement. JavaScript runtime will try its best to convert it to a boolean (simply saying, convert to `true` or `false`). Here are some examples of expressions that get evaluated to `true` (they are called `truthy`):

```js
if (1) {...}
if ("string") {...}
if (5 > 4) {...}
if ([]) {...}
if ({}) {...}
```

Note that 0 and an empty string always get evaluated to false (they are "falsy" values):

```js
if (0) {...}
if ("") {...}
```

Of course you can have complex experession like functions or methods calls inside the if condition:

```js
if ("string".length > 0) {...}
if ([1,2,3].includes(3)) {...}
if ( ({ status: 'open'}).status === 'open' ) {...}
```

CLEO API has many conditional commands for different types of checks. For example, the `Input` plugin provides commands to check the user input (i.g. a check that the button is pressed). Go to `intro.js` and change its content to:

```js
// intro script, revision 2
wait(2000);
if (native("IS_KEY_PRESSED", 115)) {
  log("F4 button is pressed");
}
```

Run the game. In `cleo_redux.log` you should not see the line "F4 button is pressed". Now try running it while holding the `F4` button. A new log entry should appear.

You can combine multiple conditions in the same if statement using `&&` (AND) or `||` (or) operators :

```js
if (native("IS_KEY_PRESSED", 115) || native("IS_KEY_PRESSED", 116)) {
  log("Either F4 or F5 button is pressed");
}
```

```js
if (native("IS_KEY_PRESSED", 115) && native("IS_KEY_PRESSED", 116)) {
  log("Both F4 and F5 button are pressed");
}
```

You can execute commands in `else` block if the condition is not met:

```js
if (native("IS_KEY_PRESSED", 115)) {
  log("F4 button is pressed");
} else {
  log("F4 button is not pressed");
}
```

### Loops

TBD

## Functions

TBD
