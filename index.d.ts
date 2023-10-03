type _Address = number;
type char = number;
type int32 = number;
type size_t = number;

declare const __: {
    address_view(address: _Address, readSize: size_t): void;
    address_get(address: _Address, index: int32): char;
    address_set(address: _Address, index: int32, value: char): char[];
    malloc(size: size_t): _Address | undefined; // undefined means it failed
    calloc(count: int32, size: size_t): _Address | undefined;
    realloc(address: _Address, size: size_t): _Address | undefined;
    free(address: _Address): void;
};
export = __;