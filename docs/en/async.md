# Asynchronous Programming

- [Async API](#async-api)
- [Async Functions](#async-functions)
- [Concurrent Async Functions](#concurrent-async-functions)
- [Dynamic Imports](#dynamic-imports)
- [setTimeout and setInterval](#settimeout-and-setinterval)

CLEO Redux supports asynchronous code via [Promises](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Promise) and `async/await` syntax. This enables lots of advanced code patterns.

Note that asynchoronous programming is a fairly complex topic and if you want to learn more about visit the following resources:

- [MDN](https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Asynchronous/Introducing)
- [JavaScript.info](https://javascript.info/async)

See an example of an async script for GTA III [here](https://github.com/x87/luigi3_async).

## Async API

CLEO Redux 1.0.4 has one native async command: `asyncWait`. This command pauses the script for a specified amount of time. It returns a `Promise` that resolves after the specified amount of time. `asyncWait` can only be used inside an `async` function.

```js
async function delay(ms) {
  log("Waiting for " + ms + "ms");
  await asyncWait(ms);
  log("Done waiting");
}

delay(1000);
```

Difference between `asyncWait` and `wait` is that the former is not a blocking command. If you don't put the `await` keyword in front of it, the script execution continues.

```js
async function delay(ms) {
  log("Waiting for " + ms + "ms");
  asyncWait(ms); // no await here, the script continues
  log("Executed immediately");
}

delay(1000);
```

## Async Functions

CLEO Redux does not support a top-level await. This means that you cannot use the `await` keyword in the main body of the script.

```js
// script begins
await asyncWait(1000); // won't work
showTextBox("Hello");
```

To bypass this limitation wrap your code in an anonymous async function.

```js
(async function () {
  // script begins
  await asyncWait(1000); // works, because it's inside an async function
  showTextBox("Hello");
})();
```

Note that by design any exception thrown inside an async function is not caught automatically. This means that if you want to catch an exception you need to wrap your code in a try/catch block or add `.catch` handler to the promise.

```js
(async function () {
  // script code goes here
  non_existing_function();
})().catch((e) => {
  log(e);
});
```

The log will contain the following message:

```
"ReferenceError: 'non_existing_function' is not defined"
```

## Concurrent Async Functions

One of the advantages of async functions is that they could run concurrently. This means that you can run multiple async functions at the same time. Some languages call these coroutines.

```js
import { KeyCode } from "./.config/enums";
let gVar = 0;

(async () => {
  await asyncWait(0);

  // running task1, task2, and task3 concurrently
  task1();
  task2();
  task3();
})();

// shakes the camera
async function task1() {
  while (true) {
    await asyncWait(0);
    Camera.Shake(30);
  }
}

// awards the player with $1000 every second and increments the global variable gVar
async function task2() {
  let p = new Player(0);
  while (true) {
    await asyncWait(1000);

    p.addScore(1);
    gVar++;
  }
}

// waits for the button J to be pressed and displays the value of gVar
async function task3() {
  while (true) {
    await asyncWait(0);
    if (Pad.IsKeyDown(KeyCode.J)) {
      showTextBox("gVar is " + gVar);
    }
  }
}
```

This is very similar to writing traditional `while(true){}` loops with a `wait` command in it, with the difference that the functions must have `async` keyword and use `asyncWait` instead of `wait`
Each of the three tasks are executed independently from each other. Note that runtime guarantees that all async functions are executed in the same thread. They share global variables and can change them. Look at how `gVar` is being incremented in `task2` and read in `task3`.

## Dynamic Imports

CLEO Redux supports [dynamic imports](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/import). It allows to load script files on-demand when they are needed. This is useful for large scripts that are not needed all the time.

```js
(async () => {
  if (somethingIsTrue) {
    // import module for side effects
    await import("./my-module.mjs");
  }
})();
```

Imported modules can export functions and variables. They can be used in the same way as in regular scripts.

my-module.mjs:

```js
export const myVar = 42;
```

main.js:

```js
(async () => {
  const { myVar } = await import("./my-module.mjs");
  log(myVar); // prints 42
})();
```

When importing JSON files, its content is available via `default` property.

```js
(async function () {
  const { default: data } = await import("./my.json");

  log(data); // prints the content of my.json
})();
```

## setTimeout and setInterval

It is easy to implement `setTimeout` and `setInterval` using `asyncWait` and `async` functions. You can [find an implementation example here](https://github.com/cleolibrary/CLEO-Redux/blob/master/examples/setTimeout%2C%20setInterval.js).

Since 1.0.6 these functions are [part of the standard library](./api.md) and are available in all scripts.