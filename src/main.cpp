#include <node_api.h>
#include <iostream>
#include <string>

#define PREPARE_ARGS(ret) napi_get_cb_info(env, info, &argc, args, nullptr, nullptr)

#define NAPI_THROW(err, ret)                                              \
    do                                                                    \
    {                                                                     \
        bool is_pending;                                                  \
        napi_is_exception_pending(env, &is_pending);                      \
        if (!is_pending)                                                  \
        {                                                                 \
            std::cout << "A C++ Exception has been thrown: " err << "\n"; \
            napi_throw_error(env, NULL, err);                             \
        }                                                                 \
        return ret;                                                       \
    } while (0)

int64_t ptr_to_int(void *ptr)
{
    return reinterpret_cast<int64_t>(ptr);
}

napi_value NM_malloc(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1];
    PREPARE_ARGS(nullptr);
    if (argc != 1)
        NAPI_THROW("Expected exactly 1 argument for the function call memory.malloc()", nullptr);
    int32_t size;
    napi_get_value_int32(env, args[0], &size);
    void *res = malloc(size);
    if (res == NULL)
        return nullptr;
    napi_value ret;
    napi_create_int64(env, ptr_to_int(res), &ret);
    return ret;
}

napi_value NM_address_view(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2];
    PREPARE_ARGS(nullptr);
    if (argc != 2)
        NAPI_THROW("Expected exactly 2 arguments for the function call memory.address_view()", nullptr);
    int64_t address;
    int32_t readSize;
    napi_get_value_int64(env, args[0], &address);
    napi_get_value_int32(env, args[1], &readSize);
    char *point = reinterpret_cast<char *>(address);
    napi_value arr;
    napi_create_array_with_length(env, readSize, &arr);
    for (int i = 0; i < readSize; i++)
    {
        napi_value val;
        napi_create_int32(env, point[i], &val);
        napi_set_named_property(env, arr, std::to_string(i).c_str(), val);
    }
    return arr;
}

napi_value NM_address_set(napi_env env, napi_callback_info info)
{
    size_t argc = 3;
    napi_value args[3];
    PREPARE_ARGS(nullptr);
    if (argc != 3)
        NAPI_THROW("Expected exactly 3 arguments for the function call memory.address_view()", nullptr);
    int64_t address;
    int32_t index;
    int32_t value;
    napi_get_value_int64(env, args[0], &address);
    napi_get_value_int32(env, args[1], &index);
    napi_get_value_int32(env, args[2], &value);
    char *point = reinterpret_cast<char *>(address);
    point[index] = value;
    return nullptr;
}

napi_value NM_address_get(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2];
    PREPARE_ARGS(nullptr);
    if (argc != 2)
        NAPI_THROW("Expected exactly 2 arguments for the function call memory.address_get()", nullptr);
    int64_t address;
    int32_t index;
    napi_get_value_int64(env, args[0], &address);
    napi_get_value_int32(env, args[1], &index);
    char *point = reinterpret_cast<char *>(address);
    napi_value res;
    napi_create_int32(env, point[index], &res);
    return res;
}

napi_value NM_free(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1];
    PREPARE_ARGS(nullptr);
    if (argc != 1)
        NAPI_THROW("Expected exactly 1 argument for the function call memory.free()", nullptr);
    int64_t address;
    napi_get_value_int64(env, args[0], &address);
    free(reinterpret_cast<void *>(address));
    return nullptr;
}

napi_value NM_calloc(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2];
    PREPARE_ARGS(nullptr);
    if (argc != 2)
        NAPI_THROW("Expected exactly 2 arguments for the function call memory.calloc()", nullptr);
    int32_t count;
    int32_t size;
    napi_get_value_int32(env, args[0], &count);
    napi_get_value_int32(env, args[1], &size);
    void *res = calloc(count, size);
    if (res == NULL)
        return nullptr;
    napi_value ret;
    napi_create_int64(env, ptr_to_int(res), &ret);
    return ret;
}

napi_value NM_realloc(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2];
    PREPARE_ARGS(nullptr);
    if (argc != 2)
        NAPI_THROW("Expected exactly 2 arguments for the function call memory.realloc()", nullptr);
    int64_t address;
    int32_t size;
    napi_get_value_int64(env, args[0], &address);
    napi_get_value_int32(env, args[1], &size);
    void *res = realloc(reinterpret_cast<void *>(address), size);
    if (res == NULL)
        return nullptr;
    napi_value ret;
    napi_create_int64(env, ptr_to_int(res), &ret);
    return ret;
}

#define SET_FUNCTION(name, key)                                    \
    napi_value key;                                                \
    napi_create_function(env, nullptr, NULL, name, nullptr, &key); \
    napi_set_named_property(env, object, #key, key);

napi_value init(napi_env env, napi_value exports)
{
    napi_value object;
    napi_create_object(env, &object);
    SET_FUNCTION(NM_address_view, address_view);
    SET_FUNCTION(NM_address_get, address_get);
    SET_FUNCTION(NM_address_set, address_set);
    SET_FUNCTION(NM_malloc, malloc);
    SET_FUNCTION(NM_realloc, realloc);
    SET_FUNCTION(NM_calloc, calloc);
    SET_FUNCTION(NM_free, free);
    return object;
}

NAPI_MODULE(_, init);