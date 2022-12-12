# TypeScript

Since v1.0.5 CLEO Redux adds first-class support for TypeScript. TypeScript is a superset of JavaScript with static types and other features. It is compiled to JavaScript and can be efficiently used in large-scale projects. TypeScript has excellent IDE support so you get autocompletion, type checking and other features in your editor for free.

TypeScript website: [https://www.typescriptlang.org/](https://www.typescriptlang.org/).

TS scripts have `.ts` extension and can be used anywhere [where JS scripts are supported](./script-lifecycle.md). They can be imported directly in both JS and TS scripts using [`import`](./imports.md) statements.

## TS Config

CLEO Redux creates `tsconfig.json` file in the [CLEO directory](./cleo-directory.md) when you run it for the first time. It contains necessary information for VS Code and other IDEs on where to look for typing files, so you don't have to include `/// <reference path="..." />` lines in your scripts. You can edit it to change the default settings.
