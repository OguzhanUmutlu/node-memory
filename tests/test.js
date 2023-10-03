const { malloc, free, address_set, address_get } = require("../index");

const address = malloc(1);
console.log(address);

address_set(address, 0, 100);

const data = address_get(address, 0);
console.log(data);

free(address);