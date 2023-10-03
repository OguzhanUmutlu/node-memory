const { malloc, free, address_set, address_get, address_view } = require("../index");

const address = malloc(1);
console.log(address);

address_set(address, 0, 100);

const data = address_get(address, 0);
console.log(data);

const all = address_view(address, 1);
console.log(all);

free(address);