# memory-man

This npm package streamlines memory management to node.js from C++.

> Do not use this for production.
>
> Node's V8 would probably be faster in bigger scales.

# Installing

Type this command line to install the Memory Man:

```shell
npm install memory-man
```

Now you can import it from your JavaScript code:

```js
import MemoryMan from "memory-man";
// Or
const MemoryMan = require("memory-man");
```

Now you can access the functions of the Memory Man!

```js
const {malloc, calloc, realloc, free, address_set, address_get, address_view} = MemoryMan;
```

# malloc(size)

This method is used to dynamically allocate a block of memory on the
heap (a region of a computer's memory) during program execution.

```js
const address = malloc(10); // Will allocate 10 bytes in memory!
console.log(`The address of the allocated memory is: ${address}`);
```

# free(address)

This method is used to release the memory back to the heap so that it
can be reused by the system or other parts of your program.

```js
free(address); // Now the address is erased!
```

# calloc(count, size)

This method is does nearly the same thing as malloc, but unlike malloc
this method will initialize the allocated memory to zero.

```js
const address = calloc(1, 10); // count, size
console.log(`The address of the allocated memory is: ${address}`);
```

# realloc(address, size)

This method is used to change the size of a previously allocated block of memory.

```js
realloc(address, 100); // The allocated memory has been resized to 100!
```

# address_set(address, index, value)

This method is used to set an element of an address in memory.

```js
address_set(address, 0, 10);
```

# address_get(address, index)

This method is used to get an element of an address in memory.

```js
console.log(address_get(address, 0)); // 10
```